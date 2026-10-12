#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// A controled pair (i, j) is such that ind1[i] - ind2[i] <= ind1[j] - ind2[j] + d, d >= 0

inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

ll merge_sort(int l, int r, vector<ll> &a, vector<ll> &aux, ll d) {
    if (r - l <= 1) {
        return 0;
    }

    int mid = l + (r - l) / 2;

    ll cnt = 0;
    cnt += merge_sort(l, mid, a, aux, d);
    cnt += merge_sort(mid, r, a, aux, d);

    int p = l;
    for (int j = mid; j < r; j++) {
        while (p < mid && a[p] <= a[j] + d) {
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
    fastIO();

    int n;
    ll d;
    cin >> n >> d;

    vector<ll> ind1(n, 0);
    vector<ll> ind2(n, 0);
    vector<ll> a(n, 0);
    vector<ll> aux(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> ind1[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> ind2[i];
    }

    for (int i = 0; i < n; i++) {
        a[i] = ind1[i] - ind2[i];
    }

    int l = 0, r = n;
    auto rsp = merge_sort(l, r, a, aux, d);
    cout << rsp << '\n';
}
