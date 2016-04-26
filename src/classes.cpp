
#include "classes.h"

//construtores
Transportes::Transportes(string linha, int dinheiro, int tempo,string nome):linha(linha),dinheiro(dinheiro),tempo(tempo),nome(nome){



}
Comboio::Comboio(string linha, int dinheiro,  int tempo):Transportes(linha, dinheiro, tempo,"Comboio"){

}
Metro::Metro(string linha, int dinheiro,  int tempo):Transportes(linha, dinheiro,  tempo,"Metro"){

}
Autocarro::Autocarro(string linha, int dinheiro,  int tempo):Transportes(linha, dinheiro,  tempo,"Autocarro"){

}
Caminhar:: Caminhar(string linha, int dinheiro, int tempo):Transportes(linha, dinheiro, tempo,"Caminhar"){

}

//funcoes referentes a comboio
string Transportes::getLinha()const {
	return linha;
}
int Transportes::getDinheiro()const {
	return dinheiro;
}

int Transportes::getTempo()const {
	return tempo;
}
void Transportes::setDinheiro(int dinheiro){
	this->dinheiro=dinheiro;
}

void Transportes::setTempo(int time){
	this->tempo=time;
}
string Transportes::getNome()const{
	return nome;
}

