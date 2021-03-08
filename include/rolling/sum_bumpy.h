#pragma once


namespace rolling
{
	/*
		Running sum where errors are "bumped" away automatically.
			Problem: tends toward worsening cancellation error over time due to large totals.
	*/
	template<
		typename float_type,
		typename accumulator_type = float_type>
	struct sum_bumpy
	{
		using float_t = float_type;
		
		
		accumulator_type gain, hold, lose;
		
		void    reset()                noexcept    {gain = hold = lose = 0;}
		void    push (const float_t x) noexcept    {gain += x;}
		void    pop  (const float_t x) noexcept
		{
			if (lose == hold)
			{
				hold = gain;
				lose = gain = 0;
			}
			lose += x;
		}
		float_t sum  () const noexcept             {return gain + (hold - lose);}
	};
}
