#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

enum ActionType // The actions supported (you can add more if needed)
{
	//  Possible action

	LOAD,	// Load game file
	SAVE,	// Save game to a file
	START,	// Start the game
	PAUSE,	//Pause the game
	////////////////////////////my extra actions////////////

	ENEMY, //ask the user to place an enemy tile.
	PLAYER, //ask the user to select where the player starts on the grid
	OBSTACLE, // ask the user to place an obstacle
	EMPTYCELL,// ask the user to clear existing cells rendering them empty
	HEART, // asks the user to place a heart cell that gives an extra life
	WINGS, // asks the user to place a wings cell that allows them to fly over 1 barrier
	EGG, // asks the user to place an Egg, the player must collect all eggs before they can escape
	ARMOUR, // asks the user to place an armour cells that gives extra hitpoints.
	BOMB, // asks the user to place a bomb cell Kills enemies in the region ±3 cells in the vertical and horizontal direction 
	FREEZER, // asks the user to place a freezer that slows down zombies.
	GOAL, // asks the user to place the spaceship that saves the player and wins the game



	////////////////////////////////////////////////////////
	EXIT,	// Exit Application
	////////////////////////////////////////////////////////


	////// Player move direction///////////////////////// 
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	NO_MOVE,

	EMPTY,				// a click inside empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// a click inside Grid Area
	STATUS 				// a click inside StatusBar Area
};

#endif