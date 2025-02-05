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

#include "platform.h"

#if defined(USE_FREQ_SENSOR)

#include "drivers/io.h"
#include "drivers/nvic.h"
#include "drivers/timer.h"
#include "drivers/freq.h"

#include "pg/pg.h"
#include "pg/pg_ids.h"

#include "freq.h"

PG_REGISTER_WITH_RESET_FN(freqConfig_t, freqConfig, PG_FREQ_CONFIG, 0);

void pgResetFn_freqConfig(freqConfig_t *freqConfig)
{
    for (unsigned index = 0; index < FREQ_SENSOR_PORT_COUNT; index++) {
        freqConfig->ioTag[index] = timerioTagGetByUsage(TIM_USE_FREQ, index);
    }
}

#endif
