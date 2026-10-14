#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;

// A controled pair (i, j) is such that ind1[i] - ind2[i] <= ind1[j] - ind2[j] + d, d >= 0

inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void first_merge_sort(int l, int r, vector<ll> &a, vector<ll> &aux, vector<pll> &ijpair) {
    if (r - l <= 1) {
        return;
    }

    int mid = l + (r - l) / 2;

    ijpair.clear();

    first_merge_sort(l, mid, a, aux, ijpair);
    first_merge_sort(mid, r, a, aux, ijpair);

    int p = l;
    for (int j = mid; j < r; j++) {
        while (p < mid && a[p] < a[j]) {
            p++;
        }
        // [2, 3, 4, 5] [4, 10, 12, 10000]
        //  i            j
        //     i         j
        //        i      j
        // => {4, 2} == {a[j], p-l}
        //        i          j
        //            i      j
        // => ijpair.pb{10, 4}, {12, 4}, {10.000, 4}
        // => ijpair.pb{a[k], p-l} for k E [j, r]
        // => ijpair.pb{a[k], a[k] * k} for K E [j, r]
        //
        for (int k = j; k < r; k++) {
            ijpair.push_back({a[k], p - l});
        }
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
}

void second_merge_sort(int l, int r, vector<ll> &a, vector<ll> &aux, vector<pll> &ijpair) {
    if (r - l <= 1) {
        return;
    }

    int mid = l + (r - l) / 2;

    ijpair.clear();

    first_merge_sort(l, mid, a, aux, ijpair);
    first_merge_sort(mid, r, a, aux, ijpair);

    int p = l;
    for (int j = mid; j < r; j++) {
        while (p < mid && a[p] < a[j]) {
            p++;
        }
        // [2, 3, 4, 5] [4, 10, 12, 10000]
        //  i            j
        //     i         j
        //        i      j
        // => {4, 2} == {a[j], p-l}
        //        i          j
        //            i      j
        // => ijpair.pb{10, 4}, {12, 4}, {10.000, 4}
        // => ijpair.pb{a[k], p-l} for k E [j, r]
        // => ijpair.pb{a[k], a[k] * k} for K E [j, r]
        //
        for (int k = j; k < r; k++) {
            ijpair.push_back({a[k], p - l});
        }
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
}

int main() {
    fastIO();
    int n;
    vector<ll> a(n, 0);
    vector<ll> aux(n, 0);
    vector<pll> ijpair;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l = 0, r = n;
    first_merge_sort(l, r, a, aux, ijpair);
    second_merge_sort(l, r, a, aux, ijpair);
}
