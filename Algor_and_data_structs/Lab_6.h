#pragma once

class Graph
{
private:
	enum color { WHITE, GRAY, BLACK };
	class Vertex
	{
	public:
		int d = 0;
		int f = 0;
		int number;
		Vertex* parent;
		color colour = WHITE;
		std::vector<Vertex*> adj;
	};
	int** arr;
	int v, e;
	Vertex* vert;
	std::vector<Vertex*> sorted;
public:
	Graph(int v, int e)											//total = 3 + n * 1 + 1 = n
	{
		this->v = v;											//c = 1
		this->e = e;											//c = 1
		arr = new int*[v];										//c = 1
		for (int i = 0; i < v; i++)								//c = n
		{
			arr[i] = new int[v];								//c = 1
		}
		vert = new Vertex[v];									//c = 1
	}

	void input()												//total = n * (n * 1) + n = n ^ 2
	{
		for (int i = 0; i < v; i++)								//c = n
		{
			for (int j = 0; j < v; j++)							//c = n
			{
				std::cin >> arr[i][j];							//c = 1
			}
		}
		init();													//c = n
	}

	void init()													//total = n * 4 = n
	{
		for (int i = 0; i < v; i++)								//c = n
		{
			vert[i].parent = nullptr;							//c = 1
			vert[i].number = i + 1;								//c = 1
			for (int j = 0; j < v; j++)
			{
				if (arr[i][j] != 0)								//c = 1
				{
					vert[i].adj.push_back(&vert[j]);			//c = 1
				}
			}
		}
	}


	int time;													

	void dfs()													//total = n^3
	{
		time = 0;												//c = 1
		for (int i = 0; i < v; i++)								//c = n
		{
			if (vert[i].colour == WHITE)						//c = 1
				dfs_visit(&vert[i]);							//c = n^2
		}
	}

	void dfs_visit(Vertex* u)									//total = n^2
	{
		time++;													//c = 1
		u->d = time;											//c = 1
		u->colour = GRAY;										//c = 1
		for (int i = 0; i < u->adj.size(); i++)					//c = n
		{
			if (u->adj[i]->colour == WHITE)						//c = 1
			{
				u->adj[i]->parent = u;							//c = 1
				dfs_visit(u->adj[i]);							//RECURSION (n)
			}
		}
		u->colour = BLACK;										//c = 1
		time++;													//c = 1
		u->f = time;											//c = 1
		sorted.push_back(u);									//c = 1
	}

	void output()																			//total  =	1 + n * 1 + 1 + n * 1 = n
	{
		std::cout << "Input and output times for all vertices:" << std::endl;				//c = 1
		for (int i = 0; i < v; i++)															//c = n
		{
			std::cout << i << ": " << vert[i].d << ", " << vert[i].f << std::endl;			//c = 1
		}
		std::cout << "Sorted graph: " << std::endl;											//c = 1
		for (int i = 0; i < sorted.size(); i++)												//c = n
			std::cout << sorted[i]->number << " ";											//c = 1
	}
};

void useLab6()																				//total = n^3
{
	std::cout << "Enter V and E: ";															//c = 1
	int v, e;																				//c = 2
	std::cin >> v >> e;																		//c = 2
	Graph gr(v, e);																			//c = n
	std::cout << "Enter matrix: " << std::endl;												//c = 1
	gr.input();																				//c= n^2
	gr.dfs();																				//c = n^3
	gr.output();																			//c = n
	system("pause");																		//c = 1
}