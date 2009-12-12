#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "misc/boundingbox.h"
#include "guntest.h"
#include "game/tests/test.h"

namespace SITest {
	#define GUN_TEST(name) new CppUnit::TestCaller<GunTest>( \
	                                   #name, \
	                                   &GunTest::name) \
	
	void GunTest::setUp() {
		fEntityFactory = new MockGameEntityFactory();
		ShipType shiptype;
		shiptype.fBoundingShapeDesc = new BoundingBoxDescription(1.0, 1.0);
		fBulletType.fSpeed = Vector2(0.0, 0.01);
		fBulletType.fBoundingShapeDesc = new BoundingBoxDescription(0.1, 0.1);
		fShip = new Ship(new MockShipDriver(), Vector2(0, 0), 0, new EntityGroup("group"), shiptype, fEntityFactory);
		fGun = new Gun(500, fEntityFactory, fShip, Vector2(1.0, 0.5), fBulletType);
	}
	
	void GunTest::tearDown() {
		delete fGun;
		delete fShip;
		delete fEntityFactory;
		delete fBulletType.fBoundingShapeDesc;
	}
	
	void GunTest::testConstruction() {
		Bullet* b = dynamic_cast<Bullet*>(fGun->fire());
		CPPUNIT_ASSERT(b != 0);
		
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.0, 0.5), b->getPosition());
		CPPUNIT_ASSERT_EQUAL(0, b->getDirection());
		CPPUNIT_ASSERT("group" == b->getGroup()->getName());
		
		b->update(100);
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.0, 0.5+100*0.01), b->getPosition());
	}
	
	void GunTest::testFireOnlyAfterReloadTime() {
		Bullet* b = dynamic_cast<Bullet*>(fGun->fire());
		CPPUNIT_ASSERT(b != 0);
		
		fGun->update(300);
		b = dynamic_cast<Bullet*>(fGun->fire());
		CPPUNIT_ASSERT(b == 0);
		
		fGun->update(200);
		b = dynamic_cast<Bullet*>(fGun->fire());
		CPPUNIT_ASSERT(b != 0);
	}
	
	void GunTest::testToggleFire() {
		Bullet* b = dynamic_cast<Bullet*>(fGun->fire());
		CPPUNIT_ASSERT(b != 0);
		
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(1.0, 0.5), b->getPosition());
		
		fGun->update(600);
		b = dynamic_cast<Bullet*>(fGun->fire());
		SITEST_ASSERT_VECTORS_EQUAL(Vector2(-1.0, -0.5), b->getPosition());
	}
	
	CppUnit::Test* GunTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Gun test");
		suiteOfTests->addTest(GUN_TEST(testConstruction));
		suiteOfTests->addTest(GUN_TEST(testFireOnlyAfterReloadTime));
		suiteOfTests->addTest(GUN_TEST(testToggleFire));
		return suiteOfTests;
	}
}
