#include <iostream>
#include <vector>

using namespace std;
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

        data[0] = data.back();
        data.pop_back();

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
}
