#include <iostream>
#include <vector>

using namespace std;

vector<int> adj[int(1e6) + 5];
bool is_adj(int v1, int v2) {
    for (auto v : adj[v1]) {
        if (v == v2) {
            return true;
        }
    }
    return false;
}

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
vector<bool> proibidas(1e6);

int main() {
    int n;
    cin >> n;
    int t;
    cin >> t;
    int num;

    for (int l = 0; l < n; ++l) {
        cin >> num;
        proibidas[num] = true;
    }

    for (int i = 0; i < 1e6; ++i) {
        int temp = i;
        for (int k = 1; k < 1e6; k *= 10) {
            int d = temp % 10;
            if (d == 0) {
                if (!proibidas[i] && !proibidas[i + 9 * k]) {
                    adj[i].push_back(i + 9 * k);
                }

            } else {
                if (!proibidas[i] && !proibidas[i - k]) {
                    adj[i].push_back(i - k);
                }
            }
            if (d == 9) {
                if (!proibidas[i] && !proibidas[i - 9 * k]) {
                    adj[i].push_back(i - 9 * k);
                }

            } else {
                if (!proibidas[i] && !proibidas[i + k]) {
                    adj[i].push_back(i + k);
                }
            }

            temp /= 10;
        }
    }

    while (true) {
        int v1, v2;
        cin >> v1 >> v2;
        for (auto v : adj[v1]) {
            cout << v << endl;
        }
        cout << is_adj(v1, v2) << endl;
    }
}
