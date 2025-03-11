#define _CRT_SECURE_NO_WARNINGS 1
#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;


void check_wuhan(vector<string>& _vertexs, matrix::graph<string, int>& g2,vector<int>& hop)
{
    g2.BFS("�人", hop);

    cout << endl;

    for (int i = 0; i < 34; ++i)
    {
        //cout << hop[i] << endl;
        if (i != 32 && i != 33 && i != 28 && i != 26 && i != 22 && hop[i] > 3)
        {
            cout << "ȫ������ʡ����У��������۰ĺ���������̨���ͺ��ڣ����人�м䲻���� 2 ��ʡ��ʡ����У�������" << endl;
        }
        else if(i != 32 && i != 33 && i != 28 && i != 26 && i != 22 && hop[i] <= 3)
        {
            cout << _vertexs[i] << "���人���" << hop[i] - 1 << "��ʡ��" << endl;
        }
    }

    cout << "���ϣ�ȫ������ʡ����У��������۰ĺ���������̨���ͺ��ڣ����人�м䲻���� 2 ��ʡ��ʡ����У�����" << endl;
    cout << endl;
}

void shortest_D(vector<string>& _vertexs, matrix::graph<string, int>& g, vector<vector<int>>& vvDist2,vector<vector<int>>& vvParentPath2)
{
    cout << "-----------------------------------------Dijkstra�㷨" << endl;
    for (int i = 0; i < 34; ++i)
    {
        g.Dijkstra(_vertexs[i], vvDist2[i], vvParentPath2[i]);
        g.PrintShortPath(_vertexs[i], vvDist2[i], vvParentPath2[i]);
        cout << endl;
    }
    cout << endl;
}

void shortest_F(vector<string>& _vertexs, matrix::graph<string, int>& g, vector<vector<int>>& vvDist, vector<vector<int>>& vvParentPath)
{
    cout << "-----------------Floyd�㷨----------------------" << endl;
    g.Floyd_Warshall(vvDist, vvParentPath);
    for (size_t i = 0; i < 34; ++i)
    {
        g.PrintShortPath(_vertexs[i], vvDist[i], vvParentPath[i]);
        cout << endl;
    }

    cout << endl;
}


void get_all_path(string& source,string& dest, matrix::graph<string, int>& g, matrix::graph<string, int>& g2)
{
    cout << "--------------------����·��-------------------" << endl;
    cout << "���������·��" << endl;
    cin >> source;
    cout << "�������յ�·��" << endl;
    cin >> dest;

    vector<vector<string>> Path(34);
    vector<int> Dis;
    g2.get_all_paths(source, dest, Path, Dis);
    g.get_all_dis(source, dest, Path, Dis);

    vector<pair<int, int>> pair_Dis;
    for (int i = 0; i < Dis.size(); ++i)
    {
        pair_Dis.push_back({ Dis[i],i });
    }

    sort(pair_Dis.begin(), pair_Dis.end());
    vector<vector<string>> sort_Path(Path);

    for (int i = 0; i < Dis.size(); ++i)
    {
        sort_Path[i] = Path[pair_Dis[i].second];
    }

    for (int i = 0; i < Dis.size(); ++i)
    {
        for (int j = 0; j < sort_Path[i].size(); ++j)
        {
            cout << sort_Path[i][j] << "->";
        }
        cout << "::" << pair_Dis[i].first << endl;
    }


    ofstream outFile(source + "_" + dest + ".txt");//�����в��ظ�·��д���ļ���

    if (!outFile) {
        cerr << "�޷����ļ�" << endl;
        exit(-1);
    }

    for (size_t i = 0; i < pair_Dis.size(); ++i)
    {
        for (size_t j = 0; j < sort_Path[i].size(); ++j)
        {
            outFile << sort_Path[i][j] << "->";
        }
        outFile << "::" << pair_Dis[i].first << endl;
    }

    outFile.close();

    cout << endl;
}


