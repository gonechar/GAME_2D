
#include "map.h"


#include <SFML\Graphics.hpp>
#include <list>
#include <fstream>


#include "sets_n_structs.h"
#include "PlayerClass.h"







class MapLoader { // ����� �������� � ����

public:

	bool isPlayerLoaded;
	bool isAllEnemiesLoaded;
	bool isEveryMineLoaded;
	int enemiesCounter;
	int namesCounter;

	sf::String playerName;

	/*
	
	sf::String enemyImage[];
	sf::String fullEnemyName;

	//sf::String enemyImageString;
	*/

	std::string enemyName;
	sf::String fullEnemyName;

	std::list<sf::String> enemiesNamesList;
	std::list<sf::String> enemiesImageList;
	std::list<sf::String>::iterator listIt;//�������� ����� ��������� �� ��-��� ������

	MapLoader(sf::String PlayerNAME, sf::String *TileMap); //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
	
	std::list<Entity*> setEntitiesAtMap(sf::String *TileMap, sf::RenderWindow *window, std::list<sf::String> objectImages);

	int getEnemiesCount(sf::String *TileMap);

	void drawMap(sf::RenderWindow *window, sf::Sprite *s_map, sf::String *TileMap);

	void randomMapGenerate(sf::String *TileMap);
};