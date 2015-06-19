




#include <iostream>
#include "sets_n_structs.h"

#include "EnemyClass.h"


//#include "view.h"

//const float tileMapZize = 32;


Enemy::Enemy(sf::String sImage, float X, float Y, sf::String Name) :Creature(sImage, X, Y, Name){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту

	x = X; y = Y;//двумерная координата появления спрайта 

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

	for (int i = 0; i < bullNum; i++){//проходимся по элементам этого вектора(а именно по врагам)

		//bulletImageArr[i].loadFromFile("images/ammunition/Bullet3.png");
		bullets.push_back(new Bullet("images/ammunition/Bullet3.png", x, y, w, h, "Bullet", true));
	}

	//image.loadFromFile("images/APlayer/" + File);//кладем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");


	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой


	w = image.getSize().x; //ширина
	h = image.getSize().y;//высота

	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного персонажа, а не всего спрайта сразу. IntRect - приведение типов
	sprite.setOrigin(w / 2, h / 2);
};

void Enemy::update(float time, sf::String *TileMap, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.

	shotTimer += time;


	switch (level)
	{
	case 1: easyAI(getPlayerAngle(playerCoord, window, bullet), playerCoord,  bullet, window); break;
	case 2: mediumAI(getPlayerAngle(playerCoord, window, bullet), playerCoord, bullet, window); break;
	}

	/*
	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT_2D: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN_2D: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP_2D: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}
	*/

	
	//mapReaction(TileMap, dx, 0, time, blowCngTime);//вызываем функцию, отвечающую за взаимодействие с картой

	y += dy*time;//аналогично по игреку

	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение

	mapReaction(TileMap, time);//вызываем функцию, отвечающую за взаимодействие с картой

	currentSpeed = 0;//зануляем скорость, чтобы персонаж остановился.

	if (health <= 0) life = false;
	speed = 0;//зануляем скорость, чтобы персонаж остановился.

	if (life)	sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
	//else sprite.setPosition(-500, -500);

};


void Enemy::easyAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){

	visibleRadius = 400;
	damage = 2;
	waitFireTime = 1000;

	sf::Vector2f distToScreen((window->getSize().x / 2 - window->getSize().x *0.1), (window->getSize().y / 2 - window->getSize().y *0.1));
	sf::Vector2f distToPlayer((x - playerCoord.x), (y - playerCoord.y));
	

	if (distToScreen.y < abs(distToPlayer.y)){
		if (distToPlayer.y < 0){ //игрок снизу от врага
			dir = DOWN_2D; currentSpeed = regularSpeed;
		}
		if (distToPlayer.y > 0){ //игрок сверху от врага
			dir = UP_2D; currentSpeed = regularSpeed;
		}
	}

	if (distToScreen.x < abs(distToPlayer.x)){
		if (distToPlayer.x < 0){ //игрок справа от врага
			dir = RIGHT_2D; currentSpeed = regularSpeed;
		}
		if (distToPlayer.x > 0){ //игрок слева от врага
			dir = LEFT_2D; currentSpeed = regularSpeed;
		}
	}
	

		if (isTryToFind && !isPlayerVisible){
			switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			{
			case RIGHT_2D: dx = currentSpeed; 	dy = 0;	break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case LEFT_2D: dx = -currentSpeed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
			case DOWN_2D: dx = 0; dy = currentSpeed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
			case UP_2D: dx = 0; dy = -currentSpeed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
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
		}//меняет направление примерно каждые 3 сек		


		sprite.setRotation(angle);
	}


}

void Enemy::mediumAI(float angle, sf::Vector2f &playerCoord, Bullet *bullet, sf::RenderWindow *window){

}


float Enemy::getPlayerAngle(sf::Vector2f &playerCoord, sf::RenderWindow *window, Bullet *bullet)
{
	float alphaX = playerCoord.x -  getCoordinateX();//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float alphaY = playerCoord.y - getCoordinateY();//он же, координата y
	
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//получаем угол в радианах и переводим его в градусы

	float vecLength = sqrt(pow(alphaX, 2) + pow(alphaY, 2));
	sf::Vector2f normVec(alphaX / vecLength, alphaY / vecLength);

	//sf::Vector2f winSize(window->getSize().x, window->getSize().y);
	//if (vecLength < visibleRadius) isPlayerVisible = true;  //видимость в радиусе = visibleRadius;
	


	return angle;
}


void Enemy::mapReaction(sf::String *TileMap, float time)//ф-ция взаимодействия с картой
{
	for (int i = y / (tileMapSize); i < (y + h) / (tileMapSize); i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
	for (int j = x / (tileMapSize); j<(x + w) / (tileMapSize); j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
	{
		if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
		{
			if (dy>0) y = i * (tileMapSize)-h;//если мы шли вниз, //то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
			if (dy<0) y = i * (tileMapSize)+tileMapSize;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
			if (dx>0) x = j * (tileMapSize)-w;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
			if (dx < 0) x = j * (tileMapSize)+tileMapSize;//аналогично идем влево
		}
	}

}



/*
float Player::getCoordinateX(){	//этим методом будем забирать координату Х
return x;
}

float Player::getCoordinateY(){	//этим методом будем забирать координату Y
return y;
}

float Player::changeCoordinateX_by(float addX){	//этим методом будем забирать координату Х
x += addX;
return x;
}

float Player::changeCoordinateY_by(float addY){	//этим методом будем забирать координату Y
y += addY;
return y;
}

float Player::changeCoordinateX_to(float newX){	//этим методом будем забирать координату Х
x = newX;
return x;
}

float Player::changeCoordinateY_to(float newY){	//этим методом будем забирать координату Y
y = newY;
return y;
}
*/

/*
void Enemy::update(float time, sf::String *TileMap, Creature *sombody, Bullet *bullet){//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.


	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT_2D: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN_2D: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP_2D: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}

	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	mapReaction(TileMap, time);//вызываем функцию, отвечающую за взаимодействие с картой

	y += dy*time;//аналогично по игреку
	mapReaction(TileMap, time);//вызываем функцию, отвечающую за взаимодействие с картой


	speed = 0;//зануляем скорость, чтобы персонаж остановился.
	sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.


};
*/