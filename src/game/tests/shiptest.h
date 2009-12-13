#ifndef INC_SHIPTEST_H
#define INC_SHIPTEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/vector2.h"
#include "game/ship.h"

using namespace SI;

namespace SITest {

	class ShipTest {
	public:
		void setUp();
		void tearDown();
		
		void testUpdate();
		void testNegativeUpdate();
		
		static CppUnit::Test* suite();
	private:
		Ship* fShip;
		IGameEntityFactory* fEntityFactory;
	
		void assertVectorEquality(Vector2, Vector2);
	};
}

#endif //INC_SHIPTEST_H
