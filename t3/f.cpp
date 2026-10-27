#include <iostream>
#include <vector>

using namespace std;
<<<<<<< HEAD
using vc = vector<char>;
using vi = vector<int>;
using ll = long long;

int n, m;

const int MAXN = 200;
const int INF = (ll)1e9 + 1;

vi d(MAXN, INF);
vc A[MAXN];

struct PriorityQueue {
    struct Node {
        int vertex;
        int priority;
    };

    vector<Node> data;

    void push(int vertex, int priority) {
        data.push_back({vertex, priority});

        int i = (int)data.size() - 1;

        while (i > 0) {
            int parent = (i - 1) / 2;

            if (data[parent].priority <= data[i].priority)
                break;

            swap(data[parent], data[i]);
            i = parent;
        }
    }

    void pop() {
        if (empty())
            return;
=======

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
>>>>>>> f2a9d37 (F altamente seboso)

        data[0] = data.back();
        data.pop_back();

<<<<<<< HEAD
        int n = (int)data.size();
        int i = 0;

        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && data[left].priority < data[smallest].priority)
                smallest = left;

            if (right < n && data[right].priority < data[smallest].priority)
                smallest = right;

            if (smallest == i)
                break;

            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

    int front() const {
        return data[0].vertex;
    }

    int priority() const {
        return data[0].priority;
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

template <typename Heuristic> void a_star(int source, int destiny, Heuristic h) {
}

// cima, baixo, esquerda, direita
vi dx = {-1, 1, 0, 0};
vi dy = {0, 0, -1, 1};

void print_mat() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << A[i][j];
            cnt++;
        }
        if (cnt % m == 0) {
            cout << '\n';
        }
    }
}

// Número de empurrões != número de movimentos.
// Primeira ideia: Uma busca para encontrar a caixa de uma direção empurrável -> Empurrar a caixa.
// Se a caixa continuar numa posição empurrável, empurrar novamente. A direção a qual a caixa deve
// ser empurrada tem que ser calculada com BFS / A*

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string l;
        cin >> l;

        for (int c = 0; c < l.size(); c++) {
            A[i].push_back(l[c]);
        }
    }

    // encontra o menor caminho até a caixa

    print_mat();
=======
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
    q.push(posd);
    dist[posd.first][posd.second] = 0;

    while (!q.empty()) {
        pairi top = q.front();
        q.pop();

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            pairi actual = {top.first + dx[i], top.second + dy[i]};

            if (actual.first >= 0 && actual.first < n && actual.second >= 0 && actual.second < m &&
                mapa[actual.first][actual.second] != '#' &&
                dist[actual.first][actual.second] == -1) {
                dist[actual.first][actual.second] = dist[top.first][top.second] + 1;
                q.push(actual);
            }
        }
    }

    for (auto x : mapa) {
        for (auto y : x) {
            cout << y;
        }
        cout << '\n';
    }
    for (auto x : dist) {
        for (auto y : x) {
            cout << y;
        }
        cout << '\n';
    }
>>>>>>> f2a9d37 (F altamente seboso)
}
