#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>

#define LIMN 2000
#define INF 2'000'000'000
#define ENCODE(r,c,n) ((r)*(n) + (c))
#define DECODE(pos,r,c,n) c = (pos)%(n); r = (pos)/(n)

using namespace std;

void neighbors(int pos, int n, vector<int> &ret){
    int r, c;
    bool f1 = true,f2 = true;
    DECODE(pos,r,c,n);
    if(r < n-1){
        ret.push_back(ENCODE(r+1,c,n));
        if(c < n-1){
            ret.push_back(ENCODE(r,c+1,n));
            ret.push_back(ENCODE(r+1,c+1,n));
            f1 = false;
        } if (c > 0){
            ret.push_back(ENCODE(r,c-1,n));
            ret.push_back(ENCODE(r+1,c-1,n));
            f2 = false;
        }
    } if (r > 0){
        ret.push_back(ENCODE(r-1,c,n));
        if(c < n-1){
            ret.push_back(ENCODE(r-1,c+1,n));
            if(f1)
                ret.push_back(ENCODE(r,c+1,n));
        } if (c > 0){
            ret.push_back(ENCODE(r-1,c-1,n));
            if(f2)
                ret.push_back(ENCODE(r,c-1,n));
        }
    }
}

int diff(int poss,int post, int n){
    int rs, cs, rt,ct;
    DECODE(poss,rs,cs,n);
    DECODE(post,rt,ct,n);
    return max(abs(rs-rt), abs(cs-ct));
}

typedef struct{
    int priority,pos;
} node;

typedef struct{
    node elems[LIMN*LIMN];
    int map_elem[LIMN*LIMN];
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
    vector<int> dist(LIMN*LIMN,INF);
    int n,A[LIMN][LIMN];
    cin >> n;
    const int target = ENCODE(n-1,n-1,n);
    for(int i=0;i < n;++i){
        for(int j=0;j < n;++j)
            cin >> A[i][j];
    }
    heap h;
    make_empty_heap(h);
    push_heap(h,0,n-1);
    dist[0] = 0;
    while (h.size > 0){
        int curr_pos = pop_heap(h);
        int curr_r,curr_c;
        DECODE(curr_pos,curr_r,curr_c, n);
        if (curr_pos == target){
            cout << dist[curr_pos] << endl;
            return 0;
        }
        int curr_A = A[curr_r][curr_c];
        vector<int> ng;
        neighbors(curr_pos,n,ng);
        for(int pos:ng){
            int pos_r,pos_c;
            int new_distance = dist[curr_pos] + 1;
            DECODE(pos,pos_r,pos_c, n);
            if (curr_A >= A[pos_r][pos_c] && dist[pos] > new_distance){
                int heur = diff(pos,target,n)+new_distance;
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