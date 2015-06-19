





#ifndef ENTITY_CLASS
#define ENTITY_CLASS


#include <SFML\Graphics.hpp>
#include <iostream>




//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////
class Entity { // ����� �������� � ����
protected:
	float x, y = 0;
	int dir;

public:
	float w, h; 
	float dx, dy;
	float currentSpeed, speed, moveTimer; //���������� ������ � � �, h - ������, w - ������, ��������� (dx �� � � dy �� �), ���� ��������
	float regularSpeed;

	sf::String name;
	sf::String imageString;
	//bool life;//���������� �����, ����������
	bool isMove;//�������� ���������� ��������� �������� � ������ �������


	sf::Image image;//���� �����������
	sf::Texture texture;//���� ��������
	sf::Sprite sprite;//���� ������

	Entity(sf::String sImage, float X, float Y, sf::String Name); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	
	//void controls(sf::Keyboard::Key key);
	//void getPlayerCoordinateForView(float x, float y);


	virtual void update(float time, sf::String *TileMap);//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	
	virtual void mapReaction(sf::String *TileMapX, float time);

	virtual sf::FloatRect getRect();

	virtual float getCoordinateX();	//���� ������� ����� �������� ���������� �	
	virtual float getCoordinateY();	//���� ������� ����� �������� ���������� Y 	

	virtual float changeCoordinateX_by(float addX);
	virtual float changeCoordinateY_by(float addY);

	virtual float changeCoordinateX_to(float newX);
	virtual float changeCoordinateY_to(float newY);
	
};

#endif // !ENTITY_CLASS