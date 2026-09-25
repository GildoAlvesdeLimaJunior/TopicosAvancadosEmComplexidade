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
    unordered_map<char, int> mp;
    int indices = 0;

    for (auto x : r) {
      mp[x]--;
    }

    int e = 0, d = r.size() - 1;

    for (int i = e; i <= d; i++) {
      mp[s[i]]++;
    }

    while (d < s.size()) {
      bool pode = true;

      for (auto x : mp) {
        if (x.second != 0) {
          pode = false;
          break;
        }
      }

      if (pode) {
        cout << e << '\n';
        indices++;
      }

      mp[s[e]]--;
      mp[s[d + 1]]++;

      e++, d++;
    }

    if (indices == 0) {
      cout << "Nao\n";
    }
  }
}
