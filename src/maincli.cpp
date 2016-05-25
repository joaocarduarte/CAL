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
#include "matcher.h"


#include <sstream>
Graph<Paragem> g;
void MenuInicial(){

cout << "------Menu Inicial-----"<<endl;
cout << "                       "<<endl;
cout << "1. ver grafo em modo Viewer"<<endl;
cout << "2. Menu de Paragens    "<<endl;
cout << "3. Pesquisas no grafo         "<<endl;
cout << "4. Pesquisas por Matching de Strings(2ª Parte)"<<endl;
cout << "5. quit                "<<endl;
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
			string s=g.getVertexSet()[j]->getAdj()[k].getTransporte().getLinha();

			gv->setEdgeLabel(e,s); //TODO
			gv->rearrange();


			e++;
		}
	}
}
cout << string(7,'\n');
MenuInicial();
	break;
case '2':
	cout << string(7,'\n');
	MenuParagem();
	break;
case '3':
	cout << string(7,'\n');
	MenuPesquisas();
	break;
case '4':
	cout << string(7,'\n');
	MenuStringMatching();
	break;
case '5':
	return ;
	break;
default:
	cout << string(7,'\n');
	MenuInicial();
	break;

}
}

template <class T>
int exists(vector<T>v,T s){
	for(unsigned int i=0; i< v.size();i++){
		if(v[i]==s)
			return i;

	}
	return -1;

}
template <class T>
void Ordena(vector<int>&v, vector <T>&p){

	for (unsigned int i = 1; i < v.size(); i++)
	{
	int tmp = v[i];
	T tm=p[i];
	int j;
	for (j = i; j > 0 && tmp < v[j-1]; j--){
		v[j] = v[j-1];
		p[j]=p[j-1];
	}
	v[j] = tmp;
	p[j] = tm;
	}
}
void MenuStringMatching(){
	cout <<"------Menu String Matching----"<<endl;
	cout <<"                              "<<endl;
	cout <<"1.Pesquisar Paragem através de Pesquisa exacta"<<endl;
	cout <<"2.Pesquisar Paragem através de Pesquisa aproximada"<<endl;
	cout <<"3.Pesquisar se uma linha passa numa Paragem"<<endl;
	cout <<"4.Pesquisar por onde passa uma linha através de Pesquisa aproximada"<<endl;
	cout << "5. Quit"<<endl;
	char opcao;
	cin >>opcao;
		switch(opcao){
		case '1':{
			char ignore;
			string nome;
			cin.ignore();
			cin.clear();
			cout << "Nome da Paragem";
			getline(cin,nome);
			int num=0;
			int tmp;
			for(unsigned int i=0; i< g.getVertexSet().size();i++){
				tmp=num;
			num+=kmp(g.getVertexSet()[i]->getInfo().getNome(),nome);
			if(tmp!=num)
				cout <<"Paragem:"<<g.getVertexSet()[i]->getInfo().getNome()<<endl;
			}
			cout <<"Numero de Matches encontrados:"<<num<<endl;
			cin>>ignore;

		}
		MenuStringMatching();
			break;
		case '2':{
			char ignore;
			vector<int>v;
			vector<Paragem>p;
						string nome;
						cin.ignore();
						cin.clear();
						cout << "Nome da Paragem:";
						getline(cin,nome);

						cout <<endl;
						for(unsigned int i=0; i< g.getVertexSet().size();i++){
						p.push_back(g.getVertexSet()[i]->getInfo());
						v.push_back(editDistance(nome,g.getVertexSet()[i]->getInfo().getNome()));
						}
						Ordena(v,p);
						cout <<"Será que quis dizer?"<<endl;
						for(unsigned int i=0;i< v.size();i++){
							cout << p[i].getNome()<<" : "<<v[i]<<endl;
						}
						cout <<"carregue em qualquer tecla";
						cin>>ignore;
		}
		MenuStringMatching();
			break;
		case '3':{
			char ignore;

			vector <int>v;
						string nome,linha;
						cin.ignore();
						cin.clear();
						cout << "Nome da Paragem:";
						getline(cin,nome);
						cout << "Nome da Linha:";
						getline(cin,linha);

						int num=0;

						bool fer=true;
						for(unsigned int i=0; i< g.getVertexSet().size();i++){
							num=0;
						num+=kmp(g.getVertexSet()[i]->getInfo().getNome(),nome);
						for(unsigned int j=0;j<g.getVertexSet()[i]->getAdj().size();j++){

						if(0<num)
						{

						v.push_back(i);
							if(0 < kmp(g.getVertexSet()[i]->getAdj()[j].getTransporte().getLinha(),linha)){
							cout <<"Encontrou se um match para essa linha e essa paragem"<<endl;
							cout <<"Paragem:"<<g.getVertexSet()[i]->getInfo().getNome()<<";Linha:"<<g.getVertexSet()[i]->getAdj()[j].getTransporte().getLinha()<<endl;
							fer=false;
							}
						}
						}
						}
						if(fer){
							if(v.size()==0)
								cout <<"Não existe essa paragem"<<endl;
							else{
							cout <<"Não existe nenhuma linha assim a passar por esta paragem"<<endl;
							for(unsigned int u=0; u <v.size();u++)
							for(unsigned int b=0; b< g.getVertexSet()[v[u]]->getAdj().size();b++)
							cout <<"Linhas que passam por "<<g.getVertexSet()[v[u]]->getInfo().getNome()<<":"<<g.getVertexSet()[v[u]]->getAdj()[b].getTransporte().getLinha()<<endl;
						}
						}
						cin>>ignore;


		}
		MenuStringMatching();
		break;
		case '4':{
			char ignore;
			vector<int>v;
			vector<string>s;
			string nome;
			cin.ignore();
			cin.clear();
			cout << "Nome da Linha:";
			getline(cin,nome);
			cout <<endl;
			for(unsigned int i=0; i< g.getVertexSet().size();i++){
			for(unsigned int k=0;k<g.getVertexSet()[i]->getAdj().size();k++){
				if(-1==exists(s,g.getVertexSet()[i]->getAdj()[k].getTransporte().getLinha())){
			s.push_back(g.getVertexSet()[i]->getAdj()[k].getTransporte().getLinha());
			v.push_back(editDistance(nome,g.getVertexSet()[i]->getAdj()[k].getTransporte().getLinha()));
				}
			}
			}
			Ordena(v,s);
			cout << "A linha mais proxima que foi escolhida foi esta:"<<s[0]<<endl;
			nome=s[0];
			cout<<endl;
			for(unsigned int i=0; i< s.size();i++){
				cout <<s[i]<<":"<<v[i]<<endl;
			}
			cin>>ignore;
			vector<Paragem>p;
			//vector<Edge<Paragem>>e;
			vector<pair<int,int> >key;

			for(unsigned int i=0; i< g.getVertexSet().size();i++){
						for(unsigned int k=0;k<g.getVertexSet()[i]->getAdj().size();k++){
						if(g.getVertexSet()[i]->getAdj()[k].getTransporte().getLinha()==nome){
							if(-1==exists(p,g.getVertexSet()[i]->getInfo())){
							p.push_back(g.getVertexSet()[i]->getInfo());
							}
							if(-1==exists(p,g.getVertexSet()[i]->getAdj()[k].getDest()->getInfo())){
								p.push_back(g.getVertexSet()[i]->getAdj()[k].getDest()->getInfo());
							}
							key.push_back(make_pair(exists(p,g.getVertexSet()[i]->getInfo()),exists(p,g.getVertexSet()[i]->getAdj()[k].getDest()->getInfo())));
						}



						}
			}

			cout<<"Linha       "<<nome<<":"<<endl;
			for(unsigned int i=0; i< p.size();i++){
				if(i==p.size()-1)
					cout<<p[i].getNome()<<endl;
				else
				cout<<p[i].getNome()<<",";
			}
			cout <<endl;
			cin>>ignore;

			GraphViewer *gv = new GraphViewer(600, 600, false);
				gv->createWindow(600,600);

				for(unsigned int i=0;i < p.size();i++){
				Sleep(2000);
				gv->addNode(i,p[i].getX(),p[i].getY());
				gv->setVertexLabel(i,p[i].getNome());
				gv->rearrange();
			}

				for(unsigned int l=0;l<key.size();l++){
							Sleep(2000);

							gv->addEdge(l,key[l].first,key[l].second,EdgeType::DIRECTED);
							cout <<key[l].first<<";"<<key[l].second<<endl;
							gv->setEdgeLabel(l,nome);
							gv->rearrange();


						}

		}
		MenuStringMatching();
		break;

		case '5':
			MenuInicial();
			break;

		}


}

