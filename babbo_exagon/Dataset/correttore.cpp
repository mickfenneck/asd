#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

ifstream *fin;
ifstream *fcor;
ifstream *fout;

void ex(const char *msg, float res)
{
  if(msg) {
    fprintf(stderr, "%s ", msg);
  }
  printf("%f\n", res*5.0);
  exit(0);
}

template <class T>
T safe_read(const T &lowerBound, const T &upperBound)
{
  // Legge in maniera sicura un tipo ordinato e controlla che stia in
  // [lowerBound, upperBound]
  T x;
  if (lowerBound > upperBound)
    {
      cerr << "safe_read chiamato con parametri errati: " << lowerBound << " " << upperBound << "\n";
      return 1;
    }
  *fout >> x;

  if (fout->fail())
    ex("Output malformato", 0.0f);
  if (x < lowerBound || x > upperBound)
    ex("Output invalido", 0.0f);
  return x;
}

void
check_fine_file()
{
  string x;

  if (fout->eof())
    return;

  *fout >> x;
  if (x != "" || !fout->eof())
    ex("Output malformato", 0.0f);
}

int N,M;

int main(int argc, char *argv[])
{
  if(argc < 4)
    {
      cerr << "Usage: " << argv[0] << " <input> <correct output> <test output>" << endl;
      return 1;
    }

  fin = new ifstream(argv[1]);
  fcor = new ifstream(argv[2]);
  fout = new ifstream(argv[3]);

  if(fin->fail())
    {
      cerr << "Impossibile aprire il file di input " << argv[1] << "." << endl;
      return 1;
    }
  if(fcor->fail())
    {
      cerr << "Impossibile aprire il file di output corretto " << argv[2] << "." << endl;
      return 1;
    }
  if(fout->fail())
    ex("Impossibile aprire il file di output generato dal codice sottoposto al problema.", 0.0);

  *fin >> N;
  vector<bool> sol(N,false);
  int OPT;
  *fcor >> OPT;
  for(int i=0;i<OPT;i++){
    int tmp;
    *fcor >> tmp;
    sol[tmp]=true;
  }
  int solstud;
  int mistakes=0;
  solstud = safe_read(1,N);
  for(int i=0;i<solstud;i++){
    int target;
    target = safe_read(0,N-1);
    if(!sol[target])
      mistakes++;
  }
  check_fine_file();
  if(mistakes==0 && solstud==OPT)
    ex("Ottimo.",1.0f);
  if(mistakes==0 && solstud<OPT && solstud>0)
    ex("Non ha trovato tutte le soluzioni",max(0.3f,(0.0f+solstud) / OPT));
  if(solstud==0)
    ex("Soluzione vuota",0.0f);
  if(mistakes>0)
    ex("Soluzione sbagliata",0.0f);
  ex("Corretto.",1.0f);
  return 0;
}
