#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
// Não usar #include <cstdio> pra n bagunçar com a putaria do in/out do C

using namespace std;

typedef long long ll;

// Revisão:
// Para esta lista, apenas as seguintes bibliotecas estão autorizadas a serem incluídas:
//    vector
//    iostream
//    cstdio
//    string
//    algorithm

// As funções abaixo estão proibidas de serem utilizadas (estando ou não nas bibliotecas acima):
//     find() e rfind() das bibliotecas string e string_view
//     search(),
//     search_n() e
//     find_end() da biblioteca algorithm
//     strstr() e memmem()

bool z_function(const string &s, int bSize) {
    int n = s.size();
    vector<int> z(n, 0);

    int l = 0, r = 0; // janela [l , r )

    for (int i = 1; i < n; i++) {
        if (i < r)                       // dentro da janela
            z[i] = min(r - i, z[i - l]); // espelho

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i]; // estende comparando

        if (i + z[i] > r) { // enxergou mais longe ?
            l = i;          // nova janela
            r = i + z[i];
        }

        if (i >= bSize && z[i] == bSize) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string a, b;
    cin >> a >> b;

    if (b == a) {
        cout << 1 << '\n';
        return 0;
    }

    int razao = b.size() / a.size();
    bool sobra = (b.size() % a.size()) != 0;

    string c;

    if (sobra == 0) {
        c.reserve(a.size() * (razao + 1));

        for (int i = 0; i < razao; i++) {
            c += a;
        }

        if (c == b) {
            cout << razao << '\n';
        } else {
            c += a;

            string d;
            d.reserve(c.size() + b.size() + 1);
            d += b, d += '0', d += c;

            if (z_function(d, b.size())) {
                cout << razao + 1 << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    } else {
        c.reserve(a.size() * (razao + 2));

        for (int i = 0; i < razao + 1; i++) {
            c += a;
        }

        string d;
        d.reserve(c.size() + b.size() + 1);
        d += b, d += '0', d += c;

        if (z_function(d, b.size())) {
            cout << razao + 1 << '\n';
        } else {
            d += a;

            if (z_function(d, b.size())) {
                cout << razao + 2 << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}
