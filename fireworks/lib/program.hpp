#ifndef PROGRAM_HPP__
#define PROGRAM_HPP__

#include <SPI.h>
#include <TFT_eSPI.h>

#include "Lcd/lcd_utils.hpp"

class Program {
	TFT_eSPI _tft;
	
	public:
		virtual void init()
		{
			_tft = TFT_eSPI();
			initScreen();
		}
		
		TFT_eSPI& getTft() 
		{
			return _tft;
		}
		
		void setTftRotation(Rotation r) {
			setRotation(_tft, r);
		}
		
		void setTftBrightness(uint8_t level)
		{
			if (level > 100)
			{
				setBrightness(100);
			}
			else
			{
				setBrightness(level);
			}
		}
		
		void clearScreen()
		{
			_tft.fillScreen(_backgroundColor);
		}

	protected:
	
		uint32_t _backgroundColor = TFT_BLACK;

	private:
		void initScreen() 
		{
			// TFT initialization
			_tft.begin();
			setTftRotation(TOP_LEFT);

			// save eyes & energy :-)
			initializeBacklight();
			setBrightness(50);
		}
};

#endif //PROGRAM_HPP__