void MenuPesquisas(){
	cout <<"----- Menu Pesquisas----"<<endl;
	cout <<"                        "<<endl;
	cout << "1. Percurso mais rápido(bellman)"<<endl;
	cout << "2. Percurso Mais barato(dijkstra)"<<endl;
	cout << "3. Percurso com menor numero de paragens"<<endl;
	cout << "outro qualquer retornará ao menu anterior"<<endl;
	char opcao;
	string nome;
	int x,y;
	cout <<"Opção: ";
	cin >>opcao;
	switch(opcao){
	case '1':{
		cin.ignore();
		cin.clear();
		cout <<"Onde se encontra:";
		getline(cin,nome);

cout <<"Coordenada x:";
cin >> x;
cout <<"Coordenada y:";
cin >> y;
for(unsigned int i=0; i< g.getVertexSet().size();i++){
						cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
					}
cout <<"Para onde deseja ir:";
					unsigned int k;
					cin >>k;
					k--;
					bool fer=false;
Paragem p(nome,x,y);
if(g.addVertex(p)){
fer=true;
for(unsigned int i=0; i<g.getVertexSet().size();i++){
	g.addEdge(p,g.getVertexSet()[i]->getInfo(),Caminhar("Pé",0,sqrt(pow(g.getVertexSet()[i]->getInfo().getX()-x,2)+pow(g.getVertexSet()[i]->getInfo().getY()-y,2))));
}
}

		g.bellmanFordShortestPath(p);
		vector <Paragem>v=g.getPath(p,g.getVertexSet()[k]->getInfo());
		for(unsigned int i = 0; i < v.size(); i++) {
			if(i==v.size()-1)
				cout <<v[i].getNome()<<endl;
			else
				cout << v[i].getNome() <<"->";
			}
		if(fer)g.removeVertex(p);
	}
MenuPesquisas();
break;
	case '2':{
		cin.ignore();
		cin.clear();
	cout <<"Onde se encontra:";
	getline(cin,nome);

cout <<"Coordenada x:";
cin >> x;
cout <<"Coordenada y:";
cin >> y;
for(unsigned int i=0; i< g.getVertexSet().size();i++){
					cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
				}
cout <<"Para onde deseja ir:";
				unsigned int k;
				cin >>k;
k--;
bool fer=false;
Paragem p(nome,x,y);
if(g.addVertex(p)){
fer=true;
for(unsigned int i=0; i<g.getVertexSet().size();i++){
g.addEdge(p,g.getVertexSet()[i]->getInfo(),Caminhar("Pé",0,sqrt(pow(g.getVertexSet()[i]->getInfo().getX()-x,2)+pow(g.getVertexSet()[i]->getInfo().getY()-y,2))));
}
}

		g.dijkstraShortestPath(p);
		vector <Paragem>v=g.getPath(p,g.getVertexSet()[k]->getInfo());
				for(unsigned int i = 0; i < v.size(); i++) {
					if(i==v.size()-1)
						cout <<v[i].getNome()<<endl;
					else
						cout << v[i].getNome() <<"->";
					}

				if(fer)g.removeVertex(p);

	}
	MenuPesquisas();
		break;
	case '3':{
		cin.ignore();
		cin.clear();
	cout <<"Onde se encontra:";
	getline(cin,nome);

cout <<"Coordenada x:";
cin >> x;
cout <<"Coordenada y:";
cin >> y;
for(unsigned int i=0; i< g.getVertexSet().size();i++){
					cout << i+1 << ") "<< g.getVertexSet()[i]->getInfo().getNome()<<endl;
				}
cout <<"Para onde deseja ir:";
				unsigned int k;
				cin >>k;
k--;
bool fer=false;
Paragem p(nome,x,y);
if(g.addVertex(p)){
fer=true;
for(unsigned int i=0; i<g.getVertexSet().size();i++){
g.addEdge(p,g.getVertexSet()[i]->getInfo(),Caminhar("Pé",0,sqrt(pow(g.getVertexSet()[i]->getInfo().getX()-x,2)+pow(g.getVertexSet()[i]->getInfo().getY()-y,2))));
}
}

		g.unweightedShortestPath(p);
		vector <Paragem>v=g.getPath(p,g.getVertexSet()[k]->getInfo());
				for(unsigned int i = 0; i < v.size(); i++) {
					if(i==v.size()-1)
						cout <<v[i].getNome()<<endl;
					else
						cout << v[i].getNome() <<"->";
					}

				if(fer)g.removeVertex(p);

	}
	MenuPesquisas();
		break;
default:
	MenuInicial();



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
		cout <<"Tempo da viagem em minutos:";
		int tempo;
		int custo;
		string linha;
		int opcao2;
		cin >>tempo;
		cout << "Custo da viagem(euros):";
		cin >>custo;
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
			m= Metro (linha,custo,tempo);
		}
		break;
		case 2: {m=Comboio (linha,custo,tempo);}break;
		case 3:{m= Autocarro (linha,custo,tempo);}break;
		case 4: {m= Caminhar (linha,custo,tempo);}break;
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
