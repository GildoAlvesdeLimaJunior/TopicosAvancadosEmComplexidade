#include <bits/stdc++.h>
#include <csignal>

using namespace std;

using i32 = int;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<i32> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    switch (k) {
    case 1: {
        bool tem0 = false;

        for (auto x : a) {
            if (x == 0) {
                tem0 = true;
            }
        }

        if (tem0) {
            cout << "Sim\n";
        } else {
            cout << "Nao\n";
        }

        return 0;
    }
    case 2: {
        vector<bool> nums(2005, false);

        for (auto x : a) {
            nums[x + 1000] = true;

            int complemento = -x;

            if (nums[complemento + 1000]) {
                cout << "Sim\n";
                return 0;
            }
        }

        cout << "Nao\n";
        return 0;
    }
    case 4: {
        vector<bool> sum(4005, false);

        for (int j = 0; j < a.size(); j++) {
            for (int i = 0; i <= j; i++) {
                int soma = a[i] + a[j];
                sum[soma + 2000] = true;
            }

            for (int l = j; l < a.size(); l++) {
                int soma = a[j] + a[l];
                int complemento = -soma;

                if (sum[complemento + 2000]) {
                    cout << "Sim\n";
                    return 0;
                }
            }
        }

        cout << "Nao\n";
        return 0;
    }

    case 8: {
    }
    }
}
