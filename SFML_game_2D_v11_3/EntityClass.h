





#ifndef ENTITY_CLASS
#define ENTITY_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>




//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::


////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Entity { // класс Сущности в игре
protected:
	float x, y = 0;
	int dir;

public:
	float w, h; 
	float dx, dy;
	float currentSpeed, speed, moveTimer; //координаты игрока х и у, h - высота, w - ширина, ускорение (dx по х и dy по у), сама скорость
	float regularSpeed;

	sf::String name;
	sf::String imageString;
	//bool life;//переменная жизнь, логическая
	bool isMove;//добавили переменные состояния движения и выбора объекта


	sf::Image image;//сфмл изображение
	sf::Texture texture;//сфмл текстура
	sf::Sprite sprite;//сфмл спрайт

	Entity(sf::String sImage, float X, float Y, sf::String Name); //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
	
	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);


	virtual void update(float time, sf::String *TileMap);//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.

	
	virtual void mapReaction(sf::String *TileMapX, float time);

	virtual sf::FloatRect getRect();

	virtual float getCoordinateX();	//этим методом будем забирать координату Х	
	virtual float getCoordinateY();	//этим методом будем забирать координату Y 	

	virtual float changeCoordinateX_by(float addX);
	virtual float changeCoordinateY_by(float addY);

	virtual float changeCoordinateX_to(float newX);
	virtual float changeCoordinateY_to(float newY);
	
};

#endif // !ENTITY_CLASS