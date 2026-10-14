#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

// par triplamente controlado => ind[i] <= 3 * ind[j]
// [8 15 2 5]
// [8 15] [2 5]
// [8] [15] [2] [5]

// [10, 11, 12] [15, 20, 30] [40, 50, 60]
//  i            j            k

// [x, ..., xk, ..., xn] = v
//  i, ..., ik, ..., in
//  for j in v v[j] = k if j > k on {j, k}

const int MAXN = 100000;

void print_vec(vector<ll> &a) {
    for (auto &x : a) {
        cout << x << endl;
    }
}

ll merge_sort(int l, int r, vector<ll> &a, vector<ll> &aux, vector<pll> &jkpair) {
    if (r - l <= 1) {
        return 0;
    }

    const int mid = l + (r - l) / 2;
    ll cnt = 0;

    int mid1 = l + (r - l) / 3;
    int mid2 = l + 2 * (r - l) / 3;

    // merge sort em 3 partes
    cnt += merge_sort(l, mid1, a, aux, jkpair);
    cnt += merge_sort(mid1, mid2, a, aux, jkpair);
    cnt += merge_sort(mid2, r, a, aux, jkpair);

    int d = mid2;
    for (int c = mid1; c < mid2; c++) {
        while (d < r && a[c] > a[d]) {
            d++;
        }
        auto total = d - mid2;
        for (int i = c; c < mid2; c++) {
            jkpair[c] = {c, total};
        }
    }

    int c = mid1;
    for (int b = l; b < mid1; b++) {
        if (a[b] > a[c]) {
            c++;
        }
        auto total = mid2 - c;
        cnt += jkpair[c].second;
    }

    // v = [{c1, d1}, {c2, d2}, ...]
    // a[ck] < a[dk]

    int i = l;
    int j = mid1;
    int k = mid2;
    int x = l;

    while (i < mid1 || j < mid2 || k < r) {
        if (i < mid1 && (j >= mid2 || a[i] <= a[j]) && (k >= r || a[i] <= a[k])) {
            aux[x++] = a[i++];
        } else if (j < mid2 && (k >= r || a[j] <= a[k])) {
            aux[x++] = a[j++];
        } else {
            aux[x++] = a[k++];
        }
    }

    for (int p = l; p < r; p++) {
        a[p] = aux[p];
    }

    return cnt;
}

int main() {
    int n;
    cin >> n;
    vector<ll> ind(MAXN, 0);

    for (int i = 0; i < n; i++) {
        cin >> ind[i];
    }

    vector<ll> aux(n, 0);
    vector<pll> jkpair(MAXN);
    int l = 0, r = n;
    ll rsp = merge_sort(l, r, ind, aux, jkpair);
    cout << rsp << endl;
}
