#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

namespace UFT
{
	class UnionFindSet
	{
	private:
		vector<int> _uft;
	public:
		UnionFindSet(size_t n)
		{
			_uft.resize(n, -1);
		}

		int FindRoot(int i)
		{
			int root = i;

			while (_uft[root] >= 0)//找根要找到负数，所以需要>=0，而不仅仅是>0
			{
				root = _uft[root];
			}

			while (_uft[i] >= 0)//路劲压缩
			{
				int parent = _uft[i];
				_uft[i] = root;
				_uft[root]--;
				i = parent;
			}

			return root;
		}

		void Union(int src, int dst)
		{
			int root1 = FindRoot(src);
			int root2 = FindRoot(dst);

			if (root1 == root2)//在一个集合就不用合并
				return;

			if (root1 > root2)//少的加到更多的上去
				swap(root1, root2);

			_uft[root1] += _uft[root2];
			_uft[root2] = root1;
		}

		bool IsSameSet(int a, int b)
		{
			return FindRoot(a) == FindRoot(b);
		}

		int SetSize()//一共有多少个集合
		{
			int total = 0;
			for (auto& e : _uft)
			{
				if (e < 0)
					total++;
			}

			return total;
		}
	};


}