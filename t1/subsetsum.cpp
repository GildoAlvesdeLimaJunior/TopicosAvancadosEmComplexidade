#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n, 0);
    vector<vector<bool>> l(n + 1, vector<bool>(k + 1, false));
    l[0][0] = true;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // não pegar
            l[i][j] = l[i - 1][j];

            // vendo o melhor entre pegar e não pegar
            if (j >= a[i - 1]) {
                l[i][j] = l[i][j] || l[i - 1][j - a[i - 1]];
            }
        }
    }

    auto rsp = l[n][k];
    rsp ? cout << "SIM\n" : cout << "NÃO\n";
}
