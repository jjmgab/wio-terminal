#ifndef SPLASHSCREEN_HPP__
#define SPLASHSCREEN_HPP__

#include <SPI.h>
#include <TFT_eSPI.h>
#include <cstdint>

#include "Lcd/screenInfo.hpp"

class Splashscreen {
	String _splashText = "Splash";
	std::uint16_t _bgColor = TFT_GREEN;
	std::uint16_t _fgColor = TFT_RED;
	
	public:
		void show(TFT_eSPI& tft)
		{
			tft.fillScreen(TFT_BLACK);
			
			for(int i = 0; i <= SCR_WIDTH; i++)
			{
				tft.drawFastVLine(i, 0, SCR_HEIGHT, _bgColor);
				delay(5);
			}
			
			drawSplash();
			delay(1000);
			
			for(int i = 0; i <= SCR_WIDTH; i++)
			{
				tft.drawFastVLine(i, 0, SCR_HEIGHT, TFT_BLACK);
				delay(5);
			}
		}
	
	private:
		void drawSplash()
		{
			
		}
};

#endif //SPLASHSCREEN_HPP__