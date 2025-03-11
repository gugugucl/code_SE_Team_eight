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

// 计算两点间欧几里得距离
double distance(const Point& p1, const Point& p2) {
	return   sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool cmpx(Point &p1, Point& p2)  //x升序
{
    return p1.x < p2.x;
}
bool cmpy(Point& p1, Point& p2)  //y升序
{
    return p1.y < p2.y;
}

pair<Point, Point> blf(vector<Point>& points,int low,int high) {

    double minDist = numeric_limits<double>::max();//浮点型的max
    pair<Point, Point> closestPair;
    for (int i = low; i <=high; i++) //任意两两比较 O(n2)
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
    double mind = lmind < rmind ? lmind : rmind;  //找到左右最短点对距离.
    pair<Point, Point>closepair;
    if (mind == lmind)closepair = leftpair;
    else closepair = rightpair;
    //比较mind 和跨左右的min
    vector<Point>p1p2;
    for (int i = mid; i >= low && points[i].x > xm - mind; i--)//从中间开始找 不符合就结束
        p1p2.push_back(points[i]);
    for(int i=mid+1;i<=high&& points[i].x < xm + mind;i++)
        p1p2.push_back(points[i]);
    sort(p1p2.begin(),p1p2.end(), cmpy);//按y升序排序
    double d;//curmind
    for (int i = 0; i < p1p2.size(); i++)
    {
     for (int j = i + 1; j < p1p2.size()&&    (p1p2[j].y - p1p2[i].y) < mind ;j++)//分治合并时，每个点最多只需与后面 7 个点 比较。
        {
            d = distance(p1p2[i], p1p2[j]);
            if (d < mind)
            {  mind = d;//更小就更新mind
                closepair = { p1p2[i], p1p2[j] };
            //     cout <<closepair.first.x<<" "<<closepair.first.y<<" "<<closepair.second.x<<" "<<closepair.second.y
            //       cout  << distance(closepair.first, closepair.second) << endl;
            }
        }
    }
    return closepair;
}

// 生成随机点
vector<Point> generateRandomPoints(int N) {
    vector<Point> points;
    for (int i = 0; i < N; i++) {
        Point p((rand() / (double)RAND_MAX) * 10000+i, (rand() / (double)RAND_MAX) * 10000);
        points.push_back(p);
    }
    return points;
}
std::vector<Point> random_generate(int n) {
    std::set<Point> uniquePoints; // 使用 set 直接存储 Point
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1000000);

    while (uniquePoints.size() < n) {
        double x = dis(gen);
        double y = dis(gen);
        Point p = { x, y };
        if (uniquePoints.insert(p).second) { // 插入成功，说明是新点
            points.push_back(p);
        }
    }
    return points;
}

// 运行实验并统计时间
void runExperiment(int N) {
    vector<Point> points = random_generate(N);
    sort(points.begin(), points.end(), cmpx);

    auto start = high_resolution_clock::now();
  //  pair<Point, Point> brutePair = blf(points,0,N-1);
   // cout << "mind=" << distance(brutePair.first, brutePair.second)<<" ";
    auto end = high_resolution_clock::now();
  //  cout << "暴力法: " << duration_cast<milliseconds>(end - start).count() << " ms\n";

    start = high_resolution_clock::now();
    pair<Point, Point> dividePair = getclosepair(points,0,N-1);
  //  cout << "mind=" << distance(dividePair.first, dividePair.second)<<" ";
    end = high_resolution_clock::now();
    cout << "分治法: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
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
