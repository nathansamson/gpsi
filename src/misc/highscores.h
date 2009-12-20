#ifndef INC_HIGSCORES_H
#define INC_HIGHSCORES_H

#include <string>
#include <vector>
#include <map>

namespace SI {
	class Highscores {
	public:
		typedef std::pair<std::string, int> ScoreEntry;
		typedef std::map<unsigned int, ScoreEntry> HighscoreList;
	
		Highscores(std::string, unsigned int);
		~Highscores();
		
		bool isHighscore(int);
		HighscoreList setHighscore(std::string, int, int, int);
		HighscoreList getBestHighscores(int);
		void save(std::string);
	private:
		typedef std::vector<ScoreEntry> InternalHighscoreList;
	
		InternalHighscoreList fList;
		unsigned int fMaxEntries;
	};
}

#endif // INC_HIGHSCORES_H
