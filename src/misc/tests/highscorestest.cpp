#include <cstdio>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>

#include "misc/tests/highscorestest.h"

namespace SITest {

	#define HIGHSCORES_TEST(name) new CppUnit::TestCaller<HighscoresTest>( \
		                               #name, \
		                               &HighscoresTest::name) \

	#define HENTRY(name, score) std::pair<std::string, int>(name, score)
	#define HUENTRY(name, score, updated) Highscores::UpdatedScoreEntry(name, score, updated)

	void HighscoresTest::setUp() {
	}
	
	void HighscoresTest::tearDown() {
	}
	
	void HighscoresTest::testIsHighscore() {
		Highscores highScores("misc/tests/highscores/10items.high", 20); // 20 entries allowed so its an highscore by default
		CPPUNIT_ASSERT(highScores.isHighscore(0));
		
		highScores = Highscores("misc/tests/highscores/10items.high", 10);
		CPPUNIT_ASSERT(!highScores.isHighscore(0));
		
		highScores = Highscores("misc/tests/highscores/10items.high", 10);
		CPPUNIT_ASSERT(highScores.isHighscore(4500));
		
		highScores = Highscores("misc/tests/highscores/10itemsunordered.high", 10);
		CPPUNIT_ASSERT(highScores.isHighscore(4500));
		
		highScores = Highscores("misc/tests/highscores/10items.high", 5);
		CPPUNIT_ASSERT(highScores.isHighscore(7000));
		
		highScores = Highscores("misc/tests/highscores/10items.high", 5);
		CPPUNIT_ASSERT(!highScores.isHighscore(3000));
	}
	
	void HighscoresTest::testGetHighscores() {
		Highscores highScores("misc/tests/highscores/10items.high", 20);
		
		Highscores::HighscoreList list = highScores.getBestHighscores(4);
		CPPUNIT_ASSERT(list.size() == 4);
		CPPUNIT_ASSERT(HENTRY("Nathan1", 10000) == list[1]);
		CPPUNIT_ASSERT(HENTRY("Nathan2", 8000) == list[2]);
		CPPUNIT_ASSERT(HENTRY("Nathan3", 7000) == list[3]);
		CPPUNIT_ASSERT(HENTRY("Nathan4", 6000) == list[4]);
		
		list = highScores.getBestHighscores(15);
		CPPUNIT_ASSERT(list.size() == 10);
		CPPUNIT_ASSERT(HENTRY("Nathan1", 10000) == list[1]);
		CPPUNIT_ASSERT(HENTRY("Nathan10", 500) == list[10]);
		
		highScores = Highscores("misc/tests/highscores/10items.high", 5);
		list = highScores.getBestHighscores(15);
		CPPUNIT_ASSERT(list.size() == 5);
		CPPUNIT_ASSERT(HENTRY("Nathan1", 10000) == list[1]);
		CPPUNIT_ASSERT(HENTRY("Nathan5", 5000) == list[5]);
	}
	
	void HighscoresTest::testSetHighscore() {
		Highscores highScores("misc/tests/highscores/10items.high", 20);
		
		// We say we have place for 10 items (5 best + 2 * 2 contect + 1 new)
		Highscores::UpdatedHighscoreList list = highScores.setHighscore("New score", 750, 2, 5);
		CPPUNIT_ASSERT(list.size() == 10);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[2]);	
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[3]);
		CPPUNIT_ASSERT(HUENTRY("Nathan4", 6000, false) == list[4]);
		CPPUNIT_ASSERT(HUENTRY("Nathan5", 5000, false) == list[5]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("New score", 750, true) == list[10]);
		CPPUNIT_ASSERT(HUENTRY("Nathan10", 500, false) == list[11]);
		
		list = highScores.setHighscore("Best score", 20050, 2, 5);
		CPPUNIT_ASSERT(list.size() == 10);
		CPPUNIT_ASSERT(HUENTRY("Best score", 20050, true) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[2]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[3]);
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[4]);
		CPPUNIT_ASSERT(HUENTRY("Nathan4", 6000, false) == list[5]);
		CPPUNIT_ASSERT(HUENTRY("Nathan5", 5000, false) == list[6]);
		CPPUNIT_ASSERT(HUENTRY("Nathan6", 4000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[10]);
		
		list = highScores.setHighscore("Middle score", 3500, 2, 2);
		CPPUNIT_ASSERT(list.size() == 7);
		CPPUNIT_ASSERT(HUENTRY("Best score", 20050, false) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[2]);
		CPPUNIT_ASSERT(HUENTRY("Nathan5", 5000, false) == list[6]);
		CPPUNIT_ASSERT(HUENTRY("Nathan6", 4000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Middle score", 3500, true) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[10]);
		
		highScores = Highscores("misc/tests/highscores/10items.high", 10);
		list = highScores.setHighscore("New score", 750, 2, 3);
		CPPUNIT_ASSERT(list.size() == 8);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[2]);	
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[3]);
		CPPUNIT_ASSERT(HUENTRY("Nathan6", 4000, false) == list[6]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("New score", 750, true) == list[10]);
		
		highScores = Highscores("misc/tests/highscores/10items.high", 20);
		list = highScores.setHighscore("Last highscore", 400, 2, 3);
		CPPUNIT_ASSERT(list.size() == 8);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[2]);	
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[3]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("Nathan10", 500, false) == list[10]);
		CPPUNIT_ASSERT(HUENTRY("Last highscore", 400, true) == list[11]);
		
		highScores = Highscores("misc/tests/highscores/10items.high", 20);
		list = highScores.setHighscore("Best highscore", 40000, 2, 15);
		CPPUNIT_ASSERT(list.size() == 11);
		CPPUNIT_ASSERT(HUENTRY("Best highscore", 40000, true) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[2]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[3]);	
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[4]);
		CPPUNIT_ASSERT(HUENTRY("Nathan4", 6000, false) == list[5]);
		CPPUNIT_ASSERT(HUENTRY("Nathan5", 5000, false) == list[6]);
		CPPUNIT_ASSERT(HUENTRY("Nathan6", 4000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[10]);
		CPPUNIT_ASSERT(HUENTRY("Nathan10", 500, false) == list[11]);
		
		highScores = Highscores("misc/tests/highscores/10items.high", 20);
		list = highScores.setHighscore("Last highscore", 0, 7, 2);
		CPPUNIT_ASSERT(list.size() == 11);
		CPPUNIT_ASSERT(HUENTRY("Nathan1", 10000, false) == list[1]);
		CPPUNIT_ASSERT(HUENTRY("Nathan2", 8000, false) == list[2]);	
		CPPUNIT_ASSERT(HUENTRY("Nathan3", 7000, false) == list[3]);
		CPPUNIT_ASSERT(HUENTRY("Nathan4", 6000, false) == list[4]);
		CPPUNIT_ASSERT(HUENTRY("Nathan5", 5000, false) == list[5]);
		CPPUNIT_ASSERT(HUENTRY("Nathan6", 4000, false) == list[6]);
		CPPUNIT_ASSERT(HUENTRY("Nathan7", 3000, false) == list[7]);
		CPPUNIT_ASSERT(HUENTRY("Nathan8", 2000, false) == list[8]);
		CPPUNIT_ASSERT(HUENTRY("Nathan9", 1000, false) == list[9]);
		CPPUNIT_ASSERT(HUENTRY("Nathan10", 500, false) == list[10]);
		CPPUNIT_ASSERT(HUENTRY("Last highscore", 0, true) == list[11]);
	}
	
	void HighscoresTest::testSave() {
		Highscores highScores("misc/tests/highscores/10items.high", 20);
		highScores.setHighscore("New score", 750, 2, 3);
		highScores.setHighscore("Middle score", 3500, 2, 2);
		highScores.setHighscore("Best score", 20050, 2, 5);
		
		highScores.save("tmp.high");
		
		highScores = Highscores("tmp.high", 15);
		Highscores::HighscoreList list = highScores.getBestHighscores(15);
		CPPUNIT_ASSERT(list.size() == 13);
		CPPUNIT_ASSERT(HENTRY("Best score", 20050) == list[1]);
		CPPUNIT_ASSERT(HENTRY("Nathan1", 10000) == list[2]);
		CPPUNIT_ASSERT(HENTRY("Nathan2", 8000) == list[3]);	
		CPPUNIT_ASSERT(HENTRY("Nathan3", 7000) == list[4]);
		CPPUNIT_ASSERT(HENTRY("Nathan4", 6000) == list[5]);
		CPPUNIT_ASSERT(HENTRY("Nathan5", 5000) == list[6]);
		CPPUNIT_ASSERT(HENTRY("Nathan6", 4000) == list[7]);
		CPPUNIT_ASSERT(HENTRY("Middle score", 3500) == list[8]);
		CPPUNIT_ASSERT(HENTRY("Nathan7", 3000) == list[9]);
		CPPUNIT_ASSERT(HENTRY("Nathan8", 2000) == list[10]);
		CPPUNIT_ASSERT(HENTRY("Nathan9", 1000) == list[11]);
		CPPUNIT_ASSERT(HENTRY("New score", 750) == list[12]);
		CPPUNIT_ASSERT(HENTRY("Nathan10", 500) == list[13]);
		remove("tmp.high");
	}
	
	CppUnit::Test* HighscoresTest::suite() {
		CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Highscores Test");
		suiteOfTests->addTest(HIGHSCORES_TEST(testIsHighscore));
		suiteOfTests->addTest(HIGHSCORES_TEST(testGetHighscores));
		suiteOfTests->addTest(HIGHSCORES_TEST(testSetHighscore));
		suiteOfTests->addTest(HIGHSCORES_TEST(testSave));
		return suiteOfTests;
	}
}

