#ifndef PROGRAM_UTILS_HPP__
#define PROGRAM_UTILS_HPP__

uint16_t treshold(uint16_t value, uint16_t min, uint16_t max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}
	else
	{
		return value;
	}
}

#endif //PROGRAM_UTILS_HPP__