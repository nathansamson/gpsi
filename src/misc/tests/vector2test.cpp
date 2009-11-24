#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "misc/tests/vector2test.h"

namespace SITest {

	#define VECTOR2_TEST(name) new CppUnit::TestCaller<Vector2Test>( \
		                               #name, \
		                               &Vector2Test::name) \

	void Vector2Test::setUp() {
		v1 = Vector2(3.14, 2.71);
		v2 = Vector2(-8.8, 71.2);
		v3 = Vector2(3.14-8.8, 2.71+71.2);
		zero = Vector2();
	}
	
	void Vector2Test::tearDown() {
	}

	void Vector2Test::testTrivialVectorOperations() {
		v1 = v2;
		CPPUNIT_ASSERT(v1 == v2);
		
		v1.setX(-1.0);
		v1.setY(1.0);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, v1.getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v1.getY(), 1E-9);
	}

	void Vector2Test::testLength() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.147734321, v1.length(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, zero.length(), 1E-9);
	}
	
	void Vector2Test::testDotProduct() {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(165.32, v1.dotProduct(v2), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(165.32, v2.dotProduct(v1), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, zero.dotProduct(v1), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v1.dotProduct(zero), 1E-9);
	}
	
	void Vector2Test::testNormalize() {
		v1.normalize();
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.757039809, v1.getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.653368753, v1.getY(), 1E-9);
	}

	void Vector2Test::testVectorAddition() {
		assertVectorEquality(v3, v1 + v2);
		assertVectorEquality(v3, v1 += v2);
		assertVectorEquality(v3, v1);
	}
	
	void Vector2Test::testVectorSubtraction() {
		assertVectorEquality(v1, v3 - v2);
		assertVectorEquality(v1, v3 -= v2);
		assertVectorEquality(v1, v3);
	}
	
	void Vector2Test::testNegative() {
		CPPUNIT_ASSERT(-v1 == -(-(-v1)));
		CPPUNIT_ASSERT(v1 == -(-v1));
		CPPUNIT_ASSERT(-v1 == Vector2(-3.14, -2.71));
	}
	
	void Vector2Test::testScalarAddition() {
		CPPUNIT_ASSERT(1.34+v1 == v1+1.34);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.48, (1.34+v1).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.05, (1.34+v1).getY(), 1E-9);

		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.48, (v1 += 1.34).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(5.39, (v1 += 1.34).getY(), 1E-9);
	}
	
	void Vector2Test::testScalarSubtraction() {
		CPPUNIT_ASSERT(1.34-v1 == v1-1.34);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.48, (-1.34-v1).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.05, (-1.34-v1).getY(), 1E-9);
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(4.48, (v1 -= -1.34).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(2.71, (v1 -= 1.34).getY(), 1E-9);
	}
	
	void Vector2Test::testScalarMultiplication() {
		CPPUNIT_ASSERT(3.14*v1 == v1*3.14);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(9.8596, (v1*3.14).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(8.5094, (3.14*v1).getY(), 1E-9);
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(9.8596, (v1 *= 3.14).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(26.719516, (v1 *= 3.14).getY(), 1E-9);
	}
	
	void Vector2Test::testScalarDivision() {
		CPPUNIT_ASSERT(3.14/v1 == v1/3.14);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, (v1/3.14).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.863057325, (3.14/v1).getY(), 1E-9);
		
		CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, (v1 /= 3.14).getX(), 1E-9);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(0.274859021, (v1 /= 3.14).getY(), 1E-9);
	}
	
	void Vector2Test::testComparison() {
		CPPUNIT_ASSERT(v1 == v1);
		CPPUNIT_ASSERT(v1 != v2);
		v1 = v2;
		CPPUNIT_ASSERT(v1 == v2);
		v1 = Vector2(v3);
		CPPUNIT_ASSERT(v1 == v3);
	}
	
	CppUnit::Test* Vector2Test::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Vector2 Test");
		suiteOfTests->addTest(VECTOR2_TEST(testTrivialVectorOperations));
		suiteOfTests->addTest(VECTOR2_TEST(testLength));
		suiteOfTests->addTest(VECTOR2_TEST(testDotProduct));
		suiteOfTests->addTest(VECTOR2_TEST(testNormalize));
		suiteOfTests->addTest(VECTOR2_TEST(testVectorAddition));
		suiteOfTests->addTest(VECTOR2_TEST(testVectorSubtraction));
		suiteOfTests->addTest(VECTOR2_TEST(testNegative));
		suiteOfTests->addTest(VECTOR2_TEST(testScalarAddition));
		suiteOfTests->addTest(VECTOR2_TEST(testScalarSubtraction));
		suiteOfTests->addTest(VECTOR2_TEST(testScalarMultiplication));
		suiteOfTests->addTest(VECTOR2_TEST(testScalarDivision));
		suiteOfTests->addTest(VECTOR2_TEST(testComparison));
		return suiteOfTests;
	}
	
	void Vector2Test::assertVectorEquality(Vector2 expected, Vector2 actual) {
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getX(), actual.getX(), 0.0001);
		CPPUNIT_ASSERT_DOUBLES_EQUAL(expected.getY(), actual.getY(), 0.0001);
	}
}
