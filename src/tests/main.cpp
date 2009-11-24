#include <cppunit/ui/text/TextTestRunner.h>

#include "misc/tests/vector2test.h"

int main(int argc, char* argv[]) {
	CppUnit::TextTestRunner runner;
	runner.addTest(SITest::Vector2Test::suite());
	//runner.addTest(sitest::Vector2::suite() );
	runner.run();
	return 0;
}
