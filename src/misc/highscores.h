#ifndef INC_HIGSCORES_H
#define INC_HIGHSCORES_H

#include <string>
#include <vector>
#include <map>

namespace SI {
	/**
	 * A highscore list.
	*/
	class Highscores {
	public:
		/**
		 * A score entry.
		*/
		typedef std::pair<std::string, int> ScoreEntry;
		
		/**
		 * A map of highscores, the first parameter is the position in the list, the second is the scoreentry.
		*/
		typedef std::map<unsigned int, ScoreEntry> HighscoreList;
	
		Highscores(std::string, unsigned int);
		~Highscores();
		
		bool isHighscore(int);
		HighscoreList setHighscore(std::string, int, unsigned int, unsigned int);
		HighscoreList getBestHighscores(int);
		void save(std::string);
	private:
		/**
		 * A list of highscores.
		*/
		typedef std::vector<ScoreEntry> InternalHighscoreList;
	
		/**
		 * The list of highscore entries.
		*/
		InternalHighscoreList fList;
		
		/**
		 * The maximum number of entries in the list.
		*/
		unsigned int fMaxEntries;
	};
}

#endif // INC_HIGHSCORES_H
