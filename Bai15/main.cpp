#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;

void readData(int &x1, int &y1, int &x2, int &y2, int &R)
{
    fstream f;
    f.open("./input.txt", ios::in);
    f >> x1 >> y1 >> x2 >> y2 >> R;
    f.close();
}
double areaOfIntersection(int &x1, int &y1, int &x2, int &y2, int &R, int sqrDistance)
{

    // Circles do not overlap
    if (sqrt(sqrDistance) >= 2 * R)
    {
        return 0;
    }

    // Partially overlap
    else
    {
        // O1 -> O2
        double distance = sqrt(sqrDistance);
        double cosHalfAlpha = distance / (2 * R);

        // Góc chắn cung giao giữa 2 đường tròn. VD CAD
        double Alpha = 2 * acos(cosHalfAlpha);

        return Alpha * R * R - R * R * sin(Alpha);
    }
}
double areaOfUnion(int &x1, int &y1, int &x2, int &y2, int &R)
{
    int sqrDistance;
    sqrDistance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    double intersectionArea = areaOfIntersection(x1, y1, x2, y2, R, sqrDistance);
    // Nguyên lý bù trừ
    return 2 * M_PI * R * R - intersectionArea;
}
double round(double val)
{
    if (val < 0)
        return ceil(val - 0.5);
    return floor(val + 0.5);
}
int main()
{
    int x1, y1, x2, y2;
    int R;
    readData(x1, y1, x2, y2, R);
    // overlap with R1 = R2 = R
    if (x1 == x2 && y1 == y2)
    {
        cout << "result: " << M_PI * R * R;
    }
    else
    {
        double unionArea = areaOfUnion(x1, y1, x2, y2, R);
        double result = round(unionArea * 1000.0) / 1000.0;
        // Trường hợp phần lẻ là 0, vẫn in 3 số sau dấu phẩy
        cout << "result: " << setprecision(3) << fixed << result;
    }
    return 1;
}
