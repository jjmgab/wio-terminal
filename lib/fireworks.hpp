#ifndef FIREWORKS_HPP__
#define FIREWORKS_HPP__

#include <SPI.h>
#include <TFT_eSPI.h>
#include <cstdint>
#include <math.h>

#include "Lcd/screenInfo.hpp"
#include "Lcd/lcd_utils.hpp"

#define DEG2RAD(deg) M_PI * deg / 180.0

/**
 * Particle definition. Contains information about particle
 * kinematics (position, velocity, acceleration), parameters
 * (color, moment of explosion) and lifecycle status.
 */
typedef struct Particle
{
	bool alive;
	uint32_t color;
	double yToExplode;
	double sx;
	double sy;
	double vx;
	double vy;
	double ax;
	double ay;
};

/**
 * Definition of a firework.
 * Defines a whole process: shooting the rocket, exploding it
 * and handling the particles.
 */
class Fireworks {
	/**
	 * Lcd screen reference.
	 */
	static TFT_eSPI _tft;
	
	uint8_t particleCount = 12;
	Particle particles[12];
	
	Particle rocket;
	
	static uint32_t bgColor;
	static uint32_t colors[9];
	
	/**
	 * Time step.
	 */
	static constexpr double t_step = 0.1;
	/**
	 * Acceleration due to gravity.
	 */
	static constexpr double g = 0.09;
	
	double _t = 0, _v = 0, _x0 = 0, _y0 = 0;
	
	public:
		static void init(TFT_eSPI& tft, uint32_t backgroundColor)
		{
			_tft = tft;
			bgColor = backgroundColor;
		}
	
		/**
		 * Shoots the rocket and sets initial values.
		 */
		void start(
			bool clearScr = true,
			double deg = 45.0, 
			double v = 5.0, 
			double x0 = 0.0, 
			double y0 = SCR_HEIGHT)
		{
			_t = 0.0;
			_v = v;
			_x0 = x0;
			_y0 = y0;
			
			if (clearScr)
			{
				_tft.fillScreen(bgColor);
			}
			
			setRotation(_tft, TOP_LEFT);
			shoot(deg, v);
		}
		
		/**
		 * Handles calculations of new kinematics values
		 * and redraws all particles.
		 */
		void step()
		{
			if (rocket.alive)
			{
				_tft.drawPixel(rocket.sx, rocket.sy, bgColor);
				makeStep(rocket);
				_tft.drawPixel(rocket.sx, rocket.sy, rocket.color);
				
				if (rocket.yToExplode > rocket.sy)
				{
					explode();
				}
			}
			else
			{
				for (uint8_t i = 0; i < particleCount; i++)
				{
					if (particles[i].alive)
					{
						makeStep(particles[i]);
						_tft.drawPixel(particles[i].sx, particles[i].sy, particles[i].color);
					}
				}
			}
			
			_t += t_step;
		}
		
		bool isFinished()
		{
			if (rocket.alive)
			{
				return false;
			}
			
			for (uint8_t i = 0; i < particleCount; i++)
			{
				if (particles[i].alive)
				{
					return false;
				}
			}
			
			return true;
		}
	
	private:
		void shoot(double deg, double v)
		{
			rocket.alive = true;
			rocket.color = TFT_WHITE;
			rocket.yToExplode = SCR_HEIGHT / 4 + random(0, SCR_HEIGHT / 2);
			
			setParams(rocket, _x0, _y0, deg, v, 0, g);
		}
	
		void explode()
		{
			rocket.alive = false;
			
			uint8_t colorCount = sizeof(colors) / sizeof(uint32_t);
			for (uint8_t i = 0; i < particleCount; i++)
			{
				particles[i].alive = true;
				particles[i].color = colors[random(0, colorCount)];
				
				double degree = random(0, 360);
				setParams(particles[i], rocket.sx, rocket.sy, degree, 2.0, 0, g);
			}
		}
		
		void setParams(Particle& p, double x0, double y0, double deg, double v, double ax0, double ay0)
		{
			double alpha = DEG2RAD(deg);
  
			// position
			p.sx = x0;
			p.sy = y0;

			// velocity
			p.vx = v * cos(alpha);
			p.vy = - v * sin(alpha);

		  // acceleration
			p.ax = ax0;
			p.ay = ay0;
		}
		
		void makeStep(Particle& p)
		{
			// change velocity
			p.vx += p.ax * t_step;
			p.vy += p.ay * t_step;

			// change position
			p.sx += p.vx * t_step;
			p.sy += p.vy * t_step;
			
			if (p.sy > SCR_HEIGHT)
			{
				p.alive = false;
			}
		}
};

TFT_eSPI Fireworks::_tft;
uint32_t Fireworks::bgColor;
uint32_t Fireworks::colors[] = { TFT_RED, TFT_GREEN, TFT_BLUE, TFT_YELLOW, TFT_OLIVE, TFT_CYAN, TFT_MAGENTA, TFT_ORANGE, TFT_GREENYELLOW };

#endif //FIREWORKS_HPP__