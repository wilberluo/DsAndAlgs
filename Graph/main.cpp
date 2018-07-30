#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include "graph.h"
#include "graphfunc.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(int argc, char *argv[])
{
	ifstream input;
	int vertex_num=0, edge_nums=0;
	int v, w;
	int i = 0;
	input.open(argv[1], ifstream::in);
	if (input)
		//input >> vertex_num;
		input >> vertex_num >> edge_nums;
	else
	{
		cout << "input error\n";
		return 0;
	}
	Graph G(vertex_num);
	while (input >> v >> w)
	{
		G.setEdge(v, w, 0);
		//G.setEdge(w, v, 0);
		//cout << v << "\t" << w << endl;
	}
	//cout << G;
	//Dfs(G, 9);
	//Bfs(G, 0);
	//BfsPathTo(G, 0, 2);
	//CntCmpnt(G, 0, 7);
	//hasCircle(G);
	hasCircleForDG(G);
	//isBioG(G);
	//cout << G.E() << endl;
	//cout << G.V() << endl;
	//DfsPathTo(G, 2, 6);
	return 0;
}