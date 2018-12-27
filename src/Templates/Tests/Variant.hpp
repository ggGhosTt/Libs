#ifndef TEST_VARIANT_HPP
#define TEST_VARIANT_HPP

#include <tests/Test.hpp>

#include <FlameIDE/Templates/Variant.hpp>

#include "TestClass.hpp"

namespace flame_ide
{namespace test
{

class Variant: public AbstractTest
{
public:
	Variant();
	virtual ~Variant();

private:
	virtual int vStart();
	bool testVariantStruct();
	bool testVariant();
};

}}

#endif // TEST_VARIANT_HPP
