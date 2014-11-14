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
    cout << max;

    fs.close();
}

void ccdfs(const Grafo &g, int u, int counter, vector<int> &id) {
    id[u] = counter + 1;

    for(vector<int>::const_iterator
        it = g[u].begin(),
        end = g[u].end();
        it != end; ++it) {
    
        if(id[*it] == 0)
            ccdfs(g, *it, counter++, id);
    }
}

vector<int> *trova_cc(const Grafo &g, stack<int> s) {
    vector<int> *id = new vector<int>(g.size(), 0);
    int counter = 0;

    while(!s.empty()) {
        int u = s.top(); s.pop();
        if(!id->at(u))
            ccdfs(g, u, counter++, *id);
    }

    return id;
}

void tsdfs(const Grafo &g, int u, bool *visitato, stack<int> &s) {
    visitato[u] = true;
    for(vector<int>::const_iterator
        it = g[u].begin(),
        end = g[u].end();
        it != end; ++it) {
    
        if(!visitato[*it])
            tsdfs(g, *it, visitato, s);
    }

    s.push(u);
}

void topSort(const Grafo &g, stack<int> &s) {
    int n = g.size();
    bool *visitato = new bool[n];
    for(int i = 0; i < n; i++)
        visitato[i] = false;

    for(int i = 0; i < n; i++) {
        if(!visitato[i])
            tsdfs(g, i, visitato, s);
    }
    delete visitato;
}

vector<int> *trova_scc(const Grafo &g, const Grafo &gt) {
    stack<int> s;
    topSort(g, s);

    return trova_cc(gt, s);
}

Grafo *costruisci_ccg(const Grafo &g, const vector<int> &scc) {
    Grafo *ccg = new Grafo(g.size(), vector<int>());

    for(int i = 0; i < g.size(); i++) {
        int questa_scc = scc[i];

        vector<int> adiacenti = g[i];
        for(int j = 0; j < adiacenti.size(); j++) {
            int altra_scc = scc[adiacenti[j]];

            if(questa_scc != altra_scc)
                ccg->at(questa_scc).push_back(altra_scc);
        }
    }

    return ccg;
}

int conta_bfs(const Grafo &g, int node_start, int node_end) {
    int count = 0;

    queue<int> frontiera;

    frontiera.push(node_start);

    while(!frontiera.empty()) {
        int v = frontiera.front();
        frontiera.pop();

        for(vector<int>::const_iterator
            it = g[v].begin(),
            end = g[v].end();
            it != end; ++it) {

            if(*it == node_end)
                count += 1;
            else
                frontiera.push(*it);
        }
    }

    return count;
}

void scrivi(const vector<int> &v) {
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

int main() {
    Grafo g, gt, *ccg;
    int start, end;
    leggi(g, gt, start, end);

    vector<int> *scc = trova_scc(g, gt);
    //scrivi(*scc);

    ccg = costruisci_ccg(g, *scc);
    cout << "---" << endl;

    /*
    for(int i = 0; i < ccg->size(); i++) {
        cout << i << " - ";
        scrivi(ccg->at(i));
    }*/

    int num = conta_bfs(*ccg, scc->at(start), scc->at(end));
    scrivi(num);

    delete scc;
    delete ccg;
}
