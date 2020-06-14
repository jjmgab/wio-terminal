#ifndef PROGRAM_EXT_HPP__
#define PROGRAM_EXT_HPP__

#include "program.hpp"
#include "fireworks.hpp"
#include "splashscreen.hpp"

#include "program_utils.hpp"

enum ProgramPart
{
	NONE,
	FIREWORKS
};

class ProgramExt : public Program {
	
	ProgramPart _currentPart = NONE;
	
	uint8_t _fireworksCount;
	Fireworks _fireworks[10];
	
	public:
		virtual void init() override
		{
			_backgroundColor = TFT_BLACK;
			
			Program::init();
			Fireworks::init(getTft(), _backgroundColor);
			
			clearScreen();
		}
		
		void loop()
		{
			switch (_currentPart)
			{
				case FIREWORKS:
				{
					loopFireworks();
					break;
				}
			}
			
			delay(5);
		}
		
		void startFireworks(uint8_t count = 1)
		{
			_currentPart = FIREWORKS;
			_fireworksCount = treshold(count, 1, 10);
			
			_fireworks[0].start(true, random(45, 80), random(10, 15), random(0, 100));
			for (uint8_t i = 1; i < _fireworksCount; i++)
			{
				_fireworks[i].start(false, random(45, 80), random(10, 15), random(0, 100));
			}
		}

	protected:


	private:
		void loopFireworks()
		{
			bool isFinished = true;
			for (uint8_t i = 0; i < _fireworksCount; i++)
			{
				_fireworks[i].step();
				isFinished &= _fireworks[i].isFinished();
			}
			
			if (isFinished)
			{
				_currentPart = NONE;
				clearScreen();
			}
		}
};

#endif //PROGRAM_EXT_HPP__