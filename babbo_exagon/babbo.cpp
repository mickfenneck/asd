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

int **costruisciMatrice(int righe, int colonne, int val) {
    int **mat = new int*[righe];
    for(int i = 0; i < righe; i++) {
        mat[i] = new int[colonne];
        for(int j = 0; j < colonne; j++)
            mat[i][j] = val;
    }

    return mat;
}

int liberabile(const string triangoli, int **D, int i, int j) {
    if(j - i <= 1)
        D[i][j] = 1;

    if(D[i][j] < 0) {
        for(int k = i; k < j; k++) {
            bool libs = liberabile(triangoli, D, i, k),
                libd = liberabile(triangoli, D, k + 1, j);

            if((libs && triangoli[k] == 'd' && !libd) ||
                (!libs && triangoli[k] == 's' && libd)) {
                
                D[i][j] = 1;
            }
            else D[i][j] = 0;

            cout << "da " << i << " a " << j << " pos " << k 
                << ", " << libs << "-" << triangoli[k] << "-" << libd 
                << " --> " << D[i][j] << endl;
            if(D[i][j]) break;
        }
    }

    return D[i][j];
}

void calcola(const string triangoli, int **D) {
    int n = triangoli.length();

    for(int i = 0; i < n - 1; i++) {
        if(liberabile(triangoli, D, 0, i) && liberabile(triangoli, D, i + 1, n))
            cout << "---  " << i << " rimane" << endl;
    }
}

int main(int argc, char *argv[]) {
    string triangoli;
    if(argc == 1) triangoli = leggi("input.txt");
    else triangoli = leggi(argv[1]);

    cout << triangoli << endl;

    int **D = costruisciMatrice(triangoli.length(), triangoli.length(), -1);
    calcola(triangoli, D);

    int n = triangoli.length();
    for(int i = -1; i < n; i++) {
        cout << setw(3) << i;
        for(int j = 0; j < n; j++)
            cout << setw(3) << (i < 0 ? j : D[i][j]);
        cout << endl;
    }

}
