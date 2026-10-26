#include <iostream>
#include <vector>

using namespace std;

vector<int> steps(1e6, 1e9 + 7);
vector<bool> vis(1e6, false);

vector<bool> proibidas(1e6);
struct pairi {
    int first;
    int second;
};
struct PriorityQueue {
    vector<pairi> data;

    void arrangeUp(int i) {
        while (i > 0) {
            int pai = (i - 1) / 2;

            if (data[i].first < data[pai].first) {
                swap(data[i], data[pai]);
                i = pai;
            } else {
                break;
            }
        }
    }

    void arrangeDown(int i) {
        while (2 * i + 1 < data.size()) {
            int left = 2 * i + 1;
            int rigth = 2 * i + 2;
            int less = left;

            if (rigth < data.size() && data[rigth].first < data[left].first) {
                less = rigth;
            }

            if (data[less].first < data[i].first) {
                swap(data[i], data[less]);
                i = less;
            } else {
                break;
            }
        }
    }

    void push(int idx, int valor) {
        pairi temp;
        temp.first = idx;
        temp.second = valor;
        data.push_back(temp);
        arrangeUp(data.size() - 1);
    }

    void pop() {
        if (data.size() == 0) {
            cout << "Fila de Prioridade vazia";
            return;
        }

        data[0] = data.back();
        data.pop_back();

        if (data.size() != 0) {
            arrangeDown(0);
        }
    }

    int size() {
        return data.size();
    }

    pairi top() {
        return data[0];
    }

    bool isEmpty() {
        return data.empty();
    };
};
int mod(int x) {
    return x < 0 ? -x : x;
}

int h(int v1, int t) {
    int acc = 0;
    for (int k = 1; k < 1e6; k *= 10) {
        int d1 = v1 % 10;
        int dt = t % 10;
        acc += min(min(mod(dt - d1), mod((dt + 10) - d1)), mod((dt - 10) - d1));

        v1 /= 10;
        t /= 10;
    }
    return acc;
}

int a_star(int start, int t) {
    if (proibidas[start] || proibidas[t])
        return -1;
    PriorityQueue q;
    steps[start] = 0;
    int f = h(start, t);
    q.push(-f, start);
    while (!q.data.size()) {
        int curr = q.top().second;
        q.pop();
        if (curr == t)
            return steps[curr];
        if (vis[curr])
            continue;
        vis[curr] = true;
        int temp = curr;
        int u;
        for (int k = 1; k < 1e6; k *= 10) {

            int d = temp % 10;
            if (d == 0) {
                u = curr + 9 * k;

            } else {
                u = curr - k;
            }
            if (!vis[u] && !proibidas[u] && steps[curr] + 1 < steps[u]) {
                steps[u] = steps[curr] + 1;
                int f_u = steps[u] + h(u, t);
                q.push(-f_u, u);
            }
            if (d == 9) {
                u = curr - 9 * k;

            } else {
                u = curr + k;
            }

            temp /= 10;
            if (!vis[u] && !proibidas[u] && steps[curr] + 1 < steps[u]) {
                steps[u] = steps[curr] + 1;
                int f_u = steps[u] + h(u, t);
                q.push(-f_u, u);
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int t;
    cin >> t;
    int num;

    for (int l = 0; l < n; ++l) {
        cin >> num;
        proibidas[num] = true;
    }

    cout << a_star(0, t) << endl;
}
