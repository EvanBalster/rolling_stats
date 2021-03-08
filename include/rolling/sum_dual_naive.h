#pragma once


namespace rolling
{
	/*
		Running sum based on a two float accumulators.
			Problem: tends toward worsening cancellation error over time due to large totals.
	*/
	template<
		typename float_type,
		typename accumulator_type = float_type>
	struct sum_dual_naive
	{
		using float_t = float_type;
		
	
		accumulator_type total_push, total_pop;
		
		void    reset()                noexcept    {total_push = total_pop = 0;}
		void    push (const float_t x) noexcept    {total_push += x;}
		void    pop  (const float_t x) noexcept    {total_pop  += x;}
		float_t sum  () const          noexcept    {return total_push - total_pop;}
	};
}
