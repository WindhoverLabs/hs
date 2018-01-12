/****************************************************************************
 *
 *   Copyright (c) 2016-2017 Windhover Labs, L.L.C. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Windhover Labs nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "px4br_serialization.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include "px4_msgs.h"
#include "actuator_armed.pb.h"
#include "actuator_controls.pb.h"
#include "actuator_direct.pb.h"
#include "actuator_outputs.pb.h"
#include "adc_report.pb.h"
#include "airspeed.pb.h"
#include "att_pos_mocap.pb.h"
#include "battery_status.pb.h"
#include "camera_trigger.pb.h"
#include "commander_state.pb.h"
#include "control_state.pb.h"
#include "cpuload.pb.h"
#include "debug_key_value.pb.h"
#include "differential_pressure.pb.h"
#include "distance_sensor.pb.h"
#include "ekf2_innovations.pb.h"
#include "ekf2_replay.pb.h"
#include "esc_report.pb.h"
#include "esc_status.pb.h"
#include "estimator_status.pb.h"
#include "fence.pb.h"
#include "fence_vertex.pb.h"
#include "filtered_bottom_flow.pb.h"
#include "follow_target.pb.h"
#include "fw_pos_ctrl_status.pb.h"
#include "fw_virtual_attitude_setpoint.pb.h"
#include "fw_virtual_rates_setpoint.pb.h"
#include "geofence_result.pb.h"
#include "gps_dump.pb.h"
#include "gps_inject_data.pb.h"
#include "hil_sensor.pb.h"
#include "home_position.pb.h"
#include "input_rc.pb.h"
#include "log_message.pb.h"
#include "manual_control_setpoint.pb.h"
#include "mavlink_log.pb.h"
#include "mc_att_ctrl_status.pb.h"
#include "mc_virtual_attitude_setpoint.pb.h"
#include "mc_virtual_rates_setpoint.pb.h"
#include "mission.pb.h"
#include "mission_result.pb.h"
#include "multirotor_motor_limits.pb.h"
#include "offboard_control_mode.pb.h"
#include "optical_flow.pb.h"
#include "output_pwm.pb.h"
#include "parameter_update.pb.h"
#include "position_setpoint.pb.h"
#include "position_setpoint_triplet.pb.h"
#include "pwm_input.pb.h"
#include "qshell_req.pb.h"
#include "rc_channels.pb.h"
#include "rc_parameter_map.pb.h"
#include "safety.pb.h"
#include "satellite_info.pb.h"
#include "sensor_accel.pb.h"
#include "sensor_baro.pb.h"
#include "sensor_combined.pb.h"
#include "sensor_gyro.pb.h"
#include "sensor_mag.pb.h"
#include "servorail_status.pb.h"
#include "subsystem_info.pb.h"
#include "system_power.pb.h"
#include "tecs_status.pb.h"
#include "telemetry_status.pb.h"
#include "test_motor.pb.h"
#include "time_offset.pb.h"
#include "transponder_report.pb.h"
#include "uavcan_parameter_request.pb.h"
#include "uavcan_parameter_value.pb.h"
#include "vehicle_attitude.pb.h"
#include "vehicle_attitude_setpoint.pb.h"
#include "vehicle_command_ack.pb.h"
#include "vehicle_command.pb.h"
#include "vehicle_control_mode.pb.h"
#include "vehicle_force_setpoint.pb.h"
#include "vehicle_global_position.pb.h"
#include "vehicle_global_velocity_setpoint.pb.h"
#include "vehicle_gps_position.pb.h"
#include "vehicle_land_detected.pb.h"
#include "vehicle_local_position.pb.h"
#include "vehicle_local_position_setpoint.pb.h"
#include "vehicle_rates_setpoint.pb.h"
#include "vehicle_status.pb.h"
#include "vtol_vehicle_status.pb.h"
#include "wind_estimate.pb.h"
#include "led_control.pb.h"
#include "sensor_correction.pb.h"

#define PX4BR_MICROSECONDS_PER_SECOND (1000000)


void PX4_DisplayBuffer(const char* inBuffer, int inSize)
{
	uint32_t i = 0;
	uint32_t ii = 0;

	for(i = 0; i < inSize; i=i+8)
	{
		uint32_t remaining = inSize - i;
		if(remaining > 8)
		{
			remaining = 8;
		}
		OS_printf("%-5d", i);

		for(ii = i; ii < (i+remaining); ++ii)
		{
			OS_printf("0x%02x ", (inBuffer[ii] & 0xff));
		}
		OS_printf("\n");
	}
}


uint32 PX4BR_GetContentSize(const char *msgName)
{
	return 0;
}

uint32 PX4BR_ActuatorArmed_Enc(const PX4_ActuatorArmedMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_actuator_armed_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.armed = inObject->Armed;
	pbMsg.prearmed = inObject->Prearmed;
	pbMsg.ready_to_arm = inObject->ReadyToArm;
	pbMsg.lockdown = inObject->Lockdown;
	pbMsg.force_failsafe = inObject->ForceFailsafe;
	pbMsg.in_esc_calibration_mode = inObject->InEscCalibrationMode;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_actuator_armed_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ActuatorArmed_Dec(const char *inBuffer, uint32 inSize, PX4_ActuatorArmedMsg_t *inOutObject)
{
	bool status = false;
	px4_actuator_armed_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_actuator_armed_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Armed = pbMsg.armed;
	inOutObject->Prearmed = pbMsg.prearmed;
	inOutObject->ReadyToArm = pbMsg.ready_to_arm;
	inOutObject->Lockdown = pbMsg.lockdown;
	inOutObject->ForceFailsafe = pbMsg.force_failsafe;
	inOutObject->InEscCalibrationMode = pbMsg.in_esc_calibration_mode;

	return sizeof(PX4_ActuatorArmedMsg_t);
}


uint32 PX4BR_ActuatorControls_Enc(const PX4_ActuatorControlsMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_controls_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.timestamp_sample = inObject->SampleTime;
    pbMsg.control_count = PX4_ACTUATOR_CONTROL_COUNT;
	for(i=0; i < PX4_ACTUATOR_CONTROL_COUNT; ++i)
	{
		pbMsg.control[i] = inObject->Control[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_actuator_controls_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ActuatorControls_Dec(const char *inBuffer, uint32 inSize, PX4_ActuatorControlsMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_controls_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_actuator_controls_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SampleTime = pbMsg.timestamp_sample;
	for(i=0; i < PX4_ACTUATOR_CONTROL_COUNT; ++i)
	{
		inOutObject->Control[i] = pbMsg.control[i];
		//OS_printf("%f ", inOutObject->Control[i]);
	}

	return sizeof(PX4_ActuatorControlsMsg_t);
}


uint32 PX4BR_ActuatorDirect_Enc(const PX4_ActuatorDirectMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_direct_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.nvalues = inObject->NValues;
	for(i=0; i < PX4_ACTUATOR_DIRECT_MAX; ++i)
	{
		pbMsg.values[i] = inObject->Values[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_actuator_direct_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ActuatorDirect_Dec(const char *inBuffer, uint32 inSize, PX4_ActuatorDirectMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_direct_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_actuator_direct_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->NValues = pbMsg.nvalues;
	for(i=0; i < PX4_ACTUATOR_DIRECT_MAX; ++i)
	{
		inOutObject->Values[i] = pbMsg.values[i];
	}

	return sizeof(PX4_ActuatorDirectMsg_t);
}


uint32 PX4BR_ActuatorOutputs_Enc(const PX4_ActuatorOutputsMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_outputs_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.noutputs = inObject->Count;
	pbMsg.output_count = PX4_ACTUATOR_OUTPUTS_MAX;
	for(i=0; i < PX4_ACTUATOR_OUTPUTS_MAX; ++i)
	{
		pbMsg.output[i] = inObject->Output[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_actuator_outputs_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ActuatorOutputs_Dec(const char *inBuffer, uint32 inSize, PX4_ActuatorOutputsMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_actuator_outputs_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_actuator_outputs_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Count = pbMsg.noutputs;
	for(i=0; i < PX4_ACTUATOR_OUTPUTS_MAX; ++i)
	{
		inOutObject->Output[i] = pbMsg.output[i];
	}

	return sizeof(PX4_ActuatorOutputsMsg_t);
}


uint32 PX4BR_AdcReport_Enc(const PX4_AdcReportMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_AdcReport_Dec(const char *inBuffer, uint32 inSize, PX4_AdcReportMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_Airspeed_Enc(const PX4_AirspeedMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_airspeed_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.indicated_airspeed_m_s = inObject->IndicatedAirspeed;
	pbMsg.true_airspeed_m_s = inObject->TrueAirspeed;
	pbMsg.true_airspeed_unfiltered_m_s = inObject->TrueAirspeedUnfiltered;
	pbMsg.air_temperature_celsius = inObject->AirTemperature;
	pbMsg.confidence = inObject->Confidence;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_airspeed_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_Airspeed_Dec(const char *inBuffer, uint32 inSize, PX4_AirspeedMsg_t *inOutObject)
{
	bool status = false;
	px4_airspeed_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_airspeed_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->IndicatedAirspeed = pbMsg.indicated_airspeed_m_s;
	inOutObject->TrueAirspeed = pbMsg.true_airspeed_m_s;
	inOutObject->TrueAirspeedUnfiltered = pbMsg.true_airspeed_unfiltered_m_s;
	inOutObject->AirTemperature = pbMsg.air_temperature_celsius;
	inOutObject->Confidence = pbMsg.confidence;

	return sizeof(PX4_AirspeedMsg_t);
}


uint32 PX4BR_AttPosMoCap_Enc(const PX4_AttPosMoCapMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_AttPosMoCap_Dec(const char *inBuffer, uint32 inSize, PX4_AttPosMoCapMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_BatteryStatus_Enc(const PX4_BatteryStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_battery_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.voltage_v = inObject->Voltage;
	pbMsg.voltage_filtered_v = inObject->VoltageFiltered;
	pbMsg.current_a = inObject->Current;
	pbMsg.current_filtered_a = inObject->CurrentFiltered;
	pbMsg.discharged_mah = inObject->Discharged;
	pbMsg.remaining = inObject->Remaining;
	pbMsg.scale = inObject->Scale;
	pbMsg.cell_count = inObject->CellCount;
	pbMsg.connected = inObject->Connected;
	pbMsg.warning = inObject->Warning;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_battery_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_BatteryStatus_Dec(const char *inBuffer, uint32 inSize, PX4_BatteryStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_battery_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_battery_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Voltage = pbMsg.voltage_v;
	inOutObject->VoltageFiltered = pbMsg.voltage_filtered_v;
	inOutObject->Current = pbMsg.current_a;
	inOutObject->CurrentFiltered = pbMsg.current_filtered_a;
	inOutObject->Discharged = pbMsg.discharged_mah;
	inOutObject->Remaining = pbMsg.remaining;
	inOutObject->Scale = pbMsg.scale;
	inOutObject->CellCount = pbMsg.cell_count;
	inOutObject->Connected = pbMsg.connected;
	inOutObject->Warning = pbMsg.warning;

	return sizeof(PX4_BatteryStatusMsg_t);
}


uint32 PX4BR_CameraTrigger_Enc(const PX4_CameraTriggerMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_CameraTrigger_Dec(const char *inBuffer, uint32 inSize, PX4_CameraTriggerMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_CommanderState_Enc(const PX4_CommanderStateMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_commander_state_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.main_state = inObject->MainState;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_commander_state_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_CommanderState_Dec(const char *inBuffer, uint32 inSize, PX4_CommanderStateMsg_t *inOutObject)
{
	bool status = false;
	px4_commander_state_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_commander_state_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->MainState = pbMsg.main_state;

	return sizeof(PX4_CommanderStateMsg_t);
}

uint32 PX4BR_ControlState_Enc(const PX4_ControlStateMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_control_state_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.x_acc = inObject->AccX;
	pbMsg.y_acc = inObject->AccY;
	pbMsg.z_acc = inObject->AccZ;
	pbMsg.x_vel = inObject->VelX;
	pbMsg.y_vel = inObject->VelY;
	pbMsg.z_vel = inObject->VelZ;
	pbMsg.x_pos = inObject->PosX;
	pbMsg.y_pos = inObject->PosY;
	pbMsg.z_pos = inObject->PosZ;
	pbMsg.airspeed = inObject->Airspeed;
	pbMsg.vel_variance[0] = inObject->VelVariance[0];
	pbMsg.vel_variance[1] = inObject->VelVariance[1];
	pbMsg.vel_variance[2] = inObject->VelVariance[2];
	pbMsg.pos_variance[0] = inObject->PosVariance[0];
	pbMsg.pos_variance[1] = inObject->PosVariance[1];
	pbMsg.pos_variance[2] = inObject->PosVariance[2];
	pbMsg.q[0] = inObject->Q[0];
	pbMsg.q[1] = inObject->Q[1];
	pbMsg.q[2] = inObject->Q[2];
	pbMsg.q[3] = inObject->Q[3];
	pbMsg.delta_q_reset[0] = inObject->DeltaQReset[0];
	pbMsg.delta_q_reset[1] = inObject->DeltaQReset[1];
	pbMsg.delta_q_reset[2] = inObject->DeltaQReset[2];
	pbMsg.delta_q_reset[3] = inObject->DeltaQReset[3];
	pbMsg.roll_rate = inObject->RollRate;
	pbMsg.pitch_rate = inObject->PitchRate;
	pbMsg.yaw_rate = inObject->YawRate;
	pbMsg.horz_acc_mag = inObject->HorzAccMag;
	pbMsg.roll_rate_bias = inObject->RollRateBias;
	pbMsg.pitch_rate_bias = inObject->PitchRateBias;
	pbMsg.yaw_rate_bias = inObject->YawRateBias;
	pbMsg.airspeed_valid = inObject->AirspeedValid;
	pbMsg.quat_reset_counter = inObject->QuatResetCounter;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_control_state_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ControlState_Dec(const char *inBuffer, uint32 inSize, PX4_ControlStateMsg_t *inOutObject)
{
	bool status = false;
	px4_control_state_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_control_state_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->AccX = pbMsg.x_acc;
	inOutObject->AccY = pbMsg.y_acc;
	inOutObject->AccZ = pbMsg.z_acc;
	inOutObject->VelX = pbMsg.x_vel;
	inOutObject->VelY = pbMsg.y_vel;
	inOutObject->VelZ = pbMsg.z_vel;
	inOutObject->PosX = pbMsg.x_pos;
	inOutObject->PosY = pbMsg.y_pos;
	inOutObject->PosZ = pbMsg.z_pos;
	inOutObject->Airspeed = pbMsg.airspeed;
	inOutObject->VelVariance[0] = pbMsg.vel_variance[0];
	inOutObject->VelVariance[1] = pbMsg.vel_variance[1];
	inOutObject->VelVariance[2] = pbMsg.vel_variance[2];
	inOutObject->PosVariance[0] = pbMsg.pos_variance[0];
	inOutObject->PosVariance[1] = pbMsg.pos_variance[1];
	inOutObject->PosVariance[2] = pbMsg.pos_variance[2];
	inOutObject->Q[0] = pbMsg.q[0];
	inOutObject->Q[1] = pbMsg.q[1];
	inOutObject->Q[2] = pbMsg.q[2];
	inOutObject->Q[3] = pbMsg.q[3];
	inOutObject->DeltaQReset[0] = pbMsg.delta_q_reset[0];
	inOutObject->DeltaQReset[1] = pbMsg.delta_q_reset[1];
	inOutObject->DeltaQReset[2] = pbMsg.delta_q_reset[2];
	inOutObject->DeltaQReset[3] = pbMsg.delta_q_reset[3];
	inOutObject->RollRate = pbMsg.roll_rate;
	inOutObject->PitchRate = pbMsg.pitch_rate;
	inOutObject->YawRate = pbMsg.yaw_rate;
	inOutObject->HorzAccMag = pbMsg.horz_acc_mag;
	inOutObject->RollRateBias = pbMsg.roll_rate_bias;
	inOutObject->PitchRateBias = pbMsg.pitch_rate_bias;
	inOutObject->YawRateBias = pbMsg.yaw_rate_bias;
	inOutObject->AirspeedValid = pbMsg.airspeed_valid;
	inOutObject->QuatResetCounter = pbMsg.quat_reset_counter;

	return sizeof(PX4_ControlStateMsg_t);
}


uint32 PX4BR_CpuLoad_Enc(const PX4_CpuLoadMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_CpuLoad_Dec(const char *inBuffer, uint32 inSize, PX4_CpuLoadMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_DebugKeyValue_Enc(const PX4_DebugKeyValueMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_DebugKeyValue_Dec(const char *inBuffer, uint32 inSize, PX4_DebugKeyValueMsg_t *inOutObject)
{
	return 0;
}

uint32 PX4BR_DifferentialPressure_Enc(const PX4_DifferentialPressureMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_differential_pressure_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.differential_pressure_raw_pa = inObject->DifferentialPressureRaw;
	pbMsg.differential_pressure_filtered_pa = inObject->DifferentialPressureFiltered;
	pbMsg.temperature = inObject->Temperature;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_differential_pressure_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_DifferentialPressure_Dec(const char *inBuffer, uint32 inSize, PX4_DifferentialPressureMsg_t *inOutObject)
{
	bool status = false;
	px4_differential_pressure_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_differential_pressure_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->DifferentialPressureRaw = pbMsg.differential_pressure_raw_pa;
	inOutObject->DifferentialPressureFiltered = pbMsg.differential_pressure_filtered_pa;
	inOutObject->Temperature = pbMsg.temperature;

	return sizeof(PX4_DifferentialPressureMsg_t);
}


uint32 PX4BR_DistanceSensor_Enc(const PX4_DistanceSensorMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_distance_sensor_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.min_distance = inObject->MinDistance;
	pbMsg.max_distance = inObject->MaxDistance;
	pbMsg.current_distance = inObject->CurrentDistance;
	pbMsg.covariance = inObject->Covariance;
	pbMsg.type = inObject->Type;
	pbMsg.id = inObject->ID;
	pbMsg.orientation = inObject->Orientation;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_distance_sensor_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_DistanceSensor_Dec(const char *inBuffer, uint32 inSize, PX4_DistanceSensorMsg_t *inOutObject)
{
	bool status = false;
	px4_distance_sensor_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_distance_sensor_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->MinDistance = pbMsg.min_distance;
	inOutObject->MaxDistance = pbMsg.max_distance;
	inOutObject->CurrentDistance = pbMsg.current_distance;
	inOutObject->Covariance = pbMsg.covariance;
	inOutObject->Type = pbMsg.type;
	inOutObject->ID = pbMsg.id;
	inOutObject->Orientation = pbMsg.orientation;

	return sizeof(PX4_DistanceSensorMsg_t);
}

uint32 PX4BR_Ekf2Innovations_Enc(const PX4_Ekf2InnovationsMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_ekf2_innovations_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.vel_pos_innov[0] = inObject->VelPosInnov[0];
	pbMsg.vel_pos_innov[1] = inObject->VelPosInnov[1];
	pbMsg.vel_pos_innov[2] = inObject->VelPosInnov[2];
	pbMsg.vel_pos_innov[3] = inObject->VelPosInnov[3];
	pbMsg.vel_pos_innov[4] = inObject->VelPosInnov[4];
	pbMsg.vel_pos_innov[5] = inObject->VelPosInnov[5];
	pbMsg.mag_innov[0] = inObject->MagInnov[0];
	pbMsg.mag_innov[1] = inObject->MagInnov[1];
	pbMsg.mag_innov[2] = inObject->MagInnov[2];
	pbMsg.heading_innov = inObject->HeadingInnov;
	pbMsg.airspeed_innov = inObject->AirspeedInnov;
	pbMsg.flow_innov[0] = inObject->FlowInnov[0];
	pbMsg.flow_innov[1] = inObject->FlowInnov[1];
	pbMsg.hagl_innov = inObject->HaglInnov;
	pbMsg.vel_pos_innov_var[0] = inObject->VelPosInnovVar[0];
	pbMsg.vel_pos_innov_var[1] = inObject->VelPosInnovVar[1];
	pbMsg.vel_pos_innov_var[2] = inObject->VelPosInnovVar[2];
	pbMsg.vel_pos_innov_var[3] = inObject->VelPosInnovVar[3];
	pbMsg.vel_pos_innov_var[4] = inObject->VelPosInnovVar[4];
	pbMsg.vel_pos_innov_var[5] = inObject->VelPosInnovVar[5];
	pbMsg.mag_innov_var[0] = inObject->MagInnovVar[0];
	pbMsg.mag_innov_var[1] = inObject->MagInnovVar[1];
	pbMsg.mag_innov_var[2] = inObject->MagInnovVar[2];
	pbMsg.heading_innov_var = inObject->HeadingInnovVar;
	pbMsg.airspeed_innov_var = inObject->AirspeedInnovVar;
	pbMsg.flow_innov_var[0] = inObject->FlowInnovVar[0];
	pbMsg.flow_innov_var[1] = inObject->FlowInnovVar[1];
	pbMsg.hagl_innov_var = inObject->HaglInnovVar;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_ekf2_innovations_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_Ekf2Innovations_Dec(const char *inBuffer, uint32 inSize, PX4_Ekf2InnovationsMsg_t *inOutObject)
{
	bool status = false;
	px4_ekf2_innovations_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_ekf2_innovations_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->VelPosInnov[0] = pbMsg.vel_pos_innov[0];
	inOutObject->VelPosInnov[1] = pbMsg.vel_pos_innov[1];
	inOutObject->VelPosInnov[2] = pbMsg.vel_pos_innov[2];
	inOutObject->VelPosInnov[3] = pbMsg.vel_pos_innov[3];
	inOutObject->VelPosInnov[4] = pbMsg.vel_pos_innov[4];
	inOutObject->VelPosInnov[5] = pbMsg.vel_pos_innov[5];
	inOutObject->MagInnov[0] = pbMsg.mag_innov[0];
	inOutObject->MagInnov[1] = pbMsg.mag_innov[1];
	inOutObject->MagInnov[2] = pbMsg.mag_innov[2];
	inOutObject->HeadingInnov = pbMsg.heading_innov;
	inOutObject->AirspeedInnov = pbMsg.airspeed_innov;
	inOutObject->FlowInnov[0] = pbMsg.flow_innov[0];
	inOutObject->FlowInnov[1] = pbMsg.flow_innov[1];
	inOutObject->HaglInnov = pbMsg.hagl_innov;
	inOutObject->VelPosInnovVar[0] = pbMsg.vel_pos_innov_var[0];
	inOutObject->VelPosInnovVar[1] = pbMsg.vel_pos_innov_var[1];
	inOutObject->VelPosInnovVar[2] = pbMsg.vel_pos_innov_var[2];
	inOutObject->VelPosInnovVar[3] = pbMsg.vel_pos_innov_var[3];
	inOutObject->VelPosInnovVar[4] = pbMsg.vel_pos_innov_var[4];
	inOutObject->VelPosInnovVar[5] = pbMsg.vel_pos_innov_var[5];
	inOutObject->MagInnovVar[0] = pbMsg.mag_innov_var[0];
	inOutObject->MagInnovVar[1] = pbMsg.mag_innov_var[1];
	inOutObject->MagInnovVar[2] = pbMsg.mag_innov_var[2];
	inOutObject->HeadingInnovVar = pbMsg.heading_innov_var;
	inOutObject->AirspeedInnovVar = pbMsg.airspeed_innov_var;
	inOutObject->FlowInnovVar[0] = pbMsg.flow_innov_var[0];
	inOutObject->FlowInnovVar[1] = pbMsg.flow_innov_var[1];
	inOutObject->HaglInnovVar = pbMsg.hagl_innov_var;

	return sizeof(PX4_Ekf2InnovationsMsg_t);
}

uint32 PX4BR_Ekf2Replay_Enc(const PX4_Ekf2ReplayMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_Ekf2Replay_Dec(const char *inBuffer, uint32 inSize, PX4_Ekf2ReplayMsg_t *inOutObject)
{
	return 0;
}

uint32 PX4BR_EscReport_Enc(const PX4_EscReportMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_esc_report_pb pbMsg;

	//pbMsg.timestamp = inObject->Timestamp;
	pbMsg.esc_errorcount = inObject->Esc.ErrorCount;
	pbMsg.esc_rpm = inObject->Esc.Rpm;
	pbMsg.esc_voltage = inObject->Esc.Voltage;
	pbMsg.esc_current = inObject->Esc.Current;
	pbMsg.esc_temperature = inObject->Esc.Temperature;
	pbMsg.esc_setpoint = inObject->Esc.Setpoint;
	pbMsg.esc_setpoint_raw = inObject->Esc.SetpointRaw;
	pbMsg.esc_address = inObject->Esc.Address;
	pbMsg.esc_version = inObject->Esc.Version;
	pbMsg.esc_state = inObject->Esc.State;
	pbMsg.esc_vendor = inObject->Esc.Vendor;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_esc_report_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_EscReport_Dec(const char *inBuffer, uint32 inSize, PX4_EscReportMsg_t *inOutObject)
{
	bool status = false;
	px4_esc_report_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_esc_report_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	//inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Esc.ErrorCount = pbMsg.esc_errorcount;
	inOutObject->Esc.Rpm = pbMsg.esc_rpm;
	inOutObject->Esc.Voltage = pbMsg.esc_voltage;
	inOutObject->Esc.Current = pbMsg.esc_current;
	inOutObject->Esc.Temperature = pbMsg.esc_temperature;
	inOutObject->Esc.Setpoint = pbMsg.esc_setpoint;
	inOutObject->Esc.SetpointRaw = pbMsg.esc_setpoint_raw;
	inOutObject->Esc.Address = pbMsg.esc_address;
	inOutObject->Esc.Version = pbMsg.esc_version;
	inOutObject->Esc.State = pbMsg.esc_state;
	inOutObject->Esc.Vendor = pbMsg.esc_vendor;

	return sizeof(PX4_EscReportMsg_t);
}

uint32 PX4BR_EscStatus_Enc(const PX4_EscStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_esc_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.counter = inObject->Counter;
	pbMsg.esc_count = inObject->EscCount;
	pbMsg.connectiontype = inObject->ConnectionType;
	for(i=0; i < PX4_ESC_CONNECTED_ESC_MAX; ++i)
	{
		pbMsg.esc[i].timestamp = inObject->Esc[i].Timestamp;
		pbMsg.esc[i].esc_errorcount = inObject->Esc[i].ErrorCount;
		pbMsg.esc[i].esc_rpm = inObject->Esc[i].Rpm;
		pbMsg.esc[i].esc_voltage = inObject->Esc[i].Voltage;
		pbMsg.esc[i].esc_current = inObject->Esc[i].Current;
		pbMsg.esc[i].esc_temperature = inObject->Esc[i].Temperature;
		pbMsg.esc[i].esc_setpoint = inObject->Esc[i].Setpoint;
		pbMsg.esc[i].esc_setpoint_raw = inObject->Esc[i].SetpointRaw;
		pbMsg.esc[i].esc_address = inObject->Esc[i].Address;
		pbMsg.esc[i].esc_version = inObject->Esc[i].Version;
		pbMsg.esc[i].esc_state = inObject->Esc[i].State;
		pbMsg.esc[i].esc_vendor = inObject->Esc[i].Vendor;
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_esc_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_EscStatus_Dec(const char *inBuffer, uint32 inSize, PX4_EscStatusMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_esc_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_esc_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Counter = pbMsg.counter;
	inOutObject->EscCount = pbMsg.count;
	inOutObject->ConnectionType = pbMsg.connectiontype;
	for(i=0; i < PX4_ESC_CONNECTED_ESC_MAX; ++i)
	{
		//inOutObject->esc[i].timestamp = pbMsg.esc[i].timestamp;
		inOutObject->Esc[i].ErrorCount = pbMsg.esc[i].esc_errorcount;
		inOutObject->Esc[i].Rpm = pbMsg.esc[i].esc_rpm;
		inOutObject->Esc[i].Voltage = pbMsg.esc[i].esc_voltage;
		inOutObject->Esc[i].Current = pbMsg.esc[i].esc_current;
		inOutObject->Esc[i].Temperature = pbMsg.esc[i].esc_temperature;
		inOutObject->Esc[i].Setpoint = pbMsg.esc[i].esc_setpoint;
		inOutObject->Esc[i].SetpointRaw = pbMsg.esc[i].esc_setpoint_raw;
		inOutObject->Esc[i].Address = pbMsg.esc[i].esc_address;
		inOutObject->Esc[i].Version = pbMsg.esc[i].esc_version;
		inOutObject->Esc[i].State = pbMsg.esc[i].esc_state;
		inOutObject->Esc[i].Vendor = pbMsg.esc[i].esc_vendor;
	}

	return sizeof(PX4_EscStatusMsg_t);
}

uint32 PX4BR_EstimatorStatus_Enc(const PX4_EstimatorStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t iStates = 0;
	uint32_t iVibe = 0;
	uint32_t iCV = 0;
	bool status = false;
	px4_estimator_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.states_count = PX4_ESTIMATOR_STATES_MAX;
	for(iStates=0; iStates < PX4_ESTIMATOR_STATES_MAX; ++iStates)
	{
		pbMsg.states[iStates] = inObject->States[iStates];
	}
	pbMsg.n_states = inObject->NumStates;
	pbMsg.vibe_count = PX4_ESTIMATOR_VIBE_MAX;
	for(iVibe=0; iVibe < PX4_ESTIMATOR_VIBE_MAX; ++iVibe)
	{
		pbMsg.vibe[iVibe] = inObject->Vibe[iVibe];
	}
	pbMsg.covariances_count = PX4_ESTIMATOR_COVARIANCES_MAX;
	for(iCV=0; iCV < PX4_ESTIMATOR_COVARIANCES_MAX; ++iCV)
	{
		pbMsg.covariances[iCV] = inObject->Covariances[iCV];
	}
	pbMsg.gps_check_fail_flags = inObject->GpsCheckFailFlags;
	pbMsg.control_mode_flags = inObject->ControlModeFlags;
	pbMsg.filter_fault_flags = inObject->FilterFaultFlags;
	pbMsg.nan_flags = inObject->NanFlags;
	pbMsg.health_flags = inObject->HealthFlags;
	pbMsg.timeout_flags = inObject->TimeoutFlags;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_estimator_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_EstimatorStatus_Dec(const char *inBuffer, uint32 inSize, PX4_EstimatorStatusMsg_t *inOutObject)
{
	uint32_t iStates = 0;
	uint32_t iVibe = 0;
	uint32_t iCV = 0;
	bool status = false;
	px4_estimator_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_estimator_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	for(iStates=0; iStates < PX4_ESTIMATOR_STATES_MAX; ++iStates)
	{
		inOutObject->States[iStates] = pbMsg.states[iStates];
	}
	inOutObject->NumStates = pbMsg.n_states;
	for(iVibe=0; iVibe < PX4_ESTIMATOR_VIBE_MAX; ++iVibe)
	{
		inOutObject->Vibe[iVibe] = pbMsg.vibe[iVibe];
	}
	for(iCV=0; iCV < PX4_ESTIMATOR_COVARIANCES_MAX; ++iCV)
	{
		inOutObject->Covariances[iCV] = pbMsg.covariances[iCV];
	}
	inOutObject->GpsCheckFailFlags = pbMsg.gps_check_fail_flags;
	inOutObject->ControlModeFlags = pbMsg.control_mode_flags;
	inOutObject->FilterFaultFlags = pbMsg.filter_fault_flags;
	inOutObject->NanFlags = pbMsg.nan_flags;
	inOutObject->HealthFlags = pbMsg.health_flags;
	inOutObject->TimeoutFlags = pbMsg.timeout_flags;

	return sizeof(PX4_EstimatorStatusMsg_t);
}


uint32 PX4BR_Fence_Enc(const PX4_FenceMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_Fence_Dec(const char *inBuffer, uint32 inSize, PX4_FenceMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_FenceVertex_Enc(const PX4_FenceVertexMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_FenceVertex_Dec(const char *inBuffer, uint32 inSize, PX4_FenceVertexMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_FilteredBottomFlow_Enc(const PX4_FilteredBottomFlowMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_filtered_bottom_flow_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.sumx = inObject->SumX;
	pbMsg.sumy = inObject->SumY;
	pbMsg.vx = inObject->VX;
	pbMsg.vy = inObject->VY;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_filtered_bottom_flow_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_FilteredBottomFlow_Dec(const char *inBuffer, uint32 inSize, PX4_FilteredBottomFlowMsg_t *inOutObject)
{
	bool status = false;
	px4_filtered_bottom_flow_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_filtered_bottom_flow_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SumX = pbMsg.sumx;
	inOutObject->SumY = pbMsg.sumy;
	inOutObject->VX = pbMsg.vx;
	inOutObject->VY = pbMsg.vy;

	return sizeof(PX4_FilteredBottomFlowMsg_t);
}


uint32 PX4BR_FollowTarget_Enc(const PX4_FollowTargetMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_FollowTarget_Dec(const char *inBuffer, uint32 inSize, PX4_FollowTargetMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_FwPosCtrlStatus_Enc(const PX4_FwPosCtrlStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_fw_pos_ctrl_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.nav_roll = inObject->NavRoll;
	pbMsg.nav_pitch = inObject->NavPitch;
	pbMsg.nav_bearing = inObject->NavBearing;
	pbMsg.target_bearing = inObject->TargetBearing;
	pbMsg.wp_dist = inObject->WpDist;
	pbMsg.xtrack_error = inObject->XtrackError;
	pbMsg.turn_distance = inObject->TurnDistance;
	pbMsg.landing_horizontal_slope_displacement = inObject->LandingHorizontalSlopeDisplacement;
	pbMsg.landing_slope_angle_rad = inObject->LandingSlopeAngleRad;
	pbMsg.landing_flare_length = inObject->LandingFlareLength;
	pbMsg.abort_landing = inObject->AbortLanding;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_fw_pos_ctrl_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_FwPosCtrlStatus_Dec(const char *inBuffer, uint32 inSize, PX4_FwPosCtrlStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_fw_pos_ctrl_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_fw_pos_ctrl_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->NavRoll = pbMsg.nav_roll;
	inOutObject->NavPitch = pbMsg.nav_pitch;
	inOutObject->NavBearing = pbMsg.nav_bearing;
	inOutObject->TargetBearing = pbMsg.target_bearing;
	inOutObject->WpDist = pbMsg.wp_dist;
	inOutObject->XtrackError = pbMsg.xtrack_error;
	inOutObject->TurnDistance = pbMsg.turn_distance;
	inOutObject->LandingHorizontalSlopeDisplacement = pbMsg.landing_horizontal_slope_displacement;
	inOutObject->LandingSlopeAngleRad = pbMsg.landing_slope_angle_rad;
	inOutObject->LandingFlareLength = pbMsg.landing_flare_length;
	inOutObject->AbortLanding = pbMsg.abort_landing;

	return sizeof(PX4_FwPosCtrlStatusMsg_t);
}


uint32 PX4BR_FwVirtualAttitudeSetpoint_Enc(const PX4_FwVirtualAttitudeSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_fw_virtual_attitude_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll_body = inObject->RollBody;
	pbMsg.pitch_body = inObject->PitchBody;
	pbMsg.yaw_body = inObject->YawBody;
	pbMsg.yaw_sp_move_rate = inObject->YawSpMoveRate;
	pbMsg.R_body[0] = inObject->RBody[0];
	pbMsg.R_body[1] = inObject->RBody[1];
	pbMsg.R_body[2] = inObject->RBody[2];
	pbMsg.R_body[3] = inObject->RBody[3];
	pbMsg.R_body[4] = inObject->RBody[4];
	pbMsg.R_body[5] = inObject->RBody[5];
	pbMsg.R_body[6] = inObject->RBody[6];
	pbMsg.R_body[7] = inObject->RBody[7];
	pbMsg.R_body[8] = inObject->RBody[8];
	pbMsg.q_d[0] = inObject->Q_D[0];
	pbMsg.q_d[1] = inObject->Q_D[1];
	pbMsg.q_d[2] = inObject->Q_D[2];
	pbMsg.q_d[3] = inObject->Q_D[3];
	pbMsg.q_e[0] = inObject->Q_E[0];
	pbMsg.q_e[1] = inObject->Q_E[1];
	pbMsg.q_e[2] = inObject->Q_E[2];
	pbMsg.q_e[3] = inObject->Q_E[3];
	pbMsg.thrust = inObject->Thrust;
	pbMsg.R_valid = inObject->RValid;
	pbMsg.q_d_valid = inObject->Q_D_Valid;
	pbMsg.q_e_valid = inObject->Q_E_Valid;
	pbMsg.roll_reset_integral = inObject->RollResetIntegral;
	pbMsg.pitch_reset_integral = inObject->PitchResetIntegral;
	pbMsg.yaw_reset_integral = inObject->YawResetIntegral;
	pbMsg.fw_control_yaw = inObject->FwControlYaw;
	pbMsg.disable_mc_yaw_control = inObject->DisableMcYawControl;
	pbMsg.apply_flaps = inObject->ApplyFlaps;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_fw_virtual_attitude_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_FwVirtualAttitudeSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_FwVirtualAttitudeSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_fw_virtual_attitude_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_fw_virtual_attitude_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RollBody = pbMsg.roll_body;
	inOutObject->PitchBody = pbMsg.pitch_body;
	inOutObject->YawBody = pbMsg.yaw_body;
	inOutObject->YawSpMoveRate = pbMsg.yaw_sp_move_rate;
	inOutObject->RBody[0] = pbMsg.R_body[0];
	inOutObject->RBody[1] = pbMsg.R_body[1];
	inOutObject->RBody[2] = pbMsg.R_body[2];
	inOutObject->RBody[3] = pbMsg.R_body[3];
	inOutObject->RBody[4] = pbMsg.R_body[4];
	inOutObject->RBody[5] = pbMsg.R_body[5];
	inOutObject->RBody[6] = pbMsg.R_body[6];
	inOutObject->RBody[7] = pbMsg.R_body[7];
	inOutObject->RBody[8] = pbMsg.R_body[8];
	inOutObject->Q_D[0] = pbMsg.q_d[0];
	inOutObject->Q_D[1] = pbMsg.q_d[1];
	inOutObject->Q_D[2] = pbMsg.q_d[2];
	inOutObject->Q_D[3] = pbMsg.q_d[3];
	inOutObject->Q_E[0] = pbMsg.q_e[0];
	inOutObject->Q_E[1] = pbMsg.q_e[1];
	inOutObject->Q_E[2] = pbMsg.q_e[2];
	inOutObject->Q_E[3] = pbMsg.q_e[3];
	inOutObject->Thrust = pbMsg.thrust;
	inOutObject->RValid = pbMsg.R_valid;
	inOutObject->Q_D_Valid = pbMsg.q_d_valid;
	inOutObject->Q_E_Valid = pbMsg.q_e_valid;
	inOutObject->RollResetIntegral = pbMsg.roll_reset_integral;
	inOutObject->PitchResetIntegral = pbMsg.pitch_reset_integral;
	inOutObject->YawResetIntegral = pbMsg.yaw_reset_integral;
	inOutObject->FwControlYaw = pbMsg.fw_control_yaw;
	inOutObject->DisableMcYawControl = pbMsg.disable_mc_yaw_control;
	inOutObject->ApplyFlaps = pbMsg.apply_flaps;

	return sizeof(PX4_FwVirtualAttitudeSetpointMsg_t);
}


uint32 PX4BR_FwVirtualRatesSetpoint_Enc(const PX4_FwVirtualRatesSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_fw_virtual_rates_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll = inObject->Roll;
	pbMsg.pitch = inObject->Pitch;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.thrust = inObject->Thrust;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_fw_virtual_rates_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_FwVirtualRatesSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_FwVirtualRatesSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_fw_virtual_rates_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_fw_virtual_rates_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Roll = pbMsg.roll;
	inOutObject->Pitch = pbMsg.pitch;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->Thrust = pbMsg.thrust;

	return sizeof(PX4_FwVirtualRatesSetpointMsg_t);
}

uint32 PX4BR_GeofenceResult_Enc(const PX4_GeofenceResultMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_GeofenceResult_Dec(const char *inBuffer, uint32 inSize, PX4_GeofenceResultMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_GpsDump_Enc(const PX4_GpsDumpMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_gps_dump_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.len = inObject->Len;
	strncpy(pbMsg.data, inObject->Data, PX4_GPS_DUMP_DATA_MAX);

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_gps_dump_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_GpsDump_Dec(const char *inBuffer, uint32 inSize, PX4_GpsDumpMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_gps_dump_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_gps_dump_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Len = pbMsg.len;
	strncpy(inOutObject->Data, pbMsg.data, PX4_GPS_DUMP_DATA_MAX);

	return sizeof(PX4_GpsDumpMsg_t);
}


uint32 PX4BR_GpsInjectData_Enc(const PX4_GpsInjectDataMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_gps_inject_data_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.len = inObject->Len;
	pbMsg.flags = inObject->Flags;
	strncpy(pbMsg.data, inObject->Data, PX4_GPS_INJECT_DATA_MAX);
	for(i=0; i < PX4_GPS_INJECT_DATA_MAX; ++i)
	{
		pbMsg.data[i] = inObject->Data[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_gps_inject_data_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_GpsInjectData_Dec(const char *inBuffer, uint32 inSize, PX4_GpsInjectDataMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_gps_inject_data_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_gps_inject_data_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Len = pbMsg.len;
	inOutObject->Flags = pbMsg.flags;
	strncpy(inOutObject->Data, pbMsg.data, PX4_GPS_DUMP_DATA_MAX);

	return sizeof(PX4_GpsInjectDataMsg_t);
}


uint32 PX4BR_HilSensor_Enc(const PX4_HilSensorMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_HilSensor_Dec(const char *inBuffer, uint32 inSize, PX4_HilSensorMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_HomePosition_Enc(const PX4_HomePositionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_home_position_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.lat = inObject->Lat;
	pbMsg.lon = inObject->Lon;
	pbMsg.alt = inObject->Alt;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.direction_x = inObject->DirectionX;
	pbMsg.direction_y = inObject->DirectionY;
	pbMsg.direction_z = inObject->DirectionZ;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_home_position_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_HomePosition_Dec(const char *inBuffer, uint32 inSize, PX4_HomePositionMsg_t *inOutObject)
{
	bool status = false;
	px4_home_position_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_home_position_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Lat = pbMsg.lat;
	inOutObject->Lon = pbMsg.lon;
	inOutObject->Alt = pbMsg.alt;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->DirectionX = pbMsg.direction_x;
	inOutObject->DirectionY = pbMsg.direction_y;
	inOutObject->DirectionZ = pbMsg.direction_z;

	return sizeof(PX4_HomePositionMsg_t);
}


uint32 PX4BR_InputRc_Enc(const PX4_InputRcMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_input_rc_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.timestamp_last_signal = inObject->LastSignal;
	pbMsg.channel_count = inObject->ChannelCount;
	pbMsg.rssi = inObject->RSSI;
	pbMsg.rc_lost_frame_count = inObject->RcLostFrameCount;
	pbMsg.rc_total_frame_count = inObject->RcTotalFrameCount;
	pbMsg.rc_ppm_frame_length = inObject->RcPpmFrameLength;
	pbMsg.values_count = PX4_RC_INPUT_MAX_CHANNELS;
	for(i = 0; i < PX4_RC_INPUT_MAX_CHANNELS; ++i)
	{
		pbMsg.values[i] = inObject->Values[i];
	}
	pbMsg.rc_failsafe = inObject->RcFailsafe;
	pbMsg.rc_lost = inObject->RcLost;
	pbMsg.input_source = inObject->InputSource;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_input_rc_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_InputRc_Dec(const char *inBuffer, uint32 inSize, PX4_InputRcMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_input_rc_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_input_rc_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	//inOutObject->TimestampPublication = pbMsg.timestamp_publication;
	//inOutObject->timestamp_last_signal = pbMsg.timestamp_last_signal;
	inOutObject->ChannelCount = pbMsg.channel_count;
	inOutObject->RSSI = pbMsg.rssi;
	inOutObject->RcLostFrameCount = pbMsg.rc_lost_frame_count;
	inOutObject->RcTotalFrameCount = pbMsg.rc_total_frame_count;
	inOutObject->RcPpmFrameLength = pbMsg.rc_ppm_frame_length;
	for(i = 0; i < PX4_RC_INPUT_MAX_CHANNELS; ++i)
	{
		inOutObject->Values[i] = pbMsg.values[i];
	}
	inOutObject->RcFailsafe = pbMsg.rc_failsafe;
	inOutObject->RcLost = pbMsg.rc_lost;
	inOutObject->InputSource = pbMsg.input_source;

	return sizeof(PX4_InputRcMsg_t);
}


uint32 PX4BR_LogMessage_Enc(const PX4_LogMessageMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_log_message_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.severity = inObject->Severity;
	for(i = 0; i < 127; ++i)
	{
		pbMsg.text[i] = inObject->Text[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_log_message_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_LogMessage_Dec(const char *inBuffer, uint32 inSize, PX4_LogMessageMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_log_message_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_log_message_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Severity = pbMsg.severity;
	for(i = 0; i < 127; ++i)
	{
		inOutObject->Text[i] = pbMsg.text[i];
	}

	return sizeof(PX4_LogMessageMsg_t);
}


uint32 PX4BR_ManualControlSetpoint_Enc(const PX4_ManualControlSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_manual_control_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.r = inObject->R;
	pbMsg.flaps = inObject->Flaps;
	pbMsg.aux1 = inObject->Aux1;
	pbMsg.aux2 = inObject->Aux2;
	pbMsg.aux3 = inObject->Aux3;
	pbMsg.aux4 = inObject->Aux4;
	pbMsg.aux5 = inObject->Aux5;
	pbMsg.mode_switch = inObject->ModeSwitch;
	pbMsg.return_switch = inObject->ReturnSwitch;
	pbMsg.rattitude_switch = inObject->RattitudeSwitch;
	pbMsg.posctl_switch = inObject->PosctlSwitch;
	pbMsg.loiter_switch = inObject->LoiterSwitch;
	pbMsg.acro_switch = inObject->AcroSwitch;
	pbMsg.offboard_switch = inObject->OffboardSwitch;
	pbMsg.kill_switch = inObject->KillSwitch;
	pbMsg.transition_switch = inObject->TransitionSwitch;
	pbMsg.mode_slot = inObject->ModeSlot;
	pbMsg.data_source = inObject->DataSource;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_manual_control_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_ManualControlSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_ManualControlSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_manual_control_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_manual_control_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->R = pbMsg.r;
	inOutObject->Flaps = pbMsg.flaps;
	inOutObject->Aux1 = pbMsg.aux1;
	inOutObject->Aux2 = pbMsg.aux2;
	inOutObject->Aux3 = pbMsg.aux3;
	inOutObject->Aux4 = pbMsg.aux4;
	inOutObject->Aux5 = pbMsg.aux5;
	inOutObject->ModeSwitch = pbMsg.mode_switch;
	inOutObject->ReturnSwitch = pbMsg.return_switch;
	inOutObject->RattitudeSwitch = pbMsg.rattitude_switch;
	inOutObject->PosctlSwitch = pbMsg.posctl_switch;
	inOutObject->LoiterSwitch = pbMsg.loiter_switch;
	inOutObject->AcroSwitch = pbMsg.acro_switch;
	inOutObject->OffboardSwitch = pbMsg.offboard_switch;
	inOutObject->KillSwitch = pbMsg.kill_switch;
	inOutObject->TransitionSwitch = pbMsg.transition_switch;
	inOutObject->ModeSlot = pbMsg.mode_slot;
	inOutObject->DataSource = pbMsg.data_source;

	return sizeof(PX4_ManualControlSetpointMsg_t);
}

uint32 PX4BR_MavlinkLog_Enc(const PX4_MavlinkLogMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_mavlink_log_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	for(i = 0; i < 50; ++i)
	{
		pbMsg.text[i] = inObject->Text[i];
	}
	pbMsg.severity = inObject->Severity;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_mavlink_log_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_MavlinkLog_Dec(const char *inBuffer, uint32 inSize, PX4_MavlinkLogMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_mavlink_log_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_mavlink_log_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	for(i = 0; i < 50; ++i)
	{
		inOutObject->Text[i] = pbMsg.text[i];
	}
	inOutObject->Severity = pbMsg.severity;

	return sizeof(PX4_MavlinkLogMsg_t);
}


uint32 PX4BR_McAttCtrlStatus_Enc(const PX4_McAttCtrlStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_mc_att_ctrl_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll_rate_integ = inObject->RollRateInteg;
	pbMsg.pitch_rate_integ = inObject->PitchRateInteg;
	pbMsg.yaw_rate_integ = inObject->YawRateInteg;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_mc_att_ctrl_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_McAttCtrlStatus_Dec(const char *inBuffer, uint32 inSize, PX4_McAttCtrlStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_mc_att_ctrl_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_mc_att_ctrl_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RollRateInteg = pbMsg.roll_rate_integ;
	inOutObject->PitchRateInteg = pbMsg.pitch_rate_integ;
	inOutObject->YawRateInteg = pbMsg.yaw_rate_integ;

	return sizeof(PX4_McAttCtrlStatusMsg_t);
}

uint32 PX4BR_McVirtualAttitudeSetpoint_Enc(const PX4_McVirtualAttitudeSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_mc_virtual_attitude_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll_body = inObject->RollBody;
	pbMsg.pitch_body = inObject->PitchBody;
	pbMsg.yaw_body = inObject->YawBody;
	pbMsg.yaw_sp_move_rate = inObject->YawSpMoveRate;
	pbMsg.R_body[0] = inObject->R_Body[0];
	pbMsg.R_body[1] = inObject->R_Body[1];
	pbMsg.R_body[2] = inObject->R_Body[2];
	pbMsg.R_body[3] = inObject->R_Body[3];
	pbMsg.R_body[4] = inObject->R_Body[4];
	pbMsg.R_body[5] = inObject->R_Body[5];
	pbMsg.R_body[6] = inObject->R_Body[6];
	pbMsg.R_body[7] = inObject->R_Body[7];
	pbMsg.R_body[8] = inObject->R_Body[8];
	pbMsg.q_d[0] = inObject->Q_D[0];
	pbMsg.q_d[1] = inObject->Q_D[1];
	pbMsg.q_d[2] = inObject->Q_D[2];
	pbMsg.q_d[3] = inObject->Q_D[3];
	pbMsg.q_e[0] = inObject->Q_E[0];
	pbMsg.q_e[1] = inObject->Q_E[1];
	pbMsg.q_e[2] = inObject->Q_E[2];
	pbMsg.q_e[3] = inObject->Q_E[3];
	pbMsg.thrust = inObject->Thrust;
	pbMsg.R_valid = inObject->R_Valid;
	pbMsg.q_d_valid = inObject->Q_D_Valid;
	pbMsg.q_e_valid = inObject->Q_E_Valid;
	pbMsg.roll_reset_integral = inObject->RollResetIntegral;
	pbMsg.pitch_reset_integral = inObject->PitchResetIntegral;
	pbMsg.yaw_reset_integral = inObject->YawResetIntegral;
	pbMsg.fw_control_yaw = inObject->FwControlYaw;
	pbMsg.disable_mc_yaw_control = inObject->DisableMcYawControl;
	pbMsg.apply_flaps = inObject->ApplyFlaps;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_mc_virtual_attitude_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_McVirtualAttitudeSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_McVirtualAttitudeSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_mc_virtual_attitude_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_mc_virtual_attitude_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RollBody = pbMsg.roll_body;
	inOutObject->PitchBody = pbMsg.pitch_body;
	inOutObject->YawBody = pbMsg.yaw_body;
	inOutObject->YawSpMoveRate = pbMsg.yaw_sp_move_rate;
	inOutObject->R_Body[0] = pbMsg.R_body[0];
	inOutObject->R_Body[1] = pbMsg.R_body[1];
	inOutObject->R_Body[2] = pbMsg.R_body[2];
	inOutObject->R_Body[3] = pbMsg.R_body[3];
	inOutObject->R_Body[4] = pbMsg.R_body[4];
	inOutObject->R_Body[5] = pbMsg.R_body[5];
	inOutObject->R_Body[6] = pbMsg.R_body[6];
	inOutObject->R_Body[7] = pbMsg.R_body[7];
	inOutObject->R_Body[8] = pbMsg.R_body[8];
	inOutObject->Q_D[0] = pbMsg.q_d[0];
	inOutObject->Q_D[1] = pbMsg.q_d[1];
	inOutObject->Q_D[2] = pbMsg.q_d[2];
	inOutObject->Q_D[3] = pbMsg.q_d[3];
	inOutObject->Q_E[0] = pbMsg.q_e[0];
	inOutObject->Q_E[1] = pbMsg.q_e[1];
	inOutObject->Q_E[2] = pbMsg.q_e[2];
	inOutObject->Q_E[3] = pbMsg.q_e[3];
	inOutObject->Thrust = pbMsg.thrust;
	inOutObject->R_Valid = pbMsg.R_valid;
	inOutObject->Q_D_Valid = pbMsg.q_d_valid;
	inOutObject->Q_E_Valid = pbMsg.q_e_valid;
	inOutObject->RollResetIntegral = pbMsg.roll_reset_integral;
	inOutObject->PitchResetIntegral = pbMsg.pitch_reset_integral;
	inOutObject->YawResetIntegral = pbMsg.yaw_reset_integral;
	inOutObject->FwControlYaw = pbMsg.fw_control_yaw;
	inOutObject->DisableMcYawControl = pbMsg.disable_mc_yaw_control;
	inOutObject->ApplyFlaps = pbMsg.apply_flaps;

	return sizeof(PX4_McVirtualAttitudeSetpointMsg_t);
}


uint32 PX4BR_McVirtualRatesSetpoint_Enc(const PX4_McVirtualRatesSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_mc_virtual_rates_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll = inObject->Roll;
	pbMsg.pitch = inObject->Pitch;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.thrust = inObject->Thrust;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_mc_virtual_rates_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_McVirtualRatesSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_McVirtualRatesSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_mc_virtual_rates_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_mc_virtual_rates_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Roll = pbMsg.roll;
	inOutObject->Pitch = pbMsg.pitch;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->Thrust = pbMsg.thrust;

	return sizeof(PX4_McVirtualRatesSetpointMsg_t);
}


uint32 PX4BR_Mission_Enc(const PX4_MissionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_Mission_Dec(const char *inBuffer, uint32 inSize, PX4_MissionMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_MissionResult_Enc(const PX4_MissionResultMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_MissionResult_Dec(const char *inBuffer, uint32 inSize, PX4_MissionResultMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_MultirotorMotorLimits_Enc(const PX4_MultirotorMotorLimitsMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_multirotor_motor_limits_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.saturation_status = inObject->SaturationStatus.Value;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_multirotor_motor_limits_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_MultirotorMotorLimits_Dec(const char *inBuffer, uint32 inSize, PX4_MultirotorMotorLimitsMsg_t *inOutObject)
{
	bool status = false;
	px4_multirotor_motor_limits_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_multirotor_motor_limits_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SaturationStatus.Value = pbMsg.saturation_status;

	return sizeof(PX4_MultirotorMotorLimitsMsg_t);
}


uint32 PX4BR_OffboardControlMode_Enc(const PX4_OffboardControlModeMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_offboard_control_mode_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.ignore_thrust = inObject->IgnoreThrust;
	pbMsg.ignore_attitude = inObject->IgnoreAttitude;
	pbMsg.ignore_bodyrate = inObject->IgnoreBodyrate;
	pbMsg.ignore_position = inObject->IgnorePosition;
	pbMsg.ignore_velocity = inObject->IgnoreVelocity;
	pbMsg.ignore_acceleration_force = inObject->IgnoreAccelerationForce;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_offboard_control_mode_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_OffboardControlMode_Dec(const char *inBuffer, uint32 inSize, PX4_OffboardControlModeMsg_t *inOutObject)
{
	bool status = false;
	px4_offboard_control_mode_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_offboard_control_mode_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->IgnoreThrust = pbMsg.ignore_thrust;
	inOutObject->IgnoreAttitude = pbMsg.ignore_attitude;
	inOutObject->IgnoreBodyrate = pbMsg.ignore_bodyrate;
	inOutObject->IgnorePosition = pbMsg.ignore_position;
	inOutObject->IgnoreVelocity = pbMsg.ignore_velocity;
	inOutObject->IgnoreAccelerationForce = pbMsg.ignore_acceleration_force;

	return sizeof(PX4_OffboardControlModeMsg_t);
}


uint32 PX4BR_OpticalFlow_Enc(const PX4_OpticalFlowMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_optical_flow_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.pixel_flow_x_integral = inObject->PixelFlowXIntegral;
	pbMsg.pixel_flow_y_integral = inObject->PixelFlowYIntegral;
	pbMsg.gyro_x_rate_integral = inObject->GyroXRateIntegral;
	pbMsg.gyro_y_rate_integral = inObject->GyroYRateIntegral;
	pbMsg.gyro_z_rate_integral = inObject->GyroZRateIntegral;
	pbMsg.ground_distance_m = inObject->GroundDistance;
	pbMsg.integration_timespan = inObject->IntegrationTimespan;
	pbMsg.time_since_last_sonar_update = inObject->TimeSinceLastSonarUpdate;
	pbMsg.frame_count_since_last_readout = inObject->FrameCountSinceLastReadout;
	pbMsg.gyro_temperature = inObject->GyroTemperature;
	pbMsg.sensor_id = inObject->SensorID;
	pbMsg.quality = inObject->Quality;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_optical_flow_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_OpticalFlow_Dec(const char *inBuffer, uint32 inSize, PX4_OpticalFlowMsg_t *inOutObject)
{
	bool status = false;
	px4_optical_flow_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_optical_flow_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->PixelFlowXIntegral = pbMsg.pixel_flow_x_integral;
	inOutObject->PixelFlowYIntegral = pbMsg.pixel_flow_y_integral;
	inOutObject->GyroXRateIntegral = pbMsg.gyro_x_rate_integral;
	inOutObject->GyroYRateIntegral = pbMsg.gyro_y_rate_integral;
	inOutObject->GyroZRateIntegral = pbMsg.gyro_z_rate_integral;
	inOutObject->GroundDistance = pbMsg.ground_distance_m;
	inOutObject->IntegrationTimespan = pbMsg.integration_timespan;
	inOutObject->TimeSinceLastSonarUpdate = pbMsg.time_since_last_sonar_update;
	inOutObject->FrameCountSinceLastReadout = pbMsg.frame_count_since_last_readout;
	inOutObject->GyroTemperature = pbMsg.gyro_temperature;
	inOutObject->SensorID = pbMsg.sensor_id;
	inOutObject->Quality = pbMsg.quality;

	return sizeof(PX4_OpticalFlowMsg_t);
}


uint32 PX4BR_OutputPwm_Enc(const PX4_OutputPwmMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_output_pwm_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.channel_count = inObject->ChannelCount;
	pbMsg.values_count = PX4_PWM_OUTPUT_MAX_CHANNELS;
	for(i = 0; i < PX4_PWM_OUTPUT_MAX_CHANNELS; ++i)
	{
		pbMsg.values[i] = inObject->Values[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_output_pwm_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_OutputPwm_Dec(const char *inBuffer, uint32 inSize, PX4_OutputPwmMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_output_pwm_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_output_pwm_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->ChannelCount = pbMsg.channel_count;
	for(i = 0; i < PX4_PWM_OUTPUT_MAX_CHANNELS; ++i)
	{
		inOutObject->Values[i] = pbMsg.values[i];
	}

	return sizeof(PX4_OutputPwmMsg_t);
}

uint32 PX4BR_ParameterUpdate_Enc(const PX4_ParameterUpdateMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_ParameterUpdate_Dec(const char *inBuffer, uint32 inSize, PX4_ParameterUpdateMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_PositionSetpoint_Enc(const PX4_PositionSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_PositionSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_PositionSetpointMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_PositionSetpointTriplet_Enc(const PX4_PositionSetpointTripletMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_position_setpoint_triplet_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;

	pbMsg.previous.timestamp = inObject->Previous.Timestamp;
	pbMsg.previous.lat = inObject->Previous.Lat;
	pbMsg.previous.lon = inObject->Previous.Lon;
	pbMsg.previous.x = inObject->Previous.X;
	pbMsg.previous.y = inObject->Previous.Y;
	pbMsg.previous.z = inObject->Previous.Z;
	pbMsg.previous.vx = inObject->Previous.VX;
	pbMsg.previous.vy = inObject->Previous.VY;
	pbMsg.previous.vz = inObject->Previous.VZ;
	pbMsg.previous.alt = inObject->Previous.Alt;
	pbMsg.previous.yaw = inObject->Previous.Yaw;
	pbMsg.previous.yawspeed = inObject->Previous.Yawspeed;
	pbMsg.previous.loiter_radius = inObject->Previous.LoiterRadius;
	pbMsg.previous.pitch_min = inObject->Previous.PitchMin;
	pbMsg.previous.a_x = inObject->Previous.A_X;
	pbMsg.previous.a_y = inObject->Previous.A_Y;
	pbMsg.previous.a_z = inObject->Previous.A_Z;
	pbMsg.previous.acceptance_radius = inObject->Previous.AcceptanceRadius;
	pbMsg.previous.cruising_speed = inObject->Previous.CruisingSpeed;
	pbMsg.previous.cruising_throttle = inObject->Previous.CruisingThrottle;
	pbMsg.previous.valid = inObject->Previous.Valid;
	pbMsg.previous.type = inObject->Previous.Type;
	pbMsg.previous.position_valid = inObject->Previous.PositionValid;
	pbMsg.previous.velocity_valid = inObject->Previous.VelocityValid;
	pbMsg.previous.velocity_frame = inObject->Previous.VelocityFrame;
	pbMsg.previous.alt_valid = inObject->Previous.AltValid;
	pbMsg.previous.yaw_valid = inObject->Previous.YawValid;
	pbMsg.previous.disable_mc_yaw_control = inObject->Previous.DisableMcYawControl;
	pbMsg.previous.yawspeed_valid = inObject->Previous.YawspeedValid;
	pbMsg.previous.loiter_direction = inObject->Previous.LoiterDirection;
	pbMsg.previous.acceleration_valid = inObject->Previous.AccelerationValid;
	pbMsg.previous.acceleration_is_force = inObject->Previous.AccelerationIsForce;

	pbMsg.current.timestamp = inObject->Current.Timestamp;
	pbMsg.current.lat = inObject->Current.Lat;
	pbMsg.current.lon = inObject->Current.Lon;
	pbMsg.current.x = inObject->Current.X;
	pbMsg.current.y = inObject->Current.Y;
	pbMsg.current.z = inObject->Current.Z;
	pbMsg.current.vx = inObject->Current.VX;
	pbMsg.current.vy = inObject->Current.VY;
	pbMsg.current.vz = inObject->Current.VZ;
	pbMsg.current.alt = inObject->Current.Alt;
	pbMsg.current.yaw = inObject->Current.Yaw;
	pbMsg.current.yawspeed = inObject->Current.Yawspeed;
	pbMsg.current.loiter_radius = inObject->Current.LoiterRadius;
	pbMsg.current.pitch_min = inObject->Current.PitchMin;
	pbMsg.current.a_x = inObject->Current.A_X;
	pbMsg.current.a_y = inObject->Current.A_Y;
	pbMsg.current.a_z = inObject->Current.A_Z;
	pbMsg.current.acceptance_radius = inObject->Current.AcceptanceRadius;
	pbMsg.current.cruising_speed = inObject->Current.CruisingSpeed;
	pbMsg.current.cruising_throttle = inObject->Current.CruisingThrottle;
	pbMsg.current.valid = inObject->Current.Valid;
	pbMsg.current.type = inObject->Current.Type;
	pbMsg.current.position_valid = inObject->Current.PositionValid;
	pbMsg.current.velocity_valid = inObject->Current.VelocityValid;
	pbMsg.current.velocity_frame = inObject->Current.VelocityFrame;
	pbMsg.current.alt_valid = inObject->Current.AltValid;
	pbMsg.current.yaw_valid = inObject->Current.YawValid;
	pbMsg.current.disable_mc_yaw_control = inObject->Current.DisableMcYawControl;
	pbMsg.current.yawspeed_valid = inObject->Current.YawspeedValid;
	pbMsg.current.loiter_direction = inObject->Current.LoiterDirection;
	pbMsg.current.acceleration_valid = inObject->Current.AccelerationValid;
	pbMsg.current.acceleration_is_force = inObject->Current.AccelerationIsForce;

	pbMsg.next.timestamp = inObject->Next.Timestamp;
	pbMsg.next.lat = inObject->Next.Lat;
	pbMsg.next.lon = inObject->Next.Lon;
	pbMsg.next.x = inObject->Next.X;
	pbMsg.next.y = inObject->Next.Y;
	pbMsg.next.z = inObject->Next.Z;
	pbMsg.next.vx = inObject->Next.VX;
	pbMsg.next.vy = inObject->Next.VY;
	pbMsg.next.vz = inObject->Next.VZ;
	pbMsg.next.alt = inObject->Next.Alt;
	pbMsg.next.yaw = inObject->Next.Yaw;
	pbMsg.next.yawspeed = inObject->Next.Yawspeed;
	pbMsg.next.loiter_radius = inObject->Next.LoiterRadius;
	pbMsg.next.pitch_min = inObject->Next.PitchMin;
	pbMsg.next.a_x = inObject->Next.A_X;
	pbMsg.next.a_y = inObject->Next.A_Y;
	pbMsg.next.a_z = inObject->Next.A_Z;
	pbMsg.next.acceptance_radius = inObject->Next.AcceptanceRadius;
	pbMsg.next.cruising_speed = inObject->Next.CruisingSpeed;
	pbMsg.next.cruising_throttle = inObject->Next.CruisingThrottle;
	pbMsg.next.valid = inObject->Next.Valid;
	pbMsg.next.type = inObject->Next.Type;
	pbMsg.next.position_valid = inObject->Next.PositionValid;
	pbMsg.next.velocity_valid = inObject->Next.VelocityValid;
	pbMsg.next.velocity_frame = inObject->Next.VelocityFrame;
	pbMsg.next.alt_valid = inObject->Next.AltValid;
	pbMsg.next.yaw_valid = inObject->Next.YawValid;
	pbMsg.next.disable_mc_yaw_control = inObject->Next.DisableMcYawControl;
	pbMsg.next.yawspeed_valid = inObject->Next.YawspeedValid;
	pbMsg.next.loiter_direction = inObject->Next.LoiterDirection;
	pbMsg.next.acceleration_valid = inObject->Next.AccelerationValid;
	pbMsg.next.acceleration_is_force = inObject->Next.AccelerationIsForce;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_position_setpoint_triplet_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_PositionSetpointTriplet_Dec(const char *inBuffer, uint32 inSize, PX4_PositionSetpointTripletMsg_t *inOutObject)
{
	bool status = false;
	px4_position_setpoint_triplet_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_position_setpoint_triplet_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;

	inOutObject->Previous.Timestamp = pbMsg.previous.timestamp;
	inOutObject->Previous.Lat = pbMsg.previous.lat;
	inOutObject->Previous.Lon = pbMsg.previous.lon;
	inOutObject->Previous.X = pbMsg.previous.x;
	inOutObject->Previous.Y = pbMsg.previous.y;
	inOutObject->Previous.Z = pbMsg.previous.z;
	inOutObject->Previous.VX = pbMsg.previous.vx;
	inOutObject->Previous.VY = pbMsg.previous.vy;
	inOutObject->Previous.VZ = pbMsg.previous.vz;
	inOutObject->Previous.Alt = pbMsg.previous.alt;
	inOutObject->Previous.Yaw = pbMsg.previous.yaw;
	inOutObject->Previous.Yawspeed = pbMsg.previous.yawspeed;
	inOutObject->Previous.LoiterRadius = pbMsg.previous.loiter_radius;
	inOutObject->Previous.PitchMin = pbMsg.previous.pitch_min;
	inOutObject->Previous.A_X = pbMsg.previous.a_x;
	inOutObject->Previous.A_Y = pbMsg.previous.a_y;
	inOutObject->Previous.A_Z = pbMsg.previous.a_z;
	inOutObject->Previous.AcceptanceRadius = pbMsg.previous.acceptance_radius;
	inOutObject->Previous.CruisingSpeed = pbMsg.previous.cruising_speed;
	inOutObject->Previous.CruisingThrottle = pbMsg.previous.cruising_throttle;
	inOutObject->Previous.Valid = pbMsg.previous.valid;
	inOutObject->Previous.Type = pbMsg.previous.type;
	inOutObject->Previous.PositionValid = pbMsg.previous.position_valid;
	inOutObject->Previous.VelocityValid = pbMsg.previous.velocity_valid;
	inOutObject->Previous.VelocityFrame = pbMsg.previous.velocity_frame;
	inOutObject->Previous.AltValid = pbMsg.previous.alt_valid;
	inOutObject->Previous.YawValid = pbMsg.previous.yaw_valid;
	inOutObject->Previous.DisableMcYawControl = pbMsg.previous.disable_mc_yaw_control;
	inOutObject->Previous.YawspeedValid = pbMsg.previous.yawspeed_valid;
	inOutObject->Previous.LoiterDirection = pbMsg.previous.loiter_direction;
	inOutObject->Previous.AccelerationValid = pbMsg.previous.acceleration_valid;
	inOutObject->Previous.AccelerationIsForce = pbMsg.previous.acceleration_is_force;

	inOutObject->Current.Timestamp = pbMsg.current.timestamp;
	inOutObject->Current.Lat = pbMsg.current.lat;
	inOutObject->Current.Lon = pbMsg.current.lon;
	inOutObject->Current.X = pbMsg.current.x;
	inOutObject->Current.Y = pbMsg.current.y;
	inOutObject->Current.Z = pbMsg.current.z;
	inOutObject->Current.VX = pbMsg.current.vx;
	inOutObject->Current.VY = pbMsg.current.vy;
	inOutObject->Current.VZ = pbMsg.current.vz;
	inOutObject->Current.Alt = pbMsg.current.alt;
	inOutObject->Current.Yaw = pbMsg.current.yaw;
	inOutObject->Current.Yawspeed = pbMsg.current.yawspeed;
	inOutObject->Current.LoiterRadius = pbMsg.current.loiter_radius;
	inOutObject->Current.PitchMin = pbMsg.current.pitch_min;
	inOutObject->Current.A_X = pbMsg.current.a_x;
	inOutObject->Current.A_Y = pbMsg.current.a_y;
	inOutObject->Current.A_Z = pbMsg.current.a_z;
	inOutObject->Current.AcceptanceRadius = pbMsg.current.acceptance_radius;
	inOutObject->Current.CruisingSpeed = pbMsg.current.cruising_speed;
	inOutObject->Current.CruisingThrottle = pbMsg.current.cruising_throttle;
	inOutObject->Current.Valid = pbMsg.current.valid;
	inOutObject->Current.Type = pbMsg.current.type;
	inOutObject->Current.PositionValid = pbMsg.current.position_valid;
	inOutObject->Current.VelocityValid = pbMsg.current.velocity_valid;
	inOutObject->Current.VelocityFrame = pbMsg.current.velocity_frame;
	inOutObject->Current.AltValid = pbMsg.current.alt_valid;
	inOutObject->Current.YawValid = pbMsg.current.yaw_valid;
	inOutObject->Current.DisableMcYawControl = pbMsg.current.disable_mc_yaw_control;
	inOutObject->Current.YawspeedValid = pbMsg.current.yawspeed_valid;
	inOutObject->Current.LoiterDirection = pbMsg.current.loiter_direction;
	inOutObject->Current.AccelerationValid = pbMsg.current.acceleration_valid;
	inOutObject->Current.AccelerationIsForce = pbMsg.current.acceleration_is_force;

	inOutObject->Next.Timestamp = pbMsg.next.timestamp;
	inOutObject->Next.Lat = pbMsg.next.lat;
	inOutObject->Next.Lon = pbMsg.next.lon;
	inOutObject->Next.X = pbMsg.next.x;
	inOutObject->Next.Y = pbMsg.next.y;
	inOutObject->Next.Z = pbMsg.next.z;
	inOutObject->Next.VX = pbMsg.next.vx;
	inOutObject->Next.VY = pbMsg.next.vy;
	inOutObject->Next.VZ = pbMsg.next.vz;
	inOutObject->Next.Alt = pbMsg.next.alt;
	inOutObject->Next.Yaw = pbMsg.next.yaw;
	inOutObject->Next.Yawspeed = pbMsg.next.yawspeed;
	inOutObject->Next.LoiterRadius = pbMsg.next.loiter_radius;
	inOutObject->Next.PitchMin = pbMsg.next.pitch_min;
	inOutObject->Next.A_X = pbMsg.next.a_x;
	inOutObject->Next.A_Y = pbMsg.next.a_y;
	inOutObject->Next.A_Z = pbMsg.next.a_z;
	inOutObject->Next.AcceptanceRadius = pbMsg.next.acceptance_radius;
	inOutObject->Next.CruisingSpeed = pbMsg.next.cruising_speed;
	inOutObject->Next.CruisingThrottle = pbMsg.next.cruising_throttle;
	inOutObject->Next.Valid = pbMsg.next.valid;
	inOutObject->Next.Type = pbMsg.next.type;
	inOutObject->Next.PositionValid = pbMsg.next.position_valid;
	inOutObject->Next.VelocityValid = pbMsg.next.velocity_valid;
	inOutObject->Next.VelocityFrame = pbMsg.next.velocity_frame;
	inOutObject->Next.AltValid = pbMsg.next.alt_valid;
	inOutObject->Next.YawValid = pbMsg.next.yaw_valid;
	inOutObject->Next.DisableMcYawControl = pbMsg.next.disable_mc_yaw_control;
	inOutObject->Next.YawspeedValid = pbMsg.next.yawspeed_valid;
	inOutObject->Next.LoiterDirection = pbMsg.next.loiter_direction;
	inOutObject->Next.AccelerationValid = pbMsg.next.acceleration_valid;
	inOutObject->Next.AccelerationIsForce = pbMsg.next.acceleration_is_force;

	return sizeof(PX4_PositionSetpointTripletMsg_t);
}


uint32 PX4BR_PwmInput_Enc(const PX4_PwmInputMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_pwm_input_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.pulse_width = inObject->PulseWidth;
	pbMsg.period = inObject->Period;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_pwm_input_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_PwmInput_Dec(const char *inBuffer, uint32 inSize, PX4_PwmInputMsg_t *inOutObject)
{
	bool status = false;
	px4_pwm_input_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_pwm_input_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->PulseWidth = pbMsg.pulse_width;
	inOutObject->Period = pbMsg.period;

	return sizeof(PX4_PwmInputMsg_t);
}


uint32 PX4BR_QShellReq_Enc(const PX4_QShellReqMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_QShellReq_Dec(const char *inBuffer, uint32 inSize, PX4_QShellReqMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_RcChannels_Enc(const PX4_RcChannelsMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t iChannel = 0;
	uint32_t iFunction = 0;
	bool status = false;
	px4_rc_channels_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.timestamp_last_valid = inObject->TimestampLastValid;
	for(iChannel = 0; iChannel < PX4_RC_INPUT_MAX_CHANNELS; ++iChannel)
	{
		pbMsg.channels[iChannel] = inObject->Channels[iChannel];
	}
	pbMsg.channels_count = PX4_RC_INPUT_MAX_CHANNELS;
	pbMsg.frame_drop_count = inObject->FrameDropCount;
	pbMsg.channel_count = inObject->ChannelCount;
	for(iFunction = 0; iFunction < 22; ++iFunction)
	{
		pbMsg.function[iFunction] = inObject->Function[iFunction];
	}
	pbMsg.function_count = 22;
	pbMsg.rssi = inObject->RSSI;
	pbMsg.signal_lost = inObject->SignalLost;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_rc_channels_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_RcChannels_Dec(const char *inBuffer, uint32 inSize, PX4_RcChannelsMsg_t *inOutObject)
{
	uint32_t iChannel = 0;
	uint32_t iFunction = 0;
	bool status = false;
	px4_rc_channels_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_rc_channels_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	//OutObject->timestamp = pbMsg.timestamp;
	//inOutObject->timestamp_last_valid = pbMsg.timestamp_last_valid;
	for(iChannel = 0; iChannel < PX4_RC_INPUT_MAX_CHANNELS; ++iChannel)
	{
		inOutObject->Channels[iChannel] = pbMsg.channels[iChannel];
	}
	inOutObject->FrameDropCount = pbMsg.frame_drop_count;
	inOutObject->ChannelCount = pbMsg.channel_count;
	for(iFunction = 0; iFunction < 22; ++iFunction)
	{
		inOutObject->Function[iFunction] = pbMsg.function[iFunction];
	}
	inOutObject->RSSI = pbMsg.rssi;
	inOutObject->SignalLost = pbMsg.signal_lost;

	return sizeof(PX4_RcChannelsMsg_t);
}


uint32 PX4BR_RcParameterMap_Enc(const PX4_RcParameterMapMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_RcParameterMap_Dec(const char *inBuffer, uint32 inSize, PX4_RcParameterMapMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_Safety_Enc(const PX4_SafetyMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_safety_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.safety_switch_available = inObject->SafetySwitchAvailable;
	pbMsg.safety_off = inObject->SafetyOff;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_safety_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_Safety_Dec(const char *inBuffer, uint32 inSize, PX4_SafetyMsg_t *inOutObject)
{
	bool status = false;
	px4_safety_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_safety_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SafetySwitchAvailable = pbMsg.safety_switch_available;
	inOutObject->SafetyOff = pbMsg.safety_off;

	return sizeof(PX4_SafetyMsg_t);
}


uint32 PX4BR_SatelliteInfo_Enc(const PX4_SatelliteInfoMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	uint32_t i = 0;
	bool status = false;
	px4_satellite_info_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.count = inObject->Count;
	pbMsg.svid_count = PX4_SAT_INFO_MAX_SATELLITES;
	pbMsg.used_count = PX4_SAT_INFO_MAX_SATELLITES;
	pbMsg.elevation_count = PX4_SAT_INFO_MAX_SATELLITES;
	pbMsg.azimuth_count = PX4_SAT_INFO_MAX_SATELLITES;
	pbMsg.snr_count = PX4_SAT_INFO_MAX_SATELLITES;
	for(i = 0; i < PX4_SAT_INFO_MAX_SATELLITES; ++i)
	{
		pbMsg.svid[i] = inObject->SVID[i];
		pbMsg.used[i] = inObject->Used[i];
		pbMsg.elevation[i] = inObject->Elevation[i];
		pbMsg.azimuth[i] = inObject->Azimuth[i];
		pbMsg.snr[i] = inObject->SNR[i];
	}

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_satellite_info_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SatelliteInfo_Dec(const char *inBuffer, uint32 inSize, PX4_SatelliteInfoMsg_t *inOutObject)
{
	uint32_t i = 0;
	bool status = false;
	px4_satellite_info_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_satellite_info_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Count = pbMsg.count;
	for(i = 0; i < pbMsg.svid_count; ++i)
	{
		inOutObject->SVID[i] = pbMsg.svid[i];
	}

	for(i = 0; i < pbMsg.used_count; ++i)
	{
		inOutObject->Used[i] = pbMsg.used[i];
	}

	for(i = 0; i < pbMsg.elevation_count; ++i)
	{
		inOutObject->Elevation[i] = pbMsg.elevation[i];
	}

	for(i = 0; i < pbMsg.azimuth_count; ++i)
	{
		inOutObject->Azimuth[i] = pbMsg.azimuth[i];
	}

	for(i = 0; i < pbMsg.snr_count; ++i)
	{
		inOutObject->SNR[i] = pbMsg.snr[i];
	}

	return sizeof(PX4_SatelliteInfoMsg_t);
}


uint32 PX4BR_SensorAccel_Enc(const PX4_SensorAccelMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.integral_dt = inObject->IntegralDt;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.x_integral = inObject->XIntegral;
	pbMsg.y_integral = inObject->YIntegral;
	pbMsg.z_integral = inObject->ZIntegral;
	pbMsg.temperature = inObject->Temperature;
	pbMsg.range_m_s2 = inObject->Range_m_s2;
	pbMsg.scaling = inObject->Scaling;
	pbMsg.device_id = inObject->DeviceID;
	pbMsg.x_raw = inObject->XRaw;
	pbMsg.y_raw = inObject->YRaw;
	pbMsg.z_raw = inObject->ZRaw;
	pbMsg.temperature_raw = inObject->TemperatureRaw;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_accel_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorAccel_Dec(const char *inBuffer, uint32 inSize, PX4_SensorAccelMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_accel_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_accel_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->IntegralDt = pbMsg.integral_dt;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->XIntegral = pbMsg.x_integral;
	inOutObject->YIntegral = pbMsg.y_integral;
	inOutObject->ZIntegral = pbMsg.z_integral;
	inOutObject->Temperature = pbMsg.temperature;
	inOutObject->Range_m_s2 = pbMsg.range_m_s2;
	inOutObject->Scaling = pbMsg.scaling;
	inOutObject->DeviceID = pbMsg.device_id;
	inOutObject->XRaw = pbMsg.x_raw;
	inOutObject->YRaw = pbMsg.y_raw;
	inOutObject->ZRaw = pbMsg.z_raw;
	inOutObject->TemperatureRaw = pbMsg.temperature_raw;

	return sizeof(PX4_SensorAccelMsg_t);
}


uint32 PX4BR_SensorBaro_Enc(const PX4_SensorBaroMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_baro_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.pressure = inObject->Pressure;
	pbMsg.altitude = inObject->Altitude;
	pbMsg.temperature = inObject->Temperature;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_baro_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorBaro_Dec(const char *inBuffer, uint32 inSize, PX4_SensorBaroMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_baro_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_baro_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->Pressure = pbMsg.pressure;
	inOutObject->Altitude = pbMsg.altitude;
	inOutObject->Temperature = pbMsg.temperature;

	return sizeof(PX4_SensorBaroMsg_t);
}


uint32 PX4BR_SensorCombined_Enc(const PX4_SensorCombinedMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_combined_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.gyro_rad_count = 3;
	pbMsg.gyro_rad[0] = inObject->GyroRad[0];
	pbMsg.gyro_rad[1] = inObject->GyroRad[1];
	pbMsg.gyro_rad[2] = inObject->GyroRad[2];
	pbMsg.gyro_integral_dt = inObject->GyroIntegralDt;
	pbMsg.accelerometer_timestamp_relative = inObject->AccTimestampRelative;
	pbMsg.accelerometer_m_s2_count = 3;
	pbMsg.accelerometer_m_s2[0] = inObject->Acc[0];
	pbMsg.accelerometer_m_s2[1] = inObject->Acc[1];
	pbMsg.accelerometer_m_s2[2] = inObject->Acc[2];
	pbMsg.accelerometer_integral_dt = inObject->AccIntegralDt;
	pbMsg.magnetometer_timestamp_relative = inObject->MagTimestampRelative;
	pbMsg.magnetometer_ga_count = 3;
	pbMsg.magnetometer_ga[0] = inObject->Mag[0];
	pbMsg.magnetometer_ga[1] = inObject->Mag[1];
	pbMsg.magnetometer_ga[2] = inObject->Mag[2];
	pbMsg.baro_timestamp_relative = inObject->BaroTimestampRelative;
	pbMsg.baro_alt_meter = inObject->BaroAlt;
	pbMsg.baro_temp_celcius = inObject->BaroTemp;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_combined_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorCombined_Dec(const char *inBuffer, uint32 inSize, PX4_SensorCombinedMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_combined_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_combined_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->GyroRad[0] = pbMsg.gyro_rad[0];
	inOutObject->GyroRad[1] = pbMsg.gyro_rad[1];
	inOutObject->GyroRad[2] = pbMsg.gyro_rad[2];
	inOutObject->GyroIntegralDt = pbMsg.gyro_integral_dt;
	inOutObject->AccTimestampRelative = pbMsg.accelerometer_timestamp_relative;
	inOutObject->Acc[0] = pbMsg.accelerometer_m_s2[0];
	inOutObject->Acc[1] = pbMsg.accelerometer_m_s2[1];
	inOutObject->Acc[2] = pbMsg.accelerometer_m_s2[2];
	inOutObject->AccIntegralDt = pbMsg.accelerometer_integral_dt;
	inOutObject->MagTimestampRelative = pbMsg.magnetometer_timestamp_relative;
	inOutObject->Mag[0] = pbMsg.magnetometer_ga[0];
	inOutObject->Mag[1] = pbMsg.magnetometer_ga[1];
	inOutObject->Mag[2] = pbMsg.magnetometer_ga[2];
	inOutObject->BaroTimestampRelative = pbMsg.baro_timestamp_relative;
	inOutObject->BaroAlt = pbMsg.baro_alt_meter;
	inOutObject->BaroTemp = pbMsg.baro_temp_celcius;

	return sizeof(PX4_SensorCombinedMsg_t);
}


uint32 PX4BR_SensorCorrection_Enc(const PX4_SensorCorrectionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_correction_pb pbMsg;
	CFE_TIME_SysTime_t timestamp;

	timestamp = CFE_SB_GetMsgTime((CFE_SB_MsgPtr_t)inObject);

	pbMsg.gyro_offset_0_count = 3;
	pbMsg.gyro_offset_0[0] = inObject->gyro_offset_0[0];
	pbMsg.gyro_offset_0[1] = inObject->gyro_offset_0[1];
	pbMsg.gyro_offset_0[2] = inObject->gyro_offset_0[2];
	pbMsg.gyro_offset_1_count = 3;
	pbMsg.gyro_offset_1[0] = inObject->gyro_offset_1[0];
	pbMsg.gyro_offset_1[1] = inObject->gyro_offset_1[1];
	pbMsg.gyro_offset_1[2] = inObject->gyro_offset_1[2];
	pbMsg.gyro_offset_2_count = 3;
	pbMsg.gyro_offset_2[0] = inObject->gyro_offset_2[0];
	pbMsg.gyro_offset_2[1] = inObject->gyro_offset_2[1];
	pbMsg.gyro_offset_2[2] = inObject->gyro_offset_2[2];

	pbMsg.gyro_scale_0_count = 3;
	pbMsg.gyro_scale_0[0] = inObject->gyro_scale_0[0];
	pbMsg.gyro_scale_0[1] = inObject->gyro_scale_0[1];
	pbMsg.gyro_scale_0[2] = inObject->gyro_scale_0[2];
	pbMsg.gyro_scale_1_count = 3;
	pbMsg.gyro_scale_1[0] = inObject->gyro_scale_1[0];
	pbMsg.gyro_scale_1[1] = inObject->gyro_scale_1[1];
	pbMsg.gyro_scale_1[2] = inObject->gyro_scale_1[2];
	pbMsg.gyro_scale_2_count = 3;
	pbMsg.gyro_scale_2[0] = inObject->gyro_scale_2[0];
	pbMsg.gyro_scale_2[1] = inObject->gyro_scale_2[1];
	pbMsg.gyro_scale_2[2] = inObject->gyro_scale_2[2];

	pbMsg.accel_offset_0_count = 3;
	pbMsg.accel_offset_0[0] = inObject->accel_offset_0[0];
	pbMsg.accel_offset_0[1] = inObject->accel_offset_0[1];
	pbMsg.accel_offset_0[2] = inObject->accel_offset_0[2];
	pbMsg.accel_offset_1_count = 3;
	pbMsg.accel_offset_1[0] = inObject->accel_offset_1[0];
	pbMsg.accel_offset_1[1] = inObject->accel_offset_1[1];
	pbMsg.accel_offset_1[2] = inObject->accel_offset_1[2];
	pbMsg.accel_offset_2_count = 3;
	pbMsg.accel_offset_2[0] = inObject->accel_offset_2[0];
	pbMsg.accel_offset_2[1] = inObject->accel_offset_2[1];
	pbMsg.accel_offset_2[2] = inObject->accel_offset_2[2];
	pbMsg.accel_scale_0_count = 3;
	pbMsg.accel_scale_0[0] = inObject->accel_scale_0[0];
	pbMsg.accel_scale_0[1] = inObject->accel_scale_0[1];
	pbMsg.accel_scale_0[2] = inObject->accel_scale_0[2];
	pbMsg.accel_scale_1_count = 3;
	pbMsg.accel_scale_1[0] = inObject->accel_scale_1[0];
	pbMsg.accel_scale_1[1] = inObject->accel_scale_1[1];
	pbMsg.accel_scale_1[2] = inObject->accel_scale_1[2];
	pbMsg.accel_scale_2_count = 3;
	pbMsg.accel_scale_2[0] = inObject->accel_scale_2[0];
	pbMsg.accel_scale_2[1] = inObject->accel_scale_2[1];
	pbMsg.accel_scale_2[2] = inObject->accel_scale_2[2];

	pbMsg.baro_offset_0 = inObject->baro_offset_0;
	pbMsg.baro_offset_0 = inObject->baro_offset_0;
	pbMsg.baro_offset_0 = inObject->baro_offset_0;
	pbMsg.baro_offset_1 = inObject->baro_offset_1;
	pbMsg.baro_offset_1 = inObject->baro_offset_1;
	pbMsg.baro_offset_1 = inObject->baro_offset_1;
	pbMsg.baro_offset_2 = inObject->baro_offset_2;
	pbMsg.baro_offset_2 = inObject->baro_offset_2;
	pbMsg.baro_offset_2 = inObject->baro_offset_2;

	pbMsg.baro_scale_0 = inObject->baro_scale_0;
	pbMsg.baro_scale_0 = inObject->baro_scale_0;
	pbMsg.baro_scale_0 = inObject->baro_scale_0;
	pbMsg.baro_scale_1 = inObject->baro_scale_1;
	pbMsg.baro_scale_1 = inObject->baro_scale_1;
	pbMsg.baro_scale_1 = inObject->baro_scale_1;
	pbMsg.baro_scale_2 = inObject->baro_scale_2;
	pbMsg.baro_scale_2 = inObject->baro_scale_2;
	pbMsg.baro_scale_2 = inObject->baro_scale_2;

	pbMsg.selected_gyro_instance = inObject->selected_gyro_instance;
	pbMsg.selected_accel_instance = inObject->selected_accel_instance;
	pbMsg.selected_baro_instance = inObject->selected_baro_instance;

	pbMsg.gyro_mapping_count = 3;
	pbMsg.gyro_mapping[0] = inObject->gyro_mapping[0];
	pbMsg.gyro_mapping[1] = inObject->gyro_mapping[1];
	pbMsg.gyro_mapping[2] = inObject->gyro_mapping[2];

	pbMsg.accel_mapping_count = 3;
	pbMsg.accel_mapping[0] = inObject->accel_mapping[0];
	pbMsg.accel_mapping[1] = inObject->accel_mapping[1];
	pbMsg.accel_mapping[2] = inObject->accel_mapping[2];

	pbMsg.baro_mapping_count = 3;
	pbMsg.baro_mapping[0] = inObject->baro_mapping[0];
	pbMsg.baro_mapping[1] = inObject->baro_mapping[1];
	pbMsg.baro_mapping[2] = inObject->baro_mapping[2];

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_combined_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorCorrection_Dec(const char *inBuffer, uint32 inSize, PX4_SensorCorrectionMsg_t *inOutObject)
{
//	bool status = false;
//	px4_sensor_combined_pb pbMsg;
//
//	/* Create a stream that reads from the buffer. */
//	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);
//
//	/* Now we are ready to decode the message. */
//	status = pb_decode(&stream, px4_sensor_combined_pb_fields, &pbMsg);
//
//	/* Check for errors... */
//	if (!status)
//	{
//		return 0;
//	}
//
//	inOutObject->Timestamp = pbMsg.timestamp;
//	inOutObject->GyroRad[0] = pbMsg.gyro_rad[0];
//	inOutObject->GyroRad[1] = pbMsg.gyro_rad[1];
//	inOutObject->GyroRad[2] = pbMsg.gyro_rad[2];
//	inOutObject->GyroIntegralDt = pbMsg.gyro_integral_dt;
//	//inOutObject->accelerometer_timestamp_relative = pbMsg.accelerometer_timestamp_relative;
//	inOutObject->Acc[0] = pbMsg.accelerometer_m_s2[0];
//	inOutObject->Acc[1] = pbMsg.accelerometer_m_s2[1];
//	inOutObject->Acc[2] = pbMsg.accelerometer_m_s2[2];
//	inOutObject->AccIntegralDt = pbMsg.accelerometer_integral_dt;
//	//inOutObject->magnetometer_timestamp_relative = pbMsg.magnetometer_timestamp_relative;
//	inOutObject->Mag[0] = pbMsg.magnetometer_ga[0];
//	inOutObject->Mag[1] = pbMsg.magnetometer_ga[1];
//	inOutObject->Mag[2] = pbMsg.magnetometer_ga[2];
//	//inOutObject->baro_timestamp_relative = pbMsg.baro_timestamp_relative;
//	inOutObject->BaroAlt = pbMsg.baro_alt_meter;
//	inOutObject->BaroTemp = pbMsg.baro_temp_celcius;

	return sizeof(PX4_SensorCombinedMsg_t);
}


