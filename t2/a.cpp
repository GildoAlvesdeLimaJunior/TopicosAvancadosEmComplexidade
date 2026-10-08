#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
using namespace std;

// Um array eh k-bacana se existem k elementos de a maiores ou iguais a k.
//
// ex:
//
// 1-bacana:
// 0 0 0 0 0 0 2
//
// 2-bacana:
// 0 2 2
//
// 5-bacana:
// 0 1 3 6 7 9 9 10

int eh_k_bacana(int k, vector<int> &a) {
    int n = a.size();
    int l = 0, r = n;

    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] >= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    int cnt = n - l;

    // k bacana
    if (cnt == k)
        return 1;

    // eh k1 bacana pra k1 < k
    if (cnt < k)
        return 2;

    // eh k1 bacana pra k1 > k
    return 3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l, r, asn, k;
    l = 0, r = n;
    asn = -1;

    while (l <= r) {
        int k = l + (r - l) / 2;

        if (eh_k_bacana(k, a) == 1) {
            asn = k;
            break;
        }

        else if (eh_k_bacana(k, a) == 2) {
            r = k - 1;
        }

        else {
            l = k + 1;
        }
    }
    cout << asn << '\n';
}
