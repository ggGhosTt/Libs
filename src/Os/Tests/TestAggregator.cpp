#include <FlameIDE/../../src/Os/Tests/TestAggregator.hpp>

#include <FlameIDE/../../src/Os/Tests/LibraryTest.hpp>
#include <FlameIDE/../../src/Os/Tests/Ipv4Test.hpp>
#include <FlameIDE/../../src/Os/Tests/UdpFunctionsTest.hpp>
#include <FlameIDE/../../src/Os/Tests/UdpTest.hpp>

namespace flame_ide
{namespace os
{namespace tests
{

TestAggregator::TestAggregator() : ::TestAggregator("Os")
{
	pushBackTest(std::make_shared<LibraryTest>());
	pushBackTest(std::make_shared<Ipv4Test>());
	pushBackTest(std::make_shared<UdpFunctionsTest>());
	pushBackTest(std::make_shared<UdpTest>());
}

}}} // namespace flame_ide::os::tests
