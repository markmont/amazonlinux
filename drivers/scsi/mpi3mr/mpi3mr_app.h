/* SPDX-License-Identifier: GPL-2.0-or-later */
/*
 * Driver for Broadcom MPI3 Storage Controllers
 *
 * Copyright (C) 2017-2022 Broadcom Inc.
 *  (mailto: mpi3mr-linuxdrv.pdl@broadcom.com)
 *
 */

#ifndef MPI3MR_APP_H_INCLUDED
#define MPI3MR_APP_H_INCLUDED

#include <linux/bsg-lib.h>

/* Definitions for BSG commands */
#define MPI3MR_DEV_NAME				"mpi3mrctl"

#define MPI3MR_IOCTL_VERSION			0x06

#define MPI3MR_APP_DEFAULT_TIMEOUT		(60) /*seconds*/

#define MPI3MR_BSG_ADPTYPE_UNKNOWN		0
#define MPI3MR_BSG_ADPTYPE_AVGFAMILY		1

#define MPI3MR_BSG_ADPSTATE_UNKNOWN		0
#define MPI3MR_BSG_ADPSTATE_OPERATIONAL		1
#define MPI3MR_BSG_ADPSTATE_FAULT		2
#define MPI3MR_BSG_ADPSTATE_IN_RESET		3
#define MPI3MR_BSG_ADPSTATE_UNRECOVERABLE	4

#define MPI3MR_BSG_ADPRESET_UNKNOWN		0
#define MPI3MR_BSG_ADPRESET_SOFT		1
#define MPI3MR_BSG_ADPRESET_DIAG_FAULT		2

#define MPI3MR_BSG_LOGDATA_MAX_ENTRIES		400
#define MPI3MR_BSG_LOGDATA_ENTRY_HEADER_SZ	4

#define MPI3MR_DRVBSG_OPCODE_UNKNOWN		0
#define MPI3MR_DRVBSG_OPCODE_ADPINFO		1
#define MPI3MR_DRVBSG_OPCODE_ADPRESET		2
#define MPI3MR_DRVBSG_OPCODE_ALLTGTDEVINFO	4
#define MPI3MR_DRVBSG_OPCODE_GETCHGCNT		5
#define MPI3MR_DRVBSG_OPCODE_LOGDATAENABLE	6
#define MPI3MR_DRVBSG_OPCODE_PELENABLE		7
#define MPI3MR_DRVBSG_OPCODE_GETLOGDATA		8
#define MPI3MR_DRVBSG_OPCODE_QUERY_HDB		9
#define MPI3MR_DRVBSG_OPCODE_REPOST_HDB		10
#define MPI3MR_DRVBSG_OPCODE_UPLOAD_HDB		11
#define MPI3MR_DRVBSG_OPCODE_REFRESH_HDB_TRIGGERS	12


#define MPI3MR_BSG_BUFTYPE_UNKNOWN		0
#define MPI3MR_BSG_BUFTYPE_RAIDMGMT_CMD		1
#define MPI3MR_BSG_BUFTYPE_RAIDMGMT_RESP	2
#define MPI3MR_BSG_BUFTYPE_DATA_IN		3
#define MPI3MR_BSG_BUFTYPE_DATA_OUT		4
#define MPI3MR_BSG_BUFTYPE_MPI_REPLY		5
#define MPI3MR_BSG_BUFTYPE_ERR_RESPONSE		6
#define MPI3MR_BSG_BUFTYPE_MPI_REQUEST		0xFE

#define MPI3MR_BSG_MPI_REPLY_BUFTYPE_UNKNOWN	0
#define MPI3MR_BSG_MPI_REPLY_BUFTYPE_STATUS	1
#define MPI3MR_BSG_MPI_REPLY_BUFTYPE_ADDRESS	2

#define MPI3MR_HDB_BUFTYPE_UNKNOWN		0
#define MPI3MR_HDB_BUFTYPE_TRACE		1
#define MPI3MR_HDB_BUFTYPE_FIRMWARE		2
#define MPI3MR_HDB_BUFTYPE_RESERVED		3

#define MPI3MR_HDB_BUFSTATUS_UNKNOWN		0
#define MPI3MR_HDB_BUFSTATUS_NOT_ALLOCATED	1
#define MPI3MR_HDB_BUFSTATUS_POSTED_UNPAUSED	2
#define MPI3MR_HDB_BUFSTATUS_POSTED_PAUSED	3
#define MPI3MR_HDB_BUFSTATUS_RELEASED		4

#define MPI3MR_HDB_TRIGGER_TYPE_UNKNOWN		0
#define MPI3MR_HDB_TRIGGER_TYPE_FAULT		1
#define MPI3MR_HDB_TRIGGER_TYPE_ELEMENT		2
#define MPI3MR_HDB_TRIGGER_TYPE_MASTER		3
#define MPI3MR_HDB_TRIGGER_TYPE_SOFT_RESET	4
#define MPI3MR_HDB_TRIGGER_TYPE_FW_RELEASED	5

