#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

// [1, 2, 3, 4]
// 1 + 2, 1 + 3, 1 + 4

vi half_ssum(vi &v, int b, int e) {
    vi sums = {0};
    for (long long x : v) {
        int n = sums.size();
        for (int i = 0; i < n; i++) {
            sums.push_back(sums[i] + x);
        }
    }
    return sums;
}

int main() {
    int n, k;
    cin >> n >> k;
    vi v(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    vi f = half_ssum(v, 0, n / 2);
    vi s = half_ssum(v, n / 2 + 1, n);

    f.insert(f.end(), s.begin(), s.end());

    unordered_map<int, int> freq;
    vi rsp = {};

    for (int i = 0; i < n; i++) {
        if (auto it = freq.find(k - f[i]); it != freq.end()) {
            rsp.push_back(i);
            rsp.push_back(freq[k - f[i]]);
        }
        freq[f[i]] = i;
    }

    rsp.empty() ? cout << "NÃO\n" : cout << "SIM\n";
}
