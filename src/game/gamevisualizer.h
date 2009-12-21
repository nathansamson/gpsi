#ifndef INC_GAMEVISUALIZER_H
#define INC_GAMEVISUALIZER_H

#include <string>

namespace SI {
	/**
	 * Interface for visualizing global game properties.
	 *
	 * 
	*/
	class IGameVisualizer {
	public:
		virtual ~IGameVisualizer() {}
	
		virtual void draw() = 0;
		virtual bool inNonGamePhase() = 0;
		virtual void userDies() = 0;
		virtual void userWins() = 0;
		virtual void levelChange(std::string) = 0;
	};
}

#endif
