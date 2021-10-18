// 求一个函数在一个区间上的数值积分

double f(double x) { // 题目中要求的辛普森积分函数，这里简单写一下f(x)=x*x
    return x * x;
}

double Simpson(double a, double b) {
    double mid = (a + b) / 2.0;
    return (b - a) *(f(a) + f(b) + 4.0 * f(mid)) / 6.0;
}

double DFS(double a, double b, double eps)
{
    double mid = (a + b) / 2.0;
    double SA = Simpson(a, mid), SM = Simpson(a, b), SB = Simpson(mid, b);
    if(fabs(SA + SB - SM) <= 15.0 * eps) 
        return SA + SB + (SA + SB - SM) / 15.0;
    return DFS(a, mid, eps / 2.0) + DFS(mid, b, eps / 2.0);
}

// 求一个函数在0~无穷的上的数值积分，若收敛输出答案，若发散输出orz