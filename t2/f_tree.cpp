#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/container_base_dispatch.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

using ordered_set = tree<pair<ll, int>, null_type, less<pair<ll, int>>, rb_tree_tag,
                         tree_order_statistics_node_update>;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n), L(n), R(n);
    for (auto &x : a)
        cin >> x;

    ordered_set bst;

    for (int j = 0; j < n; j++) {
        L[j] = bst.order_of_key({a[j], -1});
        bst.insert({a[j], j});
    }

    bst.clear();

    for (int j = n - 1; j >= 0; j--) {
        R[j] = bst.size() - bst.order_of_key({a[j], n});
        bst.insert({a[j], j});
    }

    ll asn = 0;
    for (int j = 0; j < n; j++) {
        asn += L[j] * R[j];
    }

    cout << asn << '\n';
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
        cout << endl;
    }
}
