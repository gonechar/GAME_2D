
#ifndef STRUCT_H
#define STRUCT_H

#include <SFML\Graphics.hpp>
#include <locale>

/*
const int HEIGHT_MAP = 40;//размер карты высота
const int WIDTH_MAP = 61;//размер карты ширина 
*/

const int HEIGHT_MAP = 40;//размер карты высота
const int WIDTH_MAP = 124;//размер карты ширина 

const float tileMapSize = 32;

const int enemyNumber = 3;
const int bullNum = 5;

const bool arrows = true;
const bool WASD = true;

const float playerScale = 1.5;

enum Direction2D {
	RIGHT_2D = 0, LEFT_2D = 1, DOWN_2D = 2, UP_2D = 3, RD = 4, RU = 5
};

enum Axis2D {
	HORIZONTAL = 0, VERTICAL = 1
};

enum KeyboardPress {
	PRESS_UP = sf::Keyboard::Up, PRESS_DOWN = sf::Keyboard::Down, PRESS_LEFT = sf::Keyboard::Left, PRESS_RIGHT = sf::Keyboard::Right
};

const float PI = 3.14159265;

const int WIN_HEIGHT = 768;
const int WIN_WIDTH = 1366;

#endif