

#include "sets_n_structs.h"

#include <iostream>
#include <sstream>

#include <cmath> 


#include "MapLoaderClass.h"

#include "view.h"
#include "PlayerClass.h"
#include "EnemyClass.h"
#include "BulletClass.h"

//#include "mission.h"
//#include <vector>
//#include <queue>
#include <list>


#include "sources/txt_maps/map2.txt"




//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::



bool showMissionText = true;//логическая переменная, отвечающая за появление текста миссии на экране



int main()
{


	//sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "2D Game!");
	sf::RenderWindow window(sf::VideoMode(1366, 768), "2D Game!", sf::Style::Fullscreen);

	view.reset(sf::FloatRect(0, 0, WIN_WIDTH, WIN_HEIGHT));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.
	
	sf::Vector2u winSize = window.getSize();


	/*------------------------------- подключаем ГЛАВНЫЙ шрифт текста ----------------------------------------------------------------*/

	sf::Font font;//шрифт 
	font.loadFromFile("sources/TIMCYR.ttf");//передаем нашему шрифту файл шрифта


	sf::Text TabText("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	TabText.setColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, а то по умолчанию он белый
		
	
	sf::Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(sf::Color::Black);//покрасили текст в красный. если убрать эту строку, а то по умолчанию он белый
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	/*_____________________________________________________________________________________________________________________*/
		/*----------------------------- подключаем изображение свитка -----------------------------------------------------*/
	sf::Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(sf::Color(0, 0, 0));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));  //приведение типов, размеры картинки исходные
	s_quest.setScale(0.6f, 0.6f);//чуть уменьшили картинку, => размер стал меньше
	/*________________________________________________________________________________________________________________*/

	/*-------------------------------- подключаем изображение карты -------------------------------------------------*/
	sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/maps/map_V2_2.png");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	/*________________________________________________________________________________________________________________*/

	std::list<sf::String> objectImages;

	//Player p("lion001.png", 250, 250, 96.0, 96.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.




	sf::String playerImage = "images/MPlayer/Player1.png";

	sf::String bulletImage = "images/ammunition/Bullet.png";

	sf::String enemyImage[enemyNumber];
	sf::String enemyImageString;
	//enemyImage.loadFromFile("images/MEnemy/Enemy1.png");

	//objectImages.push_back(playerImage);
	

	std::ostringstream enemyName[enemyNumber];
	sf::String fullEnemyName;

	MapLoader *testMap = new MapLoader(playerImage, TileMap);

	//MapLoader testMap("Player1", TileMap);

	/*
	for (int i = 0; i < enemyNumber; i++){

		enemyName[i] << i + 1;

		fullEnemyName = "Enemy" + enemyName[i].str();
		enemyImage[i] = "images/MEnemy/" + fullEnemyName + ".png";

		objectImages.push_back(enemyImage[enemyNumber]);
	}
	*/

	/*
	enemyImageString = "images/MEnemy/Enemy1.png";
	objectImages.push_back(enemyImageString);
	*/
	

	std::list<Entity*> entities = testMap->setEntitiesAtMap(TileMap, &window, objectImages);
	std::list<Entity*>::iterator entIt;


	//Player *p = new Player(playerImage, 416, 288, "Player");//создаем объект p класса player,задаем "player.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	
	
	




	


	std::list<Enemy*>  enemies;//создаю список, сюда буду кидать объекты.например врагов.


	std::list<Enemy*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::list<Bullet*>::iterator bIt;//итератор чтобы проходить по эл-там списка

	/*
	std::ostringstream enemyName[enemyNumber];
	sf::String fullEnemyName;
	sf::String imageStringName[enemyNumber];
	*/

	int yEnPlace;
	int z = 0;

	entIt = entities.begin();

	Player *p = new Player((*entIt)->imageString, (*entIt)->getCoordinateX(), (*entIt)->getCoordinateY(), (*entIt)->name);
	
	entIt = entities.erase(entIt);

	for (entIt = entities.begin(); entIt != entities.end(); entIt++)
		enemies.push_back(new Enemy((*entIt)->imageString, (*entIt)->getCoordinateX(), (*entIt)->getCoordinateY(), (*entIt)->name));//и закидываем в список всех наших врагов с карты	
	
		/*
	sf::Vector2f bulStartPos(p->getCoordinateX(), p->getCoordinateY());
	sf::Vector2f offset(p->w, p->h);


	Bullet *bullet = new Bullet(bulletImage, bulStartPos.x, bulStartPos.y, offset.x, offset.y, "Bullet", true); //создаем объект p класса player,задаем "player.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	*/

	/*
	for (int i = 0; i < enemyNumber; i++){//проходимся по элементам этого вектора(а именно по врагам)
		enemyName[i] << i+1;

		fullEnemyName = "Enemy" + enemyName[i].str();
		imageStringName[i] = "images/MEnemy/" + fullEnemyName + ".png";

		//enemyImage[i].loadFromFile(imageStringName);

		yEnPlace = (640 * i + 64);

		if (yEnPlace > HEIGHT_MAP*tileMapSize) yEnPlace = (HEIGHT_MAP*tileMapSize - 100);

		
		for (int i = 0; i < enemyNumber; i++)		objectImages.push_back(enemyImage[enemyNumber]); 
	
		//enemies.push_back(new Enemy(imageStringName[i], 1600, yEnPlace, fullEnemyName));//и закидываем в список всех наших врагов с карты	
	}
	*/


	float blowCngTime = 0;
	
	sf::Clock clock;

	
	//sf::Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	//int gameTime = 0;//объявили игровое время, инициализировали.



	testMap->randomMapGenerate(TileMap);//генерация случ камней

	sf::Keyboard::Key key = sf::Keyboard::Unknown;

	//float shotTimer = 0;

	p->shotTimer = 0;

	for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
			(*it)->shotTimer = 0;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		//float angle;
		

		//if (p->life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); else  view.move(0.1, 0); //игровое время в секундах идёт вперед, пока жив игрок, перезагружать как time его не надо. оно не обновляет логику игры
		
		clock.restart(); //перезагружает время
		time = time / 800; //скорость игры
	


		sf::Vector2i cursorPixelPosition = sf::Mouse::getPosition(window);//забираем коорд курсора
		sf::Vector2f cursor = window.mapPixelToCoords(cursorPixelPosition);//переводим их в игровые (уходим от коорд окна)

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
			
			if (event.type == sf::Event::MouseMoved){

			}
		
			

			if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == sf::Mouse::Left){//а именно левая

				
			}


		}
		
		////p->shotTimer += time;

		sf::Vector2f playerCoord(p->getCoordinateX(), p->getCoordinateY());

		setPlayerCoordinateForView(p->getCoordinateX(), p->getCoordinateY(), &winSize);//передаем координаты игрока в функцию управления камерой

		


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// АПДЕЙТЫ ////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		
		/*----------------------- АПДЕЙТ ВСЕХ ВРАГОВ И ПАТРОНОВ КАЖДОГО ИЗ НИХ ----------------------------------*/
		
		for (it = enemies.begin(); it != enemies.end();)//говорим что проходимся от начала до конца
			{
				//Creature *b = *it;//для удобства, чтобы не писать (*it)->

			(*it)->update(time, TileMap, playerCoord, (*it)->bullets.front(), &window);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)



			for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)//говорим что проходимся от начала до конца
				(*bIt)->update(time, TileMap, playerCoord.x + (*bIt)->offsetX, playerCoord.y + (*bIt)->offsetY, (*it)->getCoordinateX(), (*it)->getCoordinateY());//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
				

			if ((*it)->bullets.front()->isMove){
				//b = playerBullets.front();
				(*it)->bullets.push_back((*it)->bullets.front());
				(*it)->bullets.pop_front();
			}



			if ((*it)->life == false)	{
					it = enemies.erase(it); // если этот враг мертв, то удаляем его
					//delete (*it); // если этот объект мертв, то удаляем его
			}
			else {it++;}//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка

			}


		/*----------------------- АПДЕЙТ ИГРОКА И ЕГО ПАТРОНОВ ----------------------------------*/
		
		p->update(time, TileMap, cursor, p->bullets.front());//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++)//говорим что проходимся от начала до конца
		{
			//bullets.front()->update();
			(*bIt)->update(time, TileMap, cursor.x, cursor.y, playerCoord.x, playerCoord.y);//вызываем ф-цию update для всех патронов игрока

		}

		if (p->bullets.front()->isMove){
			//b = playerBullets.front();
			p->bullets.push_back(p->bullets.front());
			p->bullets.pop_front();
		}

		/* ________________________________ КОНЕЦ АПДЕЙТА ИГРОКА _______________________________________________ */

		


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ВЗАИМОДЕЙСТВИЕ ОБЪЕКТОВ ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* ---------------------- столкновение игрока и врага -------------------------------------- */
		/* ------------------------ выталкивание игрока от врага при простом соприкосновении ------- */
		//z = 0;
		if (!enemies.empty()){
			for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
			{
				//fullEnemyName = "Enemy" + enemyName[z].str();
				//if (z < 3)z++;
				if ((*it)->getRect().intersects(p->getRect()))//если прямоугольник спрайта объекта пересекается с игроком
				{
					if (p->dx < 0) {
						p->changeCoordinateX_to((*it)->getCoordinateX() + (*it)->w);
						//(*it)->changeCoordinateX_to(p->getCoordinateX() - p->w);
					}//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
					if (p->dx > 0) {
						p->changeCoordinateX_to((*it)->getCoordinateX() - p->w);
						//(*it)->changeCoordinateX_to(p->getCoordinateX() + (*it)->w);
					}//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
					if (p->dy < 0) {
						p->changeCoordinateY_to((*it)->getCoordinateY() + (*it)->h);
						//	(*it)->changeCoordinateY_to(p->getCoordinateY() - p->h);
					}//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
					if (p->dy > 0) {
						p->changeCoordinateY_to((*it)->getCoordinateY() - p->h);
						//(*it)->changeCoordinateY_to(p->getCoordinateY() + (*it)->h);
					}//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
				}
			}
		}


		/* ----------------- нанесение урона врагу при попадании от пули игрока ------------------------------ */
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++)//проходимся по эл-там списка
		{

			for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
				{
					if ((*it)->getRect().intersects((*bIt)->getRect()))//если прямоугольник спрайта объекта пересекается с игроком
					{
						if ((*bIt)->isMove)	{
							(*it)->health -= p->damage;
							(*bIt)->isMove = false;
							(*bIt)->touched = true;
						}

					}
				}
		}

		/* ----------------- попадание пули врага по игроку ------------------------------ */

		for (it = enemies.begin(); it != enemies.end(); it++)//говорим что проходимся от начала до конца
		{
			//Creature *b = *it;//для удобства, чтобы не писать (*it)->

			for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)//проходимся по эл-там списка
			{
				if (p->getRect().intersects((*bIt)->getRect()))//если прямоугольник спрайта объекта пересекается с игроком
				{
					if ((*bIt)->isMove)	{
						//(*it)->health -= p->damage;
						(*bIt)->isMove = false;
						(*bIt)->touched = true;
					}

				}
			}

		}
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear();


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ПРОРИСОВКА ВСЕХ СПРАЙТОВ ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/* ----------------------прорисовка карты -------------------------------------- */
		testMap->drawMap(&window, &s_map, TileMap);

		/* ------------------------ прорисовка спрайтов игрока и патронов игрока --------------------------*/
		window.draw(p->sprite); //рисуем спрайт объекта p класса player
		//for (bIt = playerBullets.begin(); bIt != playerBullets.end(); bIt++)window.draw((*bIt)->sprite); //рисуем пули игрока
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++) window.draw((*bIt)->sprite); //рисуем пули игрока


		//window.draw(bullet->sprite);

		
		/* ------------------------ прорисовка спрайтов игрока и патронов игрока --------------------------*/
		if (!enemies.empty()){
			for (it = enemies.begin(); it != enemies.end(); it++){
				window.draw((*it)->sprite); //рисуем entities объекты (сейчас это только враги)
				for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)window.draw((*bIt)->sprite); //рисуем пули игрока
				
			}
		}


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ВЫВОД РАЗЛИЧНОГО ТЕКСТА ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::ostringstream playerHealthString, gameTimeString , playerAmmoString;    // объявили переменную здоровья и времени
		std::ostringstream checkString;

		std::ostringstream enemyInfo[enemyNumber];

		sf::String fullText;
		

		if (p->life){
			playerHealthString << p->health;		//занесли в нее количество очков здоровья, то есть формируем строку
			playerAmmoString << p->ammo;

			//it = creatures.begin();

			

			checkString << p->health;

			sf::String checkText = checkString.str();

			fullText = "Здоровье: " + playerHealthString.str() + "\tПатроны: " + playerAmmoString.str() + "\n " ;

			fullText = fullText + "Shot Timer:  " + checkText + "\n";
			
			/*
			std::list<std::ostringstream> enemyInfoString;
			std::list<std::ostringstream>::iterator strIt;
			*/
		
			std::string  enemyInfoString;
			//std::ostringstream::intTo



			//int k = 0;
			if (!enemies.empty()){
				for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка
				{
					//enemyInfoString = (*it)->health;
					//fullText = (*it)->health;

					enemyInfoString = std::to_string((*it)->health);

					fullText = fullText + "Здоровье " + (*it)->name + ":\t  " + enemyInfoString + "\n";

					//enemyInfoString << "";
					
				}
			}
			

			text.setString(fullText.toAnsiString(std::locale::global(std::locale("rus"))));//задаем строку тексту и вызываем сформированную выше строку методом .str() 
			text.setPosition(view.getCenter().x - winSize.x / 2 + 5, view.getCenter().y - winSize.y/2 + 5);//задаем позицию текста, отступая от центра камеры
		}
		else{
			playerHealthString << p->health;
			//gameTimeString << gameTime;		
			text.setCharacterSize(30);
			text.setColor(sf::Color::Red);

			fullText = "Игра окончена ! \n\n";
				fullText = fullText + "Здоровье: " + playerHealthString.str(); //формируем строку
			//fullText = fullText + "\nВремя игры: " + gameTimeString.str();


			text.setString(fullText.toAnsiString(std::locale::global(std::locale("rus"))));//задаем строку тексту и вызываем сформированную выше строку
			text.setPosition(view.getCenter().x - 115, view.getCenter().y - 60);//задаем позицию текста, отступая от центра камеры
		}
		

		/* -------------- прорисовка текста --------------------------- */
		window.draw(text);

		/* ------------------- вывод на экран ------------------------- */
		window.display();
	}

	delete p;
	delete testMap;
	return 0;
}
