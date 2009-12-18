#ifndef INC_GUNTEST_H
#define INC_GUNTEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "game/tests/test.h"
#include "game/weapons/gun.h"
#include "game/ship.h"

using namespace SI;

namespace SITest {

	class GunTest {
	public:
		void setUp();
		void tearDown();
		
		void testConstruction();
		void testFireOnlyAfterReloadTime();
		void testToggleFire();
		
		static CppUnit::Test* suite();
	private:
		BulletType* fBulletType;
		IGameEntityFactory* fEntityFactory;
		Ship* fShip;
		Gun* fGun;
		EntityGroup* fEntityGroup;
	};
}

#endif //INC_GUNTEST_H
