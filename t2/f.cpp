#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main() {
    long long maxn = 5e8;
    int n;
    cin >> n;
    vector<long long> v(n);
    vector<long long> v2(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        v2[i] = v[i];
        v[i] = v[i] + maxn * i;
    }

    sort(v.begin(), v.end());
    //    sort(v2.begin(), v2.end());

    // for (int i = 0; i < n - 1; ++i) {
    //     if (v[i] % maxn == v[i + 1] % maxn) {
    //         v[i + 1] = v[i];
    //     }
    // }
    for (auto e : v) {
        cout << e << " ";
    }
    cout << endl;
    // for (auto e : v2) {
    //     cout << e << " ";
    // }
}
