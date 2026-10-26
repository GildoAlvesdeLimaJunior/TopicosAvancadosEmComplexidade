#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> steps(1e6, 1e9 + 7);
vector<bool> vis(1e6, false);

vector<bool> proibidas(1e6);

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
    priority_queue<pair<int, int>> q;
    steps[start] = 0;
    int f = h(start, t);
    q.push({-f, start});
    while (!q.empty()) {
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
                q.push({-f_u, u});
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
                q.push({-f_u, u});
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
