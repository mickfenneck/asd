#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

string leggi(const char *file) {
    fstream fin;
    fin.open(file, ios::in);

    int count = 0;
    fin >> count;

    string s;
    fin >> s;

    fin.close();

    return s;
}

int ****costruisciMatrice(int n1, int n2, int n3, int n4, int val) {
    int ****mat = new int***[n1];
    for(int i = 0; i < n2; i++) {
        mat[i] = new int**[n2];
        for(int j = 0; j < n2; j++) {
            mat[i][j] = new int*[n3];
            for(int k = 0; k < n3; k++) {
                mat[i][j][k] = new int[n4];
                for(int l = 0; l < n4; l++)
                    mat[i][j][k][l] = val;
            }
        }
    }

    return mat;
}

// indica se la parte da i a j è liberabile potendo eliminare anche l'inizio s o la fine e
int liberabile(const string triangoli, int ****D, int i, int j, int s, int e) {
    if(j - i <= 1)
        D[i][j][s][e] = 1;

    if(D[i][j][s][e] < 0) {
        int start = s ? i : i + 1,
            end = e ? j : j - 1;

        for(int k = start; k < end; k++) {
            bool libs = liberabile(triangoli, D, i, k, s, 1),
                libd = liberabile(triangoli, D, k + 1, j, 1, e);

            if((libs && triangoli[k] == 'd' && !libd) ||
                (!libs && triangoli[k] == 's' && libd)) {
                
                D[i][j][s][e] = 1;
            }
            else D[i][j][s][e] = 0;

            cout << "da " << i << " a " << j << " pos " << k 
                << ", " << libs << "-" << triangoli[k] << "-" << libd 
                << " --> " << D[i][j][s][e] << endl;
            if(D[i][j][s][e]) break;
        }
    }

    return D[i][j][s][e];
}

void calcola(const string triangoli, int ****D) {
    int n = triangoli.length();

    for(int i = 0; i < n - 1; i++) {
        int libs = liberabile(triangoli, D, 0, i, 0, 1),
            libd = liberabile(triangoli, D, i + 1, n - 1, 1, 0);

        if(libs && libd)
            cout << "---  " << i << " rimane" << endl;
    }
}

int main(int argc, char *argv[]) {
    string triangoli;
    if(argc == 1) triangoli = leggi("input.txt");
    else triangoli = leggi(argv[1]);

    cout << triangoli << endl;

    int ****D = costruisciMatrice(triangoli.length(), triangoli.length(), 2, 2, -1);
    calcola(triangoli, D);
}
