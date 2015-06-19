




#include <iostream>
#include "sets_n_structs.h"
#include "BulletClass.h"


Bullet::Bullet(sf::String sImage, float X, float Y, float OFFsetX, float OFFsetY, sf::String Name, bool isPlayerBullet) :Entity(sImage, X, Y, Name){ //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

	x = X; y = Y;//��������� ���������� ��������� �������
	dir = -1;


	w = image.getSize().x; //������ 
	h = image.getSize().y;//������

	offsetX = OFFsetX*0.5;
	offsetY = OFFsetY*0.5;



	dx = 0;	dy = 0;
	currentSpeed, moveTimer = 0;
	speed = 15;

	name = Name;


	//life = true;//���������������� ���������� ���������� �����
	touched = false;
	isMove = false;
	isReady = false;

	//image.loadFromFile("images/APlayer/" + File);//������ � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");


	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������




	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ����� ������� �����. IntRect - ���������� �����
	sprite.setOrigin(0, 0);
	sprite.setPosition(x + offsetX, y + offsetY); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
};

void Bullet::update(float &time, sf::String *TileMap, float destinX, float destinY, float sourceX, float sourceY){//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	//speed = 1;
	/*
	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT_2D: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN_2D: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP_2D: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}
	*/

	sf::Vector2f destination(destinX, destinY);
	sf::Vector2f holderCoord(sourceX, sourceY);

	if (touched || !isMove){
		normVec = findDirection(destination, holderCoord);
	}
	/*
	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	y += dy*time;//���������� �� ������
	*/
	
	followForHolder(destination, holderCoord);


	dx = normVec.x;
	dy = normVec.y;
	

	//speed = 0;//�������� ��������, ����� �������� �����������.
	//sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	//sprite.move();

	if (isMove && !touched){
		sprite.setColor(sf::Color::White);
		sprite.move(dx * speed, dy * speed);
	}
	else {
		sprite.setColor(sf::Color::Transparent);
	}

	x = sprite.getPosition().x;
	y = sprite.getPosition().y;

	mapReaction(TileMap, time);//�������� �������, ���������� �� �������������� � ������
	
	//if (touched) sprite.setPosition();

};



sf::Vector2f Bullet::findDirection(sf::Vector2f &destination, sf::Vector2f &holderCoord){

	
		float alphaX = destination.x - (holderCoord.x + offsetX);//������ , ����������� ������, ������� ���������� ������ � ������
		float alphaY = destination.y - (holderCoord.y + offsetY);//�� ��, ���������� y

		float vecLength = sqrt(pow(alphaX, 2) + pow(alphaY, 2));
		sf::Vector2f normVec(alphaX / vecLength, alphaY / vecLength);
		return normVec;

	
}

void Bullet::followForHolder(sf::Vector2f &destination, sf::Vector2f &holderCoord){
	
	if (touched || !isMove){

	float alphaX = destination.x - holderCoord.x;//������ , ����������� ������, ������� ���������� ������ � ������
	float alphaY = destination.y - holderCoord.y;//�� ��, ���������� y
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//�������� ���� � �������� � ��������� ��� � �������

	
		sprite.setPosition(holderCoord.x + offsetX, holderCoord.y + offsetY);
		sprite.setRotation(angle);
		touched = false;
	}
}

void Bullet::mapReaction(sf::String *TileMap, float &time)//�-��� �������������� � ������
{
	for (int i = y / (tileMapSize); i < (y + h) / (tileMapSize); i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	for (int j = x / (tileMapSize); j<(x + w) / (tileMapSize); j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
	{
		if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
		{

			touched = true;
			isMove = false;

			//speed = 0;

		}
	}
}

