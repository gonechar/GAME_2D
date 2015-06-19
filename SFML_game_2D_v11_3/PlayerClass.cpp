





#include <iostream>
#include "sets_n_structs.h"

#include "PlayerClass.h"


//#include "view.h"

//const float tileMapZize = 32;




Player::Player(sf::String sImage, float X, float Y, sf::String Name) :Creature(sImage, X, Y, Name){ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту

	dx = 0;
	dy = 0;
	dir = -1; 

	shotTimer = 0;
	

	regularSpeed = 0.3; 
	currentSpeed = 0;
	isRifle = true;

	

	if (isPistol) fireSpeed = 400;
	if (isRifle) fireSpeed = 200;
 


	playerScore = 0; health = 100; // инициализировали переменную жизни в конструкторе
	ammo = 50;
	life = true;//инициализировали логическую переменную жизни
	isMove = false; 
	isReloading = false;
	

	


	
	for (int i = 0; i < bullNum; i++){//проходимся по элементам этого вектора(а именно по врагам)

		//bulletImageArr[i].loadFromFile("images/ammunition/Bullet3.png");
		//bulletNameString[i]
		bullets.push_back(new Bullet("images/ammunition/Bullet3.png", x, y, w, h, "Bullet", true));
	}
	


	texture.loadFromImage(image);//закидываем наше изображение в текстуру
	sprite.setTexture(texture);//заливаем спрайт текстурой
	
	x = X; y = Y;//двумерная координата появления спрайта 

	

	w = image.getSize().x; //ширина
	h = image.getSize().y;//высота

	sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного персонажа, а не всего спрайта сразу. IntRect - приведение типов
	sprite.setOrigin(w / 2, h / 2);
	
};



void Player::update(float &time, sf::String *TileMap, sf::Vector2f &cursor, Bullet *bullet){//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.

	shotTimer += time;

	if (isRifle) damage = 20;
	else damage = 10;

	if (life) {
		controls(time, cursor, bullet);
	}
	
	switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
	{
	case RIGHT_2D: dx = currentSpeed; 	dy = 0;	break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
	case LEFT_2D: dx = -currentSpeed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
	case DOWN_2D: dx = 0; dy = currentSpeed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
	case UP_2D: dx = 0; dy = -currentSpeed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
	}

	x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
	//mapReaction(TileMap, dx, 0, time, blowCngTime);//вызываем функцию, отвечающую за взаимодействие с картой

	y += dy*time;//аналогично по игреку
	mapReaction(TileMap, time);//вызываем функцию, отвечающую за взаимодействие с картой

	currentSpeed = 0;//зануляем скорость, чтобы персонаж остановился.
	sprite.setPosition(x + w / 2, y + h / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.



	if (health <= 0){ life = false; currentSpeed = 0; }//если жизней меньше либо равно 0, то умираем и исключаем движение игрока после смерти
	//return axisDirection;
};


void Player::mapReaction(sf::String *TileMap, float &time)//ф-ция взаимодействия с картой
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

		if (TileMap[i][j] == 's') { //если символ равен 's' (камень)
			ammo += 5;;//если взяли камень, переменная playerScore=playerScore+1;
			TileMap[i][j] = ' ';//убираем камень, типа взяли бонус. можем и не убирать, кстати.
		}

/*--------------------------------------------------------------------------------------------*/
/*----------------------------Анимация мины--------------------------------------------------*/
		if (TileMap[i][j] == 'm') {
			if (health <= 20) health = 0; //если если наступили на мину, то health=health-40;
			else health -= 40;
			TileMap[i][j] = '}';
		}

/*__________________________________________________________________________________________*/

		if (TileMap[i][j] == 'h') {
			if (health >= 80) health = 100;
			else health += 20;//если взяли сердечко,то переменная health=health+20;
			TileMap[i][j] = ' ';//убрали сердечко
		}
	}

}


void Player::controls(float &time, sf::Vector2f &cursor, Bullet *bullet){

	if (arrows == true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir = LEFT_2D; currentSpeed = regularSpeed;//dir =1 - направление вверх, currentSpeed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir = RIGHT_2D; currentSpeed = regularSpeed;//направление вправо, см выше
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			dir = UP_2D; currentSpeed = regularSpeed;//направление вниз, см выше
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			dir = DOWN_2D; currentSpeed = regularSpeed;//направление вверх, см выше
		}
	}

	if (WASD == true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir = LEFT_2D; currentSpeed = regularSpeed;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir = RIGHT_2D; currentSpeed = regularSpeed;//направление вправо, см выше
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
			dir = UP_2D; currentSpeed = regularSpeed;//направление вниз, см выше
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
			dir = DOWN_2D; currentSpeed = regularSpeed;//направление вверх, см выше
		}
	}

	float alphaX = cursor.x - getCoordinateX();//вектор , колинеарный прямой, которая пересекает спрайт и курсор
	float alphaY = cursor.y - getCoordinateY();//он же, координата y
	float angle = (atan2(alphaY, alphaX)) * 180 / PI;//получаем угол в радианах и переводим его в градусы
	//std::cout << angle << "\n";//смотрим на градусы в консольке


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if (sprite.getGlobalBounds().contains(cursor.x, cursor.y))//и при этом координата курсора попадает в спрайт
		{
			//p.sprite.setColor(sf::Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
			//p.isSelect = true;
		}
		else {
			if (shotTimer> fireSpeed){ 

				shotTimer = 0;
				if (ammo > 0) {
					ammo--;
					bullet->isMove = true;
				}
			}//меняет направление примерно каждые 3 сек		
		}
	}

	//if (!bullet->isMove){
	sprite.setRotation(angle);
}


