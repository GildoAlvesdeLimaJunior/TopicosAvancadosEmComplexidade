#include <algorithm>
#include <bits/stdc++.h>
#include <numeric>
#include <pthread.h>
using namespace std;
using ll = long long;

// There is just one ship for all containers, it implies that we need to max the number of
// containers done in one trip.
// If i<j, the container (i) can't be done before the container (j). It implies that i can't sort
// them. (I)
// I should return the value of the minimum capacity of a ship that can done n containers
// in k days or less.
//
// Example:
// 5 2
// 13 10 7 5 15
//
// We must deliver 5 containers in 2 days max.
//
// Rsp: A ship with cap = 27 can do this job
// 13 + 15 = 27 on the first day
// 10 + 7 + 5 = 27 on the last day
//
// Solution: Binary search on the ship capacity.
// Ex:
// Possible capacities: [1, 2, 3, ..., sum(w)]
//
// m = (1 + sum(w)) / 2
// If we can solve the problem with m in k days, => Go find the minimum m.
//
// It works because the answers have a natural order => If i can solve the problem in k days with m
// ship capacity, i can solve it with more capacity.
//
// The question is: Can i sort them or the (I) point don't let it happen?

namespace ope {
ll sum(vector<ll> &w) {
    ll sum = 0;
    for (auto x : w) {
        sum += x;
    }
    return sum;
}

ll max(vector<ll> &w) {
    ll max = w[1];
    auto sz = w.size();
    for (int i = 0; i < sz; i++) {
        if (w[i] > max) {
            max = w[i];
        }
    }
    return max;
}
} // namespace ope

// This function should check if a ship with capacity m can deliver n containers in k days or
// less.
// Ex:
// want to check if a ship with cap = 27 can deliver the containers [13, 10, 7, 5, 15] in k days or
// less
//
// Firstly, we sort it in descending order.
// [15, 13, 10, 7, 5, 15]
//
// for i in range(0, k):
//     while cap <= m: fill the ship
//  if there is left containers return false else return true

bool solve(vector<ll> &w, int m, int k) {
    int days = 1;
    ll cap = 0;

    for (auto weight : w) {
        if (weight > m) {
            return false;
        }
        if (cap + weight > m) {
            days++;
            cap = weight;
        } else {
            cap += weight;
        }
    }
    if (days > k) {
        return false;
    }
    return true;
}

inline void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

int main() {
    fastIO();

    int n, k;
    cin >> n >> k;

    vector<ll> w(n, 0);

    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    int l = ope::max(w);
    int r = ope::sum(w);

    while (l < r) {
        int m = l + (r - l) / 2;
        if (solve(w, m, k)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << "\n";
}
