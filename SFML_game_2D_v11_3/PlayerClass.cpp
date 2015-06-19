





#include <iostream>
#include "sets_n_structs.h"

#include "PlayerClass.h"


//#include "view.h"

//const float tileMapZize = 32;




Player::Player(sf::String sImage, float X, float Y, sf::String Name) :Creature(sImage, X, Y, Name){ //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

	dx = 0;
	dy = 0;
	dir = -1; 

	shotTimer = 0;
	

	regularSpeed = 0.3; 
	currentSpeed = 0;
	isRifle = true;

	

	if (isPistol) fireSpeed = 400;
	if (isRifle) fireSpeed = 200;
 


	playerScore = 0; health = 100; // ���������������� ���������� ����� � ������������
	ammo = 50;
	life = true;//���������������� ���������� ���������� �����
	isMove = false; 
	isReloading = false;
	

	


	
	for (int i = 0; i < bullNum; i++){//���������� �� ��������� ����� �������(� ������ �� ������)

		//bulletImageArr[i].loadFromFile("images/ammunition/Bullet3.png");
		//bulletNameString[i]
		bullets.push_back(new Bullet("images/ammunition/Bullet3.png", x, y, w, h, "Bullet", true));
	}
	


	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������
	
	x = X; y = Y;//��������� ���������� ��������� ������� 

	

	w = image.getSize().x; //������
	h = image.getSize().y;//������

	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ����� ������� �����. IntRect - ���������� �����
	sprite.setOrigin(w / 2, h / 2);
	
};



void Player::update(float &time, sf::String *TileMap, sf::Vector2f &cursor, Bullet *bullet){//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	shotTimer += time;

	if (isRifle) damage = 20;
	else damage = 10;

	if (life) {
		controls(time, cursor, bullet);
	}
	
	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT_2D: dx = currentSpeed; 	dy = 0;	break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT_2D: dx = -currentSpeed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN_2D: dx = 0; dy = currentSpeed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP_2D: dx = 0; dy = -currentSpeed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}

	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������
	//mapReaction(TileMap, dx, 0, time, blowCngTime);//�������� �������, ���������� �� �������������� � ������

	y += dy*time;//���������� �� ������
	mapReaction(TileMap, time);//�������� �������, ���������� �� �������������� � ������

	currentSpeed = 0;//�������� ��������, ����� �������� �����������.
	sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.



	if (health <= 0){ life = false; currentSpeed = 0; }//���� ������ ������ ���� ����� 0, �� ������� � ��������� �������� ������ ����� ������
	//return axisDirection;
};


void Player::mapReaction(sf::String *TileMap, float &time)//�-��� �������������� � ������
{


	for (int i = y / (tileMapSize); i < (y + h) / (tileMapSize); i++)//���������� �� ���� �����, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
	for (int j = x / (tileMapSize); j<(x + w) / (tileMapSize); j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
	{
		if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
		{
			if (dy>0) y = i * (tileMapSize)-h;//���� �� ��� ����, //�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
			if (dy<0) y = i * (tileMapSize)+tileMapSize;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
			if (dx>0) x = j * (tileMapSize)-w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
			if (dx < 0) x = j * (tileMapSize)+tileMapSize;//���������� ���� �����
		}

		if (TileMap[i][j] == 's') { //���� ������ ����� 's' (������)
			ammo += 5;;//���� ����� ������, ���������� playerScore=playerScore+1;
			TileMap[i][j] = ' ';//������� ������, ���� ����� �����. ����� � �� �������, ������.
		}

/*--------------------------------------------------------------------------------------------*/
/*----------------------------�������� ����--------------------------------------------------*/
		if (TileMap[i][j] == 'm') {
			if (health <= 20) health = 0; //���� ���� ��������� �� ����, �� health=health-40;
			else health -= 40;
			TileMap[i][j] = '}';
		}

/*__________________________________________________________________________________________*/

		if (TileMap[i][j] == 'h') {
			if (health >= 80) health = 100;
			else health += 20;//���� ����� ��������,�� ���������� health=health+20;
			TileMap[i][j] = ' ';//������ ��������
		}
	}

}


void Player::controls(float &time, sf::Vector2f &cursor, Bullet *bullet){

	if (arrows == true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir = LEFT_2D; currentSpeed = regularSpeed;//dir =1 - ����������� �����, currentSpeed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir = RIGHT_2D; currentSpeed = regularSpeed;//����������� ������, �� ����
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			dir = UP_2D; currentSpeed = regularSpeed;//����������� ����, �� ����
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			dir = DOWN_2D; currentSpeed = regularSpeed;//����������� �����, �� ����
		}
	}

	if (WASD == true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir = LEFT_2D; currentSpeed = regularSpeed;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir = RIGHT_2D; currentSpeed = regularSpeed;//����������� ������, �� ����
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			dir = UP_2D; currentSpeed = regularSpeed;//����������� ����, �� ����
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			dir = DOWN_2D; currentSpeed = regularSpeed;//����������� �����, �� ����
		}
	}

	float alphaX = cursor.x - getCoordinateX();//������ , ����������� ������, ������� ���������� ������ � ������
	float alphaY = cursor.y - getCoordinateY();//�� ��, ���������� y
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//�������� ���� � �������� � ��������� ��� � �������
	//std::cout << angle << "\n";//������� �� ������� � ���������


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (sprite.getGlobalBounds().contains(cursor.x, cursor.y))//� ��� ���� ���������� ������� �������� � ������
		{
			//p.sprite.setColor(sf::Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
			//p.isSelect = true;
		}
		else {
			if (shotTimer> fireSpeed){ 

				shotTimer = 0;
				if (ammo > 0) {
					ammo--;
					bullet->isMove = true;
				}
			}//������ ����������� �������� ������ 3 ���		
		}
	}

	//if (!bullet->isMove){
	sprite.setRotation(angle);
}


