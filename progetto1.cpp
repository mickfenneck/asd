#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
#include <stack>

using namespace std;

typedef vector< vector<int> > Grafo;

// legge un grafo ed il suo trasposto
void leggi(Grafo &g, Grafo &gt, int &start, int &end) {
    fstream fs;
    int n, m, u, v;

    fs.open("input.txt", ios::in);
    fs >> n >> m >> start >> end;

    for(int i = 0; i < n; i++) {
        g.push_back(vector<int>());
        gt.push_back(vector<int>());
    }

    for(int i = 0; i < m; i++) {
        fs >> u >> v;

        g[u].push_back(v);
        gt[v].push_back(u);
    }

    fs.close();
}

void scrivi(int max) {
    fstream fs;
    fs.open("output.txt", ios::out);
    
    fs << max;
    cout << max << endl;

    fs.close();
}

void ccdfs(const Grafo &g, int u, int counter, vector<int> &id) {
    id[u] = counter;

    for(vector<int>::const_iterator
        it = g[u].begin(), end = g[u].end();
        it != end; ++it) {
    
        if(id[*it] == 0)
            ccdfs(g, *it, counter, id);
    }
}

vector<int> *trova_cc(const Grafo &g, stack<int> s) {
    vector<int> *id = new vector<int>(g.size(), 0);
    int counter = -1;

    while(!s.empty()) {
        int u = s.top(); s.pop();
        if(!id->at(u))
            ccdfs(g, u, ++counter, *id);
    }

    return id;
}

void tsdfs(const Grafo &g, int u, vector<bool> &visitato, stack<int> &s) {
    visitato[u] = true;
    for(vector<int>::const_iterator
        it = g[u].begin(), end = g[u].end();
        it != end; ++it) {
    
        if(!visitato[*it])
            tsdfs(g, *it, visitato, s);
    }

    s.push(u);
}

void topSort(const Grafo &g, stack<int> &s) {
    int n = g.size();
    vector<bool> visitato(n, false);

    for(int i = 0; i < n; i++) {
        if(!visitato[i])
            tsdfs(g, i, visitato, s);
    }
}

vector<int> *trova_scc(const Grafo &g, const Grafo &gt) {
    stack<int> s;
    topSort(g, s);

    return trova_cc(gt, s);
}

void costruisci_ccg(const Grafo &g, const vector<int> &scc, Grafo &ccg) {
    for(int i = 0; i < g.size(); i++)
        ccg.push_back(vector<int>());

    for(int i = 0; i < g.size(); i++) {
        int questa_scc = scc[i];

        vector<int> adiacenti = g[i];
        for(int j = 0; j < adiacenti.size(); j++) {
            int altra_scc = scc[adiacenti[j]];

            if(questa_scc != altra_scc)
                ccg[questa_scc].push_back(altra_scc);
        }
    }
}

void scrivi(const vector<int> &v) {
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void scrivi(const Grafo &g) {
    for(int i = 0; i < g.size(); i++) {
        cout << i << " - "; scrivi(g[i]);
    }
}

int numcammini(const Grafo &g, stack<int> toporder, int from, int to) {
    vector<int> cammini(toporder.size(), 0);
    cammini[from] = 1;

    while(!toporder.empty()) {
        int v = toporder.top(); toporder.pop();
        int count_to_here = cammini[v];

        for(vector<int>::const_iterator
            it = g[v].begin(), end = g[v].end();
            it != end; ++it) {
        
            cammini[*it] += count_to_here;
        }
    }

    //cout << endl; cout << "ccg "; scrivi(g);
    //cout << endl; cout << "cammini "; scrivi(cammini);
    return cammini[to];
}

int main() {
    Grafo g, gt, ccg;
    int start, end;
    leggi(g, gt, start, end);

    vector<int> *scc = trova_scc(g, gt);

    costruisci_ccg(g, *scc, ccg);
    //cout << "scc "; scrivi(*scc);
    //cout << "---" << endl;

    stack<int> toporder;
    topSort(ccg, toporder);

    int num = numcammini(ccg, toporder, scc->at(start), scc->at(end));
    scrivi(num);

    delete scc;
}
