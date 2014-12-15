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
int liberabile(const string triangoli, int ****D, int i, int j, int s, int e) {
    if(j < 0 || i < 0 || i >= triangoli.length() || j > triangoli.length())
        return 1;

    if(j - i < 0) {
        D[i][j][s][e] = 1;
        return 1;
    }

    if(D[i][j][s][e] < 0) {
        int start = s ? i : i + 1,
            end = e ? j : j - 1,
            liberato = 0;

        for(int k = start; k <= end; k++) {
            if(triangoli[k] == 's') {
                for(int l = i; l < k; l++) {
                    int lib_il = liberabile(triangoli, D, i, l - 1, s, 1),
                        lib_lk = liberabile(triangoli, D, l + 1, k - 1, 1, 1),
                        lib_kj = liberabile(triangoli, D, k + 1, j, 1, e);

                    if(lib_il && lib_lk && lib_kj)
                        liberato = 1;
                }
            }
            else {
                for(int l = k + 1; l <= j; l++) {
                    int lib_ik = liberabile(triangoli, D, i, k - 1, s, 1),
                        lib_kl = liberabile(triangoli, D, k + 1, l - 1, 1, 1),
                        lib_lj = liberabile(triangoli, D, l + 1, j, 1, e);

                    if(lib_ik && lib_kl && lib_lj)
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

void calcola(const string triangoli, int ****D, vector<int> &rimane) {
    int n = triangoli.length();

    for(int i = 0; i < n; i += 1) {
        int libs = liberabile(triangoli, D, 0, i - 1, 0, 1),
            libd = liberabile(triangoli, D, i + 1, n - 1, 1, 0);

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

    int ****D = costruisciMatrice(triangoli.length(), triangoli.length(), 2, 2, -1);
    vector<int> rimane;
    calcola(triangoli, D, rimane);

    scrivi(rimane);
}
