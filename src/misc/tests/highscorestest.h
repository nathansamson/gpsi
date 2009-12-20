#ifndef INC_HIGHSCORES_TEST_H
#define INC_HIGHSCORES_TEST_H

#include <cppunit/Test.h>
#include <cppunit/TestFixture.h>

#include "misc/highscores.h"

namespace SITest {
	using namespace SI;

	class HighscoresTest : public CppUnit::TestFixture {
	public:
		void setUp();
		void tearDown();
		
		void testIsHighscore();
		void testGetHighscores();
		void testSetHighscore();
		void testSave();
		
		static CppUnit::Test* suite();
	};
}

#endif //INC_HIGHSCORES_TEST
