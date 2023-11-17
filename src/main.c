#include "main.h"

static const int led_delay1 = 1000;
static const int led_delay2 = 200;

int main(void)
{    
  system_clock_init();
  gpioc13_init();

  xTaskCreate(led_task, "led1", 128, (void *)&led_delay1, configMAX_PRIORITIES-1, NULL);
  xTaskCreate(led_task, "led2", 128, (void *)&led_delay2, configMAX_PRIORITIES-1, NULL);
  vTaskStartScheduler();

  // Code below should never be reached if FreeRTOS works correctly
  while (1) {

  }
  return 0;
}


static void led_task(void *args) {
  int delay_ms = *(int*)args;
  while (1) {
    GPIOC->ODR ^= (GPIO_ODR_ODR_13);
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
  };
}

/**
 * @brief Initialize GPIOC Pin 13 to output
 * 
 */
static inline void gpioc13_init(void)
{
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
  CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODER13);
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODER13_0);            // General output mode
  CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT13);             // Set output type to push pull
  SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED13_1);       // Set Fast Speed
  GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);                   // no pull up nor pull down
}


/**
 * @brief System initialization covering system clock and flash
 * 
 */
static inline void system_clock_init(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);               // Enable HSE
  while(!(RCC->CR & RCC_CR_HSERDY)) ;           // Wait for HSE Ready
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);     // Power enable
  SET_BIT(PWR->CR, PWR_CR_VOS);                 // Voltage regulator
  MODIFY_REG(FLASH->ACR, 
              FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY,
              FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS);
  MODIFY_REG(RCC->CFGR,
              RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
              RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1);
  MODIFY_REG(RCC->PLLCFGR,
              RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLSRC,
              (25U << RCC_PLLCFGR_PLLM_Pos) | (192U << RCC_PLLCFGR_PLLN_Pos) | (0U << RCC_PLLCFGR_PLLP_Pos) | (4U << RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSE);
  SET_BIT(RCC->CR, RCC_CR_PLLON);               // Enable PLL
  while(!(RCC->CR & RCC_CR_PLLRDY)) ;           // Wait for PLL Ready
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)) ;
  SystemCoreClockUpdate();
}