/*
 * maincli.cpp
 *
 *  Created on: 10/04/2016
 *      Author: jp
 */
#include "menu.h"
#include "IO.cpp"
#include <cstdio>
#include "graphviewer.h"
#include <fstream>

#include <sstream>
Graph<Paragem> g;
void MenuInicial(){

cout << "------Menu Inicial-----"<<endl;
cout << "                       "<<endl;
cout << "1. ver grafo           "<<endl;
cout << "2. Menu de Paragens    "<<endl;
cout << "3. quit                "<<endl;
cout <<"Qual a opção :";
char opcao;
cin >> opcao;
int e=0;
switch(opcao) {
case '1':{
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600,600);

	for(unsigned int i=0;i < g.getVertexSet().size();i++){

	Sleep(2000);
	gv->addNode(i,g.getVertexSet()[i]->getInfo().getX(),g.getVertexSet()[i]->getInfo().getY());
	gv->setVertexLabel(i,g.getVertexSet()[i]->getInfo().getNome());
	gv->rearrange();
}
	for (unsigned int j=0;j <g.getVertexSet().size();j++){
		for(unsigned int k=0;k<g.getVertexSet()[j]->getAdj().size();k++){
			Sleep(2000);
			gv->addEdge(e,j,g.findadjonVertex(g.getVertexSet()[j]->getAdj()[k].getDest()),EdgeType::DIRECTED);
			gv->setEdgeLabel(e,g.getVertexSet()[j]->getAdj()[k].getTransporte().getLinha());
			gv->rearrange();


			e++;
		}
	}
}
MenuInicial();
	break;
case '2':
	MenuParagem();
	break;
case '3':
	return ;
	break;
default:
	MenuInicial();
	break;

}
}
void MenuParagem(){
	cout << "------Menu Paragem----"<<endl;
	cout << "                      "<<endl;
	cout << "                      "<<endl;
	cout << "1. Adicionar Paragem  "<<endl;
	cout << "2. Remover Paragem    "<<endl;
	cout << "3. Adicionar Transporte(Aresta)"<<endl;
	cout << "4. Remover Transporte(Aresta)  "<<endl;
	cout << "5. Voltar ao menu anterior"<<endl;
	char opcao;
	cout <<"Opção: ";
	cin >>opcao;
	string nome;
	int x=0;
	int y=0;
	switch(opcao){
	case '1':{
		cin.ignore();
		cin.clear();
		cout <<"Nome da paragem:";
		getline(cin,nome);
		cout<<"Posição x:";

		cin>>x;
		cin.ignore();
		cin.clear();
		cout<<"Posição y:";
		cin >>y;
		Paragem p = Paragem(nome,x,y);
		g.addVertex(p);
		saveGraph(g);
	}
	MenuParagem();
		break;
	case '2':
	{
		if(g.getVertexSet().empty())
			cout << "Não existem Paragens"<<endl;
		else{
			cin.ignore();
			cin.clear();
			cout <<"Nome da paragem a remover:"<<endl;
			for(unsigned int i=0; i< g.getVertexSet().size();i++){
						cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
					}
					unsigned int i;
					cin >>i;
					i--;
					if(i<0 || i >= g.getVertexSet().size() )
						cout<< " escolheu uma opção errada não existe esse indice de paragem" <<endl;
					else
					g.removeVertex(g.getVertexSet()[i]->getInfo());

		saveGraph(g);
	}
	}
		MenuParagem();
		break;
	case '3':{
		cout <<"-------Criação de Ligação----" <<endl;
				cout << endl;
		cout << "Paragem de destino:"<<endl;
		for(unsigned int i=0; i< g.getVertexSet().size();i++){
			cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
		}
		unsigned int i;
		cin >>i;
		i--;
		cout << "Paragem de Origem:"<<endl;
		for(unsigned int j=0; j< g.getVertexSet().size();j++){
					if(i ==j){

					}
					else
					cout << j+1 << ") "<< g.getVertexSet()[j]->getInfo().getNome()<<endl;
				}
		unsigned int k;
		cin >>k;
		k--;
		cout <<"Tempo da viagem em minutos";
		int tempo;
		int custo;
		int distancia;
		string linha;
		int opcao2;
		cin >>tempo;
		cout << "Custo da viagem(euros):";
		cin >>custo;
		cout <<"Distancia entre as paragens(metros):";
		cin >>distancia;
		cout << "Tipo de transporte disponiveis:"<<endl;
		cout << "1: metro"<<endl;
		cout << "2: comboio"<<endl;
		cout << "3: autocarro"<<endl;
		cout << "4: a pé"<<endl;
		cout <<"Escolha:";
		cin >> opcao2;
		cin.ignore();
		cin.clear();
		cout <<"linha a que pertence:";
		getline(cin,linha);
		Transportes m;

		switch(opcao2){
		case 1:{
			m= Metro (linha,custo,distancia,tempo);
		}
		break;
		case 2: {m=Comboio (linha,custo,distancia,tempo);}break;
		case 3:{m= Autocarro (linha,custo,distancia,tempo);}break;
		case 4: {m= Caminhar (linha,custo,distancia,tempo);}break;
		default: cout <<"não é uma opção possivel";
		}
		if(i<0 || i >= g.getVertexSet().size() || k<0 || k >= g.getVertexSet().size()|| custo<0)
			cout<< " escolheu uma opção errada não existe esse indice de paragem" <<endl;
		else{
			g.addEdge(g.getVertexSet()[k]->getInfo(),g.getVertexSet()[i]->getInfo(),m);

		}

saveGraph(g);
	}
	MenuParagem();
		break;
	case '4':{
		cout <<"-------Remoção de Ligação----" <<endl;
		cout << endl;
		cout << "Paragem de destino:"<<endl;
				for(unsigned int i=0; i< g.getVertexSet().size();i++){
					cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
				}
				unsigned int i;
				cin >>i;
				i--;
				cout << "Paragem de Origem:"<<endl;
				for(unsigned int j=0; j< g.getVertexSet().size();j++){
							if(i ==j){

							}
							else
							cout << j+1 << ") "<< g.getVertexSet()[j]->getInfo().getNome()<<endl;
						}
				unsigned int k;
				cin >>k;
				k--;
				if(i<0 || i >= g.getVertexSet().size() || k<0 || k >= g.getVertexSet().size())
					cout<< " escolheu uma opção errada não existe esse indice de paragem" <<endl;
				else
				g.removeEdge(g.getVertexSet()[k]->getInfo(),g.getVertexSet()[i]->getInfo());

				saveGraph(g);
	}
	MenuParagem();
		break;

	case '5':
		MenuInicial();
		break;
	default:
		cout <<"escolha uma opção possível"<<endl;
		MenuParagem();
		break;

	}
}

int main() {


	loadGraph(g);
	MenuInicial();
	getchar();
	return 0;
}