void skip_one(string& source, string& dest,string& city, vector<string>& _vertexs,matrix::graph<string, int>& g)
{
    cout << "------------------------------����ĳ����----------------------------" << endl;
    cout << "������Ҫ�����ĳ���" << endl;


    cin >> city;


    cout << "������������" << endl;
    cin >> source;


    cout << "�������յ����" << endl;
    cin >> dest;

    vector<int> dis;
    vector<int> parentPath;
    g.skip_Dijkstra(city, source, dis, parentPath);

    int desti = g.getindex(dest);
    int srci = g.getindex(source);
    vector<int> path;
    size_t parenti = desti;
    while (parenti != srci)
    {
        path.push_back(parenti);
        parenti = parentPath[parenti];
    }
    path.push_back(srci);
    reverse(path.begin(), path.end());

    for (auto index : path)
    {
        cout << _vertexs[index] << "->";
    }
    cout << dis[desti] << endl;

    cout << endl;
}

int main()
{
    int count = 0;
    
    vector<string> _vertexs;
    vector<vector<int>> _edge(34, vector<int>(34,INT_MAX));
    vector<vector<int>> _edge2(34, vector<int>(34,0));

    for (int i = 0; i < 34; ++i)
    {
        for (int j = 0; j < 34; ++j)
        {
            if (i == j)
            {
                _edge[i][j] = 0;
            }
        }
    }

    ifstream file("ʡ����о������.csv");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        //cout << line << endl;
        stringstream ss(line);
        string cell;
        vector<string> row;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        if (count == 0)
        {
            _vertexs = row;
        }
        // Process the row here
        for (int i = 0;i < row.size();++i)
        {
            //cout << row[i] << " ";
            if (i != 0 && count != 0 && row[i] != "")
            {
                _edge[count - 1][i - 1] = stoi(row[i]);
            }
        }
        count++;
        //cout << endl;
    }

    file.close();
    _vertexs.push_back("����");
    _vertexs.erase(_vertexs.begin());
    //cout << "_______" << endl;
    /*for (auto& e : _vertexs)
    {
        cout << e << endl;
    }*/


   /* for (int i = 0; i < 34; ++i)
    {
        for (int j = 0; j < 34; ++j)
        {
            if (_edge[i][j] == INT_MAX)
            {
                cout << "*" << " ";
            }
            else
                cout << _edge[i][j] << " ";
        }
        cout << endl;
    }*/



    count = 0;
    ifstream file2("ʡ������ڽӾ���.csv");
    if (!file2.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line1;
    while (getline(file2, line1))
    {
        //cout << line << endl;
        stringstream ss(line1);
        string cell;
        vector<string> row;
        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        // Process the row here
        for (int i = 0; i < row.size(); ++i)
        {
            if (i != 0 && count != 0 && row[i] != "0")
            {
                _edge2[count - 1][i - 1] = stoi(row[i]);
            }
        }
        count++;
        //cout << endl;
    }

    file2.close();

    matrix::graph<string, int> g(_vertexs,_edge);//����ͼ
    matrix::graph<string, int> g2(_vertexs, _edge2);//�ڽ�ͼ
    vector<int> hop(34);
    vector<vector<int>> vvDist;
    vector<vector<int>> vvDist2(34);

    vector<vector<int>> vvParentPath;
    vector<vector<int>> vvParentPath2(34);

    string source = "";
    string dest = "";
    string city = "";

    int input = 0;
    while (input != -1)
    {
        cout << "*************************************************************************" << endl;
        cout << "*************************************************************************" << endl;
        cout << "************1����֤ȫ������ʡ����е��人�м䲻����2��ʡ�Ƿ����*********" << endl;
        cout << "************2����ѯ�����м����·����Dijkstra�㷨��**********************" << endl;
        cout << "************3����ѯ�����м����·����Floyd�㷨��*************************" << endl;
        cout << "************4����ѯ���в��ظ��Ŀ���·��**********************************" << endl;
        cout << "************5���ƹ�ĳ���ض��ĳ��������·��******************************" << endl;
        cout << "************-1 �� �˳�  *************************************************" << endl;
        cout << "*************************************************************************" << endl;
        cout << "*************************************************************************" << endl;

       
        cin >> input;

        switch (input)
        {
        case 1:
            check_wuhan(_vertexs, g2, hop);
            break;
        case 2:
            shortest_D(_vertexs, g, vvDist2, vvParentPath2);
            break;
        case 3:
            shortest_F(_vertexs, g, vvDist, vvParentPath);
            break;
        case 4:
            get_all_path(source, dest, g, g2);
            break;
        case 5:
            skip_one(source, dest, city, _vertexs, g);
            break;
        case -1:
            return 0;
        }

    }
    return 0;
}