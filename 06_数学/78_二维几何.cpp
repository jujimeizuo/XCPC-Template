#include <iostream>
#include <cmath>

using namespace std;

const double eps = 1e-6;
const double pi = acos(-1);

#define zero(x) (((x) > 0 ? (x) : -(x)) < eps) 

int sgn(double d) {
    if(fabs(d) < eps) 
        return 0;
    if(d > 0) 
        return 1;
    else 
        return -1;
}

int dcmp(double x, double y) {
    if(fabs(x - y) < eps) 
        return 0;
    if(x > y) 
        return 1;
    else 
        return -1;
}

struct Point{ // 点
    double x, y; 
    Point(double x = 0, double y = 0) : x(x), y(y) {} 
};

struct line{ 
    Point a, b;
};

typedef Point Vector; // 向量

// 运算(向量之间)

Vector operator + (Vector A, Vector B) { // AB
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator - (Point A, Point B) { // BA
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator * (Vector A, double p) { // A * p
    return Vector(A.x * p, A.y * p);
}

Vector operator / (Vector A, double p) { // A / p
    return  Vector(A.x / p, A.y / p);
}

bool operator < (const Point& a, const Point& b) { // 将点升序排列
    if(a.x == b.x) 
        return a.y < b.y;
    return a.x < b.x;
}

bool operator == (const Point& a, const Point& b) { // 判断是否为同一点
    if(dcmp(a.x, b.x) == 0 && dcmp(a.y, b.y) == 0)
        return true;
    else 
        return false;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// 向量

double Dot(Vector A, Vector B) { // 内积
    return A.x * B.x + A.y * B.y;
}

double Cross(Vector A, Vector B) { // 外积
    return A.x * B.y - A.y * B.x;
}

double Length(Vector A) { // 向量取模
    return sqrt(Dot(A, A));
}

double Angle(Vector A, Vector B) { // 向量夹角
    return acos(Dot(A, B) / Length(A) / Length(B));
}

double Area(Point A, Point B, Point C) { // 计算两向量构成的平行四边形有向面积
    return Cross(B - A, C - A);
}

Vector Rotate(Vector A, double rad) { // 计算向量逆时针旋转后的向量
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad)); 
}

Vector Normal(Vector A) { // 计算向量逆时针转90度后的单位法向量
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}

bool ToLeftTest(Point a, Point b, Point c) { // 判断bc是不是向ab的逆时针方向转向
    return Cross(b - a, c - b) > 0;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// 直线与线段

double Pow(double x) {
    return x * x;
}

double distance (Point p1, Point p2) {// 两点距离
    return sqrt(Pow(p1.x - p2.x) + Pow(p1.y - p2.y));
}

int dots_inline(Point p1, Point p2, Point p3) { // 判断三点共线
    return Cross(p2 - p1, p3 - p1);
}

int dot_online_in(Point p, line l) { // 判断点在线段上（包含端点）
    return zero(Cross(l.b - p, l.a - p) && ((l.a.x - p.x) * (l.b.x - p.x) < eps) && ((l.a.y - p.y) * (l.b.y - p.y) < eps));
}

int dot_online_ex(Point p, line l) { // 判断点在线段上（不包含端点）
    return dot_online_in(p, l) && (!zero(p.x - l.a.x) || !zero(p.y - l.a.y)) && (!zero(p.x - l.b.x) || !zero(p.y - l.b.y));
}

int same_side(Point p1, Point p2, line l) { // 判断两点在线段同侧，点在线段上返回0
    return Cross(l.a - l.b, p1 - l.b) * Cross(l.a - l.b, p2 - l.b) > eps;
}

int opposite_side(Point p1, Point p2, line l) { // 判断两点在线段异侧，点在线段上返回0
    return Cross(l.a - l.b, p1 - l.b) * Cross(l.a - l.b, p2 - l.b) < -eps;
}

int parallel(line u, line v) { // 判断两直线平行
    return zero((u.a.x - u.b.x) * (v.a.y - v.b.y) - (u.a.y - u.b.y) * (v.a.x - v.b.x));
}

int  perpendicular(line u, line v) { // 判断两直线垂直
    return zero((u.a.x - u.b.x) * (v.a.x - v.b.x) + (u.a.y - u.b.y) * (v.a.y - v.b.y));
}

int intersect_in(line u, line v) {// 判断两线段相交，包括端点和部分重合
    if(!dots_inline(u.a, u.b, v.a) || !dots_inline(u.a, u.b, v.b)) {
        return !same_side(u.a, u.b, v) && !same_side(v.a, v.b, u);
    }
    return dot_online_in(u.a, v) || dot_online_in(u.b, v) || dot_online_in(v.a, u) || dot_online_in(v.b, u);
}

int intersect_ex(line u, line v) {// 判断两线段相交，不包括端点和部分重合
    return opposite_side(u.a, u.b, v) && opposite_side(v.a, v.b, u);
}  

// 计算两直线交点，注意事先判断直线是否相交
// 计算两线段交点，注意事先判断线段相交和平行
Point intersection(line u, line v) {
    Point ret = u.a;
    double t = ((u.a.x - v.a.x) * (v.a.y - v.b.y) - (u.a.y - v.a.y) * (v.a.x - v.b.x)) / ((u.a.x - u.b.x) * (v.a.y - v.b.y) - (u.a.y - u.b.y) * (v.a.x - v.b.x));
    ret.x += (u.b.x - u.a.x) * t;
    ret.y += (u.b.y - u.a.y) * t;
    return ret;
}

Point ptoline(Point p, line l) { // 点到直线最近点
    Point t = p;
    t.x += l.a.y - l.b.y;
    t.y += l.b.x - l.a.x;
    line u = {p, t};
    return intersection(u, l);
}

double disptoline(Point p, line l) { // 点到直线距离
    return fabs(Cross(p - l.b, l.a - l.b) / distance(l.a, l.b));
}

Point ptoseg(Point p, line l) { // 点到线段最近点
    Point t = p;
    t.x += l.a.y - l.b.y;
    t.y += l.b.x - l.a.x;
    if(Cross(l.a - p, t - p) * Cross(l.b - p, t - p) > eps) 
        return distance(p, l.a) < distance(p, l.b) ? l.a : l.b;
    line u = {p, t};
    return intersection(u, l);
}

double disptoseg(Point p, line l) { // 点到线段距离
    Point t = p;
    t.x += l.a.y - l.b.y;
    t.y += l.b.x - l.a.x;
    if(Cross(l.a - p, t - p) * Cross(l.b - p, t - p) > eps) {
        double dis1 = distance(p, l.a);
        double dis2 = distance(p, l.b);
        return dis1 < dis2 ? dis1 : dis2;
    }
    return fabs(Cross(p - l.b, l.a - l.b) / distance(l.a, l.b));
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// 面积

double area_triangle(Point p1, Point p2, Point p3) { // 三角形面积（输入三顶点）
    return fabs(Cross(p1 - p3, p2 - p3)) / 2;
}

double area_triangle(double a, double b, double c) { // 三角形面积（输入三边长）
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double area_polygon(int n, Point *p) { // 计算多边形面积，顶点按顺时针或逆时针输入
    double s1 = 0, s2 = 0;
    for(int i = 0;i < n; i++) {
        s1 += p[(i + 1) % n].y * p[i].x;
        s2 += p[(i + 1) % n].y * p[(i + 2) % n].x;
    }
    return fabs(s1 - s2) / 2;
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// 球面

//计算圆心角 lat 表示纬度,-90<=w<=90,lng 表示经度 
//返回两点所在大圆劣弧对应圆心角,0<=angle<=pi 

double angle(double lng1, double lat1, double lng2, double lat2) {
    double dlng = fabs(lng1 - lng2) * pi / 180;
    while(dlng >= pi + pi) {
        dlng -= pi + pi;
    }
    if(dlng > pi) 
    dlng = pi + pi - dlng;
    lat1 *= pi / 180;
    lat2 *= pi / 180;
    return acos(cos(lat1) * cos(lat2) * cos(dlng) + sin(lat1) * sin(lat2));
}

// 计算两点距离

double line_dist(double r, double lng1, double lat1, double lng2, double lat2) {
    double dlng = fabs(lng1 - lng2) * pi / 180;
    while(dlng >= pi + pi) {
        dlng -= pi + pi;
    }
    if(dlng > pi) 
    dlng = pi + pi - dlng;
    lat1 *= pi / 180;
    lat2 *= pi / 180;
    return r * sqrt(2 - 2 * (cos(lat1) * cos(lat2) * cos(dlng) + sin(lat1) * sin(lat2)));
}

// 计算球面距离

inline double sphere_dist(double r, double lng1, double lat1, double lng2, double lat2) {
    return r * angle(lng1, lat1, lng2, lat2);
}

/*-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
// 三角形

// 外心

Point circumcenter(Point a, Point b, Point c) {
    line u, v;
    u.a.x = (a.x + b.x) / 2;
    u.a.y = (a.y + b.y) / 2;
    u.b.x = u.a.x - a.y + b.y;
    u.b.y = u.a.y + a.x - b.x;
    v.a.x = (a.x + c.x) / 2;
    v.a.y = (a.y + c.y) / 2;
    v.b.x = v.a.x - a.y + c.y;
    v.b.y = v.a.y + a.x - c.y;
    return intersection(u, v);
}

// 内心

Point incenter(Point a, Point b, Point c) {
    line u, v;
    double m, n;
    u.a = a;
    m = atan2(b.y - a.y, b.x - a.x);
    n = atan2(c.y - a.y, c.x - a.x);
    u.b.x = u.a.x + cos((m + n) / 2);
    u.b.y = u.a.y + sin((m + n) / 2);
    v.a = b;
    m=atan2(a.y - b.y, a.x - b.x); 
    n=atan2(c.y - b.y, c.x - b.x); 
    v.b.x=v.a.x + cos((m + n) / 2); 
    v.b.y=v.a.y + sin((m + n) / 2);
    return intersection(u, v); 
}

// 垂心

Point perpencenter(Point a, Point b, Point c) {
    line u, v;
    u.a = c; 
    u.b.x = u.a.x - a.y + b.y; 
    u.b.y = u.a.y + a.x - b.x; 
    v.a = b; 
    v.b.x = v.a.x - a.y + c.y; 
    v.b.y = v.a.y + a.x - c.x; 
return intersection(u, v); 
}

// 重心
//到三角形三顶点距离的平方和最小的点 
//三角形内到三边距离之积最大的点 

Point barycenter(Point a, Point b, Point c) {
    line u,v; 
    u.a.x = (a.x + b.x) / 2; 
    u.a.y = (a.y + b.y) / 2; 
    u.b = c; 
    v.a.x = (a.x + c.x) / 2; 
    v.a.y = (a.y + c.y) / 2; 
    v.b = b; 
return intersection(u, v); 
}

//费马点 
//到三角形三顶点距离之和最小的点 
Point fermentpoint(Point a, Point b, Point c) { 
    Point u,v; 
    double step = fabs(a.x) + fabs(a.y) + fabs(b.x) + fabs(b.y) + fabs(c.x) + fabs(c.y); 
    int i, j, k; 
    u.x = (a.x + b.x + c.x) / 3; 
    u.y = (a.y + b.y + c.y) / 3; 
    while(step > 1e-10) 
    for(k = 0;k < 10; step /= 2, k++) 
        for (i = -1;i <= 1; i++) 
            for (j = -1;j <= 1; j++){ 
            v.x = u.x + step * i; 
            v.y = u.y + step * j; 
            if(distance(u,a) + distance(u,b) + distance(u,c) > distance(v,a) + distance(v,b) + distance(v,c)) 
                u = v; 
            } 
    return u; 
} 