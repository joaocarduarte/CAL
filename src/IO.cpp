/*
 * IO.cpp
 *
 *  Created on: 17/04/2016
 *      Author: jp
 */
#include <iostream>
#include "Paragem.h"
#include "Graph.h"
#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;
template <class T>
void loadGraph(Graph<T> &g){
ifstream f,e;
f.open("vertex.txt");
string nome;
string x,y;
string line,line2;

if ( f.is_open() ) {

	while( !f.eof()) {

		getline(f,line);
		stringstream linestream(line);
		getline(linestream,nome,',');
		getline(linestream,x,',');
		linestream >>y;

		Paragem p=Paragem(nome,atoi(x.c_str()),atoi(y.c_str()));
		g.addVertex(p);

	}
}
f.close();
string sourc,dest,tipo,dinheiro,linha,tempo;
e.open("edge.txt");
if(e.is_open()){
	while(!e.eof()){
		getline(e,line2);
		stringstream ss(line2);
		getline(ss,sourc,',');
		getline(ss,dest,',');
		getline(ss,tipo,',');
		getline(ss,dinheiro,',');
		getline(ss,linha,',');
		getline(ss,tempo);
		Transportes t;

		if(tipo=="Metro"){
			t=Metro(linha,atoi(dinheiro.c_str()),atoi(tempo.c_str()));
		}

		if(tipo== "Comboio"){
					t=Comboio(linha,atoi(dinheiro.c_str()),atoi(tempo.c_str()));
				}

		if(tipo== "Autocarro"){
					t=Autocarro(linha,atoi(dinheiro.c_str()),atoi(tempo.c_str()));
				}

		if(tipo== "Caminhar"){
					t=Caminhar(linha,atoi(dinheiro.c_str()),atoi(tempo.c_str()));
				}



		g.addEdge(g.getVertexSet()[atoi(sourc.c_str())]->getInfo(),g.getVertexSet()[atoi(dest.c_str())]->getInfo(),t);
	}

}
e.close();
}
template<class T>
void saveGraph(Graph<T> g){
	ofstream f;
	f.open("vertex.txt");

	if ( f.is_open() ) {

		for (unsigned int i=0;i<g.getVertexSet().size();i++ ) {
			if(i==g.getVertexSet().size()-1)
				f << g.getVertexSet()[i]->getInfo().getNome() <<','<<g.getVertexSet()[i]->getInfo().getX()<<','<<g.getVertexSet()[i]->getInfo().getY();
			else
			f << g.getVertexSet()[i]->getInfo().getNome() <<','<<g.getVertexSet()[i]->getInfo().getX()<<','<<g.getVertexSet()[i]->getInfo().getY()<<endl;

		}
	}
	f.close();

ofstream e;
e.open("edge.txt");
if ( e.is_open() ) {
int k=0;
	for (unsigned int i=0;i<g.getVertexSet().size();i++ ) {
		for(unsigned int j=0; j<g.getVertexSet()[i]->getAdj().size();j++){
			if(k==g.NumArestas()-1)
			e << i<<','<<g.findadjonVertex(g.getVertexSet()[i]->getAdj()[j].getDest()) <<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getNome()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getDinheiro()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getLinha()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getTempo();
			else
				e << i<<','<<g.findadjonVertex(g.getVertexSet()[i]->getAdj()[j].getDest()) <<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getNome()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getDinheiro()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getLinha()<<','<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getTempo()<<endl;
			k++;
		}


	}
}
e.close();
}
