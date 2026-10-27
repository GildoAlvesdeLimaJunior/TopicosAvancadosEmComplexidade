#include <bits/stdc++.h>
using namespace std;

int n = 4, m = 4;
using vi = vector<int>;

// cima, baixo, esquerda, direita
vi dx = {-1, 1, 0, 0};
vi dy = {0, 0, -1, 1};

vector<string> grid = {"..#.", ".#..", "...#", "#..."};

int main() {
    pair<int, int> initial_pos = {1, 1};

    for (int i = 0; i < 4; i++) {
        auto nx = initial_pos.first;
        auto ny = initial_pos.second;

        nx += dx[i];
        ny += dy[i];

        if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            continue;

        if (grid[nx][ny] == '#')
            continue;
    }
}
