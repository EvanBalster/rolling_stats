#pragma once


#include <bit>
#include <cstdint>


namespace rolling
{
	/*
		Running fixed-point sum.
			Problem: need to know the magnitude of the values, has a small fixed error per sample.
	*/
	template<
		typename float_type,
		typename fixed_type = int32_t,
		fixed_type FIXED_PRECISION = 16777216,
		bool       OPTIMIZE_F2I = false>
	struct sum_fixed
	{
		using float_t = float_type;
		using fixed_t = fixed_type;
		
		
		fixed_t total;
		
		static fixed_t float_to_fixed(float_t x) noexcept
		{
			if (OPTIMIZE_F2I)
			{
				return std::nearbyint(float_t(FIXED_PRECISION) * x);
			}
			else
			{
				return fixed_t(FIXED_PRECISION * x);
			}
		}
		static float_t fixed_to_float(fixed_t x) noexcept    {return float_t(x) / FIXED_PRECISION;}
		
		void    reset()                noexcept    {total = 0;}
		void    push (const float_t x) noexcept    {total += float_to_fixed(x);}
		void    pop  (const float_t x) noexcept    {total -= float_to_fixed(x);}
		float_t sum  () const          noexcept    {return fixed_to_float(total);}
	};
}
