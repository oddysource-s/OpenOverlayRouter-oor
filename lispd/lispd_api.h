/*
 * lispd_api.h
 *
 * This file is part of LISPmob implementation. It defines the API to
 * interact with LISPmob internals.
 *
 * Copyright (C) The LISPmob project, 2015. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Please send any bug reports or fixes you make to the email address(es):
 *    LISPmob developers <devel@lispmob.org>
 *
 */

#include <stdint.h>

#define IPC_FILE "ipc:///tmp/lispmob-ipc"

#define MAX_API_PKT_LEN 4096 //MAX_IP_PKT_LEN

enum {
    LMAPI_NOFLAGS,
	LMAPI_DONTWAIT,
	LMAPI_ERROR = -1,
	LMAPI_NOTHINGTOREAD = -2
};

typedef enum lmapi_msg_device_e_ {

    LMAPI_DEV_XTR,
    LMAPI_DEV_MS,
    LMAPI_DEV_MR,
    LMAPI_DEV_RTR

} lmapi_msg_device_e; //Device of the operation

typedef enum lmapi_msg_opr_e_ {

    LMAPI_OPR_CREATE,
    LMAPI_OPR_READ,
    LMAPI_OPR_UPDATE,
    LMAPI_OPR_DELETE

} lmapi_msg_opr_e; //Type of operation

typedef enum lmapi_msg_target_e_ {

    LMAPI_TRGT_MRLIST,
    LMAPI_TRGT_MSLIST,
    LMAPI_TRGT_PETRLIST,
    LMAPI_TRGT_MAPCACHE,
    LMAPI_TRGT_MAPDB

} lmapi_msg_target_e; //Target of the operation

typedef enum lmapi_msg_type_e_ {

    LMAPI_TYPE_REQUEST,
    LMAPI_TYPE_RESULT

} lmapi_msg_type_e; //Type

typedef enum lmapi_msg_result_e_ {

    LMAPI_RES_OK,
    LMAPI_RES_ERR

} lmapi_msg_result_e; //Results

typedef struct lmapi_msg_hdr_t_ {

    uint8_t device;
    uint8_t target;
    uint8_t operation;
    uint8_t type;
    uint32_t datalen;

} lmapi_msg_hdr_t;

typedef struct lmapi_connection_t_ {
    void *context;
    void *socket;
} lmapi_connection_t;

/* Initialize API system (client) */
int lmapi_init_client(lmapi_connection_t *conn);

/* Shutdown API system */
void lmapi_end(lmapi_connection_t *conn);

uint8_t *lmapi_hdr_push(uint8_t *buf, lmapi_msg_hdr_t * hdr);

int lmapi_send(lmapi_connection_t *conn, void *msg, int len, int flags);

int lmapi_recv(lmapi_connection_t *conn, void *buffer, int flags);

void fill_lmapi_hdr(
        lmapi_msg_hdr_t *   hdr,
        lmapi_msg_device_e  dev,
        lmapi_msg_target_e  trgt,
        lmapi_msg_opr_e     opr,
        lmapi_msg_type_e    type,
        int dlen);

int lmapi_result_msg_new(
        uint8_t **          buf,
        lmapi_msg_device_e  dev,
        lmapi_msg_target_e  trgt,
        lmapi_msg_opr_e     opr,
        lmapi_msg_result_e  res);

int lmapi_apply_config(lmapi_connection_t *conn,
                       int dev,
					   int trgt,
					   int opr,
					   uint8_t *data,
					   int dlen);

