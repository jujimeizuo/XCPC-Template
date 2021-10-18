#include<iostream>
using namespace std;

const int N=4;

void GaleShapley(const int (&man)[MAX][MAX], const int (&woman)[MAX][MAX], int (&match)[MAX]) {
	int wm[MAX][MAX];    // wm[i][j]: rank from girl i to boy j
	int choose[MAX];    // choose[i]: current boyfriend of girl i
	int manIndex[MAX]; //    manIndex[i]: how many girls that have rejected boy i
	int i, j;
	int w, m;
	for (i = 0; i < N; i++) {
		match[i] = -1;
		choose[i] = -1;
		manIndex[i] = 0;
		for (j = 0; j < N; j++)
			wm[i][woman[i][j]] = j;
	}

	bool bSingle = false;
	while (!bSingle) {
		bSingle = true;
		for (i = 0; i < N; i++) {
			if (match[i] != -1) // boy i already have a girlfriend
				continue;
			bSingle = false;
			j = manIndex[i]++; // the jth girl that boy i like most
			w = man[i][j];
			m = choose[w];    // current girl w's boyfriend
			if (m == -1 || wm[w][i] < wm[w][m]) { // if girl w prefer boy i
				match[i] = w;
				choose[w] = i;
				if (m != -1)
					match[m] = -1;
			}
		}
	}
}


void Print(const int(&match)[MAX], int N) {
	for (int i = 0; i < N; i++)
		cout << i << " " << match[i] << endl;
}


int main(){
    int man[N][N]={
        {2,3,1,0},
        {2,1,3,0},
        {0,2,3,1},
        {1,3,2,0},
    };
    int woman[N][N]={
        {0,3,2,1},
        {0,1,2,3},
        {0,2,3,1},
        {1,0,3,2},
    };

    int match[N];
    GaleShapley(man,woman,match);
    Print(match,N);

    return 0;
}