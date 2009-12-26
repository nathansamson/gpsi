/** \file
 * File for the highscores.
 *
 * @author Nathan Samson
*/

#include <algorithm>

#include "tinyxml/ticpp.h"
#include "misc/highscores.h"

bool highscoreComp(std::pair<std::string, int> a,
                   std::pair<std::string, int> b) {
	return a.second > b.second;
}

namespace SI {
	/**
	 * Public constructor.
	 *
	 * @param fileName the filename to load highscores.
	 * @param maxEntries the maximum of entries in the list.
	*/
	Highscores::Highscores(std::string fileName, unsigned int maxEntries): fMaxEntries(maxEntries) {
		ticpp::Document highscores(fileName);
		try {
			highscores.LoadFile();
			
			ticpp::Element* root = highscores.FirstChild("highscores")->ToElement();
			
			typedef ticpp::Iterator<ticpp::Element> iterator;
			for (iterator score = iterator("entry").begin(root); score != score.end(); score++) {
				fList.push_back(std::pair<std::string, int>(
				                           score->GetAttribute("name"),
				                           score->GetAttribute<int>("score")));
			}
			
			std::sort(fList.begin(), fList.end(), highscoreComp);
			if (fList.size() > fMaxEntries) {
				fList.erase(fList.begin()+fMaxEntries, fList.end());
			}
		} catch (ticpp::Exception e) {
			std::cout << e.what() << std::endl;
		}
	}
	
	/**
	 * Destructor.
	*/
	Highscores::~Highscores() {
	}
	
	/**
	 * Checks if a given score comes in the highscore list.
	 *
	 * @param score The score.
	 * @return True if score is a new high score, false if not.
	*/
	bool Highscores::isHighscore(int score) {
		if (fList.size() < fMaxEntries) {
			return true;
		} else {
			return fList.back().second < score;
		}
	}
	
	/**
	 * Insert a new highscore in the list.
	 *
	 * @param name The name of the winner.
	 * @param score The score of the winner.
	 * @param context The number of entries around the new highscore.
	 * @param entries The number of best entries.
	 *
	 * @return A highscore list with entries best entries and context entries before and after the new highscore.
	*/
	Highscores::HighscoreList Highscores::setHighscore(std::string name, int score,
	                                       unsigned int context, unsigned int entries) {
		
		unsigned int pos = 0;
		for (InternalHighscoreList::iterator it = fList.begin(); it != fList.end(); it++) {
			if ((*it).second < score) {
				fList.insert(it, 1, ScoreEntry(name, score)); 
				break;
			}
			pos++;
		}
		if (pos == fList.size()) {
			// We did not insert, the new score is the last score.
			fList.push_back(ScoreEntry(name, score));
		}
		if (fList.size() > fMaxEntries) {
			fList.erase(fList.begin()+fMaxEntries, fList.end());
		}
		
		HighscoreList subset;
		if (pos < entries) {
			// the context is bad, so we will fill with 2 * context + entries + 1
			entries = 2 * context + entries + 1;
			if (entries > fList.size()) {
				entries = fList.size();
			}
			unsigned int pos = 1;
			for (InternalHighscoreList::iterator it = fList.begin(); it != fList.begin()+entries && pos <= entries; it++) {
				subset[pos] = (*it);
				pos++;
			}
		} else {
			int best = 1;
			for (InternalHighscoreList::iterator it = fList.begin(); it != fList.begin()+entries; it++) {
				subset[best] = (*it);
				best++;
			}
			
			int contextLeft = pos - context + 1;
			int contextRight = pos + context + 1;
			
			if (contextRight >= (int)fList.size()) {
				contextLeft -= (contextRight - fList.size());
				contextRight = fList.size();
			}
			if (contextLeft < 1) {
				contextLeft = 1;
			}
			
			for (int i = contextLeft; i <= contextRight; i++) {
				subset[i] = fList[i-1];
			}
		}
		return subset;
	}
	
	/**
	 * Get the best highscore.
	 *
	 * @param entries The number of entries in the list.
	 *
	 * @return The list of best highscores.
	*/
	Highscores::HighscoreList Highscores::getBestHighscores(int entries) {
		HighscoreList subset;
		entries = std::min(entries, (int)fList.size());
		int i = 1;
		for (InternalHighscoreList::iterator it = fList.begin(); it != fList.begin()+entries; it++) {
			subset[i] = (*it);
			i++;
		}
		return subset;
	}
	
	/**
	 * Save the highscore to a file.
	 *
	 * @param fileName The filename to save the highscores file.
	*/
	void Highscores::save(std::string fileName) {
		ticpp::Document high(fileName);
		ticpp::Element root = ticpp::Element("highscores");
		
		for (InternalHighscoreList::iterator it = fList.begin(); it != fList.end(); it++) {
			ticpp::Element entry = ticpp::Element("entry");
			entry.SetAttribute("name", (*it).first);
			entry.SetAttribute<int>("score", (*it).second);
			root.InsertEndChild(entry);
		}
		high.InsertEndChild(root);
		
		high.SaveFile();
	}
}
