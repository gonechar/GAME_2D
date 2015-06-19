
#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
//using namespace sf;

sf::View view;//�������� sfml ������ "���", ������� � �������� �������

sf::View setPlayerCoordinateForView(float x, float y, sf::Vector2u *winSize) { //������� ��� ���������� ��������� ������

	//sf::Vector2u winSize = window->getSize();

	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����
	float tempWidth = winSize->x; float tempHieght = winSize->y;

	if (x < tempWidth / 2) tempX = tempWidth/2;//������� �� ���� ����� �������
	if (y < tempHieght / 2) tempY = tempHieght/2;//������� �������
	if (y > HEIGHT_MAP * 32 - tempHieght / 2) tempY = HEIGHT_MAP * 32 - tempHieght / 2;//������ �������	

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ���������� ������. +100 - �������� ������ �� ���� ������. �����������������
	return view;
}

/*
View viewMap(float time) { //������� ��� ����������� ������ �� �����. ��������� ����� sfml


if (Keyboard::isKeyPressed(Keyboard::D)) {
view.move(0.1*time, 0);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
}

if (Keyboard::isKeyPressed(Keyboard::S)) {
view.move(0, 0.1*time);//�������� ����� ���� (�� ����, ����� �� ������� ����� - �� ���� �����)
}

if (Keyboard::isKeyPressed(Keyboard::A)) {
view.move(-0.1*time, 0);//�������� ����� ����� (�� ����, ����� �� ������� ����� - �� ���� �����)
}
if (Keyboard::isKeyPressed(Keyboard::W)) {
view.move(0, -0.1*time);//�������� ����� ������ (�� ����, ����� �� ������� ����� - �� ���� �����)
}

return view;
}
*/

/*
View changeView(){


if (Keyboard::isKeyPressed(Keyboard::U)) {
view.zoom(1.0100f); //������������, ����������
//view.zoom(1.0006f); //���� ����� ����������� ��������������
}

if (Keyboard::isKeyPressed(Keyboard::R)) {
//view.setRotation(90);//����� �� ������ ������� ������
view.rotate(1);//���������� ������������ ������ (������������� �������� - � �������� �������)
}


if (Keyboard::isKeyPressed(Keyboard::I)) {
view.setSize(640, 480);//������������� ������ ������ (��� ��������)
}

if (Keyboard::isKeyPressed(Keyboard::P)) {
view.setSize(540, 380);//�������� ������ ������
}


if (Keyboard::isKeyPressed(Keyboard::Q)) {
view.setViewport(sf::FloatRect(0, 0, 0.5f, 1));//����� ������� �������� ���������� ����� ��� ���� �� �����. ����� ������ ������� ��� ���� ������ View � ����������� � ���� ���������� ������ 2.
}
return view;

}
*/

#endif