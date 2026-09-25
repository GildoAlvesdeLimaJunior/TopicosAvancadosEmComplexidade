#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string r, s;
  cin >> r >> s;

  unordered_map<char, int> mp;

  if (r.size() != s.size()) {
    cout << "NAO\n";
    return 0;
  } else {
    for (int i = 0; i < r.size(); i++) {
      mp[r[i]]++;
      mp[s[i]]--;
    }
  }

  for (auto x : mp) {
    if (x.second != 0) {
      cout << "NAO\n";
      return 0;
    }
  }

  cout << "SIM\n";
}
