#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  int trio = 0;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < n; i++) {

    int e = i + 1, d = n - 1;

    while (e < d) {
      int sum = a[i] + a[e] + a[d];

      if (!sum) {
        cout << i << " " << e << " " << d << '\n';

        e++, d--, trio++;

        while (e < d && a[e] == a[e - 1])
          e++;
        while (e < d && a[d] == a[d + 1])
          d--;
      } else if (sum > 0) {
        d--;
      } else {
        e++;
      }
    }
  }

  if (!trio) {
    cout << "Nao" << '\n';
  }
}
