#pragma once

#include "Cell.h"
#include "GUI.h"
class Grid;

class Player 
{
	int lives;    // number of lives (initially 3)
	float health; // player's health percentage (initially 100% -> full health)
	float score;  // player's score (initially 0)
	Cell PositionCell;

public:

	Player(Cell pos); // Constructor

	int get_lives();

	float get_health();

	float get_score();

	void set_lives(int);

	void set_health(float);

	void set_score(float);

	void setPosition(Cell);
	void Move(Grid* pGrid, ActionType MoveAction); // Moves the Player in a specific direction if possible
};

