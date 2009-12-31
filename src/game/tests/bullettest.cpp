#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "bullettest.h"
#include "misc/boundingbox.h"

namespace SITest {
	#define BULLET_TEST(name) new CppUnit::TestCaller<BulletTest>( \
	                                   #name, \
	                                   &BulletTest::name) \
	
	void BulletTest::setUp() {
		IBoundingShapeDescription* shape = new BoundingBoxDescription(0.1, 0.1);
		BulletType* b = new BulletType(shape, Vector2(0.000, 0.001));
		fBullet = new Bullet(Vector2(0.0, 0.0), 0, 0, b, 0);
		delete b;
	}
	
	void BulletTest::tearDown() {
		delete fBullet;
	}
	
	void BulletTest::testBullet() {
		SITEST_ASSERT_VECTORS_EQUAL(SI::Vector2(0.0, 0.0), fBullet->getPosition());
		fBullet->update(100);
		SITEST_ASSERT_VECTORS_EQUAL(SI::Vector2(0.0, 0.1), fBullet->getPosition());
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, fBullet->getImpact(), 1E-10);
	}
	
	CppUnit::Test* BulletTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Bullet test");
		suiteOfTests->addTest(BULLET_TEST(testBullet));
		return suiteOfTests;
	}
}
