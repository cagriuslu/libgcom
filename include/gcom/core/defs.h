/// \mainpage libgcom
///
/// libgcom is a graph computer library.
///
/// \section Introduction
///
/// Some text.
///
/// \section Installation
///
/// Some text.
///
/// \subsection On Unix
///
/// Some text.
///

/// design principles
/// - slow start-time is better than slow run-time
/// - make common case fast
/// - speed is more important than memory
/// - graph configuration (ports, links, computers) should be static,
///   behaviour of components can be dynamic

#ifndef GCOM_DEFS_H
#define GCOM_DEFS_H

// Error codes
#define GCOM_OK (0)
#define GCOM_ERR (-1)
#define GCOM_TIMEDOUT (-2)
#define GCOM_ABORTED (-3)
#define GCOM_NOT_STARTED (-4)

// States (Error codes also)
#define GCOM_STARTED (1)
#define GCOM_STOPPED (2)

// Object types
#define GCOM_PACKET (0)
#define GCOM_BASE (1)
#define GCOM_LINK (2)
#define GCOM_PORT (3)
#define GCOM_INPUT (4)
#define GCOM_OUTPUT (5)
#define GCOM_NODE (6)


/*
#define GCOM_STATEFUL (0)
#define GCOM_PACKET (1)
#define GCOM_PORT (2)
#define GCOM_INPUT (3)
#define GCOM_OUTPUT (4)
#define GCOM_CONTAINER (5)
*/
#endif
