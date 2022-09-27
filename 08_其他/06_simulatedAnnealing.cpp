const double DOWN = 0.996;
const double START_T = 5000;
double ansx, ansy, ansz, anse;

void initAns() {
    //初始化一个答案点(可以选任意点)
}

double getEnergy(double x, double y, double z) {
    //具体分析题目
}

void SA() {
    double T = START_T;
    while (T > 1e-15) {
        double newx = ansx + (rand() * 2 - RAND_MAX) * T;
        double newy = ansy + (rand() * 2 - RAND_MAX) * T;
        double newz = ansz + (rand() * 2 - RAND_MAX) * T;
        double newe = getEnergy(newx, newy, newz);
        double delta = newe - anse;
        if (delta < 0) ansx = newx, ansy = newy, ansz = newz, anse = newe;
        else if (exp(-delta / T) * RAND_MAX > rand())
            ansx = newx, ansy = newy, ansz = newz;
        T *= DOWN;
    }
}

void solve() {
    initAns();
    while ((double) clock() / CLOCKS_PER_SEC < 2.0) SA();
}

