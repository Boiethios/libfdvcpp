//test

#include <Math/Vector.class.hpp>

#include <iostream>

FDV_BEGIN_NAMESPACE

void
test(void)
{
	Vector3<float>	my_vec1(0.f);
	Vector3<float>	my_vec2(1.f);

	(void)(my_vec1 /= my_vec2);
	(void)(my_vec1 == my_vec2);
}

FDV_END_NAMESPACE
