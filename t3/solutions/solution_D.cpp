#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

#define LIMPOS 1'000'000
#define INF 2'000'000'000

using namespace std;

void neighbors(int pos, vector<int> &ret){
    int aux_pos = pos;
    int pot = 1;
    while(pot <= 100'000){
        int x = aux_pos%10;
        aux_pos /= 10;
        if(x < 9)
            ret.push_back(pos+pot);
        else
            ret.push_back(pos-9*pot);
        if(x > 0)
            ret.push_back(pos-pot);
        else
            ret.push_back(pos+9*pot);
        pot *= 10;
    }
}

int diff(int s, int t){
    int acum = 0;
    while(s > 0 || t > 0){
        int x = abs((s%10) - (t%10));
        s /= 10;
        t /= 10;
        acum += (x <= 5 ? x : 10-x);
    }
    return acum;
}

typedef struct{
    int priority,pos;
} node;

typedef struct{
    node elems[LIMPOS];
    int map_elem[LIMPOS];
    int size;
} heap;

void make_empty_heap(heap &h){
    h.size=0;
}

void push_heap(heap &h, int pos, int priority){
    int ind = h.size;
    int indp = (ind-1)/2;
    while(ind > 0 && h.elems[indp].priority > priority){
        h.elems[ind] = h.elems[indp];
        h.map_elem[h.elems[indp].pos] = ind;
        ind = indp;
        indp = (ind-1)/2;
    }
    h.elems[ind].pos = pos;
    h.elems[ind].priority = priority;
    h.map_elem[pos] = ind;
    ++h.size;
}

int pop_heap(heap &h){
    int min_pos = h.elems[0].pos;
    node desc = h.elems[--h.size];
    int indp = 0, indf1 = 1, indf2 = 2;
    while(indf2 < h.size && (desc.priority > h.elems[indf1].priority || desc.priority > h.elems[indf2].priority)){
        int ind_next = h.elems[indf1].priority < h.elems[indf2].priority ? indf1 : indf2;
        h.elems[indp] = h.elems[ind_next];
        h.map_elem[h.elems[ind_next].pos] = indp;
        indp = ind_next;
        indf1 = 2*indp + 1;
        indf2 = 2*indp + 2;
    }
    if(indf1 < h.size && desc.priority > h.elems[indf1].priority){
        h.elems[indp] = h.elems[indf1];
        h.map_elem[h.elems[indf1].pos] = indp;
        indp = indf1;
    }
    h.elems[indp] = desc;
    h.map_elem[desc.pos] = indp;
    return min_pos;
}

void decrease_priority_heap(heap &h, int pos, int new_priority){
    int ind = h.map_elem[pos];
    int indp = (ind-1)/2;
    while(ind > 0 && h.elems[indp].priority > new_priority){
        h.elems[ind] = h.elems[indp];
        h.map_elem[h.elems[indp].pos] = ind;
        ind = indp;
        indp = (ind-1)/2;
    }
    h.elems[ind].pos = pos;
    h.elems[ind].priority = new_priority;
    h.map_elem[pos] = ind;
}

void print_heap(heap &h){
    for(int i=0;i < h.size;++i)
        cout << "(" << h.elems[i].priority << ", " << h.elems[i].pos << "), ";
    cout << endl;
}

        
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> dist(LIMPOS,INF);
    vector<bool> forbidden(LIMPOS,false);
    int n,t;
    cin >> n >> t;
    for(int i=0;i < n;++i){
        int forb_pos;
        cin >> forb_pos;
        if (forb_pos == 0 || forb_pos == t){
            cout << -1 << endl;
            fflush(stdout);
            return 0;
        }
        forbidden[forb_pos] = true;
    }
    heap h;
    make_empty_heap(h);
    push_heap(h,0,diff(0,t));
    dist[0] = 0;
    while (h.size > 0){
        int curr_pos = pop_heap(h);
        if (curr_pos == t){
            cout << dist[curr_pos] << endl;
            return 0;
        }
        vector<int> ng;
        neighbors(curr_pos,ng);
        for(int pos:ng){
            int new_distance = dist[curr_pos] + 1;
            if (!forbidden[pos] && dist[pos] > new_distance){
                int heur = diff(pos,t)+new_distance;
                if(dist[pos] < INF)
                    decrease_priority_heap(h,pos,heur);
                else
                    push_heap(h,pos,heur);
                dist[pos] = new_distance;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}