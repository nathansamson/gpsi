#ifndef INC_VECTOR2_TEST_H
#define INC_VECTOR2_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/vector2.h"

namespace SITest {
	using namespace SI;

	class Vector2Test : public CppUnit::TestFixture {
	public:
		void setUp();
		void tearDown();
		
		//Tests
		void testTrivialVectorOperations();
		void testLength();
		void testDotProduct();
		void testNormalize();
		

		// Operators
		void testVectorAddition();
		void testVectorSubtraction();
		void testNegative();
		void testScalarAddition();
		void testScalarSubtraction();
		void testScalarMultiplication();
		void testScalarDivision();
		void testComparison();



		static CppUnit::Test* suite();
	private:
		Vector2 v1, v2, v3, zero;
		void assertVectorEquality(Vector2 v1, Vector2 v2);
	};
	
}

#endif // INC_VECTOR2_TEST_H