#define MPI3MR_HDB_REFRESH_TYPE_RESERVED	0
#define MPI3MR_HDB_REFRESH_TYPE_CURRENT		1
#define MPI3MR_HDB_REFRESH_TYPE_DEFAULT		2
#define MPI3MR_HDB_HDB_REFRESH_TYPE_PERSISTENT	3

/* Supported BSG commands */
enum command {
	MPI3MRDRVCMD = 1,
	MPI3MRMPTCMD = 2,
};

/* Data direction definitions */
enum data_direction {
	DATA_IN = 1,
	DATA_OUT = 2,
};

/**
 * struct mpi3mr_bsg_in_adpinfo - Adapter information request
 * data returned by the driver.
 *
 * @adp_type: Adapter type
 * @rsvd1: Reserved
 * @pci_dev_id: PCI device ID of the adapter
 * @pci_dev_hw_rev: PCI revision of the adapter
 * @pci_subsys_dev_id: PCI subsystem device ID of the adapter
 * @pci_subsys_ven_id: PCI subsystem vendor ID of the adapter
 * @pci_dev: PCI device
 * @pci_func: PCI function
 * @pci_bus: PCI bus
 * @rsvd2: Reserved
 * @pci_seg_id: PCI segment ID
 * @app_intfc_ver: version of the application interface definition
 * @rsvd3: Reserved
 * @rsvd4: Reserved
 * @rsvd5: Reserved
 * @driver_info: Driver Information (Version/Name)
 */
struct mpi3mr_bsg_in_adpinfo {
	uint32_t adp_type;
	uint32_t rsvd1;
	uint32_t pci_dev_id;
	uint32_t pci_dev_hw_rev;
	uint32_t pci_subsys_dev_id;
	uint32_t pci_subsys_ven_id;
	uint32_t pci_dev:5;
	uint32_t pci_func:3;
	uint32_t pci_bus:8;
	uint16_t rsvd2;
	uint32_t pci_seg_id;
	uint32_t app_intfc_ver;
	uint8_t adp_state;
	uint8_t rsvd3;
	uint16_t rsvd4;
	uint32_t rsvd5[2];
	struct mpi3_driver_info_layout driver_info;
};

/**
 * struct mpi3mr_bsg_adp_reset - Adapter reset request
 * payload data to the driver.
 *
 * @reset_type: Reset type
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 */
struct mpi3mr_bsg_adp_reset {
	uint8_t reset_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
};

/**
 * struct mpi3mr_change_count - Topology change count
 * returned by the driver.
 *
 * @change_count: Topology change count
 * @rsvd: Reserved
 */
struct mpi3mr_change_count {
	uint16_t change_count;
	uint16_t rsvd;
};

/**
 * struct mpi3mr_device_map_info - Target device mapping
 * information
 *
 * @handle: Firmware device handle
 * @perst_id: Persistent ID assigned by the firmware
 * @target_id: Target ID assigned by the driver
 * @bus_id: Bus ID assigned by the driver
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 */
struct mpi3mr_device_map_info {
	uint16_t handle;
	uint16_t perst_id;
	uint32_t target_id;
	uint8_t bus_id;
	uint8_t rsvd1;
	uint16_t rsvd2;
};

/**
 * struct mpi3mr_all_tgt_info - Target device mapping
 * information returned by the driver
 *
 * @num_devices: The number of devices in driver's inventory
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @dmi: Variable length array of mapping information of targets
 */
struct mpi3mr_all_tgt_info {
	uint16_t num_devices; //The number of devices in driver's inventory
	uint16_t rsvd1;
	uint32_t rsvd2;
	struct mpi3mr_device_map_info dmi[1]; //Variable length Array
};

/**
 * struct mpi3mr_logdata_enable - Number of log data
 * entries saved by the driver returned as payload data for
 * enable logdata BSG request by the driver.
 *
 * @max_entries: Number of log data entries cached by the driver
 * @rsvd: Reserved
 */
struct mpi3mr_logdata_enable {
	uint16_t max_entries;
	uint16_t rsvd;
};

/**
 * struct mpi3mr_bsg_out_pel_enable - PEL enable request payload
 * data to the driver.
 *
 * @pel_locale: PEL locale to the firmware
 * @pel_class: PEL class to the firmware
 * @rsvd: Reserved
 */
struct mpi3mr_bsg_out_pel_enable {
	uint16_t pel_locale;
	uint8_t pel_class;
	uint8_t rsvd;
};

/**
 * struct mpi3mr_logdata_entry - Log data entry cached by the
 * driver.
 *
 * @valid_entry: Is the entry valid
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @data: Log entry data of controller specific size
 */
struct mpi3mr_logdata_entry {
	uint8_t valid_entry;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint8_t data[1]; //Variable length Array
};

/**
 * struct mpi3mr_bsg_in_log_data - Log data entries saved by
 * the driver returned as payload data for Get logdata request
 * by the driver.
 *
 * @entry: Log data entry
 */
struct mpi3mr_bsg_in_log_data {
	struct mpi3mr_logdata_entry entry[1]; //Variable length Array
};

