


#include <iostream>
#include "sets_n_structs.h"
#include "EntityClass.h"

Entity::Entity(sf::String sImage, float X, float Y, sf::String Name){ //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

	x = X; y = Y;//��������� ���������� ��������� �������
	dir = -1; 

	imageString = sImage;
	image.loadFromFile(imageString);

	w = image.getSize().x; //������ 
	h = image.getSize().y;//������
	dx = 0;	dy = 0;
	currentSpeed, speed, moveTimer = 0;

	name = Name; 

	
	//life = true;//���������������� ���������� ���������� �����
	isMove = false;

	//image.loadFromFile("images/APlayer/" + File);//������ � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");
	

	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������

	


	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ����� ������� �����. IntRect - ���������� �����
	sprite.setOrigin(w / 2, h / 2);
};

void Entity::update(float time, sf::String *TileMap){//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	

	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT_2D: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN_2D: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP_2D: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}

	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	mapReaction(TileMap, time);//�������� �������, ���������� �� �������������� � ������

	y += dy*time;//���������� �� ������
	mapReaction(TileMap, time);//�������� �������, ���������� �� �������������� � ������

	speed = 0;//�������� ��������, ����� �������� �����������.
	sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.


};

sf::FloatRect Entity::getRect(){
	return sf::FloatRect(x, y, w, h);
}


void Entity::mapReaction(sf::String *TileMap, float time)//�-��� �������������� � ������
{
	for (int i = y / (tileMapSize); i < (y + h) / (tileMapSize); i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	for (int j = x / (tileMapSize); j<(x + w) / (tileMapSize); j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
	{
		if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
		{
			if (dy>0)//���� �� ��� ����,
			{

				y = i * (tileMapSize)-h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
			}
			if (dy<0)
			{

				y = i * (tileMapSize)+tileMapSize;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
			}
			if (dx>0)
			{

				x = j * (tileMapSize)-w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
			}
			if (dx < 0)
			{

				x = j * (tileMapSize)+tileMapSize;//���������� ���� �����
			}
		}
	}
}


float Entity::getCoordinateX(){	//���� ������� ����� �������� ���������� �	
	return x;
}

float Entity::getCoordinateY(){	//���� ������� ����� �������� ���������� Y 	
	return y;
}

float Entity::changeCoordinateX_by(float addX){	//���� ������� ����� �������� ���������� �	
	x += addX;
	return x;
}

float Entity::changeCoordinateY_by(float addY){	//���� ������� ����� �������� ���������� Y 	
	y += addY;
	return y;
}

float Entity::changeCoordinateX_to(float newX){	//���� ������� ����� �������� ���������� �	
	x = newX;
	return x;
}

float Entity::changeCoordinateY_to(float newY){	//���� ������� ����� �������� ���������� Y 	
	y = newY;
	return y;
}


