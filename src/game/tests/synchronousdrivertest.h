#ifndef INC_SYNC_DRIVERTEST_H
#define INC_SYNC_DRIVERTEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "game/tests/test.h"
#include "game/ship.h"
#include "game/synchronousdriver.h"

using namespace SI;

namespace SITest {

	class SynchronousDriverTest {
	public:
		void setUp();
		void tearDown();
		
		void testMoveNormal();
		void testMoveChangeDirection();
		
		static CppUnit::Test* suite();
	private:
		SI::Ship* fShip;
		SI::SynchronousDriver* fDriver;
	};
}

#endif // INC_SYNC_DRIVERTEST_H
