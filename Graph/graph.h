#pragma once
class Edge
{
public:
	int vertex, weight;
	Edge();
	Edge(int, int);
};

class Graph
{
public:
	Graph(int);
	~Graph();

	int n();
	int e();
	void setEdge(int, int, int);
	void delEdge(int, int);
	std::list<Edge> getEdge(int);
	int weight(int, int);
	friend std::ostream &operator<<(std::ostream &, const Graph &);

private:
	int numVertex, numEdge;
	std::list<Edge>** vertex;
};

std::ostream &operator<<(std::ostream &, const Graph &);
