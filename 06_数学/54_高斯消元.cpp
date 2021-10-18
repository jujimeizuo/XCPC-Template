#include <bits/stdc++.h>
using namespace std;
const int N=210;
int a[N][N];//增广矩阵
int x[N];//解集
int freeX[N];//自由变元
// equ:方程个数 var:变量个数
int Gauss(int equ, int var){//返回自由变元个数
    /*初始化*/
    for(int i = 0;i <= var; i++){
        x[i] = 0;
        freeX[i] = 0;
    }

    /*转换为阶梯阵*/
    int col = 0;//当前处理的列
    int num = 0;//自由变元的序号
    int k;//当前处理的行
    for(k = 0;k < equ && col < var; k++, col++) {//枚举当前处理的行
        int maxr = k;//当前列绝对值最大的行
        for(int i = k + 1;i < equ; i++){//寻找当前列绝对值最大的行
            if(a[i][col] > a[maxr][col]){
                maxr = i;
                swap(a[k], a[maxr]);//与第k行交换
                break;
            }
        }
        if(a[k][col] == 0){//col列第k行以下全是0，处理当前行的下一列
            freeX[num++] = col;//记录自由变元
            k--;
            continue;
        }

        for(int i = k + 1;i < equ; i++){
            if(a[i][col] != 0){
                for(int j = col;j < var + 1; j++){//对于下面出现该列中有1的行，需要把1消掉
                    a[i][j] ^= a[k][j];
                }
            }
        }
    }

    /*求解*/
    //无解：化简的增广阵中存在(0,0,...,a)这样的行，且a!=0
    for(int i = k;i < equ; i++)
        if(a[i][col] != 0)
            return -1;

    //无穷解: 在var*(var+1)的增广阵中出现(0,0,...,0)这样的行
    if(k < var)//返回自由变元数
        return var - k;//自由变元有var-k个

    //唯一解: 在var*(var+1)的增广阵中形成严格的上三角阵
    for(int i = var - 1;i >= 0; i--){//计算解集
        x[i] = a[i][var];
        for(int j = i + 1;j < var; j++)
            x[i] ^= (a[i][j] && x[j]);
    }
    return 0;
}