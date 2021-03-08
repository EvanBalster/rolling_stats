#pragma once


namespace rolling
{
	/*
		Running sum where errors are "bumped" away every so often by the caller.
			Problem: tends toward worsening cancellation error over time due to large totals.
	*/
	template<
		typename float_type,
		typename accumulator_type = float_type>
	struct sum_bumpy_v1
	{
		using float_t = float_type;
		
		
		accumulator_type rise, fall;
		
		void    reset()                noexcept    {rise = fall = 0;}
		void    push (const float_t x) noexcept    {rise += x;}
		void    pop  (const float_t x) noexcept    {fall -= x;}
		float_t sum  () const          noexcept    {return rise + fall;}
		
		// This must be called once per N samples, where N is the number of elements in the sum
		void    bump() noexcept    {fall = rise; rise = 0;}
	};
}