uint32 PX4BR_SensorGyro_Enc(const PX4_SensorGyroMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_gyro_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.integral_dt = inObject->IntegralDt;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.x_integral = inObject->XIntegral;
	pbMsg.y_integral = inObject->YIntegral;
	pbMsg.z_integral = inObject->ZIntegral;
	pbMsg.temperature = inObject->Temperature;
	pbMsg.range_rad_s = inObject->Range;
	pbMsg.scaling = inObject->Scaling;
	pbMsg.device_id = inObject->DeviceID;
	pbMsg.x_raw = inObject->XRaw;
	pbMsg.y_raw = inObject->YRaw;
	pbMsg.z_raw = inObject->ZRaw;
	pbMsg.temperature_raw = inObject->TemperatureRaw;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_gyro_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorGyro_Dec(const char *inBuffer, uint32 inSize, PX4_SensorGyroMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_gyro_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_gyro_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->IntegralDt = pbMsg.integral_dt;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->XIntegral = pbMsg.x_integral;
	inOutObject->YIntegral = pbMsg.y_integral;
	inOutObject->ZIntegral = pbMsg.z_integral;
	inOutObject->Temperature = pbMsg.temperature;
	inOutObject->Range = pbMsg.range_rad_s;
	inOutObject->Scaling = pbMsg.scaling;
	inOutObject->DeviceID = pbMsg.device_id;
	inOutObject->XRaw = pbMsg.x_raw;
	inOutObject->YRaw = pbMsg.y_raw;
	inOutObject->ZRaw = pbMsg.z_raw;
	inOutObject->TemperatureRaw = pbMsg.temperature_raw;

	return sizeof(PX4_SensorGyroMsg_t);
}

uint32 PX4BR_SensorMag_Enc(const PX4_SensorMagMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_sensor_mag_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.error_count = inObject->ErrorCount;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.range_ga = inObject->Range;
	pbMsg.scaling = inObject->Scaling;
	pbMsg.temperature = inObject->Temperature;
	pbMsg.device_id = inObject->DeviceID;
	pbMsg.x_raw = inObject->XRaw;
	pbMsg.y_raw = inObject->YRaw;
	pbMsg.z_raw = inObject->ZRaw;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_sensor_mag_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SensorMag_Dec(const char *inBuffer, uint32 inSize, PX4_SensorMagMsg_t *inOutObject)
{
	bool status = false;
	px4_sensor_mag_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_sensor_mag_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->ErrorCount = pbMsg.error_count;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->Range = pbMsg.range_ga;
	inOutObject->Scaling = pbMsg.scaling;
	inOutObject->Temperature = pbMsg.temperature;
	inOutObject->DeviceID = pbMsg.device_id;
	inOutObject->XRaw = pbMsg.x_raw;
	inOutObject->YRaw = pbMsg.y_raw;
	inOutObject->ZRaw = pbMsg.z_raw;

	return sizeof(PX4_SensorMagMsg_t);
}


uint32 PX4BR_ServorailStatus_Enc(const PX4_ServorailStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_ServorailStatus_Dec(const char *inBuffer, uint32 inSize, PX4_ServorailStatusMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_SubsystemInfo_Enc(const PX4_SubsystemInfoMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_subsystem_info_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.subsystem_type = inObject->SubsystemType;
	pbMsg.present = inObject->Present;
	pbMsg.enabled = inObject->Enabled;
	pbMsg.ok = inObject->Ok;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_subsystem_info_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SubsystemInfo_Dec(const char *inBuffer, uint32 inSize, PX4_SubsystemInfoMsg_t *inOutObject)
{
	bool status = false;
	px4_subsystem_info_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_subsystem_info_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SubsystemType = pbMsg.subsystem_type;
	inOutObject->Present = pbMsg.present;
	inOutObject->Enabled = pbMsg.enabled;
	inOutObject->Ok = pbMsg.ok;

	return sizeof(PX4_SubsystemInfoMsg_t);
}


uint32 PX4BR_SystemPower_Enc(const PX4_SystemPowerMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_system_power_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.voltage5V_v = inObject->Voltage5V;
	pbMsg.usb_connected = inObject->UsbConnected;
	pbMsg.brick_valid = inObject->BrickValid;
	pbMsg.servo_valid = inObject->ServoValid;
	pbMsg.periph_5V_OC = inObject->Periph5V;
	pbMsg.hipower_5V_OC = inObject->HiPower5V;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_system_power_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_SystemPower_Dec(const char *inBuffer, uint32 inSize, PX4_SystemPowerMsg_t *inOutObject)
{
	bool status = false;
	px4_system_power_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_system_power_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Voltage5V = pbMsg.voltage5V_v;
	inOutObject->UsbConnected = pbMsg.usb_connected;
	inOutObject->BrickValid = pbMsg.brick_valid;
	inOutObject->ServoValid = pbMsg.servo_valid;
	inOutObject->Periph5V = pbMsg.periph_5V_OC;
	inOutObject->HiPower5V = pbMsg.hipower_5V_OC;

	return sizeof(PX4_SystemPowerMsg_t);
}


uint32 PX4BR_TecsStatus_Enc(const PX4_TecsStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_tecs_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.altitudeSp = inObject->AltitudeSp;
	pbMsg.altitude_filtered = inObject->AltitudeFiltered;
	pbMsg.flightPathAngleSp = inObject->FlightPathAngleSp;
	pbMsg.flightPathAngle = inObject->FlightPathAngle;
	pbMsg.flightPathAngleFiltered = inObject->FlightPathAngleFiltered;
	pbMsg.airspeedSp = inObject->AirspeedSp;
	pbMsg.airspeed_filtered = inObject->AirspeedFiltered;
	pbMsg.airspeedDerivativeSp = inObject->AirspeedDerivativeSp;
	pbMsg.airspeedDerivative = inObject->AirspeedDerivative;
	pbMsg.totalEnergyError = inObject->TotalEnergyError;
	pbMsg.energyDistributionError = inObject->EnergyDistributionError;
	pbMsg.totalEnergyRateError = inObject->TotalEnergyRateError;
	pbMsg.energyDistributionRateError = inObject->EnergyDistributionRateError;
	pbMsg.throttle_integ = inObject->ThrottleInteg;
	pbMsg.pitch_integ = inObject->PitchInteg;
	pbMsg.mode = inObject->Mode;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_tecs_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_TecsStatus_Dec(const char *inBuffer, uint32 inSize, PX4_TecsStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_tecs_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_tecs_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->AltitudeSp = pbMsg.altitudeSp;
	inOutObject->AltitudeFiltered = pbMsg.altitude_filtered;
	inOutObject->FlightPathAngleSp = pbMsg.flightPathAngleSp;
	inOutObject->FlightPathAngle = pbMsg.flightPathAngle;
	inOutObject->FlightPathAngleFiltered = pbMsg.flightPathAngleFiltered;
	inOutObject->AirspeedSp = pbMsg.airspeedSp;
	inOutObject->AirspeedFiltered = pbMsg.airspeed_filtered;
	inOutObject->AirspeedDerivativeSp = pbMsg.airspeedDerivativeSp;
	inOutObject->AirspeedDerivative = pbMsg.airspeedDerivative;
	inOutObject->TotalEnergyError = pbMsg.totalEnergyError;
	inOutObject->EnergyDistributionError = pbMsg.energyDistributionError;
	inOutObject->TotalEnergyRateError = pbMsg.totalEnergyRateError;
	inOutObject->EnergyDistributionRateError = pbMsg.energyDistributionRateError;
	inOutObject->ThrottleInteg = pbMsg.throttle_integ;
	inOutObject->PitchInteg = pbMsg.pitch_integ;
	inOutObject->Mode = pbMsg.mode;

	return sizeof(PX4_TecsStatusMsg_t);
}


uint32 PX4BR_TelemetryStatus_Enc(const PX4_TelemetryStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_telemetry_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.heartbeat_time = inObject->HeartbeatTime;
	pbMsg.telem_time = inObject->TelemTime;
	pbMsg.rxerrors = inObject->RxErrors;
	pbMsg.fixed = inObject->Fixed;
	pbMsg.type = inObject->Type;
	pbMsg.rssi = inObject->RSSI;
	pbMsg.remote_rssi = inObject->RemoteRSSI;
	pbMsg.noise = inObject->Noise;
	pbMsg.remote_noise = inObject->RemoteNoise;
	pbMsg.txbuf = inObject->TxBuf;
	pbMsg.system_id = inObject->SystemID;
	pbMsg.component_id = inObject->ComponentID;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_telemetry_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_TelemetryStatus_Dec(const char *inBuffer, uint32 inSize, PX4_TelemetryStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_telemetry_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_telemetry_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->HeartbeatTime = pbMsg.heartbeat_time;
	inOutObject->TelemTime = pbMsg.telem_time;
	inOutObject->RxErrors = pbMsg.rxerrors;
	inOutObject->Fixed = pbMsg.fixed;
	inOutObject->Type = pbMsg.type;
	inOutObject->RSSI = pbMsg.rssi;
	inOutObject->RemoteRSSI = pbMsg.remote_rssi;
	inOutObject->Noise = pbMsg.noise;
	inOutObject->RemoteNoise = pbMsg.remote_noise;
	inOutObject->TxBuf = pbMsg.txbuf;
	inOutObject->SystemID = pbMsg.system_id;
	inOutObject->ComponentID = pbMsg.component_id;

	return sizeof(PX4_TelemetryStatusMsg_t);
}


uint32 PX4BR_TestMotor_Enc(const PX4_TestMotorMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_TestMotor_Dec(const char *inBuffer, uint32 inSize, PX4_TestMotorMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_TimeOffset_Enc(const PX4_TimeOffsetMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_time_offset_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.offset_ns = inObject->OffsetNs;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_time_offset_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_TimeOffset_Dec(const char *inBuffer, uint32 inSize, PX4_TimeOffsetMsg_t *inOutObject)
{
	bool status = false;
	px4_time_offset_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_time_offset_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->OffsetNs = pbMsg.offset_ns;

	return sizeof(PX4_TimeOffsetMsg_t);
}


uint32 PX4BR_TransponderReport_Enc(const PX4_TransponderReportMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_TransponderReport_Dec(const char *inBuffer, uint32 inSize, PX4_TransponderReportMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_UavCanParameterRequest_Enc(const PX4_UavCanParameterRequestMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_UavCanParameterRequest_Dec(const char *inBuffer, uint32 inSize, PX4_UavCanParameterRequestMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_UavCanParameterValue_Enc(const PX4_UavCanParameterValueMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_UavCanParameterValue_Dec(const char *inBuffer, uint32 inSize, PX4_UavCanParameterValueMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_VehicleAttitude_Enc(const PX4_VehicleAttitudeMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_attitude_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.rollspeed = inObject->RollSpeed;
	pbMsg.pitchspeed = inObject->PitchSpeed;
	pbMsg.yawspeed = inObject->YawSpeed;
	pbMsg.q_count = 4;
    pbMsg.q[0] = inObject->Q[0];
    pbMsg.q[1] = inObject->Q[1];
    pbMsg.q[2] = inObject->Q[2];
    pbMsg.q[3] = inObject->Q[3];

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_attitude_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleAttitude_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleAttitudeMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_attitude_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_attitude_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RollSpeed = pbMsg.rollspeed;
	inOutObject->PitchSpeed = pbMsg.pitchspeed;
	inOutObject->YawSpeed = pbMsg.yawspeed;
	inOutObject->Q[0] = pbMsg.q[0];
	inOutObject->Q[1] = pbMsg.q[1];
	inOutObject->Q[2] = pbMsg.q[2];
	inOutObject->Q[3] = pbMsg.q[3];

	return sizeof(PX4_VehicleAttitudeMsg_t);
}


uint32 PX4BR_VehicleAttitudeSetpoint_Enc(const PX4_VehicleAttitudeSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_attitude_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll_body = inObject->RollBody;
	pbMsg.pitch_body = inObject->PitchBody;
	pbMsg.yaw_body = inObject->YawBody;
	pbMsg.yaw_sp_move_rate = inObject->YawSpMoveRate;
	pbMsg.q_d_count = 4;
	pbMsg.q_d[0] = inObject->Q_D[0];
	pbMsg.q_d[1] = inObject->Q_D[1];
	pbMsg.q_d[2] = inObject->Q_D[2];
	pbMsg.q_d[3] = inObject->Q_D[3];
    pbMsg.q_d_valid = inObject->Q_D_Valid;
    pbMsg.thrust = inObject->Thrust;
    pbMsg.roll_reset_integral = inObject->RollResetIntegral;
    pbMsg.pitch_reset_integral = inObject->PitchResetIntegral;
	pbMsg.yaw_reset_integral = inObject->YawResetIntegral;
	pbMsg.fw_control_yaw = inObject->FwControlYaw;
	pbMsg.disable_mc_yaw_control = inObject->DisableMcYawControl;
	pbMsg.apply_flaps = inObject->ApplyFlaps;
    pbMsg.landing_gear = inObject->LandingGear;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_attitude_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleAttitudeSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleAttitudeSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_attitude_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_attitude_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RollBody = pbMsg.roll_body;
	inOutObject->PitchBody = pbMsg.pitch_body;
	inOutObject->YawBody = pbMsg.yaw_body;
	inOutObject->YawSpMoveRate = pbMsg.yaw_sp_move_rate;
	inOutObject->Q_D[0] = pbMsg.q_d[0];
	inOutObject->Q_D[1] = pbMsg.q_d[1];
	inOutObject->Q_D[2] = pbMsg.q_d[2];
	inOutObject->Q_D[3] = pbMsg.q_d[3];
    inOutObject->Q_D_Valid = pbMsg.q_d_valid;
	inOutObject->Thrust = pbMsg.thrust;
	inOutObject->RollResetIntegral = pbMsg.roll_reset_integral;
	inOutObject->PitchResetIntegral = pbMsg.pitch_reset_integral;
	inOutObject->YawResetIntegral = pbMsg.yaw_reset_integral;
	inOutObject->FwControlYaw = pbMsg.fw_control_yaw;
	inOutObject->DisableMcYawControl = pbMsg.disable_mc_yaw_control;
	inOutObject->ApplyFlaps = pbMsg.apply_flaps;
    inOutObject->LandingGear = pbMsg.landing_gear;

	return sizeof(PX4_VehicleAttitudeSetpointMsg_t);
}


uint32 PX4BR_VehicleCommandAck_Enc(const PX4_VehicleCommandAckMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_VehicleCommandAck_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleCommandAckMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_VehicleCommand_Enc(const PX4_VehicleCommandMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_command_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.param5 = inObject->Param5;
	pbMsg.param6 = inObject->Param6;
	pbMsg.param1 = inObject->Param1;
	pbMsg.param2 = inObject->Param2;
	pbMsg.param3 = inObject->Param3;
	pbMsg.param4 = inObject->Param4;
	pbMsg.param7 = inObject->Param7;
	pbMsg.command = inObject->Command;
	pbMsg.target_system = inObject->TargetSystem;
	pbMsg.target_component = inObject->TargetComponent;
	pbMsg.source_system = inObject->SourceSystem;
	pbMsg.source_component = inObject->SourceComponent;
	pbMsg.confirmation = inObject->Confirmation;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_command_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleCommand_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleCommandMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_command_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_command_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Param5 = pbMsg.param5;
	inOutObject->Param6 = pbMsg.param6;
	inOutObject->Param1 = pbMsg.param1;
	inOutObject->Param2 = pbMsg.param2;
	inOutObject->Param3 = pbMsg.param3;
	inOutObject->Param4 = pbMsg.param4;
	inOutObject->Param7 = pbMsg.param7;
	inOutObject->Command = pbMsg.command;
	inOutObject->TargetSystem = pbMsg.target_system;
	inOutObject->TargetComponent = pbMsg.target_component;
	inOutObject->SourceSystem = pbMsg.source_system;
	inOutObject->SourceComponent = pbMsg.source_component;
	inOutObject->Confirmation = pbMsg.confirmation;

	return sizeof(PX4_VehicleCommandMsg_t);
}


uint32 PX4BR_VehicleControlMode_Enc(const PX4_VehicleControlModeMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_control_mode_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.flag_armed = inObject->Armed;
	pbMsg.flag_external_manual_override_ok = inObject->ExternalManualOverrideOk;
	pbMsg.flag_system_hil_enabled = inObject->SystemHilEnabled;
	pbMsg.flag_control_manual_enabled = inObject->ControlManualEnabled;
	pbMsg.flag_control_auto_enabled = inObject->ControlAutoEnabled;
	pbMsg.flag_control_offboard_enabled = inObject->ControlOffboardEnabled;
	pbMsg.flag_control_rates_enabled = inObject->ControlRatesEnabled;
	pbMsg.flag_control_attitude_enabled = inObject->ControlAttitudeEnabled;
	pbMsg.flag_control_rattitude_enabled = inObject->ControlRattitudeEnabled;
	pbMsg.flag_control_force_enabled = inObject->ControlForceEnabled;
	pbMsg.flag_control_acceleration_enabled = inObject->ControlAccelerationEnabled;
	pbMsg.flag_control_velocity_enabled = inObject->ControlVelocityEnabled;
	pbMsg.flag_control_position_enabled = inObject->ControlPositionEnabled;
	pbMsg.flag_control_altitude_enabled = inObject->ControlAltitudeEnabled;
	pbMsg.flag_control_climb_rate_enabled = inObject->ControlClimbRateEnabled;
	pbMsg.flag_control_termination_enabled = inObject->ControlTerminationEnabled;
	pbMsg.flag_control_fixed_hdg_enabled = inObject->ControlFixedHdgEnabled;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_control_mode_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleControlMode_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleControlModeMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_control_mode_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_control_mode_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Armed = pbMsg.flag_armed;
	inOutObject->ExternalManualOverrideOk = pbMsg.flag_external_manual_override_ok;
	inOutObject->SystemHilEnabled = pbMsg.flag_system_hil_enabled;
	inOutObject->ControlManualEnabled = pbMsg.flag_control_manual_enabled;
	inOutObject->ControlAutoEnabled = pbMsg.flag_control_auto_enabled;
	inOutObject->ControlOffboardEnabled = pbMsg.flag_control_offboard_enabled;
	inOutObject->ControlRatesEnabled = pbMsg.flag_control_rates_enabled;
	inOutObject->ControlAttitudeEnabled = pbMsg.flag_control_attitude_enabled;
	inOutObject->ControlRattitudeEnabled = pbMsg.flag_control_rattitude_enabled;
	inOutObject->ControlForceEnabled = pbMsg.flag_control_force_enabled;
	inOutObject->ControlAccelerationEnabled = pbMsg.flag_control_acceleration_enabled;
	inOutObject->ControlVelocityEnabled = pbMsg.flag_control_velocity_enabled;
	inOutObject->ControlPositionEnabled = pbMsg.flag_control_position_enabled;
	inOutObject->ControlAltitudeEnabled = pbMsg.flag_control_altitude_enabled;
	inOutObject->ControlClimbRateEnabled = pbMsg.flag_control_climb_rate_enabled;
	inOutObject->ControlTerminationEnabled = pbMsg.flag_control_termination_enabled;
	inOutObject->ControlFixedHdgEnabled = pbMsg.flag_control_fixed_hdg_enabled;

	return sizeof(PX4_VehicleControlModeMsg_t);
}


uint32 PX4BR_VehicleForceSetpoint_Enc(const PX4_VehicleForceSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_force_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.yaw = inObject->Yaw;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_force_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleForceSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleForceSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_force_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_force_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->Yaw = pbMsg.yaw;

	return sizeof(PX4_VehicleForceSetpointMsg_t);
}


uint32 PX4BR_VehicleGlobalPosition_Enc(const PX4_VehicleGlobalPositionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_global_position_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.time_utc_usec = inObject->TimeUtcUsec;
	pbMsg.lat = inObject->Lat;
	pbMsg.lon = inObject->Lon;
	pbMsg.alt = inObject->Alt;
	pbMsg.vel_n = inObject->VelN;
	pbMsg.vel_e = inObject->VelE;
	pbMsg.vel_d = inObject->VelD;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.eph = inObject->EpH;
	pbMsg.epv = inObject->EpV;
	pbMsg.terrain_alt = inObject->TerrainAlt;
	pbMsg.pressure_alt = inObject->PressureAlt;
	pbMsg.terrain_alt_valid = inObject->TerrainAltValid;
	pbMsg.dead_reckoning = inObject->DeadReckoning;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_global_position_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleGlobalPosition_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleGlobalPositionMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_global_position_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_global_position_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->TimeUtcUsec = pbMsg.time_utc_usec;
	inOutObject->Lat = pbMsg.lat;
	inOutObject->Lon = pbMsg.lon;
	inOutObject->Alt = pbMsg.alt;
	inOutObject->VelN = pbMsg.vel_n;
	inOutObject->VelE = pbMsg.vel_e;
	inOutObject->VelD = pbMsg.vel_d;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->EpH = pbMsg.eph;
	inOutObject->EpV = pbMsg.epv;
	inOutObject->TerrainAlt = pbMsg.terrain_alt;
	inOutObject->PressureAlt = pbMsg.pressure_alt;
	inOutObject->TerrainAltValid = pbMsg.terrain_alt_valid;
	inOutObject->DeadReckoning = pbMsg.dead_reckoning;

	return sizeof(PX4_VehicleGlobalPositionMsg_t);
}


uint32 PX4BR_VehicleGlobalVelocitySetpoint_Enc(const PX4_VehicleGlobalVelocitySetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_global_velocity_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.vx = inObject->VX;
	pbMsg.vy = inObject->VY;
	pbMsg.vz = inObject->VZ;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_global_velocity_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleGlobalVelocitySetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleGlobalVelocitySetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_global_velocity_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_global_velocity_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->VX = pbMsg.vx;
	inOutObject->VY = pbMsg.vy;
	inOutObject->VZ = pbMsg.vz;

	return sizeof(PX4_VehicleGlobalVelocitySetpointMsg_t);
}


uint32 PX4BR_VehicleGpsPosition_Enc(const PX4_VehicleGpsPositionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_gps_position_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.time_utc_usec = inObject->TimeUtcUsec;
	pbMsg.lat = inObject->Lat;
	pbMsg.lon = inObject->Lon;
	pbMsg.alt = inObject->Alt;
	pbMsg.alt_ellipsoid = inObject->AltEllipsoid;
	pbMsg.s_variance_m_s = inObject->SVariance;
	pbMsg.c_variance_rad = inObject->CVariance;
	pbMsg.eph = inObject->EpH;
	pbMsg.epv = inObject->EpV;
	pbMsg.hdop = inObject->HDOP;
	pbMsg.vdop = inObject->VDOP;
	pbMsg.noise_per_ms = inObject->NoisePerMs;
	pbMsg.jamming_indicator = inObject->JammingIndicator;
	pbMsg.vel_m_s = inObject->Vel_m_s;
	pbMsg.vel_n_m_s = inObject->Vel_n_m_s;
	pbMsg.vel_e_m_s = inObject->Vel_e_m_s;
	pbMsg.vel_d_m_s = inObject->Vel_d_m_s;
	pbMsg.cog_rad = inObject->COG;
	pbMsg.timestamp_time_relative = inObject->TimestampTimeRelative;
	pbMsg.fix_type = inObject->FixType;
	pbMsg.vel_ned_valid = inObject->VelNedValid;
	pbMsg.satellites_used = inObject->SatellitesUsed;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_gps_position_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleGpsPosition_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleGpsPositionMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_gps_position_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_gps_position_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->TimeUtcUsec = pbMsg.time_utc_usec;
	inOutObject->Lat = pbMsg.lat;
	inOutObject->Lon = pbMsg.lon;
	inOutObject->Alt = pbMsg.alt;
	inOutObject->AltEllipsoid = pbMsg.alt_ellipsoid;
	inOutObject->SVariance = pbMsg.s_variance_m_s;
	inOutObject->CVariance = pbMsg.c_variance_rad;
	inOutObject->EpH = pbMsg.eph;
	inOutObject->EpV = pbMsg.epv;
	inOutObject->HDOP = pbMsg.hdop;
	inOutObject->VDOP = pbMsg.vdop;
	inOutObject->NoisePerMs = pbMsg.noise_per_ms;
	inOutObject->JammingIndicator = pbMsg.jamming_indicator;
	inOutObject->Vel_m_s = pbMsg.vel_m_s;
	inOutObject->Vel_n_m_s = pbMsg.vel_n_m_s;
	inOutObject->Vel_e_m_s = pbMsg.vel_e_m_s;
	inOutObject->Vel_d_m_s = pbMsg.vel_d_m_s;
	inOutObject->COG = pbMsg.cog_rad;
	inOutObject->TimestampTimeRelative = pbMsg.timestamp_time_relative;
	inOutObject->FixType = pbMsg.fix_type;
	inOutObject->VelNedValid = pbMsg.vel_ned_valid;
	inOutObject->SatellitesUsed = pbMsg.satellites_used;

	return sizeof(PX4_VehicleGpsPositionMsg_t);
}


uint32 PX4BR_VehicleLandDetected_Enc(const PX4_VehicleLandDetectedMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_land_detected_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.alt_max = inObject->AltMax;
	pbMsg.landed = inObject->Landed;
	pbMsg.freefall = inObject->Freefall;
	pbMsg.ground_contact = inObject->GroundContact;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_land_detected_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleLandDetected_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleLandDetectedMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_land_detected_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_land_detected_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->AltMax = pbMsg.alt_max;
	inOutObject->Landed = pbMsg.landed;
	inOutObject->Freefall = pbMsg.freefall;
	inOutObject->GroundContact = pbMsg.ground_contact;

	return sizeof(PX4_VehicleLandDetectedMsg_t);
}


uint32 PX4BR_VehicleLocalPosition_Enc(const PX4_VehicleLocalPositionMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_local_position_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.ref_timestamp = inObject->RefTimestamp;
	pbMsg.ref_lat = inObject->RefLat;
	pbMsg.ref_lon = inObject->RefLon;
	pbMsg.surface_bottom_timestamp = inObject->SurfaceBottomTimestamp;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.delta_xy_count = 2;
	pbMsg.delta_xy[0] = inObject->Delta_XY[0];
	pbMsg.delta_xy[1] = inObject->Delta_XY[1];
	pbMsg.delta_z = inObject->Delta_Z;
	pbMsg.vx = inObject->VX;
	pbMsg.vy = inObject->VY;
	pbMsg.vz = inObject->VZ;
	pbMsg.delta_vxy_count = 2;
	pbMsg.delta_vxy[0] = inObject->Delta_VXY[0];
	pbMsg.delta_vxy[1] = inObject->Delta_VXY[1];
	pbMsg.delta_vz = inObject->Delta_VZ;
	pbMsg.ax = inObject->AX;
	pbMsg.ay = inObject->AY;
	pbMsg.az = inObject->AZ;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.ref_alt = inObject->RefAlt;
	pbMsg.dist_bottom = inObject->DistBottom;
	pbMsg.dist_bottom_rate = inObject->DistBottomRate;
	pbMsg.eph = inObject->EpH;
	pbMsg.epv = inObject->EpV;
	pbMsg.evh = inObject->EvH;
	pbMsg.evv = inObject->EvV;
	pbMsg.estimator_type = inObject->EstimatorType;
	pbMsg.xy_valid = inObject->XY_Valid;
	pbMsg.z_valid = inObject->Z_Valid;
	pbMsg.v_xy_valid = inObject->V_XY_Valid;
	pbMsg.v_z_valid = inObject->V_Z_Valid;
	pbMsg.xy_reset_counter = inObject->XY_ResetCounter;
	pbMsg.z_reset_counter = inObject->Z_ResetCounter;
	pbMsg.vxy_reset_counter = inObject->VXY_ResetCounter;
	pbMsg.vz_reset_counter = inObject->VZ_ResetCounter;
	pbMsg.xy_global = inObject->XY_Global;
	pbMsg.z_global = inObject->Z_Global;
	pbMsg.dist_bottom_valid = inObject->DistBottomValid;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_local_position_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleLocalPosition_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleLocalPositionMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_local_position_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_local_position_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->RefTimestamp = pbMsg.ref_timestamp;
	inOutObject->RefLat = pbMsg.ref_lat;
	inOutObject->RefLon = pbMsg.ref_lon;
	inOutObject->SurfaceBottomTimestamp = pbMsg.surface_bottom_timestamp;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->Delta_XY[0] = pbMsg.delta_xy[0];
	inOutObject->Delta_XY[1] = pbMsg.delta_xy[1];
	inOutObject->VX = pbMsg.vx;
	inOutObject->VY = pbMsg.vy;
	inOutObject->VZ = pbMsg.vz;
	inOutObject->Delta_VXY[0] = pbMsg.delta_vxy[0];
	inOutObject->Delta_VXY[1] = pbMsg.delta_vxy[1];
	inOutObject->AX = pbMsg.ax;
	inOutObject->AY = pbMsg.ay;
	inOutObject->AZ = pbMsg.az;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->RefAlt = pbMsg.ref_alt;
	inOutObject->DistBottom = pbMsg.dist_bottom;
	inOutObject->DistBottomRate = pbMsg.dist_bottom_rate;
	inOutObject->EpH = pbMsg.eph;
	inOutObject->EpV = pbMsg.epv;
	inOutObject->EvH = pbMsg.evh;
	inOutObject->EvV = pbMsg.evv;
	inOutObject->EstimatorType = pbMsg.estimator_type;
	inOutObject->XY_Valid = pbMsg.xy_valid;
	inOutObject->Z_Valid = pbMsg.z_valid;
	inOutObject->V_XY_Valid = pbMsg.v_xy_valid;
	inOutObject->V_Z_Valid = pbMsg.v_z_valid;
	inOutObject->XY_Global = pbMsg.xy_global;
	inOutObject->XY_ResetCounter = pbMsg.xy_reset_counter;
	inOutObject->Z_ResetCounter = pbMsg.z_reset_counter;
	inOutObject->VXY_ResetCounter = pbMsg.vxy_reset_counter;
	inOutObject->VZ_ResetCounter = pbMsg.vz_reset_counter;
	inOutObject->Z_Global = pbMsg.z_global;
	inOutObject->DistBottomValid = pbMsg.dist_bottom_valid;

	return sizeof(PX4_VehicleLocalPositionMsg_t);
}


uint32 PX4BR_VehicleLocalPositionSetpoint_Enc(const PX4_VehicleLocalPositionSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_local_position_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.x = inObject->X;
	pbMsg.y = inObject->Y;
	pbMsg.z = inObject->Z;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.vx = inObject->VX;
	pbMsg.vy = inObject->VY;
	pbMsg.vz = inObject->VZ;
	pbMsg.acc_x = inObject->AccX;
	pbMsg.acc_y = inObject->AccY;
	pbMsg.acc_z = inObject->AccZ;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_local_position_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleLocalPositionSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleLocalPositionSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_local_position_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_local_position_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->X = pbMsg.x;
	inOutObject->Y = pbMsg.y;
	inOutObject->Z = pbMsg.z;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->VX = pbMsg.vx;
	inOutObject->VY = pbMsg.vy;
	inOutObject->VZ = pbMsg.vz;
	inOutObject->AccX = pbMsg.acc_x;
	inOutObject->AccY = pbMsg.acc_y;
	inOutObject->AccZ = pbMsg.acc_z;

	return sizeof(PX4_VehicleLocalPositionSetpointMsg_t);
}


uint32 PX4BR_VehicleRatesSetpoint_Enc(const PX4_VehicleRatesSetpointMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_rates_setpoint_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.roll = inObject->Roll;
	pbMsg.pitch = inObject->Pitch;
	pbMsg.yaw = inObject->Yaw;
	pbMsg.thrust = inObject->Thrust;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_rates_setpoint_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleRatesSetpoint_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleRatesSetpointMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_rates_setpoint_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_rates_setpoint_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->Roll = pbMsg.roll;
	inOutObject->Pitch = pbMsg.pitch;
	inOutObject->Yaw = pbMsg.yaw;
	inOutObject->Thrust = pbMsg.thrust;

	return sizeof(PX4_VehicleRatesSetpointMsg_t);
}


uint32 PX4BR_VehicleStatus_Enc(const PX4_VehicleStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_vehicle_status_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.system_id = inObject->SystemID;
	pbMsg.component_id = inObject->ComponentID;
	pbMsg.onboard_control_sensors_present = inObject->OnboardControlSensorsPresent;
	pbMsg.onboard_control_sensors_enabled = inObject->OnboardControlSensorsEnabled;
	pbMsg.onboard_control_sensors_health = inObject->OnboardControlSensorsHealth;
	pbMsg.nav_state = inObject->NavState;
	pbMsg.arming_state = inObject->ArmingState;
	pbMsg.hil_state = inObject->HilState;
	pbMsg.failsafe = inObject->Failsafe;
	pbMsg.system_type = inObject->SystemType;
	pbMsg.is_rotary_wing = inObject->IsRotaryWing;
	pbMsg.is_vtol = inObject->IsVtol;
	pbMsg.vtol_fw_permanent_stab = inObject->VtolFwPermanentStab;
	pbMsg.in_transition_mode = inObject->InTransitionMode;
	pbMsg.rc_signal_lost = inObject->RcSignalLost;
	pbMsg.rc_input_mode = inObject->RcInputMode;
	pbMsg.data_link_lost = inObject->DataLinkLost;
	pbMsg.data_link_lost_counter = inObject->DataLinkLostCounter;
	pbMsg.engine_failure = inObject->EngineFailure;
	pbMsg.engine_failure_cmd = inObject->EngineFailureCmd;
	pbMsg.mission_failure = inObject->MissionFailure;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_vehicle_status_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_VehicleStatus_Dec(const char *inBuffer, uint32 inSize, PX4_VehicleStatusMsg_t *inOutObject)
{
	bool status = false;
	px4_vehicle_status_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_vehicle_status_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->SystemID = pbMsg.system_id;
	inOutObject->ComponentID = pbMsg.component_id;
	inOutObject->OnboardControlSensorsPresent = pbMsg.onboard_control_sensors_present;
	inOutObject->OnboardControlSensorsEnabled = pbMsg.onboard_control_sensors_enabled;
	inOutObject->OnboardControlSensorsHealth = pbMsg.onboard_control_sensors_health;
	inOutObject->NavState = pbMsg.nav_state;
	inOutObject->ArmingState = pbMsg.arming_state;
	inOutObject->HilState = pbMsg.hil_state;
	inOutObject->Failsafe = pbMsg.failsafe;
	inOutObject->SystemType = pbMsg.system_type;
	inOutObject->IsRotaryWing = pbMsg.is_rotary_wing;
	inOutObject->IsVtol = pbMsg.is_vtol;
	inOutObject->VtolFwPermanentStab = pbMsg.vtol_fw_permanent_stab;
	inOutObject->InTransitionMode = pbMsg.in_transition_mode;
	inOutObject->RcSignalLost = pbMsg.rc_signal_lost;
	inOutObject->RcInputMode = pbMsg.rc_input_mode;
	inOutObject->DataLinkLost = pbMsg.data_link_lost;
	inOutObject->DataLinkLostCounter = pbMsg.data_link_lost_counter;
	inOutObject->EngineFailure = pbMsg.engine_failure;
	inOutObject->EngineFailureCmd = pbMsg.engine_failure_cmd;
	inOutObject->MissionFailure = pbMsg.mission_failure;

	return sizeof(PX4_VehicleStatusMsg_t);
}

uint32 PX4BR_VisionPositionEstimate_Enc(const PX4_VisionPositionEstimateMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_VisionPositionEstimate_Dec(const char *inBuffer, uint32 inSize, PX4_VisionPositionEstimateMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_VtolVehicleStatus_Enc(const PX4_VtolVehicleStatusMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	return 0;
}

uint32 PX4BR_VtolVehicleStatus_Dec(const char *inBuffer, uint32 inSize, PX4_VtolVehicleStatusMsg_t *inOutObject)
{
	return 0;
}


uint32 PX4BR_WindEstimate_Enc(const PX4_WindEstimateMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_wind_estimate_pb pbMsg;

	pbMsg.timestamp = inObject->Timestamp;
	pbMsg.windspeed_north = inObject->WindspeedNorth;
	pbMsg.windspeed_east = inObject->WindspeedEast;
	pbMsg.covariance_north = inObject->CovarianceNorth;
	pbMsg.covariance_east = inObject->CovarianceEast;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_wind_estimate_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_WindEstimate_Dec(const char *inBuffer, uint32 inSize, PX4_WindEstimateMsg_t *inOutObject)
{
	bool status = false;
	px4_wind_estimate_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_wind_estimate_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	inOutObject->Timestamp = pbMsg.timestamp;
	inOutObject->WindspeedNorth = pbMsg.windspeed_north;
	inOutObject->WindspeedEast = pbMsg.windspeed_east;
	inOutObject->CovarianceNorth = pbMsg.covariance_north;
	inOutObject->CovarianceEast = pbMsg.covariance_east;

	return sizeof(PX4_WindEstimateMsg_t);
}


uint32 PX4BR_LedControl_Enc(const PX4_LedControlMsg_t *inObject, char *inOutBuffer, uint32 inSize)
{
	bool status = false;
	px4_led_control_pb pbMsg;

    pbMsg.led_mask = inObject->LedMask;
    pbMsg.color = inObject->Color;
    pbMsg.mode = inObject->Mode;
    pbMsg.num_blinks = inObject->NumBlinks;
    pbMsg.priority = inObject->Priority;

	/* Create a stream that will write to our buffer. */
	pb_ostream_t stream = pb_ostream_from_buffer((pb_byte_t *)inOutBuffer, inSize);

	/* Now we are ready to encode the message. */
	status = pb_encode(&stream, px4_led_control_pb_fields, &pbMsg);
	/* Check for errors... */
	if (!status)
	{
		return 0;
	}

	return stream.bytes_written;
}

uint32 PX4BR_LedControl_Dec(const char *inBuffer, uint32 inSize, PX4_LedControlMsg_t *inOutObject)
{
	bool status = false;
	px4_led_control_pb pbMsg;

	/* Create a stream that reads from the buffer. */
	pb_istream_t stream = pb_istream_from_buffer((const pb_byte_t *)inBuffer, inSize);

	/* Now we are ready to decode the message. */
	status = pb_decode(&stream, px4_led_control_pb_fields, &pbMsg);

	/* Check for errors... */
	if (!status)
	{
		return 0;
	}
    
	inOutObject->LedMask = pbMsg.led_mask;
	inOutObject->Color = pbMsg.color;
	inOutObject->Mode = pbMsg.mode;
	inOutObject->NumBlinks = pbMsg.num_blinks;
	inOutObject->Priority = pbMsg.priority;

	return sizeof(PX4_LedControlMsg_t);
}
