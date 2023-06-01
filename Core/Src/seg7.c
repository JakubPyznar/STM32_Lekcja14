#include "seg7.h"
#include <stdbool.h>
#include "gpio.h"

static void set_output(uint8_t mask)
{
	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, mask & 0x01);
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, mask & 0x02);
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, mask & 0x04);
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, mask & 0x08);
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, mask & 0x10);
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, mask & 0x20);
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, mask & 0x40);
}

static void seg7_show_digit(uint32_t value)
{
	const uint8_t digit[] =
	{
			0b0111111,
			0b0000110,
			0b1011011,
			0b1001111,
			0b1100110,
			0b1101101,
			0b1111101,
			0b0000111,
			0b1111111,
			0b1101111
	};

	set_output(digit[value % 10]);
}

static uint32_t actual_value;
static uint32_t active_digit;

void seg7_show(uint32_t value)
{
	actual_value = value;
}

void seg7_update(void)
{
	HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_SET);

	switch (active_digit)
	{
	case 0:
		if (actual_value < 100)		seg7_show_digit(actual_value % 10);
		else						set_output(0b1000000);
		HAL_GPIO_WritePin(SEG_1_GPIO_Port, SEG_1_Pin, GPIO_PIN_RESET);
		active_digit = 1;
		break;
	case 1:
		if (actual_value < 100)		seg7_show_digit(actual_value / 10);
		else						set_output(0b1000000);
		HAL_GPIO_WritePin(SEG_2_GPIO_Port, SEG_2_Pin, GPIO_PIN_RESET);
		active_digit = 0;
		break;
	}
}
