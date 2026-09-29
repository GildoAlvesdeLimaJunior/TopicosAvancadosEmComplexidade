#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string r, s;
    cin >> r >> s;

    vector<int> ms(26, 0), mr(26, 0);

    if (r.size() > s.size()) {
        cout << "Nao\n";
        return 0;
    } else {
        for (int i = 0; i < r.size(); i++) {
            mr[r[i] - 'a']++;
            ms[s[i] - 'a']++;
        }

        if (mr == ms) {
            cout << "Sim\n";
            return 0;
        }

        for (int i = r.size(); i < s.size(); i++) {
            ms[s[i] - 'a']++;
            ms[s[i - r.size()] - 'a']--;

            if (mr == ms) {
                cout << "Sim\n";
                return 0;
            }
        }

        cout << "Nao\n";
    }
}
