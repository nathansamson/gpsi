#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "game/ship.h"
#include "gametest.h"

namespace SITest {
	#define GAME_TEST(name) new CppUnit::TestCaller<GameTest>( \
	                                   #name, \
	                                   &GameTest::name) \
	
	void GameTest::setUp() {
		fEntityFactory = new MockGameEntityFactory();
		fGame = new Game(new MockShipDriver(), fEntityFactory);
	}
	
	void GameTest::tearDown() {
		delete fGame;
	}
	
	void GameTest::testSimpleGame() {
		CPPUNIT_ASSERT(fEntityFactory->fCreatedShip != 0);
		CPPUNIT_ASSERT(!fEntityFactory->fCreatedShip->fVisualized);
		fGame->update(1000);
		CPPUNIT_ASSERT(fEntityFactory->fCreatedShip->fVisualized);
		fEntityFactory->fCreatedShip->fVisualized = false;
		assertVectorEquality(Vector2(10, 0), fEntityFactory->fCreatedShip->getPosition());
		
	}
	
	CppUnit::Test* GameTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Game test");
		suiteOfTests->addTest(GAME_TEST(testSimpleGame));
		return suiteOfTests;
	}
	
	void GameTest::assertVectorEquality(Vector2 expected, Vector2 actual) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getX(), actual.getX(), 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getY(), actual.getY(), 0.0001);
	}
}
