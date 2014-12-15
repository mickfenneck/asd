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

bool **costruisciMatrice(int n1, int n2) {
    bool **mat = new bool*[n1];
    for(int i = 0; i < n2; i++) {
        mat[i] = new bool[n2];
        mat[i][i] = true;
    }
    return mat;
}


string calcola (const string triangoli) {
    int n = triangoli.length();
    cout << n << endl;
    bool ** matrix = costruisciMatrice(n+1,n+1);
    
     for (int l = 2; l <= n; l += 2) { 
        for (int i = 0; i < n; i++) { 
          int j = i + l; 
          if (j > n) { 
            break; 
          } 
            for (int k = i + 1; k < j; k++) { 
            if (matrix[i + 1][k] && matrix[k + 1][j] && ((i > 0 && triangoli[i] == 'r') || (k < n - 1 && triangoli[k] == 'l'))) { 
                matrix[i][j] = true; 
            } 
          } 
        } 
      }  
    
    
    for(int m = 0; m < n+1; m++) {
        for(int o = 0; o < n+1;o++)
            cout << matrix[m][o];
        cout << endl;
    }/*
    string res = ""; 
    for (int i = 0; i < n; i++) { 
        if (matrix[0][i] && matrix[i + 1][n]) { 
          res += 'o'; 
        } else { 
          res += '.'; 
        } 
    } */
      return ""; 
    
}



int main(int argc, char *argv[]) {
    string triangoli;
    if(argc == 1) triangoli = leggi("input.txt");
    else triangoli = leggi(argv[1]);

    cout << triangoli << endl;
    
   
    
    cout <<  calcola(triangoli) << endl;
    
}
