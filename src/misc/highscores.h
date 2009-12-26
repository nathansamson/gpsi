#ifndef INC_HIGSCORES_H
#define INC_HIGHSCORES_H

/** \file
 * File for the highscores.
 *
 * @author Nathan Samson
*/

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
		 * An updated score entry.
		*/
		class UpdatedScoreEntry {
		public:
			UpdatedScoreEntry();
			UpdatedScoreEntry(std::string, int, bool);
			
			bool operator==(const UpdatedScoreEntry& o);
			
			std::string getName();
			int getScore();
			bool isUpdated();
			
			
		private:
			/**
			 * Name of the entry-holder.
			*/
			std::string fName;
			
			/**
			 * The score of the entry.
			*/
			int fScore;
		
			/**
			 * Flag to see if the entry is updated.
			*/
			bool fUpdated;
		};
		
		/**
		 * A map of highscores, the first parameter is the position in the list, the second is the scoreentry.
		*/
		typedef std::map<unsigned int, ScoreEntry> HighscoreList;
		
		/**
		 * A map of highscores, the first parameter is the position in the list, the second is the updated scoreentry.
		*/
		typedef std::map<unsigned int, UpdatedScoreEntry> UpdatedHighscoreList;
	
		Highscores(std::string, unsigned int);
		~Highscores();
		
		bool isHighscore(int);
		UpdatedHighscoreList setHighscore(std::string, int, unsigned int, unsigned int);
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
