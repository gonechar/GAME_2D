

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




//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::



bool showMissionText = true;//���������� ����������, ���������� �� ��������� ������ ������ �� ������



int main()
{


	//sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "2D Game!");
	sf::RenderWindow window(sf::VideoMode(1366, 768), "2D Game!", sf::Style::Fullscreen);

	view.reset(sf::FloatRect(0, 0, WIN_WIDTH, WIN_HEIGHT));//������ "����" ������ ��� �������� ������� ���� ������. (����� ����� ������ ��� �����) ��� �� ���� �������������.
	
	sf::Vector2u winSize = window.getSize();


	/*------------------------------- ���������� ������� ����� ������ ----------------------------------------------------------------*/

	sf::Font font;//����� 
	font.loadFromFile("sources/TIMCYR.ttf");//�������� ������ ������ ���� ������


	sf::Text TabText("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	TabText.setColor(sf::Color::Black);//��������� ����� � �������. ���� ������ ��� ������, � �� �� ��������� �� �����
		
	
	sf::Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	text.setColor(sf::Color::Black);//��������� ����� � �������. ���� ������ ��� ������, � �� �� ��������� �� �����
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);//������ � ������������ �����. �� ��������� �� "�����":)) � �� ������������

	/*_____________________________________________________________________________________________________________________*/
		/*----------------------------- ���������� ����������� ������ -----------------------------------------------------*/
	sf::Image quest_image;
	quest_image.loadFromFile("images/missionbg.jpg");
	quest_image.createMaskFromColor(sf::Color(0, 0, 0));
	sf::Texture quest_texture;
	quest_texture.loadFromImage(quest_image);
	sf::Sprite s_quest;
	s_quest.setTexture(quest_texture);
	s_quest.setTextureRect(sf::IntRect(0, 0, 340, 510));  //���������� �����, ������� �������� ��������
	s_quest.setScale(0.6f, 0.6f);//���� ��������� ��������, => ������ ���� ������
	/*________________________________________________________________________________________________________________*/

	/*-------------------------------- ���������� ����������� ����� -------------------------------------------------*/
	sf::Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/maps/map_V2_2.png");//��������� ���� ��� �����
	sf::Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	sf::Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������
	/*________________________________________________________________________________________________________________*/

	std::list<sf::String> objectImages;

	//Player p("lion001.png", 250, 250, 96.0, 96.0);//������� ������ p ������ player,������ "hero.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.




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


	//Player *p = new Player(playerImage, 416, 288, "Player");//������� ������ p ������ player,������ "player.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	
	
	




	


	std::list<Enemy*>  enemies;//������ ������, ���� ���� ������ �������.�������� ������.


	std::list<Enemy*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	std::list<Bullet*>::iterator bIt;//�������� ����� ��������� �� ��-��� ������

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
		enemies.push_back(new Enemy((*entIt)->imageString, (*entIt)->getCoordinateX(), (*entIt)->getCoordinateY(), (*entIt)->name));//� ���������� � ������ ���� ����� ������ � �����	
	
		/*
	sf::Vector2f bulStartPos(p->getCoordinateX(), p->getCoordinateY());
	sf::Vector2f offset(p->w, p->h);


	Bullet *bullet = new Bullet(bulletImage, bulStartPos.x, bulStartPos.y, offset.x, offset.y, "Bullet", true); //������� ������ p ������ player,������ "player.png" ��� ��� �����+����������, ����� ���������� �,�, ������, ������.
	*/

	/*
	for (int i = 0; i < enemyNumber; i++){//���������� �� ��������� ����� �������(� ������ �� ������)
		enemyName[i] << i+1;

		fullEnemyName = "Enemy" + enemyName[i].str();
		imageStringName[i] = "images/MEnemy/" + fullEnemyName + ".png";

		//enemyImage[i].loadFromFile(imageStringName);

		yEnPlace = (640 * i + 64);

		if (yEnPlace > HEIGHT_MAP*tileMapSize) yEnPlace = (HEIGHT_MAP*tileMapSize - 100);

		
		for (int i = 0; i < enemyNumber; i++)		objectImages.push_back(enemyImage[enemyNumber]); 
	
		//enemies.push_back(new Enemy(imageStringName[i], 1600, yEnPlace, fullEnemyName));//� ���������� � ������ ���� ����� ������ � �����	
	}
	*/


	float blowCngTime = 0;
	
	sf::Clock clock;

	
	//sf::Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	//int gameTime = 0;//�������� ������� �����, ����������������.



	testMap->randomMapGenerate(TileMap);//��������� ���� ������

	sf::Keyboard::Key key = sf::Keyboard::Unknown;

	//float shotTimer = 0;

	p->shotTimer = 0;

	for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������
			(*it)->shotTimer = 0;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		//float angle;
		

		//if (p->life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); else  view.move(0.1, 0); //������� ����� � �������� ��� ������, ���� ��� �����, ������������� ��� time ��� �� ����. ��� �� ��������� ������ ����
		
		clock.restart(); //������������� �����
		time = time / 800; //�������� ����
	


		sf::Vector2i cursorPixelPosition = sf::Mouse::getPosition(window);//�������� ����� �������
		sf::Vector2f cursor = window.mapPixelToCoords(cursorPixelPosition);//��������� �� � ������� (������ �� ����� ����)

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
			
			if (event.type == sf::Event::MouseMoved){

			}
		
			

			if (event.type == sf::Event::MouseButtonPressed)//���� ������ ������� ����
			if (event.key.code == sf::Mouse::Left){//� ������ �����

				
			}


		}
		
		////p->shotTimer += time;

		sf::Vector2f playerCoord(p->getCoordinateX(), p->getCoordinateY());

		setPlayerCoordinateForView(p->getCoordinateX(), p->getCoordinateY(), &winSize);//�������� ���������� ������ � ������� ���������� �������

		


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ������� ////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		
		/*----------------------- ������ ���� ������ � �������� ������� �� ��� ----------------------------------*/
		
		for (it = enemies.begin(); it != enemies.end();)//������� ��� ���������� �� ������ �� �����
			{
				//Creature *b = *it;//��� ��������, ����� �� ������ (*it)->

			(*it)->update(time, TileMap, playerCoord, (*it)->bullets.front(), &window);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)



			for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)//������� ��� ���������� �� ������ �� �����
				(*bIt)->update(time, TileMap, playerCoord.x + (*bIt)->offsetX, playerCoord.y + (*bIt)->offsetY, (*it)->getCoordinateX(), (*it)->getCoordinateY());//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
				

			if ((*it)->bullets.front()->isMove){
				//b = playerBullets.front();
				(*it)->bullets.push_back((*it)->bullets.front());
				(*it)->bullets.pop_front();
			}



			if ((*it)->life == false)	{
					it = enemies.erase(it); // ���� ���� ���� �����, �� ������� ���
					//delete (*it); // ���� ���� ������ �����, �� ������� ���
			}
			else {it++;}//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������

			}


		/*----------------------- ������ ������ � ��� �������� ----------------------------------*/
		
		p->update(time, TileMap, cursor, p->bullets.front());//�������� ������ p ������ Player � ������� ������� sfml, ��������� ����� � �������� ��������� ������� update. ��������� ����� �������� ����� ���������
		
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++)//������� ��� ���������� �� ������ �� �����
		{
			//bullets.front()->update();
			(*bIt)->update(time, TileMap, cursor.x, cursor.y, playerCoord.x, playerCoord.y);//�������� �-��� update ��� ���� �������� ������

		}

		if (p->bullets.front()->isMove){
			//b = playerBullets.front();
			p->bullets.push_back(p->bullets.front());
			p->bullets.pop_front();
		}

		/* ________________________________ ����� ������� ������ _______________________________________________ */

		


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// �������������� �������� ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* ---------------------- ������������ ������ � ����� -------------------------------------- */
		/* ------------------------ ������������ ������ �� ����� ��� ������� ��������������� ------- */
		//z = 0;
		if (!enemies.empty()){
			for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������
			{
				//fullEnemyName = "Enemy" + enemyName[z].str();
				//if (z < 3)z++;
				if ((*it)->getRect().intersects(p->getRect()))//���� ������������� ������� ������� ������������ � �������
				{
					if (p->dx < 0) {
						p->changeCoordinateX_to((*it)->getCoordinateX() + (*it)->w);
						//(*it)->changeCoordinateX_to(p->getCoordinateX() - p->w);
					}//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
					if (p->dx > 0) {
						p->changeCoordinateX_to((*it)->getCoordinateX() - p->w);
						//(*it)->changeCoordinateX_to(p->getCoordinateX() + (*it)->w);
					}//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
					if (p->dy < 0) {
						p->changeCoordinateY_to((*it)->getCoordinateY() + (*it)->h);
						//	(*it)->changeCoordinateY_to(p->getCoordinateY() - p->h);
					}//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
					if (p->dy > 0) {
						p->changeCoordinateY_to((*it)->getCoordinateY() - p->h);
						//(*it)->changeCoordinateY_to(p->getCoordinateY() + (*it)->h);
					}//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
				}
			}
		}


		/* ----------------- ��������� ����� ����� ��� ��������� �� ���� ������ ------------------------------ */
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++)//���������� �� ��-��� ������
		{

			for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������
				{
					if ((*it)->getRect().intersects((*bIt)->getRect()))//���� ������������� ������� ������� ������������ � �������
					{
						if ((*bIt)->isMove)	{
							(*it)->health -= p->damage;
							(*bIt)->isMove = false;
							(*bIt)->touched = true;
						}

					}
				}
		}

		/* ----------------- ��������� ���� ����� �� ������ ------------------------------ */

		for (it = enemies.begin(); it != enemies.end(); it++)//������� ��� ���������� �� ������ �� �����
		{
			//Creature *b = *it;//��� ��������, ����� �� ������ (*it)->

			for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)//���������� �� ��-��� ������
			{
				if (p->getRect().intersects((*bIt)->getRect()))//���� ������������� ������� ������� ������������ � �������
				{
					if ((*bIt)->isMove)	{
						//(*it)->health -= p->damage;
						(*bIt)->isMove = false;
						(*bIt)->touched = true;
					}

				}
			}

		}
		window.setView(view);//"��������" ������ � ���� sfml
		window.clear();


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ���������� ���� �������� ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/* ----------------------���������� ����� -------------------------------------- */
		testMap->drawMap(&window, &s_map, TileMap);

		/* ------------------------ ���������� �������� ������ � �������� ������ --------------------------*/
		window.draw(p->sprite); //������ ������ ������� p ������ player
		//for (bIt = playerBullets.begin(); bIt != playerBullets.end(); bIt++)window.draw((*bIt)->sprite); //������ ���� ������
		for (bIt = p->bullets.begin(); bIt != p->bullets.end(); bIt++) window.draw((*bIt)->sprite); //������ ���� ������


		//window.draw(bullet->sprite);

		
		/* ------------------------ ���������� �������� ������ � �������� ������ --------------------------*/
		if (!enemies.empty()){
			for (it = enemies.begin(); it != enemies.end(); it++){
				window.draw((*it)->sprite); //������ entities ������� (������ ��� ������ �����)
				for (bIt = (*it)->bullets.begin(); bIt != (*it)->bullets.end(); bIt++)window.draw((*bIt)->sprite); //������ ���� ������
				
			}
		}


  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //////////////////////////////////////////////////// ����� ���������� ������ ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		std::ostringstream playerHealthString, gameTimeString , playerAmmoString;    // �������� ���������� �������� � �������
		std::ostringstream checkString;

		std::ostringstream enemyInfo[enemyNumber];

		sf::String fullText;
		

		if (p->life){
			playerHealthString << p->health;		//������� � ��� ���������� ����� ��������, �� ���� ��������� ������
			playerAmmoString << p->ammo;

			//it = creatures.begin();

			

			checkString << p->health;

			sf::String checkText = checkString.str();

			fullText = "��������: " + playerHealthString.str() + "\t�������: " + playerAmmoString.str() + "\n " ;

			fullText = fullText + "Shot Timer:  " + checkText + "\n";
			
			/*
			std::list<std::ostringstream> enemyInfoString;
			std::list<std::ostringstream>::iterator strIt;
			*/
		
			std::string  enemyInfoString;
			//std::ostringstream::intTo



			//int k = 0;
			if (!enemies.empty()){
				for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������
				{
					//enemyInfoString = (*it)->health;
					//fullText = (*it)->health;

					enemyInfoString = std::to_string((*it)->health);

					fullText = fullText + "�������� " + (*it)->name + ":\t  " + enemyInfoString + "\n";

					//enemyInfoString << "";
					
				}
			}
			

			text.setString(fullText.toAnsiString(std::locale::global(std::locale("rus"))));//������ ������ ������ � �������� �������������� ���� ������ ������� .str() 
			text.setPosition(view.getCenter().x - winSize.x / 2 + 5, view.getCenter().y - winSize.y/2 + 5);//������ ������� ������, �������� �� ������ ������
		}
		else{
			playerHealthString << p->health;
			//gameTimeString << gameTime;		
			text.setCharacterSize(30);
			text.setColor(sf::Color::Red);

			fullText = "���� �������� ! \n\n";
				fullText = fullText + "��������: " + playerHealthString.str(); //��������� ������
			//fullText = fullText + "\n����� ����: " + gameTimeString.str();


			text.setString(fullText.toAnsiString(std::locale::global(std::locale("rus"))));//������ ������ ������ � �������� �������������� ���� ������
			text.setPosition(view.getCenter().x - 115, view.getCenter().y - 60);//������ ������� ������, �������� �� ������ ������
		}
		

		/* -------------- ���������� ������ --------------------------- */
		window.draw(text);

		/* ------------------- ����� �� ����� ------------------------- */
		window.display();
	}

	delete p;
	delete testMap;
	return 0;
}
