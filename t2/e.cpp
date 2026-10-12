#include <bits/stdc++.h>
#include <iterator>
#include <vector>
using namespace std;
int main() {
    long long maxn = 5e8;
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        v[i] += i * maxn;
    }
    sort(v.begin(), v.end());

    for (auto e : v) {
        cout << e << " ";
    }
    cout << endl;
}
