






#ifndef BULLET_CLASS
#define BULLET_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>

//#include "EntityClass.h"
#include "EntityClass.h"



//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::


////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Bullet :public Entity { // класс Игрока
private:
	//float x, y = 0;
	//int dir;

public:
	/*
	float w, h, dx, dy, speed = 0; //координаты игрока х и у, h - высота, w - ширина, ускорение (dx по х и dy по у), сама скорость
	int playerScore, health, ammo;// (dir - direction) направление движения игрока; playerScore - очки; health - переменная, хранящая жизни игрока

	bool life;//переменная жизнь, логическая
	bool isMove, isSelect;//добавили переменные состояния движения и выбора объекта

	sf::String File; //файл с расширением
	sf::Image image;//сфмл изображение
	sf::Vector2u playerImSize;
	sf::Texture texture;//сфмл текстура
	sf::Sprite sprite;//сфмл спрайт
	*/

	float offsetX, offsetY;

	//int playerScore, health, ammo;// (dir - direction) направление движения игрока; playerScore - очки; health - переменная, хранящая жизни игрока
	int speed;
	bool isMove;
	bool touched;
	bool isReady;
	bool isPlayerBullet;

	sf::Vector2f normVec;

	Bullet(sf::String sImage, float X, float Y, float OFFsetX, float OFFsetY, sf::String Name, bool isPlayerBullet);
	//Bullet(sf::String *sImage, sf::Vector2f startPos, sf::Vector2f offset, sf::String Name, bool isPlayerBullet); //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту

	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);


	void update(float &time, sf::String *TileMap, float destinX, float destinY, float sourceX, float sourceY);//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void mapReaction(sf::String *TileMapX, float &time);
	
	sf::Vector2f findDirection(sf::Vector2f &destination, sf::Vector2f &holderCoord);

	void Bullet::followForHolder(sf::Vector2f &destination, sf::Vector2f &holderCoord);

	/*
	float getPlayerCoordinateX();	//этим методом будем забирать координату Х
	float getPlayerCoordinateY();	//этим методом будем забирать координату Y

	float changePlayerCoordinateX_by(float addX);
	float changePlayerCoordinateY_by(float addY);

	float changePlayerCoordinateX_to(float newX);
	float changePlayerCoordinateY_to(float newY);
	*/


};

#endif // !PLAYER_CLASS