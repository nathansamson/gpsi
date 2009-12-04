#ifndef INC_BULLETTEST_H
#define INC_BULLETTEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/vector2.h"
#include "game/tests/test.h"
#include "game/bullet.h"

using namespace SI;

namespace SITest {

	class BulletTest {
	public:
		void setUp();
		void tearDown();
		
		void testBullet();
		
		static CppUnit::Test* suite();
	private:
		SI::Bullet* fBullet;
	};
}

#endif //INC_BULETTEST_H
