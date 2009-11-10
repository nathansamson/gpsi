#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "vector2test.h"

namespace sitest {

	void Vector2Test::setUp() {
		v1 = Vector2(3.14, 2.71);
		v2 = Vector2(-8.8, 71.2);
		v3 = Vector2(3.14-8.8, 2.71+71.2);
	}
	
	void Vector2Test::tearDown() {
	}

	void Vector2Test::testAddition() {
		assertVectorEquality(v1 + v2, v3);
	}
	
	void Vector2Test::testSubtraction() {
		assertVectorEquality(v3 - v2, v1);
	}
	
	void Vector2Test::testNegative() {
		CPPUNIT_ASSERT(-v1 == -(-(-v1)));
		CPPUNIT_ASSERT(v1 == -(-v1));
		CPPUNIT_ASSERT(-v1 == Vector2(-3.14, -2.71));
	}
	
	CppUnit::Test* Vector2Test::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Vector2 Test");
		suiteOfTests->addTest(new CppUnit::TestCaller<Vector2Test>( 
		                               "testAdditon", 
		                               &sitest::Vector2Test::testAddition));
		suiteOfTests->addTest(new CppUnit::TestCaller<Vector2Test>(
		                               "testSubtraction",
		                               &Vector2Test::testSubtraction));
		return suiteOfTests;
	}
	
	void Vector2Test::assertVectorEquality(Vector2 v1, Vector2 v2) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(v1.getX(), v2.getX(), 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(v1.getY(), v2.getY(), 0.0001);
	}
}
