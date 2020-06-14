#ifndef LCD_UTILS_HPP__
#define LCD_UTILS_HPP__

#include "lcd_backlight.hpp"

#include <cstdint>

/**
 *	Rotation
 */
enum Rotation {
	TOP_RIGHT = 0,
	BOTTOM_RIGHT = 1,
	BOTTOM_LEFT = 2,
	TOP_LEFT = 3
};

void setRotation(TFT_eSPI& tft, Rotation rotation) {
    tft.setRotation((int)rotation);
}

/**
 *	Brightness
 */
static LCDBackLight backLight;
static std::uint8_t backLightMaxBrightness;

void initializeBacklight() {
	backLight.initialize();
	backLightMaxBrightness = backLight.getMaxBrightness();
}

void setBrightness(std::uint8_t percent) {
	if (percent > backLightMaxBrightness) {
		backLight.setBrightness(backLightMaxBrightness);
	}
	else {
		backLight.setBrightness(backLightMaxBrightness / 100 * percent);
	}
}

#endif // LCD_UTILS_HPP__