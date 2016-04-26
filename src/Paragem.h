/*
 * Paragem.h
 *
 *  Created on: 10/04/2016
 *      Author: jp
 */
#include <iostream>
using namespace std;

class Paragem {

private:
	int x;
	int y;
	string nome;

public:
	Paragem();
	Paragem(string nome,int x, int y);
	string getNome()const;
	int getX()const;
	int getY()const;
bool operator==(Paragem p);
bool operator!=(Paragem p);
};


