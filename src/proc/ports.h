/*
 * Phoenix-RTOS
 *
 * Operating system kernel
 *
 * Ports
 *
 * Copyright 2017, 2018 Phoenix Systems
 * Author: Jakub Sejdak, Pawel Pisarczyk, Aleksander Kaminski
 *
 * This file is part of Phoenix-RTOS.
 *
 * %LICENSE%
 */

#ifndef _PROC_PORT_H_
#define _PROC_PORT_H_

#include HAL
#include "msg.h"
#include "process.h"
#include "threads.h"
#include "file.h"

typedef struct _port_t {
	rbnode_t linkage;
	u32 id;

	int refs;
	kmsg_t *kmessages;
	spinlock_t spinlock;
	thread_t *threads;
} port_t;


extern port_t *port_get(u32 id);


extern void port_put(port_t *port);


extern int proc_portCreate(u32 id);


extern void _port_init(void);


#endif
