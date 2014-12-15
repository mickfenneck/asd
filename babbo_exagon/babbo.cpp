#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

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

void scrivi(const vector<int> r) {
    fstream fout;
    fout.open("output.txt", ios::out);

    fout << r.size() << endl;
    for(vector<int>::const_iterator it = r.begin(),
        end = r.end(); it != end; ++it) {
        
        fout << *it << " ";
    }

    fout.close();
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
int liberabile(const char *triangoli, int n, int ****D, int i, int j, int s, int e) {
    if(j < 0 || i < 0 || i >= n || j >= n || j - i < 0)
        return 1;

    if(D[i][j][s][e] < 0) {
        int liberato = 0;

        for(int k = i + s; k <= j - e; k++) {
            if(triangoli[k] == 's') {
                for(int l = i; l < k && !liberato; l++) {
                    int lib_il = liberabile(triangoli, n, D, i, l - 1, s, 0);
                    if(!lib_il) continue;

                    int lib_lk = liberabile(triangoli, n, D, l + 1, k - 1, 0, 0);
                    if(!lib_lk) continue;

                    int lib_kj = liberabile(triangoli, n, D, k + 1, j, 0, e);
                    if(!lib_kj) continue;

                    liberato = 1;
                }
            }
            else {
                for(int l = k + 1; l <= j && !liberato; l++) {
                    int lib_ik = liberabile(triangoli, n, D, i, k - 1, s, 0);
                    if(!lib_ik) continue;

                    int lib_kl = liberabile(triangoli, n, D, k + 1, l - 1, 0, 0);
                    if(!lib_kl) continue;

                    int lib_lj = liberabile(triangoli, n, D, l + 1, j, 0, e);
                    if(!lib_lj) continue;

                    liberato = 1;
                }
            }
        }

        D[i][j][s][e] = liberato;
    }

    //cout << "liberabile " << i << " " << j << " " << s << " " << e 
    //    << " --> " << D[i][j][s][e] << endl;

    return D[i][j][s][e];
}

void calcola(const char *triangoli, int n, int ****D, vector<int> &rimane) {
    for(int i = 0; i < n; i++) {
        int libs = liberabile(triangoli, n, D, 0, i - 1, 1, 0),
            libd = liberabile(triangoli, n, D, i + 1, n - 1, 0, 1);

        if(libs && libd) {
            cout << "---  " << i << " rimane" << endl;
            rimane.push_back(i);
        }
    }
}

int main(int argc, char *argv[]) {
    string triangoli;
    if(argc == 1) triangoli = leggi("input.txt");
    else triangoli = leggi(argv[1]);

    cout << triangoli << endl;
    const char *s = triangoli.c_str();

    int ****D = costruisciMatrice(triangoli.length(), triangoli.length(), 2, 2, -1);
    vector<int> rimane;
    calcola(s, triangoli.length(), D, rimane);

    scrivi(rimane);
}
