#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "misc/tests/boundingboxtest.h"

namespace SITest {

	class MockBoundingShape: public VBoundingShape {
	public:
		MockBoundingShape(): fRecursive(true) {
		}
	
		bool intersects(VBoundingShape* o) {
			return this->intersects(o, true);
		}
		
		bool intersects(VBoundingShape* o, bool r) {
			fRecursive = r;
			if (r) {
				return o->intersects(this, false);
			} else {
				return false;
			}
		}
		
		bool fRecursive;
	};

	#define BOUNDINGBOX_TEST(name) new CppUnit::TestCaller<BoundingBoxTest>( \
		                               #name, \
		                               &BoundingBoxTest::name) \

	void BoundingBoxTest::setUp() {
		BoundingBoxDescription* fDescOne = new BoundingBoxDescription(1.0, 1.5);
		BoundingBoxDescription* fDescTwo = new BoundingBoxDescription(2.0, 5.0);
		fOne = new BoundingBox(fDescOne);
		fTwo = new BoundingBox(fDescTwo);
		delete fDescOne;
		delete fDescTwo;
	}
	
	void BoundingBoxTest::tearDown() {
		delete fOne;
		delete fTwo;
	}
	
	void BoundingBoxTest::testDoNotIntersects() {
		fOne->setOffset(Vector2(0.0, 0.0));
		fTwo->setOffset(Vector2(2.0, 3.0));
		
		CPPUNIT_ASSERT(!fOne->intersects(fTwo));
		CPPUNIT_ASSERT(!fTwo->intersects(fOne));
	}
	
	void BoundingBoxTest::testDoIntersects() {
		fOne->setOffset(Vector2(2.0, 4.0));
		fTwo->setOffset(Vector2(2.0, 3.0));
		
		CPPUNIT_ASSERT(fOne->intersects(fTwo));
		CPPUNIT_ASSERT(fTwo->intersects(fOne));
	}
	
	void BoundingBoxTest::testWithUnresolved() {
		MockBoundingShape* mock = new MockBoundingShape();
		
		try {
			mock->intersects(fOne);
			CPPUNIT_FAIL("This should be skipped");
		} catch (UnresolvedIntersectionException& e) {
			CPPUNIT_ASSERT(mock == e.first);
			CPPUNIT_ASSERT(fOne == e.second);
		} catch (...) {
			CPPUNIT_FAIL("Unresolved exception problems should throw UnresolvedIntersectionException");
		}
		
		fOne->intersects(mock);
		CPPUNIT_ASSERT(!mock->fRecursive);

		delete mock;
	}
	
	CppUnit::Test* BoundingBoxTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Bounding box Test");
		suiteOfTests->addTest(BOUNDINGBOX_TEST(testDoNotIntersects));
		suiteOfTests->addTest(BOUNDINGBOX_TEST(testDoIntersects));
		suiteOfTests->addTest(BOUNDINGBOX_TEST(testWithUnresolved));
		return suiteOfTests;
	}
}
