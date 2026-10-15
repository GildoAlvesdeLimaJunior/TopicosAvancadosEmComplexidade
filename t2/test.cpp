#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    map<int, int> mp;

    for (int i = 0; i < 10; i++) {
        mp[i] = i * i;
    }

    for (int i = 0; i < 10; i++) {
        cout << mp[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < 10; i++) {
        mp[i] = i;
    }

    for (int i = 0; i < 10; i++) {
        cout << mp[i] << " ";
    }
    cout << endl;

    return 0;
}
