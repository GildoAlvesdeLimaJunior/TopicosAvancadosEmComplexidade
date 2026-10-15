#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

// [8 15 2 5]
// [8 15] [2 5]
// [8] [15] [2] [5]

// [10, 11, 12] [15, 20, 30] [40, 50, 60]
//  i            j            k

// [x, ..., xk, ..., xn] = v
//  i, ..., ik, ..., in
//  for j in v v[j] = k if j > k on {j, k}

void print_vec(vector<ll> &a) {
    for (auto &x : a) {
        cout << x << ' ';
    }
    cout << endl;
}

struct Node {
    ll value;
    ll left = 0;
    ll right = 0;
};

ll count_pair(int xl, int xr, int yl, int yr, vector<Node> &a) {
    ll cnt = 0;
    int p = xl;

    for (int y = yl; y < yr; y++) {
        while (p < xr && a[p].value < a[y].value) {
            p++;
        }
        ll smaller = p = xl;
        cnt += smaller * a[y].right;
        a[y].left += smaller;
    }

    int q = yl;

    for (int x = xl; x < xr; x++) {
        while (q < yr && a[q].value <= a[x].value)
            q++;

        ll greater = yr - q;

        cnt += a[x].left * greater;
        a[x].right += greater;
    }

    return cnt;
}

ll merge_sort(int l, int r, vector<Node> &a, vector<Node> &aux) {
    if (r - l <= 1)
        return 0;

    int m1 = l + (r - l) / 3;
    int m2 = l + 2 * (r - l) / 3;

    ll cnt = 0;

    cnt += merge_sort(l, m1, a, aux);
    cnt += merge_sort(m1, m2, a, aux);
    cnt += merge_sort(m2, r, a, aux);

    cnt += count_pair(l, m1, m1, m2, a);
    cnt += count_pair(l, m1, m2, r, a);
    cnt += count_pair(m1, m2, m2, r, a);

    int i = l;
    int j = m1;
    int k = m2;
    int x = l;

    while (i < m1 || j < m2 || k < r) {
        if (i < m1 && (j >= m2 || a[i].value <= a[j].value) &&
            (k >= r || a[i].value <= a[k].value)) {
            aux[x++] = a[i++];
        } else if (j < m2 && (k >= r || a[j].value <= a[k].value)) {
            aux[x++] = a[j++];
        } else {
            aux[x++] = a[k++];
        }
    }

    for (int p = l; p < r; p++)
        a[p] = aux[p];

    return cnt;
}

int main() {
    int n;
    cin >> n;
    vector<Node> a(n), aux(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i].value;
    }

    ll rsp = merge_sort(0, n, a, aux);
    cout << "Rsp: " << rsp << endl;
}
