#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> freq(6050, 0);
    vector<bool> sum(12050, false);
    vector<int> v;

    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        freq[temp + 3000]++;

        if (freq[temp + 3000] <= 4) {
            v.push_back(temp);
        }
    }

    for (int j = 0; j < v.size(); j++) {
        for (int k = j + 1; k < v.size(); k++) {
            int soma = v[j] + v[k], complemento = -soma;

            if (sum[complemento + 6000]) {
                cout << "Sim" << '\n';
                return 0;
            }
        }

        for (int i = 0; i < j; i++) {
            int soma = v[i] + v[j];
            sum[soma + 6000] = true;
        }
    }

    cout << "Nao" << '\n';
}
