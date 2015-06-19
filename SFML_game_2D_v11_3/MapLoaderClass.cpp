






/*
#include <SFML\Graphics.hpp>
#include <iostream>

#include "sets_n_structs.h"
#include <list>
#include "EntityClass.h"
*/

#include <sstream>
#include "MapLoaderClass.h"



//using namespace sf; //включаем пространство имен SFML чтобы не указывать каждый раз принадлежность к классу -> sf::


////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////

MapLoader::MapLoader(sf::String PlayerNAME, sf::String *TileMap){

	isPlayerLoaded = false;
	isAllEnemiesLoaded = false;
	isEveryMineLoaded = false;
	enemiesCounter = 0;
	namesCounter = 0;

	playerName = PlayerNAME;

	enemiesCounter = getEnemiesCount(TileMap);

	//enemyInfoString = std::to_string((*it)->health);
	//int fixInt;

	int k=0;

	for (int i = 0; i < enemiesCounter; i++){

		k++;

		if (k > 3) k = 1;

		enemyName = std::to_string(k);
		
		
		//else enemyName = "1";

		fullEnemyName = "Enemy" + enemyName;
		//enemyImage[i] = "images/MEnemy/" + fullEnemyName + ".png";

		enemiesNamesList.push_back(fullEnemyName);
		enemiesImageList.push_back("images/MEnemy/" + fullEnemyName + ".png");
		
		enemyName = " ";
	}
	
	
	
	/*
	const int counter = enemiesCounter;
	std::ostringstream enemyName[counter];

	sf::String enemyImage[counter];

	//sf::String enemyImageString;


	sf::String fullEnemyName[counter];
	*/
};



std::list<Entity*> MapLoader::setEntitiesAtMap(sf::String *TileMap, sf::RenderWindow *window, std::list<sf::String> objectImages){

	std::list<Entity*> objects;  //здесь задается набор сущностей, содержащих путь до изображения, координаты расстановки и имя объекта

	//std::list<sf::String>::iterator it;

	//if (objectImages.empty()) return std::list<Entity*> x;
	
	
		//if (!isPlayerLoaded){
			for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if ((TileMap[i][j] == 'p')) {


					objects.push_back(new Entity(playerName, j * tileMapSize, i * tileMapSize, "Player1"));

						//s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
					TileMap[i][j] = 'x';
					isPlayerLoaded = true;
				}
			}
			
		//}

		//if (isPlayerLoaded && !isAllEnemiesLoaded){
			
			listIt = enemiesNamesList.begin();

		//	for (int k = enemiesCounter; k > 0;){
			if (!enemiesNamesList.empty()){
				for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if ((TileMap[i][j] == 'e')) {

						namesCounter++;

						//for (listIt = enemiesNamesList.begin();  listIt != enemiesNamesList.end(); listIt++)
						objects.push_back(new Entity("images/MEnemy/" + (*listIt) + ".png", j * tileMapSize, i * tileMapSize, (*listIt)));

						//objects.push_back(new Entity("images/MEnemy/Enemy1.png", j * tileMapSize, i * tileMapSize, "Enemy1"));

						listIt = enemiesNamesList.erase(listIt);

						//k--;



						TileMap[i][j] = ' ';

					}
				}
			}


			//}


		//}
	
	return objects;
};


int MapLoader::getEnemiesCount(sf::String *TileMap)
{
	int enemiesCounter2 = 0;
	for (int i = 0; i < HEIGHT_MAP; i++){
		//strcmp(TileMap[i][j], "e");
		if (TileMap[i].find('e', 0) != sf::String::InvalidPos) {
			enemiesCounter2++;

		}
	}
	return enemiesCounter2;
}


