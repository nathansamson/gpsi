#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "synchronousdrivertest.h"
#include "misc/boundingbox.h"

namespace SITest {
	#define SYNCDRIVER_TEST(name) new CppUnit::TestCaller<SynchronousDriverTest>( \
	                                   #name, \
	                                   &SynchronousDriverTest::name) \
	
	void SynchronousDriverTest::setUp() {
		fDriver = new SI::SynchronousDriver(2.0);
		ShipType t;
		t.fBoundingShapeDesc = new BoundingBoxDescription(0.0, 0.0);
		fShip = new SITest::MockShip(fDriver, SI::Vector2(0.0, 0.0), t, 0);
		delete t.fBoundingShapeDesc;
	}
	
	void SynchronousDriverTest::tearDown() {
		delete fShip;
	}
	
	void SynchronousDriverTest::testMoveNormal() {
		fShip->update(10);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(0.002, -0.001), fShip->getPosition());
		fShip->update(10000-10);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(2.0, -1.0), fShip->getPosition());
		fShip->update(10);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.998, -1.001), fShip->getPosition());
		fShip->update(10000-10);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(0.00, -2.000), fShip->getPosition());
		fShip->update(10000+10);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(-1.998, -3.001), fShip->getPosition());
		fShip->update(20000);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.998, -5.001), fShip->getPosition());
	}
	
	CppUnit::Test* SynchronousDriverTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Synchronous driver test");
		suiteOfTests->addTest(SYNCDRIVER_TEST(testMoveNormal));
		return suiteOfTests;
	}
}
