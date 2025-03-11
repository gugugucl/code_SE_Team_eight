#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
#include "UnionFindSet.h"
#include <set>
#include <stack>

using namespace std;

namespace matrix
{
	template<class V,class W>
	struct Edge
	{
		int _srci;
		int _dsti;
		W _w;
		Edge(int srci, int dsti, W weight)
			:_srci(srci)
			, _dsti(dsti)
			, _w(weight)
		{}

		bool operator>(const Edge<V, W>& edge) const
		{
			return _w > edge._w;
		}
	};


	template<class V,class W,W MAX_W = INT_MAX,bool DIRECTION = false>
	class graph
	{
		typedef graph<V, W, INT_MAX, DIRECTION> Self;
		typedef Edge<V, W> Edge;
	private:
		vector<V> _vertexs;
		map<V, int> _indexMap;
		vector<vector<W>> _weights;

	public:
		graph() = default;
		graph(vector<V>& vertexs, vector<vector<W>>& edge)
		{
			_vertexs = vertexs;
			for (int i = 0; i < vertexs.size(); ++i)
			{
				_indexMap[vertexs[i]] = i;
			}
			_weights = edge;

			for (int i = 0; i < 34; ++i)
			{
				for (int j = 0; j < 34; ++j)
				{
					_weights[i][j] = min(_weights[i][j], _weights[j][i]);
				}
			}
		}

		graph(const V* v, size_t n)
		{
			_vertexs.resize(n);
			_weights.resize(n);
			for (int i = 0; i < n; ++i)
			{
				_vertexs[i] = v[i];
				_indexMap[v[i]] = i;
				_weights[i].resize(n, MAX_W);
			}
		}

		graph(vector<string>& v, size_t n)
		{
			_vertexs.resize(n);
			_weights.resize(n);

			for (int i = 0; i < n; ++i)
			{
				_vertexs[i] = v[i];
				_indexMap[v[i]] = i;
				_weights[i].resize(n, MAX_W);
			}
		}
		int getindex(const V& v)
		{
			auto it = _indexMap.find(v);

			if (it == _indexMap.end())
			{
				throw invalid_argument("该顶点不存在");
				return -1;
			}

			return it->second;
		}

		void AddEdge(const V& src,const V& dst,W w)
		{
			int srci = getindex(src);
			int dsti = getindex(dst);

			_weights[srci][dsti] = w;

			if (DIRECTION == false)
			{
				_weights[dsti][srci] = w;
			}
		}


		void Print()
		{
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << ":" << _indexMap[_vertexs[i]] << endl;
			}

			cout << endl;

			cout << "  ";
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << " ";
			}

