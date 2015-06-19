






#ifndef CREATURE_CLASS
#define CREATURE_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>
#include "EntityClass.h"




//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////
class Creature:public Entity { // ����� ������
protected:
	/*
	float x, y = 0;
	int dir;
	*/
public:

	/*
	float w, h;
	float dx, dy;
	float currentSpeed, speed, moveTimer; //���������� ������ � � �, h - ������, w - ������, ��������� (dx �� � � dy �� �), ���� ��������
	float regularSpeed;
	
	sf::String name;
	bool isMove;//�������� ���������� ��������� �������� � ������ �������
	*/

	

	/*
	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������
	*/

	bool life;//���������� �����, ����������
	int health;// (dir - direction) ����������� �������� ������; playerScore - ����; health - ����������, �������� ����� ������


	Creature(sf::String sImage, float X, float Y, sf::String Name); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);

	
	void update(float time, sf::String *TileMap, float *blowCngTime);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	void mapReaction(sf::String *TileMapX, float time, float *blowCngTime);
	
	
	/*
	virtual sf::FloatRect getRect(){
	
	virtual float getCoordinateX();	//���� ������� ����� �������� ���������� �	
	virtual float getCoordinateY();	//���� ������� ����� �������� ���������� Y 	

	virtual float changeCoordinateX_by(float addX);
	virtual float changeCoordinateY_by(float addY);

	virtual float changeCoordinateX_to(float newX);
	virtual float changeCoordinateY_to(float newY);
	*/
};

#endif // !ENTITY_CLASS