#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string r, s;
    cin >> r >> s;

    vector<int> mp(26, 0);

    if (r.size() != s.size()) {
        cout << "Nao\n";
        return 0;
    } else {
        for (int i = 0; i < r.size(); i++) {
            mp[r[i] - 'a']++;
            mp[s[i] - 'a']--;
        }
    }

    for (auto x : mp) {
        if (x != 0) {
            cout << "Nao\n";
            return 0;
        }
    }

    cout << "Sim\n";
}
