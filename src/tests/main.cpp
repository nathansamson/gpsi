#include <cppunit/ui/text/TextTestRunner.h>

#include "misc/tests/vector2test.h"
#include "misc/tests/boundingboxtest.h"
#include "game/tests/shiptest.h"
#include "game/tests/gametest.h"
#include "game/tests/synchronousdrivertest.h"
#include "game/tests/bullettest.h"

int main(int argc, char* argv[]) {
	CppUnit::TextTestRunner runner;
	runner.addTest(SITest::Vector2Test::suite());
	runner.addTest(SITest::BoundingBoxTest::suite());
	runner.addTest(SITest::ShipTest::suite());
	runner.addTest(SITest::GameTest::suite());
	runner.addTest(SITest::SynchronousDriverTest::suite());
	runner.addTest(SITest::BulletTest::suite());
	runner.run();
	return 0;
}
