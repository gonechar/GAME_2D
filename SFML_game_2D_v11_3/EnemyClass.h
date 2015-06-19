




#ifndef ENEMY_CLASS
#define ENEMY_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>

//#include "EntityClass.h"
#include "CreatureClass.h"
#include "BulletClass.h"
#include <list>

//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::


////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Enemy :public Creature { // класс Игрока
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

	sf::Image bulletImageArr[bullNum];
	std::list<Bullet*>  bullets;//создаю список, сюда буду кидать объекты.например врагов.
	//std::list<Bullet*>::iterator bIt;//итератор чтобы проходить по эл-там списка

	float shotTimer;

	float damage;
	float waitFireTime;
	int level;

	float visibleRadius;
	int playerScore, health, ammo;// (dir - direction) направление движения игрока; playerScore - очки; health - переменная, хранящая жизни игрока
	bool isPlayerVisible;
	bool isTryToFind;

	Enemy(sf::String sImage, float X, float Y, sf::String Name); //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	
	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);

	void update(float time, sf::String *TileMap, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time, sf::String *TileMap, Creature *sombody, Bullet *bullet);//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.

	void mapReaction(sf::String *TileMapX, float time);
	float getPlayerAngle(sf::Vector2f &playerCoord, sf::RenderWindow *window, Bullet *bullet);

	
	void easyAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);
	void mediumAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);

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