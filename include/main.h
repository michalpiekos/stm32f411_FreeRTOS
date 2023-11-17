/**
 * @file main.h
 * @author Michal Piekos (michal.public@wp.pl)
 * @brief Header file for drilling down BlackPill
 * @version 0.1
 * @date 2023-05-07
 * 
 * MIT License. Copyright (c) 2023.
 * 
 */

/*****************************************************************
 * Includes
******************************************************************/

#include <stdint.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

/*****************************************************************/


/*****************************************************************
 * Function declarations
******************************************************************/

static inline void system_clock_init(void);
static inline void gpioc13_init(void);
static void led_task(void *args);

/*****************************************************************/