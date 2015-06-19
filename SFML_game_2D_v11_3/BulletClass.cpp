




#include <iostream>
#include "sets_n_structs.h"
#include "BulletClass.h"


Bullet::Bullet(sf::String sImage, float X, float Y, float OFFsetX, float OFFsetY, sf::String Name, bool isPlayerBullet) :Entity(sImage, X, Y, Name){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту

	x = X; y = Y;//двумерная координата появления спрайта
	dir = -1;


	w = image.getSize().x; //ширина 
	h = image.getSize().y;//высота

	offsetX = OFFsetX*0.5;
	offsetY = OFFsetY*0.5;



	dx = 0;	dy = 0;
	currentSpeed, moveTimer = 0;
	speed = 15;

	name = Name;


	//life = true;//инициализировали логическую переменную жизни
	touched = false;
	isMove = false;
	isReady = false;

	//image.loadFromFile("images/APlayer/" + File);//кладем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");


	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой




	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного персонажа, а не всего спрайта сразу. IntRect - приведение типов
	sprite.setOrigin(0, 0);
	sprite.setPosition(x + offsetX, y + offsetY); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
};

void Bullet::update(float &time, sf::String *TileMap, float destinX, float destinY, float sourceX, float sourceY){//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.

	//speed = 1;
	/*
	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT_2D: dx = speed; 	dy = 0;	break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT_2D: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN_2D: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP_2D: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}
	*/

	sf::Vector2f destination(destinX, destinY);
	sf::Vector2f holderCoord(sourceX, sourceY);

	if (touched || !isMove){
		normVec = findDirection(destination, holderCoord);
	}
	/*
	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	y += dy*time;//аналогично по игреку
	*/
	
	followForHolder(destination, holderCoord);


	dx = normVec.x;
	dy = normVec.y;
	

	//speed = 0;//зануляем скорость, чтобы персонаж остановился.
	//sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
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

	mapReaction(TileMap, time);//вызываем функцию, отвечающую за взаимодействие с картой
	
	//if (touched) sprite.setPosition();

};



sf::Vector2f Bullet::findDirection(sf::Vector2f &destination, sf::Vector2f &holderCoord){

	
		float alphaX = destination.x - (holderCoord.x + offsetX);//вектор , колинеарный прямой, которая пересекает спрайт и курсор
		float alphaY = destination.y - (holderCoord.y + offsetY);//он же, координата y

		float vecLength = sqrt(pow(alphaX, 2) + pow(alphaY, 2));
		sf::Vector2f normVec(alphaX / vecLength, alphaY / vecLength);
		return normVec;

	
}

void Bullet::followForHolder(sf::Vector2f &destination, sf::Vector2f &holderCoord){
	
	if (touched || !isMove){

	float alphaX = destination.x - holderCoord.x;//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float alphaY = destination.y - holderCoord.y;//он же, координата y
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//получаем угол в радианах и переводим его в градусы

	
		sprite.setPosition(holderCoord.x + offsetX, holderCoord.y + offsetY);
		sprite.setRotation(angle);
		touched = false;
	}
}

void Bullet::mapReaction(sf::String *TileMap, float &time)//ф-ция взаимодействия с картой
{
	for (int i = y / (tileMapSize); i < (y + h) / (tileMapSize); i++)//проходимся по всей карте, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
	for (int j = x / (tileMapSize); j<(x + w) / (tileMapSize); j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
	{
		if (TileMap[i][j] == '0')//если наш квадратик соответствует символу 0 (стена), то проверяем "направление скорости" персонажа:
		{

			touched = true;
			isMove = false;

			//speed = 0;

		}
	}
}

