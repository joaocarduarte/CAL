/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_
#include "classes.h"
#include <vector>
#include <queue>


template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	void addEdge(Vertex<T> *dest, Transportes t);
	bool removeEdgeTo(Vertex<T> *d);
	void resetIndegree(){
		indegree=0;
	}
	int indegree;
public:
	Vertex(T in);
	friend class Graph<T>;
	int getIndegree()const;
	void addIndegree();
	void removeIndegree();
	vector<Edge<T> > getAdj() const{
		return adj;
	}
	T getInfo() const;
};
template<class T>
void Vertex<T>::addIndegree(){
	indegree++;
}
template<class T>
void Vertex<T>::removeIndegree(){
	indegree--;
}
template <class T>
int Vertex<T>::getIndegree()const{
	return indegree;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			d->removeIndegree();
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false){
	indegree=0;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, Transportes t ){
	Edge<T> edgeD(dest,t);
	adj.push_back(edgeD);
	dest->addIndegree();
}

template <class T>
class Edge {
	Vertex<T> * dest;

	Transportes t;
public:
	Edge(Vertex<T> *d,Transportes t);
	friend class Graph<T>;
	Vertex<T>* getDest()const {
		return dest;
	}
	Transportes getTransporte()const{
		return t;
	}
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d,Transportes t): dest(d),t(t){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, Transportes t);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet();
	int getNumVertex() const;
	vector<Vertex<T>*> getSources() const;
	void resetIndegrees();
	bool isDAG();
	void auxdfs(Vertex<T> *v,vector<T> &res,bool &cycle);
	int findadjonVertex(Vertex<T>* in);
	int NumArestas(){
		int num=0;
		for(unsigned int i=0; i<vertexSet.size();i++)
			num +=vertexSet[i]->adj.size();
		return num;
	};


};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}

			typename vector<Edge<T> >::iterator itAdj= v->adj.begin();
			typename vector<Edge<T> >::iterator itAdje= v->adj.end();
			for (; itAdj!=itAdje; itAdj++) {
				itAdj->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, Transportes t) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,t);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
			{ vS=*it; found++;}
		if ( (*it)->info == dest )
			{ vD=*it;
			//vD->removeIndegree();
			found++;}
		it ++;
	}
	if (found!=2) return false;
	return vS->removeEdgeTo(vD);
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
	    if ( (*it)->visited==false )
	    	dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
	    if ( it->dest->visited == false )
	    	dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}
template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const{
	vector<Vertex<T>*> v;
for(unsigned int i=0; i< vertexSet.size();i++){
	if(vertexSet[i]->getIndegree()==0)
		v.push_back(vertexSet[i]);

}
return v;
}

template<class T>
void Graph<T>::resetIndegrees() {
	for(unsigned int i=0; i< vertexSet.size();i++)
	{
		vertexSet[i].resetIndegree();
	}
}

template <class T>
void Graph<T>::auxdfs(Vertex<T> *v,vector<T> &res,bool &cycle) {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++){
		if(it->dest->visited==true)
			    	cycle=false;
	    if ( it->dest->visited == false )
	    	auxdfs(it->dest, res,cycle);

	}
}
template<class T>
bool Graph<T>::isDAG() {
vector<T> v;
bool cycle=true;
for(unsigned int i=0;i< vertexSet.size();i++){
auxdfs(vertexSet[i],v,cycle);
}

	return cycle;
}
template<class T>
int Graph<T>::findadjonVertex(Vertex<T>* in){

	for(unsigned int i=0;i< vertexSet.size();i++){
		if(in->getInfo()==vertexSet[i]->getInfo())
			return i;
	}
	return -1;
}
#endif /* GRAPH_H_ */