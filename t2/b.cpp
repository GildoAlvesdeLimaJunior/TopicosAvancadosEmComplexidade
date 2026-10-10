#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

long long sum(vector<long long> &v) {
    int sum = 0;
    for (auto x : v) {
        sum += x;
    }
    return sum;
}

// Example:
// 4 1 2 1
// 1 5 2 2
// After sort:
//
// 1 1 2 4
// i
// 1 2 2 5
// j
//
// Trying to swap..
// suma keeps < sumb. so, i should increase somea increasing j
// 1 1 2 4
// i
// 1 2 2 5
//   j
// if i swap, suma = 9 and sumb = 9
// it implies that - If suma < sumb => j++, else i++
//
// 2 1 1 3 7 4
// 1 1 2 4
//
//

int main() {
    int n;
    cin >> n;
    vector<long long> a(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    long long a_sum = sum(a);

    int m;
    cin >> m;
    vector<long long> b(n, 0);

    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(b.begin(), b.end());
    long long b_sum = sum(b);

    int i = 0, j = 0;

    while (true) {
        pair<int, int> rsp = {i, j};

        auto ai = a[i];
        auto bj = b[j];

        if ((a_sum - ai + bj) == (b_sum - bj + ai)) {
            cout << a[rsp.first] << ' ' << b[rsp.second] << '\n';
            break;
        } else if ((a_sum - ai + bj) <= (b_sum - bj + ai)) {
            j++;
        } else {
            i++;
        }
    }
}
