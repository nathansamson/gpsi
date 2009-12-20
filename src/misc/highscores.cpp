#include <algorithm>

#include "tinyxml/ticpp.h"
#include "misc/highscores.h"

bool highscoreComp(std::pair<std::string, int> a,
                   std::pair<std::string, int> b) {
	return a.second > b.second;
}

namespace SI {
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
	
	Highscores::~Highscores() {
	}
	
	bool Highscores::isHighscore(int score) {
		if (fList.size() < fMaxEntries) {
			return true;
		} else {
			return fList.back().second < score;
		}
	}
	
	Highscores::HighscoreList Highscores::setHighscore(std::string name, int score,
	                                       int context, int entries) {
		
		int pos = 0;
		for (InternalHighscoreList::iterator it = fList.begin(); it != fList.end(); it++) {
			if ((*it).second < score) {
				fList.insert(it, 1, ScoreEntry(name, score)); 
				break;
			}
			pos++;
		}
		if (fList.size() > fMaxEntries) {
			fList.erase(fList.begin()+fMaxEntries, fList.end());
		}
		
		HighscoreList subset;
		if (pos < entries) {
			// the context is bad, so we will fill with 2 * context + entries + 1
			entries = 2 * context + entries + 1;
			int pos = 1;
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
			
			unsigned int contextLeft = pos - context + 1;
			unsigned int contextRight = pos + context + 1;
			
			if (contextRight >= fList.size()) {
				contextLeft -= (contextRight - fList.size());
				contextRight = fList.size();
			}
			
			for (unsigned int i = contextLeft; i <= contextRight; i++) {
				subset[i] = fList[i-1];
			}
		}
		return subset;
	}
	
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
