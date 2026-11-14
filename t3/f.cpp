#include <iostream>
#include <vector>

using namespace std;

struct pairi {
    int first;
    int second;
};

struct state {
    pairi player;
    pairi box;
};

struct Queue {
    vector<pairi> data;
    size_t head = 0;

    void push(pairi x) {
        data.push_back(x);
    }

    void pop() {
        if (!empty())
            head++;
    }

    pairi front() {
        return data[head];
    }

    bool empty() {
        return head == data.size();
    }

    size_t size() {
        return data.size() - head;
    }

    void clear() {
        data.clear();
        head = 0;
    }
};

struct PriorityQueue {
    vector<pairi> data;

    void arrangeUp(int i) {
        while (i > 0) {
            int pai = (i - 1) / 2;

            if (data[i].first < data[pai].first) {
                swap(data[i], data[pai]);
                i = pai;
            } else {
                break;
            }
        }
    }

    void arrangeDown(int i) {
        while (2 * i + 1 < data.size()) {
            int left = 2 * i + 1;
            int rigth = 2 * i + 2;
            int less = left;

            if (rigth < data.size() && data[rigth].first < data[left].first) {
                less = rigth;
            }

            if (data[less].first < data[i].first) {
                swap(data[i], data[less]);
                i = less;
            } else {
                break;
            }
        }
    }

    void push(int idx, int valor) {
        pairi temp;
        temp.first = idx;
        temp.second = valor;
        data.push_back(temp);
        arrangeUp(data.size() - 1);
    }

    void pop() {
        if (data.size() == 0) {
            cout << "Fila de Prioridade vazia";
            return;
        }

        data[0] = data.back();
        data.pop_back();

        if (data.size() != 0) {
            arrangeDown(0);
        }
    }

    int size() {
        return data.size();
    }

    pairi top() {
        return data[0];
    }

    bool isEmpty() {
        return data.empty();
    };
};

int heuristica(const vector<vector<int>> &dist, pairi caixa) {
    return dist[caixa.first][caixa.second];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> mapa(n, vector<char>(m));
    vector<vector<int>> dist(n, vector<int>(m, -1));
    vector<vector<int>> empuradas(n, vector<int>(m, -1));
    vector<vector<pairi>> caba_pos(n, vector<pairi>(m));
    pairi posc, posm, posd;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mapa[i][j];

            if (mapa[i][j] == 'C') {
                posc = {i, j};
            } else if (mapa[i][j] == 'M') {
                posm = {i, j};
            } else if (mapa[i][j] == 'D') {
                posd = {i, j};
            }
        }
    }

    Queue q;
    q.push(posm);
    dist[posm.first][posm.second] = 0;
    caba_pos[posm.first][posm.second] = posc;

    vector<vector<int>> vis_caba(n, vector<int>(m, 0));
    int token_caba = 0;
    Queue pq;

    while (!q.empty()) {
        pairi top = q.front();
        q.pop();

        if (top.first == posd.first && top.second == posd.second) {
            break;
        }

        pairi caba_atual = caba_pos[top.first][top.second];

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            pairi actual = {top.first + dx[i], top.second + dy[i]};

            pairi required = {top.first - dx[i], top.second - dy[i]};

            if (actual.first >= 0 && actual.first < n && actual.second >= 0 && actual.second < m &&
                mapa[actual.first][actual.second] != '#' &&
                dist[actual.first][actual.second] == -1 && required.first >= 0 &&
                required.first < n && required.second >= 0 && required.second < m &&
                mapa[required.first][required.second] != '#') {

                bool possible = false;
                token_caba++;
                pq.clear();

                pq.push(caba_atual);
                vis_caba[caba_atual.first][caba_atual.second] = token_caba;

                while (!pq.empty()) {
                    pairi top2 = pq.front();
                    pq.pop();

                    if (top2.first == required.first && top2.second == required.second) {
                        possible = true;
                        break;
                    }

                    for (int j = 0; j < 4; j++) {
                        pairi actual2 = {top2.first + dx[j], top2.second + dy[j]};

                        bool is_not_box =
                            !(actual2.first == top.first && actual2.second == top.second);

                        if (actual2.first >= 0 && actual2.first < n && actual2.second >= 0 &&
                            actual2.second < m && mapa[actual2.first][actual2.second] != '#' &&
                            is_not_box && vis_caba[actual2.first][actual2.second] != token_caba) {

                            vis_caba[actual2.first][actual2.second] = token_caba;
                            pq.push(actual2);
                        }
                    }
                }

                if (possible) {
                    dist[actual.first][actual.second] = dist[top.first][top.second] + 1;
                    q.push(actual);
                    caba_pos[actual.first][actual.second] = top;
                }
            }
        }
    }

    if (dist[posd.first][posd.second] == -1) {
        cout << -1 << '\n';
    } else {
        cout << dist[posd.first][posd.second] << '\n';
    }

    return 0;
}
