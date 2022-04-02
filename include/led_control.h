#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef enum color_type {
	COLOR_OFF = 0x00,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,
	COLOR_YELLOW,
	COLOR_CYAN,
	COLOR_MAGENTA,
	COLOR_ORANGE,
	COLOR_WHITE,
	TOTAL_COLOR // last color
} color_type_e;

struct led_interface {
	GPIO_TypeDef *GPIOx;
	uint16_t red_pin;
	uint16_t green_pin;
	uint16_t blue_pin;
	uint16_t orange_pin;
	color_type_e color;
};

/**
 * Init gpio for led
 * @param GPIOx gpio group
 * @param red_pin
 * @param green_pin
 * @param blue_pin
 */
void init_led_gpio (GPIO_TypeDef *GPIOx,
					uint16_t red_pin,
					uint16_t green_pin,
					uint16_t blue_pin,
					uint16_t orange_pin);

/**
 * Set color to led interface
 * @param iface led interface return by init_led_gpio
 * @param color set to this iface
 * @return None
 */
void led_set_color (struct led_interface *iface, color_type_e color);

void led_task (void *param);
