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

vector<int> z_function(const string &s) {
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
    }
    return z;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
}
