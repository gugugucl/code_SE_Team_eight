#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>
#include <cstdlib>
#include<unordered_set>
#include<random>
#include<set>
using namespace std;
using namespace std::chrono;

class Point {
public:
	double x, y;
    Point() = default;
    Point(double xx, double yy) :x(xx), y(yy) {};
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

// ���������ŷ����þ���
double distance(const Point& p1, const Point& p2) {
	return   sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmpx(Point &p1, Point& p2)  //x����
{
    return p1.x < p2.x;
}
bool cmpy(Point& p1, Point& p2)  //y����
{
    return p1.y < p2.y;
}

pair<Point, Point> blf(vector<Point>& points,int low,int high) {

    double minDist = numeric_limits<double>::max();//�����͵�max
    pair<Point, Point> closestPair;
    for (int i = low; i <=high; i++) //���������Ƚ� O(n2)
    {
        for (int j = i + 1; j <=high; j++)
        {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                closestPair = { points[i], points[j] };
            }
        }
    }
    return closestPair;
}

pair<Point, Point> getclosepair(vector<Point>& points, int low, int high)
{
    if (high - low <= 3)return blf(points,low,high);
    int mid = low + (high - low) / 2;
    double xm = points[mid].x;
    pair<Point, Point>leftpair = getclosepair(points, low, mid);
    pair<Point, Point>rightpair = getclosepair(points, mid, high);
    double lmind = distance(leftpair.first, leftpair.second);
    double rmind = distance(rightpair.first, rightpair.second);
    double mind = lmind < rmind ? lmind : rmind;  //�ҵ�������̵�Ծ���.
    pair<Point, Point>closepair;
    if (mind == lmind)closepair = leftpair;
    else closepair = rightpair;
    //�Ƚ�mind �Ϳ����ҵ�min
    vector<Point>p1p2;
    for (int i = mid; i >= low && points[i].x > xm - mind; i--)//���м俪ʼ�� �����Ͼͽ���
        p1p2.push_back(points[i]);
    for(int i=mid+1;i<=high&& points[i].x < xm + mind;i++)
        p1p2.push_back(points[i]);
    sort(p1p2.begin(),p1p2.end(), cmpy);//��y��������
    double d;//curmind
    for (int i = 0; i < p1p2.size(); i++)
    {
     for (int j = i + 1; j < p1p2.size()&&    (p1p2[j].y - p1p2[i].y) < mind ;j++)//���κϲ�ʱ��ÿ�������ֻ������� 7 ���� �Ƚϡ�
        {
            d = distance(p1p2[i], p1p2[j]);
            if (d < mind)
            {  mind = d;//��С�͸���mind
                closepair = { p1p2[i], p1p2[j] };
            //     cout <<closepair.first.x<<" "<<closepair.first.y<<" "<<closepair.second.x<<" "<<closepair.second.y
            //       cout  << distance(closepair.first, closepair.second) << endl;
            }
        }
    }
    return closepair;
}

// ���������
vector<Point> generateRandomPoints(int N) {
    vector<Point> points;
    for (int i = 0; i < N; i++) {
        Point p((rand() / (double)RAND_MAX) * 10000+i, (rand() / (double)RAND_MAX) * 10000);
        points.push_back(p);
    }
    return points;
}
std::vector<Point> random_generate(int n) {
    std::set<Point> uniquePoints; // ʹ�� set ֱ�Ӵ洢 Point
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1000000);

    while (uniquePoints.size() < n) {
        double x = dis(gen);
        double y = dis(gen);
        Point p = { x, y };
        if (uniquePoints.insert(p).second) { // ����ɹ���˵�����µ�
            points.push_back(p);
        }
    }
    return points;
}

// ����ʵ�鲢ͳ��ʱ��
void runExperiment(int N) {
    vector<Point> points = random_generate(N);
    sort(points.begin(), points.end(), cmpx);

    auto start = high_resolution_clock::now();
  //  pair<Point, Point> brutePair = blf(points,0,N-1);
   // cout << "mind=" << distance(brutePair.first, brutePair.second)<<" ";
    auto end = high_resolution_clock::now();
  //  cout << "������: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    pair<Point, Point> dividePair = getclosepair(points,0,N-1);
  //  cout << "mind=" << distance(dividePair.first, dividePair.second)<<" ";
    end = high_resolution_clock::now();
    cout << "���η�: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

int main() {
    srand(time(0));
    vector<int> testCases = { 100000, 200000  ,300000,400000,500000,600000,700000,800000,900000,1000000};//, 500000, 1000000};
    for (int N : testCases) {
        cout << "\nTesting N = " << N << "\n";
        runExperiment(N);
    }
    return 0;
}