			cout << endl;
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << " ";
				for (int j = 0; j < _weights[i].size(); ++j)
				{
					if (_weights[i][j] == MAX_W)
					{
						cout << "*" << " ";
					}
					else cout << _weights[i][j] << " ";
				}
				cout << endl;
			}
		}

		void _DFS(const V& src, vector<bool>& visited)
		{
			int srci = getindex(src);
			cout << _vertexs[srci] << endl;
			visited[srci] = true;
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				if (_weights[srci][i] != MAX_W && visited[i] == false)
				{
					_DFS(_vertexs[i], visited);
				}
			}
		}

		void DFS(const V& src)
		{
			vector<bool> visited(_vertexs.size(), false);
			_DFS(src, visited);
			for (int i = 0; i < visited.size(); ++i)//防止有孤岛遗漏
			{
				if (visited[i] == false)
				{
					_DFS(_vertexs[i], visited);
				}
			}
		}

		void _BFS(const V& src,vector<bool>& visited,vector<int>& hop)
		{
			int srci = getindex(src);
			queue<int> q;
			int level = 0;
			int levelSize = 1;
			q.push(srci);

			while (!q.empty())
			{
				while (levelSize--)
				{
					int front = q.front();
					//hop[front] = level;
					q.pop();

					if (visited[front] == false)
					{
						cout << _vertexs[front] << endl;
						hop[front] = level;
					}
					visited[front] = true;

					for (int i = 0; i < _vertexs.size(); ++i)
					{
						if (_weights[front][i] != 0 && visited[i] == false)
						{
							q.push(i);
						}
					}

					if (levelSize == 0)
					{
						levelSize = q.size();
						level++;
					}
				}
			}

			//再次遍历，防止孤岛节点
		}

		void BFS(const V& src,vector<int>& hop)
		{
			int n = _vertexs.size();
			vector<bool> visited(n,false);
			_BFS(src, visited,hop);

			for (int i = 0; i < n; ++i)
			{
				if (visited[i] == false)
				{
					_BFS(_vertexs[i], visited,hop);
				}
			}
		}

		W Kruskal(Self& g)
		{
			g._vertexs = _vertexs;
			g._indexMap = _indexMap;

			g._weights.resize(_vertexs.size());
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				(g._weights[i]).resize(_vertexs.size(), MAX_W);
			}

			W total = 0;
			int EdgeSize = 0;

			priority_queue<Edge, vector<Edge>, greater<Edge>> pq;//建小堆
			UFT::UnionFindSet uft(_vertexs.size());
			for (int i = 0; i < _weights.size(); ++i)//把所有的边全部进入小堆
			{
				for (int j = 0; j < _weights[i].size(); ++j)
				{
					if (i < j && _weights[i][j] != MAX_W)
					{
						pq.push(Edge(i, j, _weights[i][j]));
					}
				}
			}


			while (!pq.empty())
			{
				Edge front = pq.top();
				pq.pop();

				bool ret = uft.IsSameSet(front._srci, front._dsti);

				if (ret == false)
				{
					g.AddEdge(_vertexs[front._srci], _vertexs[front._dsti], front._w);
					uft.Union(front._srci, front._dsti);//构造边之后，并查集也要合并集合
					cout << _vertexs[front._srci] << "->" << _vertexs[front._dsti] << endl;
					total += front._w;
					EdgeSize++;
				}
			}

			if (EdgeSize == _vertexs.size() - 1)
				return total;

			return W();
		}

		W Prim(Self& g, const V& src)
		{
			g._vertexs = _vertexs;
			g._indexMap = _indexMap;

			g._weights.resize(_vertexs.size());
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				(g._weights[i]).resize(_vertexs.size(), MAX_W);
			}

			W total = 0;
			int EdgeSize = 0;

			set<int> x;

			int srci = getindex(src);
			x.insert(srci);

			priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

			for (int i = 0; i < _vertexs.size(); ++i)
			{
				if (x.count(i) == 0 && _weights[srci][i] != MAX_W)
					pq.push(Edge(srci, i, _weights[srci][i]));
			}

			while (!pq.empty())
			{
				Edge front = pq.top();
				pq.pop();
				if (x.count(front._dsti) == 0)
				{
					g.AddEdge(_vertexs[front._srci], _vertexs[front._dsti], front._w);
					cout << _vertexs[front._srci] << "->" << _vertexs[front._dsti] << endl;
					total += front._w;
					EdgeSize++;
					x.insert(front._dsti);

					for (int i = 0; i < _vertexs.size(); ++i)
					{
						if (x.count(i) == 0 && _weights[front._dsti][i] != MAX_W)
						{
							pq.push(Edge(front._dsti, i, _weights[front._dsti][i]));
						}
					}
				}
			}

			if (EdgeSize == _vertexs.size() - 1)
				return total;

			return W();
		}

		void PrintShortPath(const V& src, const vector<W>& dist, const vector<int>& pPath)
		{
			size_t srci = getindex(src);
			size_t n = _vertexs.size();
			for (size_t i = 0; i < n; ++i)
			{
				if (i != srci)
				{
					// 找出i顶点的路径
					vector<int> path;
					size_t parenti = i;
					while (parenti != srci)
					{
						path.push_back(parenti);
						parenti = pPath[parenti];
					}
					path.push_back(srci);
					reverse(path.begin(), path.end());
				
					for (auto index : path)
					{
						cout << _vertexs[index] << "->";
					}
					cout << dist[i] << endl;
				}
			}
		}

		void Dijkstra(const V& src, vector<W>& dis, vector<int>& parentpath)
		{
			int srci = getindex(src);
			int  n = _vertexs.size();
			dis.resize(n, MAX_W);
			parentpath.resize(n, -1);

			set<int> x;
			dis[srci] = W();
			parentpath[srci] = srci;

			for (int j = 0; j < n; ++j)
			{
				int min = MAX_W;
				int minindex = -1;
				for (int i = 0; i < n; ++i)
				{
					if (dis[i] < min && x.count(i) == 0)
					{
						min = dis[i];
						minindex = i;
					}
				}

				for (int i = 0; i < n; ++i)
				{
					if (_weights[minindex][i] != MAX_W && dis[minindex] + _weights[minindex][i] < dis[i] && x.count(i) == 0)
					{
						dis[i] = dis[minindex] + _weights[minindex][i];
						parentpath[i] = minindex;
					}
				}
				x.insert(minindex);

			}
		}

		void Dijkstra2(const V& src, vector<W>& dis, vector<int>& parentpath)
		{
			int srci = getindex(src);
			int  n = _vertexs.size();
			dis.resize(n, MAX_W);
			parentpath.resize(n, -1);

			set<int> x;
			dis[srci] = W();
			parentpath[srci] = srci;

			for (int j = 0; j < n; ++j)
			{
				if (j != 22)
				{
					int min = MAX_W;
					int minindex = -1;
					for (int i = 0; i < n; ++i)
					{
						if (dis[i] < min && x.count(i) == 0)
						{
							min = dis[i];
							minindex = i;
						}
					}

					for (int i = 0; i < n; ++i)
					{
						if (_weights[minindex][i] != MAX_W && dis[minindex] + _weights[minindex][i] < dis[i] && x.count(i) == 0)
						{
							dis[i] = dis[minindex] + _weights[minindex][i];
							parentpath[i] = minindex;
						}
					}
					x.insert(minindex);
				}
			}
		}

		void skip_Dijkstra(const V& skip, const V& src, vector<W>& dis, vector<int>& parentpath)
		{
			int skipi = getindex(skip);
			vector<int> tmp_row = _weights[skipi];
			vector<int> tmp_col(34);
			for (int i = 0; i < 34; ++i)
			{
				tmp_col[i] = _weights[i][skipi];
			}

			for (int i = 0; i < 34; ++i)
			{
				for (int j = 0; j < 34; ++j)
				{
					if (i == skipi || j == skipi)
					{
						_weights[i][j] = INT_MAX;
					}
				}
			}


			//求最短路
			Dijkstra2(src, dis, parentpath);


			//复原
			_weights[skipi] = tmp_row;

			for (int i = 0; i < 34; ++i)
			{
				_weights[i][skipi] = tmp_col[i];
			}
		}


		bool Bellman_Ford(const V& src, vector<W>& dis, vector<int>& parentpath)
		{
			int srci = getindex(src);
			int  n = _vertexs.size();
			dis.resize(n, MAX_W);
			parentpath.resize(n, -1);

			dis[srci] = W();
			parentpath[srci] = srci;

			for (int i = 0; i < n; ++i)//将与起点相连的边全部提前更新一下
			{
				if (_weights[srci][i] != MAX_W)
				{
					dis[i] = _weights[srci][i];
					parentpath[i] = srci;
				}
			}

			for (int k = 0; k < n; ++k)
			{
				int flag = 0;//标志
				for (int i = 0; i < n; ++i)
				{
					for (int j = 0; j < n; ++j)
					{
						if (_weights[i][j] != MAX_W && dis[i] + _weights[i][j] < dis[j])
						{
							dis[j] = dis[i] + _weights[i][j];
							parentpath[j] = i;
							flag = 1;
						}
					}
				}
				if (flag == 0)
					break;
			}

			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					if (_weights[i][j] != MAX_W && dis[i] + _weights[i][j] < dis[j])
					{
						return false;
					}
				}
			}

			return true;
		}


		void Floyd_Warshall(vector<vector<W>>& vvdis, vector<vector<int>>& vvparentpath)
		{
			int n = _vertexs.size();
			vvdis.resize(n);
			vvparentpath.resize(n);

			for (int i = 0; i < n; ++i)
			{
				vvdis[i].resize(n, MAX_W);
				vvparentpath[i].resize(n, -1);
			}

			for (int i = 0; i < n; ++i)//初始化
			{
				for (int j = 0; j < n; ++j)
				{
					if (_weights[i][j] != MAX_W)
					{
						if (i == j)
						{
							vvdis[i][j] = W();
							vvparentpath[i][j] = i;
						}
						else
						{
							vvdis[i][j] = _weights[i][j];
							vvparentpath[i][j] = i;
						}
					}
				}
			}


			for (int k = 0; k < n; ++k)
			{
				for (int i = 0; i < n; ++i)
				{
					for (int j = 0; j < n; ++j)
					{
						//不加上vvdis[i][k] != MAX_W在运算的时候可能会超出int的范围
						if (vvdis[i][k] != MAX_W && vvdis[k][j] != MAX_W && vvdis[i][k] + vvdis[k][j] < vvdis[i][j])
						{
							vvdis[i][j] = vvdis[i][k] + vvdis[k][j];
							vvparentpath[i][j] = vvparentpath[k][j];
						}
					}
				}
			}
		}

		void _dfs(const V& src, const V& dest,vector<bool>& visited,vector<vector<string>>& path, vector<int>& dis,stack<int>& s)
		{
			int srci = getindex(src);
			int desti = getindex(dest);
			
			if (visited[srci] == true)
				return;

			if (srci == desti)
			{
				int k = dis.size();
				if (k >= 34)//问题所在
					return;
				vector<int> index;

				
				while (!s.empty())
				{
					index.push_back(s.top());
					s.pop();
				}

				reverse(index.begin(), index.end());
				
				for (auto& e : index)
				{
					s.push(e);
				}

				if (index.size() > 1)//绷不住
				{
					int count = 0;
					for (int i = 0; i < index.size() - 1; ++i)
					{
						path[k].push_back(_vertexs[index[i]]);
						count += _weights[index[i]][index[i + 1]];
					}

					path[k].push_back(_vertexs[index[index.size() - 1]]);
					path[k].push_back(_vertexs[desti]);
					count += _weights[index[index.size() - 1]][desti];

					dis.push_back(count);
				}

				return;
			}

			if(visited[srci] == false)
			s.push(srci);
			visited[srci] = true;

			if (s.size() == 10)
			{
				visited[s.top()] = false;
				s.pop();
				return;
			}

			for (int i = 0; i < 34; ++i)
			{
				if (_weights[srci][i] == 1 && visited[i] == false)
				{
					_dfs(_vertexs[i], dest, visited, path, dis, s);
				}
			}

			s.pop();
			visited[srci] = false;
		}

		void get_all_paths(const V& src, const V& dest, vector<vector<string>>& path, vector<int>& dis)
		{
			stack<int> s;
			vector<bool> visited(34, false);
			_dfs(src,dest,visited,path,dis,s);
		}
		

		void get_all_dis(const V& src, const V& dest, vector<vector<string>>& path, vector<int>& dis)
		{
			for (int i = 0; i < dis.size(); ++i)
			{
				dis[i] = 0;
				for (int j = 0; j < path[i].size() - 1; ++j)
				{
					int a = getindex(path[i][j]);
					int b = getindex(path[i][j + 1]);
					dis[i] += _weights[a][b];
				}
				int a = getindex(path[i][path[i].size() - 2]);
				int b = getindex(path[i][path[i].size() - 1]);
				dis[i] += _weights[a][b];
			}
		}
	};

	//void TestFloydWarShall()
	//{
	//	const char* str = "12345";
	//	graph<char, int, INT_MAX, true> g(str, strlen(str));
	//	g.AddEdge('1', '2', 3);
	//	g.AddEdge('1', '3', 8);
	//	g.AddEdge('1', '5', -4);
	//	g.AddEdge('2', '4', 1);
	//	g.AddEdge('2', '5', 7);
	//	g.AddEdge('3', '2', 4);
	//	g.AddEdge('4', '1', 2);
	//	g.AddEdge('4', '3', -5);
	//	g.AddEdge('5', '4', 6);
	//	vector<vector<int>> vvDist;
	//	vector<vector<int>> vvParentPath;
	//	g.Floyd_Warshall(vvDist, vvParentPath);

	//	// 打印任意两点之间的最短路径
	//	for (size_t i = 0; i < strlen(str); ++i)
	//	{
	//		g.PrintShortPath(str[i], vvDist[i], vvParentPath[i]);
	//		cout << endl;
	//	}
	//}

	//void TestGraphDijkstra()
	//{
	//	const char* str = "syztx";
	//	graph<char, int, INT_MAX, true> g(str, strlen(str));
	//	g.AddEdge('s', 't', 10);
	//	g.AddEdge('s', 'y', 5);
	//	g.AddEdge('y', 't', 3);
	//	g.AddEdge('y', 'x', 9);
	//	g.AddEdge('y', 'z', 2);
	//	g.AddEdge('z', 's', 7);
	//	g.AddEdge('z', 'x', 6);
	//	g.AddEdge('t', 'y', 2);
	//	g.AddEdge('t', 'x', 1);
	//	g.AddEdge('x', 'z', 4);

	//	vector<int> dist;
	//	vector<int> parentPath;
	//	g.Dijkstra('s', dist, parentPath);
	//	//g.PrintShortPath('s', dist, parentPath);

	//	// 图中带有负权路径时，贪心策略则失效了。
	//	// 测试结果可以看到s->t->y之间的最短路径没更新出来
	//	/*const char* str = "sytx";
	//	graph<char, int, INT_MAX, true> g(str, strlen(str));
	//	g.AddEdge('s', 't', 10);
	//	g.AddEdge('s', 'y', 5);
	//	g.AddEdge('t', 'y', -7);
	//	g.AddEdge('y', 'x', 3);
	//	vector<int> dist;
	//	vector<int> parentPath;
	//	g.Dijkstra('s', dist, parentPath);
	//	g.PrintShortPath('s', dist, parentPath);*/
	//}

	//void TestGraphBellmanFord()
	//{
	//		const char* str = "syztx";
	//		graph<char, int, INT_MAX, true> g(str, strlen(str));
	//		g.AddEdge('s', 't', 6);
	//		g.AddEdge('s', 'y', 7);
	//		g.AddEdge('y', 'z', 9);
	//		g.AddEdge('y', 'x', -3);
	//		g.AddEdge('z', 's', 2);
	//		g.AddEdge('z', 'x', 7);
	//		g.AddEdge('t', 'x', 5);
	//		g.AddEdge('t', 'y', 8);
	//		g.AddEdge('t', 'z', -4);
	//		g.AddEdge('x', 't', -2);
	//		vector<int> dist;
	//		vector<int> parentPath;
	//		g.Bellman_Ford('s', dist, parentPath);
	//		g.PrintShortPath('s', dist, parentPath);

	//	//const char* str = "syztx";
	//	//graph<char, int, INT_MAX, true> g(str, strlen(str));
	//	//g.AddEdge('s', 't', 6);
	//	//g.AddEdge('s', 'y', 7);
	//	//g.AddEdge('y', 'z', 9);
	//	//g.AddEdge('y', 'x', -3);
	//	//g.AddEdge('y', 's', 1); // 新增
	//	//g.AddEdge('z', 's', 2);
	//	//g.AddEdge('z', 'x', 7);
	//	//g.AddEdge('t', 'x', 5);
	//	////g.AddEdge('t', 'y', -8); //更改
	//	//g.AddEdge('t', 'y', -8);

	//	//g.AddEdge('t', 'z', -4);
	//	//g.AddEdge('x', 't', -2);
	//	//vector<int> dist;
	//	//vector<int> parentPath;
	//	//if (g.Bellman_Ford('s', dist, parentPath))
	//	//	g.PrintShortPath('s', dist, parentPath);
	//	//else
	//	//	cout << "带负权回路" << endl;
	//}

	//void TestGraphMinTree()
	//{
	//	const char* str = "abcdefghi";
	//	graph<char, int> g(str, strlen(str));
	//	g.AddEdge('a', 'b', 4);
	//	g.AddEdge('a', 'h', 8);
	//	//g.AddEdge('a', 'h', 9);
	//	g.AddEdge('b', 'c', 8);
	//	g.AddEdge('b', 'h', 11);
	//	g.AddEdge('c', 'i', 2);
	//	g.AddEdge('c', 'f', 4);
	//	g.AddEdge('c', 'd', 7);
	//	g.AddEdge('d', 'f', 14);
	//	g.AddEdge('d', 'e', 9);
	//	g.AddEdge('e', 'f', 10);
	//	g.AddEdge('f', 'g', 2);
	//	g.AddEdge('g', 'h', 1);
	//	g.AddEdge('g', 'i', 6);
	//	g.AddEdge('h', 'i', 7);

	//	/*graph<char, int> kminTree;
	//	cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
	//	kminTree.Print();*/

	//	graph<char, int> pminTree;
	//	cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
	//	pminTree.Print();
	//	cout << endl;

	//	/*for (size_t i = 0; i < strlen(str); ++i)
	//	{
	//		cout << "Prim:" << g.Prim(pminTree, str[i]) << endl;
	//	}*/
	//}

	//void TestBDFS()
	//{
	//	string a[] = { "张三",  "王五","李四", "赵六", "周七" };
	//	graph<string, int> g1(a, sizeof(a) / sizeof(string));
	//	g1.AddEdge("张三", "李四", 100);
	//	g1.AddEdge("张三", "王五", 200);
	//	g1.AddEdge("王五", "赵六", 30);
	//	g1.AddEdge("王五", "周七", 30);
	//	g1.Print();
	//	cout << endl;
	//	g1.BFS("张三");
	//	cout << endl;
	//	//g1.DFS("张三");
	//}

	//void TestGraph1()
	//{
	//	graph<char, int, INT_MAX, true> g("0123", 4);
	//	g.AddEdge('0', '1', 1);
	//	g.AddEdge('0', '3', 4);
	//	g.AddEdge('1', '3', 2);
	//	g.AddEdge('1', '2', 9);
	//	g.AddEdge('2', '3', 8);
	//	g.AddEdge('2', '1', 5);
	//	g.AddEdge('2', '0', 3);
	//	g.AddEdge('3', '2', 6);

	//	g.Print();
	//}


}

