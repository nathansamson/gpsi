#ifndef INC_GAMEVISUALIZER_H
#define INC_GAMEVISUALIZER_H

/** \file
 * File for the game visualizer.
 *
 * @author Nathan Samson
*/

#include <string>

namespace SI {
	/**
	 * Interface for visualizing global game properties.
	*/
	class IGameVisualizer {
	public:
		virtual ~IGameVisualizer() {}
	
		/**
		 * Draw the game.
		*/
		virtual void draw() = 0;
		
		/**
		 * Checks if we are in a non game state (like pause, level change).
		*/
		virtual bool inNonGamePhase() = 0;
		
		/**
		 * Let the visualizer know that the user died.
		*/
		virtual void userDies() = 0;
		
		/**
		 * Let the visualizer know that the user has won.
		*/
		virtual void userWins() = 0;
		
		/**
		 * Let the visualizer know that the level changed.
		*/
		virtual void levelChange(std::string) = 0;
	};
}

#endif
