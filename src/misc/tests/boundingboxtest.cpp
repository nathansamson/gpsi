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
	}
	
	void BoundingBoxTest::tearDown() {
	}
	
	void BoundingBoxTest::testDoNotIntersects() {
		BoundingBox* one = new BoundingBox(1.0, 1.5);
		one->setOffset(Vector2(0.0, 0.0));
		
		BoundingBox* two = new BoundingBox(2.0, 5.0);
		two->setOffset(Vector2(2.0, 3.0));
		
		CPPUNIT_ASSERT(!one->intersects(two));
		CPPUNIT_ASSERT(!two->intersects(one));
		
		delete one;
		delete two;
	}
	
	void BoundingBoxTest::testDoIntersects() {
		BoundingBox* one = new BoundingBox(1.0, 1.5);
		one->setOffset(Vector2(2.0, 4.0));
		
		BoundingBox* two = new BoundingBox(2.0, 5.0);
		two->setOffset(Vector2(2.0, 3.0));
		
		CPPUNIT_ASSERT(one->intersects(two));
		CPPUNIT_ASSERT(two->intersects(one));
		
		delete one;
		delete two;
	}
	
	void BoundingBoxTest::testWithUnresolved() {
		BoundingBox* box = new BoundingBox(1.0, 1.0);
		MockBoundingShape* mock = new MockBoundingShape();
		
		try {
			mock->intersects(box);
			CPPUNIT_FAIL("This should be skipped");
		} catch (UnresolvedIntersectionException& e) {
			CPPUNIT_ASSERT(mock == e.first);
			CPPUNIT_ASSERT(box == e.second);
		} catch (...) {
			CPPUNIT_FAIL("Unresolved exception problems should throw UnresolvedIntersectionException");
		}
		
		box->intersects(mock);
		CPPUNIT_ASSERT(!mock->fRecursive);
		
		delete box;
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
