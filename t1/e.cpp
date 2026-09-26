#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int k = 4;
    unordered_map<int, int> map;
    vector<int> v(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        map[v[i]] = map[v[i]] ? map[v[i]] + 1 : 1;
    }
    int duplas_que_anulam = 0;
    int trios_que_anulam = 0;
    for (auto e : map) {
        if (map[-e.first]) {
            duplas_que_anulam++;
            if (map[e.first] == 3) {
                trios_que_anulam++;
            }
        }
    }
    for (auto e : map) {
        cout << " " << e.first << " " << e.second << endl;
    }
    if (duplas_que_anulam >= 2 || trios_que_anulam) {

        cout << "Sim" << endl;
    }
}