void MapLoader::drawMap(sf::RenderWindow *window, sf::Sprite *s_map, sf::String *TileMap){

	for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
		//if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

		if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '1')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '2')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '3')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '4')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

		if ((TileMap[i][j] == 'x')) s_map->setTextureRect(sf::IntRect(192, 32, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == 'y')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == 'z')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == 'w')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '-')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


		if (TileMap[i][j] == 's')  s_map->setTextureRect(sf::IntRect(32, 192, 32, 32));//если встретили символ s, то рисуем патроны
		if ((TileMap[i][j] == 'h')) s_map->setTextureRect(sf::IntRect(0, 192, 32, 32));//рисуем аптечку

		if ((TileMap[i][j] == 'm')) s_map->setTextureRect(sf::IntRect(0, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '[')) s_map->setTextureRect(sf::IntRect(32, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == ']')) s_map->setTextureRect(sf::IntRect(64, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '{')) s_map->setTextureRect(sf::IntRect(96, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '}')) s_map->setTextureRect(sf::IntRect(128, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == 'f')) s_map->setTextureRect(sf::IntRect(160, 224, 32, 32));//добавили мину

		if (TileMap[i][j] == ' ')  s_map->setTextureRect(sf::IntRect(0, 32, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
		if (TileMap[i][j] == 'x')  s_map->setTextureRect(sf::IntRect(64, 32, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
		if (TileMap[i][j] == 'y')  s_map->setTextureRect(sf::IntRect(96, 32, 32, 32));//если встретили символ s, то рисуем 2й квадратик
		if (TileMap[i][j] == 'z')  s_map->setTextureRect(sf::IntRect(124, 32, 32, 32));//если встретили символ s, то рисуем 2й квадратик
		s_map->setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

		window->draw(*s_map);//рисуем квадратики на экран
	}
};


void MapLoader::randomMapGenerate(sf::String *TileMap){//рандомно расставляем камни

	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	
	int countStone = 2;//количество камней

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ')   {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.

			countStone--;
		}
	}
};



/*
void drawMap(sf::RenderWindow *window, sf::Sprite *s_map, Player &p){

	for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
		//if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

		if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '1')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '2')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '3')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
		if ((TileMap[i][j] == '4')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик

		if (TileMap[i][j] == 's')  s_map->setTextureRect(sf::IntRect(32, 192, 32, 32));//если встретили символ s, то рисуем патроны
		if ((TileMap[i][j] == 'h')) s_map->setTextureRect(sf::IntRect(0, 192, 32, 32));//рисуем аптечку

		if ((TileMap[i][j] == 'm')) s_map->setTextureRect(sf::IntRect(0, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '[')) s_map->setTextureRect(sf::IntRect(32, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == ']')) s_map->setTextureRect(sf::IntRect(64, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '{')) s_map->setTextureRect(sf::IntRect(96, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == '}')) s_map->setTextureRect(sf::IntRect(128, 224, 32, 32));//добавили мину
		if ((TileMap[i][j] == 'f')) s_map->setTextureRect(sf::IntRect(160, 224, 32, 32));//добавили мину

		if (TileMap[i][j] == ' ')  s_map->setTextureRect(sf::IntRect(0, 32, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
		if (TileMap[i][j] == 'x')  s_map->setTextureRect(sf::IntRect(64, 32, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
		if (TileMap[i][j] == 'y')  s_map->setTextureRect(sf::IntRect(96, 32, 32, 32));//если встретили символ s, то рисуем 2й квадратик
		if (TileMap[i][j] == 'z')  s_map->setTextureRect(sf::IntRect(124, 32, 32, 32));//если встретили символ s, то рисуем 2й квадратик
		s_map->setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

		window->draw(*s_map);//рисуем квадратики на экран
	}
}

void randomMapGenerate(){//рандомно расставляем камни

	int randomElementX = 0;//случайный элемент по горизонтали
	int randomElementY = 0;//случ эл-т по вертикали
	srand(time(0));//рандом	
	int countStone = 2;//количество камней

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//рандомное по иксу от 1 до ширина карты-1, чтобы не получать числа бордюра карты
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//по игреку так же

		if (TileMap[randomElementY][randomElementX] == ' ')   {//если встретили символ пробел, 
			TileMap[randomElementY][randomElementX] = 's'; //то ставим туда камень.

			countStone--;
		}
	}
}
*/

