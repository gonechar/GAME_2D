



#ifndef PLAYER_CLASS
#define PLAYER_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>
//#include "EntityClass.h"
#include "CreatureClass.h"
#include "BulletClass.h"
#include <list>


//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////
class Player:public Creature { // ����� ������
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

	bool isPistol, isRifle;

	int damage;

	float shotTimer;

	bool isReloading;
	int playerScore, health, ammo;// (dir - direction) ����������� �������� ������; playerScore - ����; health - ����������, �������� ����� ������
	int fireSpeed;

	Player(sf::String sImage, float X, float Y, sf::String Name); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	
	

	

	
	void update(float &time, sf::String *TileMap, sf::Vector2f &cursor, Bullet *bullet);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	
	void controls(float &time, sf::Vector2f &cursor, Bullet *bullet);



	void mapReaction(sf::String *TileMapX, float &time);

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