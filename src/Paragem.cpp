/*
 * Paragem.cpp
 *
 *  Created on: 10/04/2016
 *      Author: jp
 */

#include "Paragem.h"

Paragem::Paragem(){

}
Paragem::Paragem(string nome,int x, int y): x(x),nome(nome),y(y){

}
string Paragem::getNome()const{
	return nome;

}
int Paragem::getX()const{
	return x;
}
int Paragem::getY()const{
	return y;
}
bool Paragem::operator==(Paragem p){
	if (this->nome==p.nome&& this->x==p.x&&this->y==p.y)
		return true;
	else return false;
}
bool Paragem::operator!=(Paragem p){
	if (this->nome==p.nome&& this->x==p.x&&this->y==p.y)
			return false;
	else return true;
}


