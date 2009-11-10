#ifndef INC_VECTOR2_TEST_H
#define INC_VECTOR2_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/vector2.h"

namespace sitest {
	using namespace si;

	class Vector2Test : public CppUnit::TestFixture {
		public:
			void setUp();
			void tearDown();
			
			//Tests
			void testAddition();
			void testSubtraction();
			void testNegative();
			
			static CppUnit::Test* suite();
		private:
			Vector2 v1, v2, v3;
			void assertVectorEquality(Vector2 v1, Vector2 v2);
	};
	
}

#endif // INC_VECTOR2_TEST_H
