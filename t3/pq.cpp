#include <iostream>
#include <vector>

using namespace std;

struct PriorityQueue {
    vector<int> data;

    void arrangeUp(int i) {
        while (i > 0) {
            int pai = (i - 1) / 2;

            if (data[i] < data[pai]) {
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

            if (rigth < data.size() && data[rigth] < data[left]) {
                less = rigth;
            }

            if (data[less] < data[i]) {
                swap(data[i], data[less]);
            } else {
                break;
            }
        }
    }

    void push(int valor) {
        data.push_back(valor);
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

    int top() {
        return data[0];
    }

    bool isEmpty() {
        return data.empty();
    };
};