/**
 * struct mpi3mr_hdb_entry - host diag buffer entry.
 *
 * @buf_type: Buffer type
 * @status: Buffer status
 * @trigger_type: Trigger type
 * @rsvd1: Reserved
 * @size: Buffer size
 * @rsvd2: Reserved
 * @trigger_data: Trigger specific data
 * @rsvd3: Reserved
 * @rsvd4: Reserved
 */
struct mpi3mr_hdb_entry {
	uint8_t buf_type;
	uint8_t status;
	uint8_t trigger_type;
	uint8_t rsvd1;
	uint16_t size;
	uint16_t rsvd2;
	uint64_t trigger_data;
	uint32_t rsvd3;
	uint32_t rsvd4;
};


/**
 * struct mpi3mr_bsg_in_hdb_status - This structure contains
 * return data for the BSG request to retrieve the number of host
 * diagnostic buffers supported by the driver and their current
 * status and additional status specific data if any in forms of
 * multiple hdb entries.
 *
 * @num_hdb_types: Number of host diag buffer types supported
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @rsvd3: Reserved
 * @entry: Diag buffer status entry
 */
struct mpi3mr_bsg_in_hdb_status {
	uint8_t num_hdb_types;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint32_t rsvd3;
	struct mpi3mr_hdb_entry entry[1]; //Variable length Array
};

/**
 * struct mpi3mr_bsg_out_repost_hdb - Repost host diagnostic
 * buffer request payload data to the driver.
 *
 * @buf_type: Buffer type
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 */
struct mpi3mr_bsg_out_repost_hdb {
	uint8_t buf_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
};

/**
 * struct mpi3mr_bsg_out_upload_hdb - Upload host diagnostic
 * buffer request payload data to the driver.
 *
 * @buf_type: Buffer type
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @start_offset: Start offset of the buffer from where to copy
 * @length: Length of the buffer to copy
 */
struct mpi3mr_bsg_out_upload_hdb {
	uint8_t buf_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint32_t start_offset;
	uint32_t length;
};

/**
 * struct mpi3mr_bsg_out_refresh_hdb_triggers - Refresh host
 * diagnostic buffer triggers request payload data to the driver.
 *
 * @page_type: Page type
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 */
struct mpi3mr_bsg_out_refresh_hdb_triggers {
	uint8_t page_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
};

/**
 * struct mpi3mr_bsg_drv_cmd -  Generic bsg data
 * structure for all driver specific requests.
 *
 * @mrioc_id: Controller ID
 * @opcode: Driver specific opcode
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 */
struct mpi3mr_bsg_drv_cmd {
	uint8_t mrioc_id;
	uint8_t opcode;
	uint16_t rsvd1;
	uint32_t rsvd2[4];
};
/**
 * struct mpi3mr_bsg_in_reply_buf - MPI reply buffer returned
 * for MPI Passthrough request .
 *
 * @mpi_reply_type: Type of MPI reply
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @reply_buf: Variable Length buffer based on mpirep type
 */
struct mpi3mr_bsg_in_reply_buf {
	uint8_t mpi_reply_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint8_t reply_buf[1]; /*Variable Length buffer based on mpirep type*/
};
/**
 * struct mpi3mr_buf_entry - User buffer descriptor for MPI
 * Passthrough requests.
 *
 * @buf_type: Buffer type
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @buf_len: Buffer length
 */
struct mpi3mr_buf_entry {
	uint8_t buf_type;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint32_t buf_len;
};
/**
 * struct mpi3mr_bsg_buf_entry_list - list of user buffer
 * descriptor for MPI Passthrough requests.
 *
 * @num_of_entries: Number of buffer descriptors
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @rsvd3: Reserved
 * @buf_entry: Variable length array of buffer descriptors
 */
struct mpi3mr_buf_entry_list {
	uint8_t num_of_entries;
	uint8_t rsvd1;
	uint16_t rsvd2;
	uint32_t rsvd3;
	struct mpi3mr_buf_entry buf_entry[1];
};
/**
 * struct mpi3mr_bsg_mptcmd -  Generic bsg data
 * structure for all MPI Passthrough requests .
 *
 * @mrioc_id: Controller ID
 * @rsvd1: Reserved
 * @timeout: MPI request timeout
 * @buf_entry_list: Buffer descriptor list
 */
struct mpi3mr_bsg_mptcmd {
	uint8_t mrioc_id;
	uint8_t rsvd1;
	uint16_t timeout;
	uint32_t rsvd2;
	struct mpi3mr_buf_entry_list buf_entry_list;
};

/**
 * struct mpi3mr_bsg_packet -  Generic bsg data
 * structure for all supported requests .
 *
 * @cmd_type: represents drvrcmd or mptcmd
 * @rsvd1: Reserved
 * @rsvd2: Reserved
 * @drvrcmd: driver request structure
 * @mptcmd: mpt request structure
 */
struct mpi3mr_bsg_packet {
        uint8_t cmd_type;
        uint8_t rsvd1;
        uint16_t rsvd2;
        uint32_t rsvd3;
        union {
                struct mpi3mr_bsg_drv_cmd drvrcmd;
                struct mpi3mr_bsg_mptcmd mptcmd;
        } cmd;
};

#endif
