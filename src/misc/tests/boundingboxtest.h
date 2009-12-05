#ifndef INC_BOUNDINGBOX_TEST_H
#define INC_BOUNDINGBOX_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/boundingbox.h"

namespace SITest {
	using namespace SI;

	class BoundingBoxTest : public CppUnit::TestFixture {
	public:
		void setUp();
		void tearDown();
		
		//Tests
		void testDoNotIntersects();
		void testDoIntersects();
		void testWithUnresolved();

		static CppUnit::Test* suite();
	};
	
}

#endif // INC_VECTOR2_TEST_H
