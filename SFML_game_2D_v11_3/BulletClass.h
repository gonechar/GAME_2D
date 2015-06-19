






#ifndef BULLET_CLASS
#define BULLET_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>

//#include "EntityClass.h"
#include "EntityClass.h"



//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////
class Bullet :public Entity { // ����� ������
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

	float offsetX, offsetY;

	//int playerScore, health, ammo;// (dir - direction) ����������� �������� ������; playerScore - ����; health - ����������, �������� ����� ������
	int speed;
	bool isMove;
	bool touched;
	bool isReady;
	bool isPlayerBullet;

	sf::Vector2f normVec;

	Bullet(sf::String sImage, float X, float Y, float OFFsetX, float OFFsetY, sf::String Name, bool isPlayerBullet);
	//Bullet(sf::String *sImage, sf::Vector2f startPos, sf::Vector2f offset, sf::String Name, bool isPlayerBullet); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);


	void update(float &time, sf::String *TileMap, float destinX, float destinY, float sourceX, float sourceY);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void mapReaction(sf::String *TileMapX, float &time);
	
	sf::Vector2f findDirection(sf::Vector2f &destination, sf::Vector2f &holderCoord);

	void Bullet::followForHolder(sf::Vector2f &destination, sf::Vector2f &holderCoord);

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