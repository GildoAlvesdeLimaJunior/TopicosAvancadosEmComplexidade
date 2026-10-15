#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Element {
    ll val;
    int orig_idx;
};

// par triplamente controlado => ind[i] <= 3 * ind[j]
// [8 15 2 5]
// [8 15] [2 5]
// [8] [15] [2] [5]

// [10, 11, 12] [15, 20, 30] [40, 50, 60]
//  i            j            k

// [x, ..., xk, ..., xn] = v
//  i, ..., ik, ..., in
//  for j in v v[j] = k if j > k on {j, k}

void merge_sort(int l, int r, vector<Element> &a, vector<Element> &aux, vector<ll> &left_cnt,
                vector<ll> &right_cnt) {
    if (r - l <= 1) {
        return;
    }

    int mid = l + (r - l) / 2;
    merge_sort(l, mid, a, aux, left_cnt, right_cnt);
    merge_sort(mid, r, a, aux, left_cnt, right_cnt);

    int i = l;
    for (int j = mid; j < r; j++) {
        while (i < mid && a[i].val < a[j].val) {
            i++;
        }
        left_cnt[a[j].orig_idx] += (i - l);
    }

    int j = mid;
    for (int p = l; p < mid; p++) {
        while (j < r && a[j].val <= a[p].val) {
            j++;
        }
        right_cnt[a[p].orig_idx] += (r - j);
    }

    i = l;
    j = mid;
    int x = l;
    while (i < mid || j < r) {
        if (i < mid && (j >= r || a[i].val <= a[j].val)) {
            aux[x++] = a[i++];
        } else {
            aux[x++] = a[j++];
        }
    }

    for (int p = l; p < r; p++) {
        a[p] = aux[p];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n))
        return 0;

    vector<Element> a(n), aux(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].val;
        a[i].orig_idx = i;
    }

    vector<ll> left_cnt(n, 0), right_cnt(n, 0);
    merge_sort(0, n, a, aux, left_cnt, right_cnt);

    ll total_triplets = 0;
    for (int i = 0; i < n; i++) {
        total_triplets += left_cnt[i] * right_cnt[i];
    }

    cout << total_triplets << "\n";
    return 0;
}
