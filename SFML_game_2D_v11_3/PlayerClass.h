



#ifndef PLAYER_CLASS
#define PLAYER_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>
//#include "EntityClass.h"
#include "CreatureClass.h"
#include "BulletClass.h"
#include <list>


//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::


////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player:public Creature { // класс Игрока
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

	bool isPistol, isRifle;

	int damage;

	float shotTimer;

	bool isReloading;
	int playerScore, health, ammo;// (dir - direction) направление движения игрока; playerScore - очки; health - переменная, хранящая жизни игрока
	int fireSpeed;

	Player(sf::String sImage, float X, float Y, sf::String Name); //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	
	

	

	
	void update(float &time, sf::String *TileMap, sf::Vector2f &cursor, Bullet *bullet);//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	
	void controls(float &time, sf::Vector2f &cursor, Bullet *bullet);



	void mapReaction(sf::String *TileMapX, float &time);

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