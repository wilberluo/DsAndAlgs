#pragma once
//深度优先搜索
void Dfs(Graph &g, int v, int *marked);

void Dfs(Graph & G, int v) {
	int *marked = new int[G.n()];
	for (int i = 0; i < G.n(); ++i)
		marked[i] = 0;
	Dfs(G, v, marked);
	delete[] marked;
}

void Dfs(Graph &g, int v, int *marked) {
	std::cout << v << "\t";
	marked[v] = 1;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
			Dfs(g, i.vertex, marked);
}

//深度优先搜索寻找图中s到d的路径，但是深度优先搜索无法解决找到最短路径问题。

void DfsPathTo(Graph &g, int v, int *marked, int *path) {
	marked[v] = 1;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
		{
			path[i.vertex] = v;
			DfsPathTo(g, i.vertex, marked, path);
		}
}

void DfsPathTo(Graph &g, int s, int d)
{
	int *marked = new int[g.n()];
	int *edgeTo = new int[g.n()];

	for (int i = 0; i < g.n(); i++)
		marked[i] = 0;
	DfsPathTo(g, s, marked, edgeTo);
	if (marked[d] == 1)
	{
		for (int i = d; i != s; i = edgeTo[i])
			std::cout << i << "\t";
		std::cout << s;
		std::cout << std::endl;
	}
	else
		std::cout << "NO path from " << s << "to" << d << "!\n" << std::endl;
	delete[] marked;
	delete[] edgeTo;
	return;
}


//广度优先搜索
void Bfs(Graph &g, int v)
{
	int *marked = new int[g.n()];
	for (int i = 0; i < g.n(); ++i)
		marked[i] = 0;
	std::queue<int> dq;
	dq.push(v);
	int tmp;
	while (!dq.empty())
	{
		tmp = dq.front();
		for (auto &i : g.getEdge(tmp))
			if (!marked[i.vertex])
			{
				dq.push(i.vertex);
				marked[i.vertex] = 1;
			}
		std::cout << tmp << "\t";
		marked[tmp] = 1;
		dq.pop();
	}
	delete[] marked;
	return;
}

//广度优先搜索寻找最短路径

void BfsPathTo(Graph &g, int v, int *marked, int *path)
{
	std::queue<int> dq;
	dq.push(v);
	int tmp;
	while (!dq.empty())
	{
		tmp = dq.front();
		for (auto &i : g.getEdge(tmp))
			if (!marked[i.vertex])
			{
				dq.push(i.vertex);
				path[i.vertex] = tmp;
				marked[i.vertex] = 1;
			}
		marked[tmp] = 1;
		dq.pop();
	}
	return;
}

void BfsPathTo(Graph &g, int s, int d)
{
	int *marked = new int[g.n()];
	int *edgeTo = new int[g.n()];

	for (int i = 0; i < g.n(); i++)
		marked[i] = 0;

	BfsPathTo(g, s, marked, edgeTo);
	if (marked[d] == 1)
	{
		for (int i = d; i != s; i = edgeTo[i])
			std::cout << i << "\t";
		std::cout << s;
		std::cout << std::endl;
	}
	else
		std::cout << "NO path from " << s << "to" << d << "!\n" << std::endl;
	delete[] marked;
	delete[] edgeTo;
	return;
}

//判断图的连通性和连通分量
void DfsCC(Graph &g, int v, int *marked, int *id, int count)
{
	marked[v] = 1;
	id[v] = count;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
			DfsCC(g, i.vertex, marked, id, count);
}

void CntCmpnt(Graph &g, int s, int d)
{
	int *marked = new int[g.n()];
	int *id = new int[g.n()];
	int count = 0;

	for (int i = 0; i < g.n(); i++)
		marked[i] = 0;
	for (int i = 0; i < g.n(); i++)
		if (!marked[i])
		{
			DfsCC(g, i, marked, id, count);
			count++;
		}
	std::cout << count << "\tcomponents." << std::endl;
	std::cout << (id[s] == id[d] ? "Yes" : "No") << std::endl;
	delete[] marked;
	delete[] id;
	return;
}


//判断图是否无环:仅适用于无向图
void DfsHasCircle(Graph &g, int v, int w, int *marked, bool *has)
{
	marked[v] = 1;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
			DfsHasCircle(g, i.vertex, v, marked, has);
		else if (i.vertex != w) *has = true;
}

void hasCircle(Graph &g)
{
	int *marked = new int[g.n()];
	bool hasCircle = false;
	for (int i = 0; i < g.n(); ++i)
		marked[i] = 0;
	for (int i = 0; i < g.n(); i++)
		if (!marked[i] && !hasCircle)
			DfsHasCircle(g, i, i, marked, &hasCircle);
	std::cout << (hasCircle ? "Has circle." : "No circle.") << std::endl;
	delete[] marked;
	return;
}

//有向图的有向环判断
void DfsHasCircleDG(Graph &g, int v, bool *marked, bool *onStack, int *edgeTo, bool *flag, std::vector<std::stack<int>> &circle)
{
	marked[v] = true;
	onStack[v] = true;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
		{
			edgeTo[i.vertex] = v;
			DfsHasCircleDG(g, i.vertex, marked, onStack, edgeTo, flag, circle);
		}
		else if (onStack[i.vertex])
		{
			*flag = true;
			std::stack<int> tmp;
			for (int j = v; j != i.vertex; j = edgeTo[j])
				tmp.push(j);
			tmp.push(i.vertex);
			tmp.push(v);
			circle.push_back(tmp);
		}
	onStack[v] = false;
}

void hasCircleForDG(Graph &g)
{
	int *edgeTo = new int[g.n()];
	bool *marked = new bool[g.n()];
	bool *onStack = new bool[g.n()];
	bool flag = false;
	std::vector<std::stack<int>> circle;
	for (int i = 0; i < g.n(); ++i)
	{
		marked[i] = false;
		onStack[i] = false;
	}

	for (int i = 0; i < g.n(); i++)
		if (!marked[i])
			DfsHasCircleDG(g, i, marked, onStack, edgeTo, &flag, circle);
	std::cout << (flag ? "Has circle." : "No circle.") << std::endl;
	if (flag)
		for (auto& i : circle)
		{
			while (!i.empty())
			{
				std::cout << i.top() << "\t";
				i.pop();
			}
			std::cout << std::endl;
		}
	delete[] edgeTo;
	delete[] marked;
	delete[] onStack;
}


//判断是否二分图
void DfsBioG(Graph &g, int v, int *marked, bool *color, bool *has)
{
	marked[v] = 1;
	for (auto &i : g.getEdge(v))
		if (!marked[i.vertex])
		{
			color[i.vertex] = !color[v];
			DfsBioG(g, i.vertex, marked, color, has);
		}
		else if (color[i.vertex] == color[v]) *has = false;
}

void isBioG(Graph &g)
{
	int *marked = new int[g.n()];
	bool *color = new bool[g.n()];
	bool flag = true;
	for (int i = 0; i < g.n(); ++i)
	{
		color[i] = false;
		marked[i] = 0;
	}
	for (int i = 0; i < g.n(); i++)
		if (!marked[i] && flag)
			DfsBioG(g, i, marked, color, &flag);
	std::cout << (flag ? "Bio-graph." : "Not Bia-graph.") << std::endl;
	delete[] marked;
	delete[] color;
	return;
}
