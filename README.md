# stm32f411_freertos
Basic FreeRTOS setup for popular blackpill (STM32F411 microcontroller based board).

In `main.c`:
- Main clock is set at 96MHz
- 2 tasks created based on led_task function to illustrate complex blinking pattern

## Instructions
- If your toolchain folder is not in global PATH variable then you need to create GCC_PATH variable with toolchain folder as value.
- `make all` 
- use your favourite tool to flash the device.

