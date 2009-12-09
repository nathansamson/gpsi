#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <iostream>

#include "game/ship.h"
#include "gametest.h"

namespace SITest {
	#define GAME_TEST(name) new CppUnit::TestCaller<GameTest>( \
	                                   #name, \
	                                   &GameTest::name) \
	
	void GameTest::setUp() {
		fEntityFactory = new MockGameEntityFactory();
		fEnemyDriverFactory = new MockEnemyDriverFactory();
		fGame = new Game(new MockShipDriver(), fEntityFactory, fEnemyDriverFactory);
	}
	
	void GameTest::tearDown() {
		delete fGame;
	}
	
	void GameTest::testSimpleGame() {
		CPPUNIT_ASSERT(fEntityFactory->fShips[0] != 0);
		CPPUNIT_ASSERT(!fEntityFactory->fShips[0]->fVisualized);
		CPPUNIT_ASSERT_EQUAL(0, fEntityFactory->fShips[0]->getDirection());
		
		for (int i = 1; i < 6; i++) {
			CPPUNIT_ASSERT(!fEntityFactory->fShips[i]->fVisualized);
			CPPUNIT_ASSERT_EQUAL(180, fEntityFactory->fShips[i]->getDirection());
			assertVectorEquality(Vector2(-4.0+i*8.0/6, 2.5), fEntityFactory->fShips[i]->getPosition());
		}
		
		fGame->update(100);
		CPPUNIT_ASSERT(fEntityFactory->fShips[0]->fVisualized);
		fEntityFactory->fShips[0]->fVisualized = false;
		assertVectorEquality(Vector2(1, -2.0), fEntityFactory->fShips[0]->getPosition());
		
		CPPUNIT_ASSERT(5 == (fEnemyDriverFactory->fDrivers.size()));
		
		fGame->update(MAGIC_FIRE_TICK);
		CPPUNIT_ASSERT(fEntityFactory->fBullets[0] != 0);
		CPPUNIT_ASSERT(fEntityFactory->fBullets[0]->fVisualized);
		CPPUNIT_ASSERT_EQUAL(0, fEntityFactory->fBullets[0]->getDirection());
		CPPUNIT_ASSERT_EQUAL(180, fEntityFactory->fBullets[1]->getDirection());
		assertVectorEquality(fEntityFactory->fShips[0]->getPosition(), fEntityFactory->fBullets[0]->getPosition());

		fGame->update(1);
		CPPUNIT_ASSERT(fEntityFactory->fBullets[0]->fVisualized);
		assertVectorEquality(Vector2((MAGIC_FIRE_TICK)*0.01+1, -1.999), fEntityFactory->fBullets[0]->getPosition());
		
		fGame->update(MAGIC_FIRE_TICK); // No firing, to short after the first one.
		CPPUNIT_ASSERT_EQUAL(6, (int)fEntityFactory->fBullets.size()); // The AI's use the MockShipDriver
		
		fGame->update(1000);
		CPPUNIT_ASSERT_EQUAL(6, (int)fEntityFactory->fBullets.size()); // The AI's use the MockShipDriver
		
		fGame->update(MAGIC_FIRE_TICK); // Fire again
		CPPUNIT_ASSERT_EQUAL(12, (int)fEntityFactory->fBullets.size()); // The AI's use the MockShipDriver
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
