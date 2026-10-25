#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;

const int MAXN = (int)1e5 + 10;

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

vi adj[MAXN];
vi c(MAXN);
vi out_degree(MAXN);
// dp[i] = max(dp[i], dp[v]), sendo v um superior
vi dp(MAXN);

// ordenação topológica no grafo invertido
vi topological_order(int n) {
    Queue q;
    vector<int> l;
    // grau de saida na ordenação topológica porque o grafo de entrada é invertido.
    vi degree = out_degree;

    for (int i = 0; i < n; i++) {
        if (degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        l.push_back(u);
        for (auto w : adj[u]) {
            degree[w]--;
            if (degree[w] == 0) {
                q.push(w);
            }
        }
    }
    return l;
}

void print_vec(vi &v) {
    for (auto x : v) {
        cout << x << ' ';
    }
    cout << endl;
}

// Provável problema de DP on DAG

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> c[i];
        dp[i] = i; // armazenando identificador e não custo
    }

    for (int x = 0; x < m; x++) {
        int i, j;
        cin >> i >> j;
        out_degree[i]++;
        adj[j].push_back(i);
    }

    auto t = topological_order(n);

    for (int k = n - 1; k >= 0; k--) {
        int u = t[k];
        // encontrando o maior vizinho direto ou indireto.
        for (auto v : adj[u]) {
            if (c[dp[v]] > c[dp[u]]) {
                dp[u] = dp[v];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dp[i] << (i + 1 == n ? '\n' : ' ');
    }
    cout << '\n';
}
