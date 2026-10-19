#include <iostream>
#include <vector>

using namespace std;

struct Queue {
    vector<int> data;
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
vector<int> adj[MAXN];
vector<int> degree(MAXN);

vector<int> topological_order() {
    Queue q;
    vector<int> l;

    auto dsz = degree.size();
    for (int i = 0; i < dsz; i++) {
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

int main() {
    int n, m;
    cin >> n >> m;
    degree.resize(n);

    for (int x = 0; x < m; x++) {
        int i, j;
        cin >> i >> j;
        // i -> j
        adj[i].push_back(j);
        degree[j]++;
    }

    auto rsp = topological_order();
    for (auto x : rsp) {
        cout << x << ' ';
    }
    cout << '\n';
}
