#include "stm32f4xx_hal.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"

#include "led_control.h"

static struct led_interface iface = {0};

static int _led_gpio_init(GPIO_TypeDef *GPIOx,
						  uint16_t red_pin,
						  uint16_t green_pin,
						  uint16_t blue_pin,
						  uint16_t orange_pin) {
	GPIO_InitTypeDef init_mode[4] = {
			{
			.Pin = red_pin,
			.Mode = GPIO_MODE_OUTPUT_PP,
			},
			{
			.Pin = green_pin,
			.Mode = GPIO_MODE_OUTPUT_PP,
			},
			{
			.Pin = blue_pin,
			.Mode = GPIO_MODE_OUTPUT_PP,
			},
			{
			.Pin = orange_pin,
			.Mode = GPIO_MODE_OUTPUT_PP,
			},
	};
	HAL_GPIO_Init(GPIOx, &init_mode[0]);
	HAL_GPIO_Init(GPIOx, &init_mode[1]);
	HAL_GPIO_Init(GPIOx, &init_mode[2]);
	HAL_GPIO_Init(GPIOx, &init_mode[3]);
	return 0;
}

static int _led_color_set(const struct led_interface *iface, color_type_e color) {
	switch (color) {
	case COLOR_OFF:
	{
		HAL_GPIO_WritePin(iface->GPIOx, iface->red_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->green_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->orange_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->blue_pin, GPIO_PIN_RESET);
	}
		break;
	case COLOR_RED:
	{
		HAL_GPIO_WritePin(iface->GPIOx, iface->red_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->green_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->orange_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->blue_pin, GPIO_PIN_RESET);
	}
		break;
	case COLOR_GREEN:
	{
		HAL_GPIO_WritePin(iface->GPIOx, iface->red_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->green_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->orange_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->blue_pin, GPIO_PIN_RESET);
	}
		break;
	case COLOR_BLUE:
	{
		HAL_GPIO_WritePin(iface->GPIOx, iface->red_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->green_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->orange_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->blue_pin, GPIO_PIN_SET);
	}
		break;
	case COLOR_ORANGE:
	{
		HAL_GPIO_WritePin(iface->GPIOx, iface->red_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->green_pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->orange_pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(iface->GPIOx, iface->blue_pin, GPIO_PIN_RESET);
	}
		break;
	case COLOR_YELLOW:
		break;
	case COLOR_CYAN:
		break;
	case COLOR_MAGENTA:
		break;
	case COLOR_WHITE:
		break;
	default:
		break;
	}
	return 0;
}

void init_led_gpio (GPIO_TypeDef *GPIOx,
									uint16_t red_pin,
									uint16_t green_pin,
									uint16_t blue_pin,
									uint16_t orange_pin) {
	iface.GPIOx = GPIOx;
	iface.red_pin = red_pin;
	iface.green_pin = green_pin;
	iface.blue_pin = blue_pin;
	iface.orange_pin = orange_pin;
	_led_gpio_init(GPIOx, red_pin, green_pin, blue_pin, orange_pin);
}

void led_set_color(struct led_interface *iface, color_type_e color) {
	_led_color_set(iface, color);
	iface->color = color;
}

void led_task(void *param) {
	UNUSED(param);
	color_type_e color = COLOR_OFF;
	while (1) {
		color++;
		led_set_color(&iface, color);
		vTaskDelay(1000 * portTICK_PERIOD_MS);
		if (color == TOTAL_COLOR) {
			color = COLOR_OFF;
		}
	}
}
