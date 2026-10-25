#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> par;

struct Queue {
    vector<par> data;
    size_t head = 0;

    void push(par x) {
        data.push_back(x);
    }

    void pop() {
        if (!empty())
            head++;
    }

    par front() {
        return data[head];
    }

    bool empty() {
        return head == data.size();
    }

    size_t size() {
        return data.size() - head;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));
    vector<vector<int>> dis(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    Queue q;
    q.push({0, 0});
    dis[0][0] = 0;

    while (!q.empty()) {
        par v = q.front();
        q.pop();

        int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
        int dy[] = {1, -1, 0, 1, -1, 1, -1, 0};

        for (int i = 0; i < 8; i++) {
            par u = {v.first + dx[i], v.second + dy[i]};

            if (u.first >= 0 && u.first < n && u.second >= 0 && u.second < n &&
                dis[u.first][u.second] == -1 &&
                graph[u.first][u.second] <= graph[v.first][v.second]) {

                q.push(u);
                dis[u.first][u.second] = dis[v.first][v.second] + 1;
            }
        }
    }

    cout << dis[n - 1][n - 1] << '\n';
}
