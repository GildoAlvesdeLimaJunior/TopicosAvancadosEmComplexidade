#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string r, s;
    cin >> r >> s;

    if (r.size() > s.size()) {
        cout << "Nao\n";
        return 0;
    } else {
        vector<int> mp(26, 0);
        int indices = 0;

        for (auto x : r) {
            mp[x - 'a']--;
        }

        int e = 0, d = r.size() - 1;

        for (int i = e; i <= d; i++) {
            mp[s[i] - 'a']++;
        }

        while (d < s.size() - 1) {
            bool pode = true;

            for (auto x : mp) {
                if (x != 0) {
                    pode = false;
                    break;
                }
            }

            if (pode) {
                cout << e << '\n';
                indices++;
            }

            mp[s[e] - 'a']--;
            mp[s[d + 1] - 'a']++;

            e++, d++;
        }

        bool pode = true;

        for (auto x : mp) {
            if (x != 0) {
                pode = false;
                break;
            }
        }

        if (pode) {
            cout << e << '\n';
            indices++;
        }

        if (indices == 0) {
            cout << "Nao\n";
        }
    }
}
