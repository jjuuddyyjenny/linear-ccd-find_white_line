#include "stm32f10x.h"

void LED_INIT(void);

void LED_blink(GPIO_TypeDef* PORT,u16 gpio_pin);
void LED_OFF(GPIO_TypeDef* PORT,u16 gpio_pin);
void LED_ON(GPIO_TypeDef* PORT,u16 gpio_pin);
#define LED_L  GPIO_Pin_4
#define LED_M  GPIO_Pin_3
#define LED_R  GPIO_Pin_15
