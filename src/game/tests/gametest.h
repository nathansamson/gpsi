#ifndef INC_GAMETEST_H
#define INC_SHIPTEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/vector2.h"
#include "game/tests/test.h"
#include "game/game.h"

using namespace SI;

namespace SITest {

	class GameTest {
	public:
		void setUp();
		void tearDown();
		
		void testSimpleGame();
		
		static CppUnit::Test* suite();
	private:
		Game* fGame;
	
		void assertVectorEquality(Vector2, Vector2);
		MockGameEntityFactory* fEntityFactory;
		MockEnemyDriverFactory* fEnemyDriverFactory;
	};
}

#endif //INC_GAMESHIP_H
