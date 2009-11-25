#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "game/ship.h"
#include "shiptest.h"

namespace SITest {
	#define SHIP_TEST(name) new CppUnit::TestCaller<ShipTest>( \
	                                   #name, \
	                                   &ShipTest::name) \
	
	void ShipTest::setUp() {
		fShip = new Ship(new MockShipDriver());
	}
	
	void ShipTest::tearDown() {
		delete fShip;
	}
	
	void ShipTest::testUpdate() {
		assertVectorEquality(Vector2(0, 0), fShip->getPosition());
		fShip->update(100);
		assertVectorEquality(Vector2(1, 0), fShip->getPosition());
		fShip->update(0);
		assertVectorEquality(Vector2(1, 0), fShip->getPosition());
	}
	
	CppUnit::Test* ShipTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Vector2 Test");
		suiteOfTests->addTest(SHIP_TEST(testUpdate));
		return suiteOfTests;
	}
	
	void ShipTest::assertVectorEquality(Vector2 expected, Vector2 actual) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getX(), actual.getX(), 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getY(), actual.getY(), 0.0001);
	}
	
	void MockShipDriver::update(int ticks) {
		move(Vector2(1.0/100, 0) * ticks);
	}
}
