#include <gcom/core/computer.h>
#include <gcom/core/graph.h>
#include <gcom/links/ring_buffer_link.h>
#include <gcom/packets/object_packet.h>
#include <unistd.h>
#include <string>
#include <cstdio>
#include <sys/syscall.h>
#include <sys/types.h>

class MyGenerator : public gcom::computer
{
public:
	MyGenerator()
	{
		add_output();
	}
protected:
	virtual int on_loop() override
	{
		pid_t tid = syscall(SYS_gettid);
		//fprintf(stderr, "generator %d\n", tid);
		auto packetPtr = gcom::new_packet< gcom::object_packet<int> >();
		get_output(0)->send(packetPtr);

		return GCOM_OK;
	}
};

class MyComputer : public gcom::computer
{
public:
	MyComputer()
	{
		add_input();
	}
protected:
	virtual int on_loop() override
	{
		pid_t tid = syscall(SYS_gettid);
		//fprintf(stderr, "computer %d\n", tid);
		std::shared_ptr<gcom::packet> pkt;
		int result = get_input(0)->recv(pkt);
		if (result == GCOM_OK)
		{
			printf("computer: Got packet %zu\n", pkt->get_id());
		}
		return GCOM_OK;
	}
};

int main()
{
	auto graph = gcom::new_node<gcom::graph>("graph");

	auto generator = gcom::new_node<MyGenerator>("generator");
	auto computer = gcom::new_node<MyComputer>("computer");
	gcom::new_connection<gcom::ring_buffer_link>(generator->get_output(0), computer->get_input(0));

	graph->add_child(generator);
	graph->add_child(computer);

	graph->start();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	graph->stop();

	printf("Bye\n");
	return 0;
}