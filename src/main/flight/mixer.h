/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "platform.h"

#include "common/time.h"
#include "pg/pg.h"
#include "drivers/io_types.h"
#include "drivers/pwm_output.h"

#define QUAD_MOTOR_COUNT 4

typedef enum {
    RPM_SRC_NONE = 0,
    RPM_SRC_DSHOT_TELEM,
    RPM_SRC_FREQ_SENSOR,
    RPM_SRC_ESC_SENSOR,
} rpmSource_e;

// Note: this is called MultiType/MULTITYPE_* in baseflight.
typedef enum mixerMode
{
    MIXER_TRI = 1,
    MIXER_QUADP = 2,
    MIXER_QUADX = 3,
    MIXER_BICOPTER = 4,
    MIXER_GIMBAL = 5,
    MIXER_Y6 = 6,
    MIXER_HEX6 = 7,
    MIXER_FLYING_WING = 8,
    MIXER_Y4 = 9,
    MIXER_HEX6X = 10,
    MIXER_OCTOX8 = 11,
    MIXER_OCTOFLATP = 12,
    MIXER_OCTOFLATX = 13,
    MIXER_AIRPLANE = 14,        // airplane / singlecopter / dualcopter (not yet properly supported)
    MIXER_HELI_120_CCPM = 15,
    MIXER_HELI_90_DEG = 16,
    MIXER_VTAIL4 = 17,
    MIXER_HEX6H = 18,
    MIXER_PPM_TO_SERVO = 19,    // PPM -> servo relay
    MIXER_DUALCOPTER = 20,
    MIXER_SINGLECOPTER = 21,
    MIXER_ATAIL4 = 22,
    MIXER_CUSTOM = 23,
    MIXER_CUSTOM_AIRPLANE = 24,
    MIXER_CUSTOM_TRI = 25,
    MIXER_QUADX_1234 = 26
} mixerMode_e;

// Custom mixer data per motor
typedef struct motorMixer_s {
    float throttle;
    float roll;
    float pitch;
    float yaw;
} motorMixer_t;

PG_DECLARE_ARRAY(motorMixer_t, MAX_SUPPORTED_MOTORS, customMotorMixer);

// Custom mixer configuration
typedef struct mixer_s {
    uint8_t motorCount;
    uint8_t useServo;
    const motorMixer_t *motor;
} mixer_t;

typedef struct mixerConfig_s {
    uint8_t mixerMode;
    bool yaw_motors_reversed;
    uint8_t crashflip_motor_percent;
    uint16_t gov_max_headspeed;
    uint16_t gov_gear_ratio;
    uint16_t gov_rpm_lpf;
    uint16_t gov_p_gain;
    uint16_t gov_i_gain;
    uint16_t gov_cyclic_ff_gain;
    uint16_t gov_collective_ff_gain;
    uint16_t gov_collective_ff_impulse_gain;
    uint16_t spoolup_time;
    uint16_t gov_tailmotor_assist_gain;
} mixerConfig_t;

PG_DECLARE(mixerConfig_t, mixerConfig);

#define CHANNEL_FORWARDING_DISABLED (uint8_t)0xFF

extern const mixer_t mixers[];
extern float motor[MAX_SUPPORTED_MOTORS];
extern float motor_disarmed[MAX_SUPPORTED_MOTORS];
extern float motorOutputHigh, motorOutputLow;
struct rxConfig_s;

uint8_t getMotorCount(void);
float getMotorMixRange(void);
bool areMotorsRunning(void);

void mixerLoadMix(int index, motorMixer_t *customMixers);
void initEscEndpoints(void);
void mixerInit(mixerMode_e mixerMode);

void mixerConfigureOutput(void);

void mixerResetDisarmedMotors(void);
void mixTable(timeUs_t currentTimeUs, uint8_t vbatPidCompensation);
void stopMotors(void);
void writeMotors(void);

bool mixerIsTricopter(void);

void mixerSetThrottleAngleCorrection(int correctionValue);
float mixerGetThrottle(void);
mixerMode_e getMixerMode(void);
bool isFixedWing(void);

extern float headspeed;

// HF3D
void rpmSourceInit(void);
uint8_t isHeliSpooledUp(void);
float mixerGetGovGearRatio(void);
float mixerGetGovCollectivePulseFilterGain(void);
uint16_t mixerGetYawPidsumAssistLimit(void);
int getMotorRPM(uint8_t motor);
float getFilteredMotorRPM(uint8_t motor);
bool isRpmSourceActive(void);
