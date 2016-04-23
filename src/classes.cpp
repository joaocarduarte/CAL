
#include "classes.h"

//construtores
Transportes::Transportes(string linha, int dinheiro, int distancia, int tempo,string nome):linha(linha),dinheiro(dinheiro),distancia(distancia),tempo(tempo),nome(nome){



}
Comboio::Comboio(string linha, int dinheiro, int distancia, int tempo):Transportes(linha, dinheiro, distancia, tempo,"Comboio"){

}
Metro::Metro(string linha, int dinheiro, int distancia, int tempo):Transportes(linha, dinheiro, distancia, tempo,"Metro"){

}
Autocarro::Autocarro(string linha, int dinheiro, int distancia, int tempo):Transportes(linha, dinheiro, distancia, tempo,"Autocarro"){

}
Caminhar:: Caminhar(string linha, int dinheiro, int distancia, int tempo):Transportes(linha, dinheiro, distancia, tempo,"Caminhar"){

}

//funcoes referentes a comboio
string Transportes::getLinha()const {
	return linha;
}
int Transportes::getDinheiro()const {
	return dinheiro;
}
int Transportes::getDistancia()const {
	return distancia;
}
int Transportes::getTempo()const {
	return tempo;
}
void Transportes::setDinheiro(int dinheiro){
	this->dinheiro=dinheiro;
}
void Transportes::setDistancia(int distancia){
	this->distancia=distancia;
}
void Transportes::setTempo(int time){
	this->tempo=time;
}
string Transportes::getNome()const{
	return nome;
}

