#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  string r, s;
  cin >> r >> s;

  unordered_map<char, int> ms, mr;

  if (r.size() > s.size()) {
    cout << "Nao\n";
    return 0;
  } else {
    for (auto x : s) {
      ms[x]++;
    }

    for (auto y : r) {
      mr[y]++;
    }

    for (auto z : mr) {
      char l = z.first;

      if (mr[l] - ms[l] != 0) {
        cout << "Nao\n";
        return 0;
      }
    }

    cout << "Sim\n";
  }
}
