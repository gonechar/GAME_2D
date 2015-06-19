






/*
#include <SFML\Graphics.hpp>
#include <iostream>

#include "sets_n_structs.h"
#include <list>
#include "EntityClass.h"
*/

#include <sstream>
#include "MapLoaderClass.h"



//using namespace sf; //�������� ������������ ���� SFML ����� �� ��������� ������ ��� �������������� � ������ -> sf::


////////////////////////////////////////////////////����� ������////////////////////////

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

	std::list<Entity*> objects;  //����� �������� ����� ���������, ���������� ���� �� �����������, ���������� ����������� � ��� �������

	//std::list<sf::String>::iterator it;

	//if (objectImages.empty()) return std::list<Entity*> x;
	
	
		//if (!isPlayerLoaded){
			for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if ((TileMap[i][j] == 'p')) {


					objects.push_back(new Entity(playerName, j * tileMapSize, i * tileMapSize, "Player1"));

						//s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
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
		//if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������

		if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '1')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '2')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '3')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '4')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������

		if ((TileMap[i][j] == 'x')) s_map->setTextureRect(sf::IntRect(192, 32, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == 'y')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == 'z')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == 'w')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '-')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������


		if (TileMap[i][j] == 's')  s_map->setTextureRect(sf::IntRect(32, 192, 32, 32));//���� ��������� ������ s, �� ������ �������
		if ((TileMap[i][j] == 'h')) s_map->setTextureRect(sf::IntRect(0, 192, 32, 32));//������ �������

		if ((TileMap[i][j] == 'm')) s_map->setTextureRect(sf::IntRect(0, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '[')) s_map->setTextureRect(sf::IntRect(32, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == ']')) s_map->setTextureRect(sf::IntRect(64, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '{')) s_map->setTextureRect(sf::IntRect(96, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '}')) s_map->setTextureRect(sf::IntRect(128, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == 'f')) s_map->setTextureRect(sf::IntRect(160, 224, 32, 32));//�������� ����

		if (TileMap[i][j] == ' ')  s_map->setTextureRect(sf::IntRect(0, 32, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
		if (TileMap[i][j] == 'x')  s_map->setTextureRect(sf::IntRect(64, 32, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
		if (TileMap[i][j] == 'y')  s_map->setTextureRect(sf::IntRect(96, 32, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
		if (TileMap[i][j] == 'z')  s_map->setTextureRect(sf::IntRect(124, 32, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
		s_map->setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

		window->draw(*s_map);//������ ���������� �� �����
	}
};


void MapLoader::randomMapGenerate(sf::String *TileMap){//�������� ����������� �����

	int randomElementX = 0;//��������� ������� �� �����������
	int randomElementY = 0;//���� ��-� �� ���������
	srand(time(0));//������	
	int countStone = 2;//���������� ������

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomElementY][randomElementX] == ' ')   {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 's'; //�� ������ ���� ������.

			countStone--;
		}
	}
};



/*
void drawMap(sf::RenderWindow *window, sf::Sprite *s_map, Player &p){

	for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
		//if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������

		if ((TileMap[i][j] == '0')) s_map->setTextureRect(sf::IntRect(96, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '1')) s_map->setTextureRect(sf::IntRect(160, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '2')) s_map->setTextureRect(sf::IntRect(192, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '3')) s_map->setTextureRect(sf::IntRect(156, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������
		if ((TileMap[i][j] == '4')) s_map->setTextureRect(sf::IntRect(124, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������

		if (TileMap[i][j] == 's')  s_map->setTextureRect(sf::IntRect(32, 192, 32, 32));//���� ��������� ������ s, �� ������ �������
		if ((TileMap[i][j] == 'h')) s_map->setTextureRect(sf::IntRect(0, 192, 32, 32));//������ �������

		if ((TileMap[i][j] == 'm')) s_map->setTextureRect(sf::IntRect(0, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '[')) s_map->setTextureRect(sf::IntRect(32, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == ']')) s_map->setTextureRect(sf::IntRect(64, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '{')) s_map->setTextureRect(sf::IntRect(96, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == '}')) s_map->setTextureRect(sf::IntRect(128, 224, 32, 32));//�������� ����
		if ((TileMap[i][j] == 'f')) s_map->setTextureRect(sf::IntRect(160, 224, 32, 32));//�������� ����

		if (TileMap[i][j] == ' ')  s_map->setTextureRect(sf::IntRect(0, 32, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
		if (TileMap[i][j] == 'x')  s_map->setTextureRect(sf::IntRect(64, 32, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
		if (TileMap[i][j] == 'y')  s_map->setTextureRect(sf::IntRect(96, 32, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
		if (TileMap[i][j] == 'z')  s_map->setTextureRect(sf::IntRect(124, 32, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
		s_map->setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

		window->draw(*s_map);//������ ���������� �� �����
	}
}

void randomMapGenerate(){//�������� ����������� �����

	int randomElementX = 0;//��������� ������� �� �����������
	int randomElementY = 0;//���� ��-� �� ���������
	srand(time(0));//������	
	int countStone = 2;//���������� ������

	while (countStone>0){
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������� �� ���� �� 1 �� ������ �����-1, ����� �� �������� ����� ������� �����
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� ������ ��� ��

		if (TileMap[randomElementY][randomElementX] == ' ')   {//���� ��������� ������ ������, 
			TileMap[randomElementY][randomElementX] = 's'; //�� ������ ���� ������.

			countStone--;
		}
	}
}
*/

