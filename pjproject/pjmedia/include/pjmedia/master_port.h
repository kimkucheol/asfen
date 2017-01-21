/* $Id: master_port.h 974 2007-02-19 01:13:53Z bennylp $ */
/* 
 * Copyright (C) 2003-2007 Benny Prijono <benny@prijono.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */
#ifndef __PJMEDIA_MASTER_PORT_H__
#define __PJMEDIA_MASTER_PORT_H__


/**
 * @file master_port.h
 * @brief Master port.
 */
#include <pjmedia/port.h>

/**
 * @defgroup PJMEDIA_MASTER_PORT Master Port
 * @ingroup PJMEDIA_PORT_CLOCK
 * @brief Provides media clock for media ports.
 * @{
 * A master port has two media ports connected to it, and by convention
 * thay are called downstream and upstream ports. The media stream flowing to
 * the downstream port is called encoding or send direction, and media stream 
 * flowing to the upstream port is called decoding or receive direction
 * (imagine the downstream as stream to remote endpoint, and upstream as
 * local media port; media flowing to remote endpoint (downstream) will need
 * to be encoded before it is transmitted to remote endpoint).
 *
 * A master port internally has an instance of @ref PJMEDIA_CLOCK, which
 * provides the essensial timing for the master port. The @ref PJMEDIA_CLOCK
 * runs asynchronously, and whenever a clock <b>tick</b> expires, a callback
 * will be called, and the master port performs the following tasks:
 *  - it calls <b><tt>get_frame()</tt></b> from the downstream port,
 *    when give the frame to the upstream port by calling <b><tt>put_frame
 *    </tt></b> to the upstream port, and
 *  - performs the same task, but on the reverse direction (i.e. get the stream
 *    from upstream port and give it to the downstream port).
 *
 * Because master port enables media stream to flow automatically, it is
 * said that the master port supplies @ref PJMEDIA_PORT_CLOCK to the 
 * media ports interconnection.
 *
 */

PJ_BEGIN_DECL


/**
 * Opaque declaration for master port.
 */
typedef struct pjmedia_master_port pjmedia_master_port;


/**
 * Create a master port.
 *
 * @param pool		Pool to allocate master port from.
 * @param u_port	Upstream port.
 * @param d_port	Downstream port.
 * @param options	Options flags, must be zero for now.
 * @param p_m		Pointer to receive the master port instance.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_create(pj_pool_t *pool,
						pjmedia_port *u_port,
						pjmedia_port *d_port,
						unsigned options,
						pjmedia_master_port **p_m);


/**
 * Start the media flow.
 *
 * @param m		The master port.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_start(pjmedia_master_port *m);


/**
 * Stop the media flow.
 *
 * @param m		The master port.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_stop(pjmedia_master_port *m);


/**
 * Change the upstream port. Note that application is responsible to destroy
 * current upstream port (the one that is going to be replaced with the
 * new port).
 *
 * @param m		The master port.
 * @param port		Port to be used for upstream port.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_set_uport(pjmedia_master_port *m,
						   pjmedia_port *port);


/**
 * Get the upstream port.
 *
 * @param m		The master port.
 *
 * @return		The upstream port.
 */
PJ_DECL(pjmedia_port*) pjmedia_master_port_get_uport(pjmedia_master_port*m);


/**
 * Change the downstream port. Note that application is responsible to destroy
 * current downstream port (the one that is going to be replaced with the
 * new port).
 *
 * @param m		The master port.
 * @param port		Port to be used for downstream port.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_set_dport(pjmedia_master_port *m,
						   pjmedia_port *port);


/**
 * Get the downstream port.
 *
 * @param m		The master port.
 *
 * @return		The downstream port.
 */
PJ_DECL(pjmedia_port*) pjmedia_master_port_get_dport(pjmedia_master_port*m);


/**
 * Destroy the master port, and optionally destroy the upstream and 
 * downstream ports.
 *
 * @param m		The master port.
 * @param destroy_ports	If non-zero, the function will destroy both
 *			upstream and downstream ports too.
 *
 * @return		PJ_SUCCESS on success.
 */
PJ_DECL(pj_status_t) pjmedia_master_port_destroy(pjmedia_master_port *m,
						 pj_bool_t destroy_ports);



PJ_END_DECL

/**
 * @}
 */


#endif	/* __PJMEDIA_MASTER_PORT_H__ */
