#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "synchronousdrivertest.h"
#include "misc/boundingbox.h"

namespace SITest {
	#define SYNCDRIVER_TEST(name) new CppUnit::TestCaller<SynchronousDriverTest>( \
	                                   #name, \
	                                   &SynchronousDriverTest::name) \
	
	void clearSideEffects(std::vector<VGameEntity*> sideEffects) {
		for (std::vector<VGameEntity*>::iterator it = sideEffects.begin(); it != sideEffects.end(); it++) {
			delete (*it);
		}
	}
	
	void SynchronousDriverTest::setUp() {
		fDriver = new SI::SynchronousDriver(2.0);
		ShipType t;
		t.fBoundingShapeDesc = new BoundingBoxDescription(0.0, 0.0);
		t.fMaxSpeed = Vector2(0.0002, 0.0001);
		fEntityFactory = new MockGameEntityFactory();
		fShip = new SITest::MockShip(fDriver, SI::Vector2(0.0, 0.0), 0, 0, 0, t, fEntityFactory);
		delete t.fBoundingShapeDesc;
	}
	
	void SynchronousDriverTest::tearDown() {
		delete fShip;
		delete fEntityFactory;
	}
	
	void SynchronousDriverTest::testMoveNormal() {
		std::vector<VGameEntity*> sideEffects;
		sideEffects = fShip->update(10);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(0.002, -0.001), fShip->getPosition());
		
		sideEffects = fShip->update(10000-10);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(2.0, -1.0), fShip->getPosition());
		
		sideEffects = fShip->update(10);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.998, -1.001), fShip->getPosition());
		
		sideEffects = fShip->update(10);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.996, -1.002), fShip->getPosition());
		
		sideEffects = fShip->update(10000-20);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(0.00, -2.000), fShip->getPosition());
		
		sideEffects = fShip->update(10000+10);
		clearSideEffects(sideEffects);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(-2.002, -3.001), fShip->getPosition());
	}
	
	CppUnit::Test* SynchronousDriverTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Synchronous driver test");
		suiteOfTests->addTest(SYNCDRIVER_TEST(testMoveNormal));
		return suiteOfTests;
	}
}
