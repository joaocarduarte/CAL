#include <iostream>
using namespace std;


class Transportes
{
protected:
	string linha;
	int dinheiro;

	int tempo;
	string nome;
public:
	Transportes(){};
	Transportes(string linha, int dinheiro, int tempo,string nome);
	string getLinha() const;
	int getDinheiro() const;
	int getDistancia() const;
	int getTempo() const;
	void setDinheiro(int dinheiro);
	void setTempo(int time);
	string getNome()const;
};

class Comboio: public Transportes
{
public:
	Comboio(string linha, int dinheiro,  int tempo);

};

class Metro: public Transportes
{
public:
	Metro(string linha, int dinheiro, int tempo);

};

class Autocarro: public Transportes
{
public:
	Autocarro(string linha, int dinheiro, int tempo);

};
class Caminhar: public Transportes
{
public:
	Caminhar(string linha, int dinheiro, int tempo);

};
