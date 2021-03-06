
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "stm32f10x.h"
#include "ticks.h"
#include "LEDs.h"
#include "tft_display.h"
#include "adc.h"
#include "linear_ccd.h"
#include "buzzer.h"
#include "buzzer_song.h"
#include "motor.h"
#include "helper.h"
#include "GPIO_switch.h"
#include "button.h"
#include "uart.h"
#include "servo_tutorial.h"

#define MAX_CCRn			1000
#define MIN_CCRn			450
#define GetCCRn(deg)	(((float)deg / 180) * 600 + MIN_CCRn)

#endif /* __MAIN_H */
