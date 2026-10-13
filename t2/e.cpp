#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
using ll = long long;

// par triplamente controlado => ind[i] <= 3 * ind[j]
// [8 15 2 5]
// [8 15] [2 5]
// [8] [15] [2] [5]
// aux =
//

ll merge_sort(int l, int r, vector<ll> &a, vector<ll> &aux) {
    if (r - l <= 1) {
        return 0;
    }

    int mid = l + (r - l) / 2;

    ll cnt = 0;
    cnt += merge_sort(l, mid, a, aux);
    cnt += merge_sort(mid, r, a, aux);

    int p = l;

    for (int j = mid; j < r; j++) {
        while (p < mid && a[p] <= 3 * a[j]) {
            p++;
        }
        cnt += p - l;
    }

    int i = l;
    int j = mid;
    int k = l;

    while (i < mid && j < r) {
        if (a[i] <= a[j]) {
            aux[k++] = a[i++];
        } else {
            aux[k++] = a[j++];
        }
    }

    while (i < mid) {
        aux[k++] = a[i++];
    }

    while (j < r) {
        aux[k++] = a[j++];
    }

    for (int x = l; x < r; x++) {
        a[x] = aux[x];
    }

    return cnt;
}

int main() {
    int n;
    cin >> n;
    vector<ll> ind(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> ind[i];
    }
    vector<ll> aux(n, 0);
    int l = 0, r = n;
    ll rsp = merge_sort(l, r, ind, aux);
    ll total = n * (n - 1) / 2;
    cout << total - rsp;
}
