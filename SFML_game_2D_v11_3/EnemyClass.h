




#ifndef ENEMY_CLASS
#define ENEMY_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>

//#include "EntityClass.h"
#include "CreatureClass.h"
#include "BulletClass.h"
#include <list>

//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////
class Enemy :public Creature { // ����� ������
private:
	//float x, y = 0;
	//int dir;

public:
	/*
	float w, h, dx, dy, speed = 0; //���������� ������ � � �, h - ������, w - ������, ��������� (dx �� � � dy �� �), ���� ��������
	int playerScore, health, ammo;// (dir - direction) ����������� �������� ������; playerScore - ����; health - ����������, �������� ����� ������

	bool life;//���������� �����, ����������
	bool isMove, isSelect;//�������� ���������� ��������� �������� � ������ �������

	sf::String File; //���� � �����������
	sf::Image image;//���� �����������
	sf::Vector2u playerImSize;
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������
	*/

	sf::Image bulletImageArr[bullNum];
	std::list<Bullet*>  bullets;//������ ������, ���� ���� ������ �������.�������� ������.
	//std::list<Bullet*>::iterator bIt;//�������� ����� ��������� �� ��-��� ������

	float shotTimer;

	float damage;
	float waitFireTime;
	int level;

	float visibleRadius;
	int playerScore, health, ammo;// (dir - direction) ����������� �������� ������; playerScore - ����; health - ����������, �������� ����� ������
	bool isPlayerVisible;
	bool isTryToFind;

	Enemy(sf::String sImage, float X, float Y, sf::String Name); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	
	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);

	void update(float time, sf::String *TileMap, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time, sf::String *TileMap, Creature *sombody, Bullet *bullet);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	void mapReaction(sf::String *TileMapX, float time);
	float getPlayerAngle(sf::Vector2f &playerCoord, sf::RenderWindow *window, Bullet *bullet);

	
	void easyAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);
	void mediumAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window);

	/*
	float getPlayerCoordinateX();	//���� ������� ����� �������� ���������� �
	float getPlayerCoordinateY();	//���� ������� ����� �������� ���������� Y

	float changePlayerCoordinateX_by(float addX);
	float changePlayerCoordinateY_by(float addY);

	float changePlayerCoordinateX_to(float newX);
	float changePlayerCoordinateY_to(float newY);
	*/


};

#endif // !PLAYER_CLASS