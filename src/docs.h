/**
 * \mainpage
 *
 * \section game The game
 * Space Invaders is an addictive game where the users mission is to protect his space ship from enemies.
 *
 * \section library The library
 * This library implements the game logic for the game, without visualizing the game.
 *
 * \section zabbr The GUI Library (zabbr)
 * Originally this GUI library was called AGPSGF (A General Purpose SDL GUI Framework), 
 * but this was not marketable so it was renamed to zabbr (without meaning).
 *
 * \section sdl The SDL interface
 * This executable is based on the zabbr lib and the si lib and visualizes the game with SDL.
*/

/**
 * \namespace SI
 *
 * SI is the namespace where all classes and functions are defined for the space-invaders library.
*/

/**
 * \page highscore-format Highscore XML Format
 *
 * \section intro Introduction.
 * The highscore file format is a very simple XML format.
 *
 * \section root Basic structure.
 * The root element is &lt;highscore&gt;, the only possible child of the root element is &lt;entry&gt;.
 * The &lt;entry&gt; element should have the following attributes:
 *  \li name: The name of the highscore holder. (a non-zero string)
 *  \li score: Numerical (integer) value of the score of the player.
*/
