/// \mainpage libgcom
///
/// libgcom is a parallel computing library.
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

// do not rely on numerical values of these definition
// they may change any time

///// node states /////
#define GCOMST_STARTED (1)
#define GCOMST_STOPPED (2)

///// error codes /////
#define GCOM_OK (0)
#define GCOMERR_UNKNOWN (-1)
#define GCOMERR_TIMEOUT (-2)
#define GCOMERR_ABORTED (-3)
#define GCOMERR_STOPPED (-4)
#define GCOMERR_ARGNULL (-5)
#define GCOMERR_NOTCONN (-6)
#define GCOMERR_ARGNEG (-7)

///// class types /////
// gcom core classes occupy 0x00000000-0x0FFFFFFF
#define GCOMCL_META (0x00000000)
#define GCOMCL_PACKET (0x00000001)
#define GCOMCL_BASE (0x00000002)
#define GCOMCL_LINK (0x00000003)
#define GCOMCL_PORT (0x00000004)
#define GCOMCL_NODE (0x00000005)
#define GCOMCL_GRAPH (0x00000006)
#define GCOMCL_COMPUTER (0x00000007)
// packet types occupy 0x10000000-0x1FFFFFFF and have suffix PKT
#define GCOMCL_OBJECTPKT (0x10000000)
// link types occupy 0x20000000-0x2FFFFFFF and have suffix LNK
#define GCOMCL_RINGBUFFERLNK (0x20000000)
// port types occupy 0x30000000-0x3FFFFFFF
#define GCOMCL_INPUT (0x30000000)
#define GCOMCL_OUTPUT (0x30000001)
// graph types occupy 0x40000000-0x4FFFFFFF
// computer types occupy 0x50000000-0x5FFFFFFF

#endif
