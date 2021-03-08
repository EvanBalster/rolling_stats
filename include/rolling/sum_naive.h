#pragma once


namespace rolling
{
	/*
		Running sum based on a single float accumulator.
			Problem: error in total "drifts" randomly due to imperfect cancellation.
	*/
	template<
		typename float_type,
		typename accumulator_type = float_type>
	struct sum_naive
	{
		using float_t = float_type;
		
		
		accumulator_type total;
		
		void    reset()                noexcept    {total = 0;}
		void    push (const float_t x) noexcept    {total += x;}
		void    pop  (const float_t x) noexcept    {total -= x;}
		float_t sum  () const          noexcept    {return total;}
	};
}
