




#include <iostream>
#include "sets_n_structs.h"

#include "EnemyClass.h"


//#include "view.h"

//const float tileMapZize = 32;


Enemy::Enemy(sf::String sImage, float X, float Y, sf::String Name) :Creature(sImage, X, Y, Name){ //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������

	x = X; y = Y;//��������� ���������� ��������� ������� 

	dx = 0;	dy = 0;	dir = -1;

	shotTimer = 0;

	speed = 0; health = 100; 
	regularSpeed = 0.1;	currentSpeed = 0;

	ammo = 10;
	life = true; isMove = false; isPlayerVisible = false; isTryToFind = false;
	
	visibleRadius = 800;
	damage = 10;
	waitFireTime = 1000;

	level = 1;

	
	
	if (name == "Enemy3") {
		//visibleDistance = 700;
		damage = 30;
		waitFireTime = 500;
	}
	/*
	else {
		visibleDistance = 400;
		damage = 2;
	}
	*/

	//std::ostringstream bulName[enemyNumber];

	for (int i = 0; i < bullNum; i++){//���������� �� ��������� ����� �������(� ������ �� ������)

		//bulletImageArr[i].loadFromFile("images/ammunition/Bullet3.png");
		bullets.push_back(new Bullet("images/ammunition/Bullet3.png", x, y, w, h, "Bullet", true));
	}

	//image.loadFromFile("images/APlayer/" + File);//������ � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� image.loadFromFile("images/hero/png");


	texture.loadFromImage(image);//���������� ���� ����������� � ��������
	sprite.setTexture(texture);//�������� ������ ���������


	w = image.getSize().x; //������
	h = image.getSize().y;//������

	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //������ ������� ���� ������������� ��� ������ ������ ���������, � �� ����� ������� �����. IntRect - ���������� �����
	sprite.setOrigin(w / 2, h / 2);
};

void Enemy::update(float time, sf::String *TileMap, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.

	shotTimer += time;


	switch (level)
	{
	case 1: easyAI(getPlayerAngle(playerCoord, window, bullet), playerCoord,  bullet, window); break;
	case 2: mediumAI(getPlayerAngle(playerCoord, window, bullet), playerCoord, bullet, window); break;
	}

	/*
	switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
	case LEFT_2D: dx = -speed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
	case DOWN_2D: dx = 0; dy = speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
	case UP_2D: dx = 0; dy = -speed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
	}
	*/

	
	//mapReaction(TileMap, dx, 0, time, blowCngTime);//�������� �������, ���������� �� �������������� � ������

	y += dy*time;//���������� �� ������

	x += dx*time;//�� �������� �� �������� �����. ���� ��������� �� ����� �������� �������� ��������� � ��� ��������� ��������

	mapReaction(TileMap, time);//�������� �������, ���������� �� �������������� � ������

	currentSpeed = 0;//�������� ��������, ����� �������� �����������.

	if (health <= 0) life = false;
	speed = 0;//�������� ��������, ����� �������� �����������.

	if (life)	sprite.setPosition(x + w / 2, y + h / 2); //������� ������ � ������� x y , ����������. ���������� ������� � ���� �������, ����� �� ��� ������ ����� �� �����.
	//else sprite.setPosition(-500, -500);

};


void Enemy::easyAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){

	visibleRadius = 400;
	damage = 2;
	waitFireTime = 1000;

	sf::Vector2f distToScreen((window->getSize().x / 2 - window->getSize().x *0.1), (window->getSize().y / 2 - window->getSize().y *0.1));
	sf::Vector2f distToPlayer((x - playerCoord.x), (y - playerCoord.y));
	

	if (distToScreen.y < abs(distToPlayer.y)){
		if (distToPlayer.y < 0){ //����� ����� �� �����
			dir = DOWN_2D; currentSpeed = regularSpeed;
		}
		if (distToPlayer.y > 0){ //����� ������ �� �����
			dir = UP_2D; currentSpeed = regularSpeed;
		}
	}

	if (distToScreen.x < abs(distToPlayer.x)){
		if (distToPlayer.x < 0){ //����� ������ �� �����
			dir = RIGHT_2D; currentSpeed = regularSpeed;
		}
		if (distToPlayer.x > 0){ //����� ����� �� �����
			dir = LEFT_2D; currentSpeed = regularSpeed;
		}
	}
	

		if (isTryToFind && !isPlayerVisible){
			switch (dir)//��������� ��������� � ����������� �� �����������. (������ ����� ������������� �����������)
			{
			case RIGHT_2D: dx = currentSpeed; 	dy = 0;	break;//�� ���� ������ ������������� ��������, �� ������ ��������. ��������, ��� �������� ���� ������ ������
			case LEFT_2D: dx = -currentSpeed; dy = 0; break;//�� ���� ������ ������������� ��������, �� ������ ��������. ����������, ��� �������� ���� ������ �����
			case DOWN_2D: dx = 0; dy = currentSpeed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ ����
			case UP_2D: dx = 0; dy = -currentSpeed; break;//�� ���� ������ ������� ��������, �� ������ �������������. ����������, ��� �������� ���� ������ �����
			}
		}
		else { dx = 0; dy = 0; }
	

	if ((distToScreen.x > abs(distToPlayer.x)) && (distToScreen.y > abs(distToPlayer.y)))



		isPlayerVisible = true;

	else isPlayerVisible = false;
	

	if (isPlayerVisible){
		if (shotTimer > waitFireTime){

			isTryToFind = true;
			shotTimer = 0;
			if (ammo > 0) {
				ammo--;
				bullet->isMove = true;
			}
		}//������ ����������� �������� ������ 3 ���		


		sprite.setRotation(angle);
	}


}

void Enemy::mediumAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){

}


float Enemy::getPlayerAngle(sf::Vector2f &playerCoord, sf::RenderWindow *window, Bullet *bullet)
{
	float alphaX = playerCoord.x -  getCoordinateX();//������ , ����������� ������, ������� ���������� ������ � ������
	float alphaY = playerCoord.y - getCoordinateY();//�� ��, ���������� y
	
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//�������� ���� � �������� � ��������� ��� � �������

	float vecLength = sqrt(pow(alphaX, 2) + pow(alphaY, 2));
	sf::Vector2f normVec(alphaX / vecLength, alphaY / vecLength);

	//sf::Vector2f winSize(window->getSize().x, window->getSize().y);
	//if (vecLength < visibleRadius) isPlayerVisible = true;  //��������� � ������� = visibleRadius;
	


	return angle;
}


void Enemy::mapReaction(sf::String *TileMap, float time)//�-��� �������������� � ������
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
	}

}



/*
float Player::getCoordinateX(){	//���� ������� ����� �������� ���������� �
return x;
}

float Player::getCoordinateY(){	//���� ������� ����� �������� ���������� Y
return y;
}

float Player::changeCoordinateX_by(float addX){	//���� ������� ����� �������� ���������� �
x += addX;
return x;
}

float Player::changeCoordinateY_by(float addY){	//���� ������� ����� �������� ���������� Y
y += addY;
return y;
}

float Player::changeCoordinateX_to(float newX){	//���� ������� ����� �������� ���������� �
x = newX;
return x;
}

float Player::changeCoordinateY_to(float newY){	//���� ������� ����� �������� ���������� Y
y = newY;
return y;
}
*/

/*
void Enemy::update(float time, sf::String *TileMap, Creature *sombody, Bullet *bullet){//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.


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
*/