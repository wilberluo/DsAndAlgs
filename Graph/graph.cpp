#include <iostream>
#include <list>
#include "graph.h"

Edge::Edge() :vertex(-1), weight(-1) {}

Edge::Edge(int v, int wgt) : vertex(v), weight(wgt) {}

Graph::Graph(int num) {
	int i;
	numVertex = num;
	numEdge = 0;
	vertex = new std::list<Edge>*[numVertex];
	for (i = 0; i < numVertex; i++)
		vertex[i] = new std::list<Edge>();
}

Graph::~Graph() {
	for (int i = 0; i < numVertex; i++)
		delete vertex[i];
	delete[] vertex;
}

int Graph::n() {
	return numVertex;
}

int Graph::e() {
	return numEdge;
}

void Graph::setEdge(int v, int w, int wgt) {
	Edge it(w, wgt);
	auto i = vertex[v]->begin();
	while (i != vertex[v]->end() && i->vertex != w)
		++i;
	if (i == vertex[v]->end())
		numEdge++;
	else
		vertex[v]->erase(i);
	vertex[v]->insert(i, it);
}

void Graph::delEdge(int v, int w) {
	auto i = vertex[v]->begin();
	while (i != vertex[v]->end() && i->vertex != w)
		++i;
	if (i != vertex[v]->end())
		vertex[v]->erase(i);
	else
		return;
}

std::list<Edge> Graph::getEdge(int v)
{
	return *(this->vertex[v]);
}

int Graph::weight(int v, int w) {
	auto i = vertex[v]->begin();
	while (i != vertex[v]->end() && i->vertex != w)
		++i;
	if (i != vertex[v]->end())
		return i->weight;
	else
		return 0;

}

std::ostream &operator<<(std::ostream &os, const Graph &G) {
	for (int i = 0; i < G.numVertex; i++)
	{
		os << i << ":\t";
		for (auto &j : *G.vertex[i])
			os << j.vertex << "\t";
		os << std::endl;
	}
	return os;
}