namespace table
{
	template<class W>
	struct Edge
	{
		int _dsti;//目标顶点下标
		W _weight;//边的权值
		Edge<W>* _next;//指向下一个节点

		Edge(int i,W weight)
			:_dsti(i)
			,_weight(weight)
			,_next(nullptr)
		{}
	};

	template<class V, class W, bool DIRECTION = false>
	class graph
	{
		typedef Edge<W> Edge;
	private:
		vector<V> _vertexs;
		map<V, int> _indexMap;
		vector<Edge*> _weights;
	public:
		graph(const V* v, size_t n)
		{
			_vertexs.resize(n);
			_weights.resize(n, nullptr);
			for (int i = 0; i < n; ++i)
			{
				_vertexs[i] = v[i];
				_indexMap[_vertexs[i]] = i;
			}
		}

		int getindex(const V& v)
		{
			auto it = _indexMap.find(v);

			if (it == _indexMap.end())
			{
				throw invalid_argument("该顶点不存在");
				return -1;
			}

			return it->second;
		}

		void AddEdge(const V& src, const V& dst, W w)
		{
			int srci = getindex(src);
			int dsti = getindex(dst);

			Edge* newedge = new Edge(dsti, w);
			newedge->_next = _weights[srci];
			_weights[srci] = newedge;

			if (DIRECTION == false)
			{
				Edge* newedge2 = new Edge(srci, w);
				newedge2->_next = _weights[dsti];
				_weights[dsti] = newedge2;
			}
		}

		void Print()
		{
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << ":" << i << endl;
			}

			cout << endl;
			/*cout << "  ";
			for (int i = 0; i < _vertexs.size(); ++i)
			{
				cout << _vertexs[i] << " ";
			}
			cout << endl;*/

			for (int i = 0; i < _weights.size(); ++i)
			{
				cout << _vertexs[i] << "->";
				Edge* cur = _weights[i];

				while (cur)
				{
					cout << "[" << _vertexs[cur->_dsti] << ":" << cur->_weight << "]->";
					cur = cur->_next;
				}
				cout << "nullptr" << endl;
			}
		}
	};

	void TestGraph1()
	{
		graph<char, int, true> g("0123", 4);
		g.AddEdge('0', '1', 1);
		g.AddEdge('0', '3', 4);
		g.AddEdge('1', '3', 2);
		g.AddEdge('1', '2', 9);
		g.AddEdge('2', '3', 8);
		g.AddEdge('2', '1', 5);
		g.AddEdge('2', '0', 3);
		g.AddEdge('3', '2', 6);

		g.Print();

		/*string a[] = { "张三", "李四", "王五", "赵六" };
		graph<string, int, true> g1(a, 4);
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
		g1.Print();*/
	}


}