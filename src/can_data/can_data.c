/*
 * can_data.c
 *
 *  Created on: Mar 3, 2020
 *      Author: chrisblust
 */
#include "can_data.h"
#include "can.h"
#include "common_macros.h"
#include "config.h"
#include "fault_status.h"
#include "temp_data.h"
#include "temp_monitor.h"
#include "temp_monitor_dbc.h"

#define TMSTATUS_ID 1234
#define TMSEGMENT0_ID 1235
#define TMSEGMENT1_ID 1236
#define TMSEGMENT2_ID 1237
#define TMSEGMENT3_ID 1238
#define TMSEGMENT4_ID 1239
#define TMSEGMENT5_ID 1240

static can_obj_temp_monitor_dbc_h_t current_can_data;

void send_TMStatus(void)
{
	// build and send TMStatus

	double temp; unsigned int index, encoded_temp;
	temp_monitor_hottest(&temp, &index);

	// temperatures are reported as an integers with bit significance
	// of 0.1 deg C. Dividing by 0.1 then truncating to integer results in this.
	encoded_temp = temp / 0.1;
	current_can_data.can_0x4d2_TMStatus.TMStatus_HottestTemp = encoded_temp;
	current_can_data.can_0x4d2_TMStatus.TMStatus_HottestIndex = index;

	temp_monitor_coldest(&temp, &index);
	encoded_temp = temp / 0.1;
	current_can_data.can_0x4d2_TMStatus.TMStatus_ColdestTemp = encoded_temp;
	current_can_data.can_0x4d2_TMStatus.TMStatus_ColdestIndex = index;

	current_can_data.can_0x4d2_TMStatus.TMStatus_Irrational = fault_status_get_irrational();
	current_can_data.can_0x4d2_TMStatus.TMStatus_ConfigIrrationalEn = config_rationality_check_enabled();
	current_can_data.can_0x4d2_TMStatus.TMStatus_Overtemp = fault_status_get_overtemp();
	current_can_data.can_0x4d2_TMStatus.TMStatus_ConfigOvertempEn = config_temp_monitoring_enabled();

	CANMessage message;
	message.id = TMSTATUS_ID;
	message.length = 8;
	pack_message(&current_can_data, TMSTATUS_ID, (uint64_t*)message.data);

	sendCAN(&message);
}

void send_TMSegment(int i)
{
	i = SAT(i, 0, 5);

	int id;
	switch(i)
	{
		case 0:
			id = TMSEGMENT0_ID;
			current_can_data.can_0x4d3_TMSegment0.TMSegment0_T0Temp = temp_data_get(0);
			current_can_data.can_0x4d3_TMSegment0.TMSegment0_T1Temp = temp_data_get(1);
			current_can_data.can_0x4d3_TMSegment0.TMSegment0_T2Temp = temp_data_get(2);
			current_can_data.can_0x4d3_TMSegment0.TMSegment0_T3Temp = temp_data_get(3);
			break;

		case 1:
			id = TMSEGMENT1_ID;
			current_can_data.can_0x4d4_TMSegment1.TMSegment1_T4Temp = temp_data_get(4);
			current_can_data.can_0x4d4_TMSegment1.TMSegment1_T5Temp = temp_data_get(5);
			current_can_data.can_0x4d4_TMSegment1.TMSegment1_T6Temp = temp_data_get(6);
			current_can_data.can_0x4d4_TMSegment1.TMSegment1_T7Temp = temp_data_get(7);
			break;

		case 2:
			id = TMSEGMENT2_ID;
			current_can_data.can_0x4d5_TMSegment2.TMSegment2_T8Temp = temp_data_get(8);
			current_can_data.can_0x4d5_TMSegment2.TMSegment2_T9Temp = temp_data_get(9);
			current_can_data.can_0x4d5_TMSegment2.TMSegment2_T10Temp = temp_data_get(10);
			current_can_data.can_0x4d5_TMSegment2.TMSegment2_T11Temp = temp_data_get(11);
			break;

		case 3:
			id = TMSEGMENT3_ID;
			current_can_data.can_0x4d6_TMSegment3.TMSegment3_T12Temp = temp_data_get(12);
			current_can_data.can_0x4d6_TMSegment3.TMSegment3_T13Temp = temp_data_get(13);
			current_can_data.can_0x4d6_TMSegment3.TMSegment3_T14Temp = temp_data_get(14);
			current_can_data.can_0x4d6_TMSegment3.TMSegment3_T15Temp = temp_data_get(15);
			break;

		case 4:
			id = TMSEGMENT4_ID;
			current_can_data.can_0x4d7_TMSegment4.TMSegment4_T16Temp = temp_data_get(16);
			current_can_data.can_0x4d7_TMSegment4.TMSegment4_T17Temp = temp_data_get(17);
			current_can_data.can_0x4d7_TMSegment4.TMSegment4_T18Temp = temp_data_get(18);
			current_can_data.can_0x4d7_TMSegment4.TMSegment4_T19Temp = temp_data_get(19);
			break;

		case 5:
			id = TMSEGMENT5_ID;
			current_can_data.can_0x4d8_TMSegment5.TMSegment5_T20Temp = temp_data_get(20);
			current_can_data.can_0x4d8_TMSegment5.TMSegment5_T21Temp = temp_data_get(21);
			current_can_data.can_0x4d8_TMSegment5.TMSegment5_T22Temp = temp_data_get(22);
			current_can_data.can_0x4d8_TMSegment5.TMSegment5_T23Temp = temp_data_get(23);
			break;

		default:
			// do nothing shit broke
			return;
	}
}

void can_data_1Hz(void)
{
	send_TMStatus();
	for(int i = 0; i < 6; ++i)
	{
		send_TMSegment(i);
	}
}


