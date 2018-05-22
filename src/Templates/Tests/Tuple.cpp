#include "Tuple.hpp"

using namespace flame_ide;
using namespace flame_ide::test;

Tuple::Tuple()
		: AbstractTest("Tuple")
		, tuple{'1', short(10), 100, 1000L}
{}

Tuple::~Tuple()
{}

int Tuple::vStart()
{
	std::cout << tuple.get<0>() << ' '
			<< tuple.get<1>() << ' '
			<< tuple.get<2>() << ' '
			<< tuple.get<3>() << std::endl;
	return 0;
}
