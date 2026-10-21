#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vb = vector<bool>;

struct Queue {
    vi data;
    size_t head = 0;

    void push(int x) {
        data.push_back(x);
    }

    void pop() {
        if (!empty())
            head++;
    }

    int front() {
        return data[head];
    }

    bool empty() {
        return head == data.size();
    }

    size_t size() {
        return data.size() - head;
    }
};

const int MAXN = (int)1e5;
vi adj[MAXN];
vi in_degree(MAXN);
vi out_degree(MAXN);
vb visited(MAXN, false);
vi in_result(MAXN, false);

int topological_order() {
    Queue q;
    int cnt = 0;
    vi degree = in_degree;

    for (int i = 0; i < degree.size(); i++) {
        if (degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        cnt++;
        in_result[u] = true;
        for (auto w : adj[u]) {
            degree[w]--;
            if (degree[w] == 0) {
                q.push(w);
            }
        }
    }
    return cnt;
}

void print_vec(vi &v) {
    for (auto x : v) {
        cout << x << ' ';
    }
    cout << endl;
}

// SOLUCAO: ALGORITMO DE KAHN NO GRAFO INVERTIDO

int main() {
    int n, m;
    cin >> n >> m;

    in_degree.resize(n);
    out_degree.resize(n);

    for (int x = 0; x < m; x++) {
        int i, j;
        cin >> i >> j;
        // grafo invertido
        // j -> i
        adj[j].push_back(i);
        in_degree[i]++;
        out_degree[j]++;
    }

    int secure_vertices = topological_order();
    cout << secure_vertices << ' ';
    if (secure_vertices > 0) {
        for (int i = 0; i < n; i++) {
            if (in_result[i]) {
                cout << i << ' ';
            }
        }
        cout << '\n';
    }
}
