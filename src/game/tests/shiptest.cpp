#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "game/ship.h"
#include "shiptest.h"
#include "game/tests/test.h"
#include "misc/boundingbox.h"

namespace SITest {
	#define SHIP_TEST(name) new CppUnit::TestCaller<ShipTest>( \
	                                   #name, \
	                                   &ShipTest::name) \
	
	void ShipTest::setUp() {
		ShipType s;
		s.fBoundingShapeDesc = new BoundingBoxDescription(1.0, 1.0);
		fShip = new Ship(new MockShipDriver(), Vector2(0, 0), 0, 0, s, new MockGameEntityFactory());
		delete s.fBoundingShapeDesc;
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
}
