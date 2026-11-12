#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
 
#define LIMN 1000
#define INF 2'000'000'000
#define ENCODECEL(r,c,m) ((r)*m+c)
#define DECODECEL(pos,r,c,m) r=(pos)/m;c=(pos)%m
#define ENCODEPOS(r,c,rb,m) ((r)*m*4+(c)*4+(rb))
#define DECODEPOS(pos,r,c,rb,m) rb=(pos)%4;c=((pos)/4)%m;r=((pos)/4)/m
 
// rb = 0: robo acima da caixa
// rb = 1: robo a direita da caixa
// rb = 2: robo abaixo da caixa
// rb = 3: robo a esquerda da caixa
 
using namespace std;
 
int get_rb_cell(int merc_pos, int m){
    int rb_r, rb_c;
    int merc_r,merc_c,rb;
    DECODEPOS(merc_pos,merc_r,merc_c,rb,m);
    if(rb == 0){
        rb_r = merc_r-1;
        rb_c = merc_c; 
    } else if(rb == 1){
        rb_r = merc_r;
        rb_c = merc_c+1; 
    } else if(rb == 2){
        rb_r = merc_r+1;
        rb_c = merc_c; 
    } else{
        rb_r = merc_r;
        rb_c = merc_c-1;
    }
    return ENCODECEL(rb_r,rb_c,m);
}
 
void neighbors_cell(int r, int c, int n, int m, vector<int> &ret){
    if(r < n-1)
        ret.push_back(ENCODECEL(r+1,c,m));
    if (r > 0)
        ret.push_back(ENCODECEL(r-1,c,m));
    if (c > 0)
        ret.push_back(ENCODECEL(r,c-1,m));
    if (c < m-1)
        ret.push_back(ENCODECEL(r,c+1,m));
}
 
void neighbors_pos(int r, int c, int n, int m, vector<int> &ret){
    if(r < n-1 && r > 0){
        ret.push_back(ENCODEPOS(r+1,c,0,m));
        ret.push_back(ENCODEPOS(r-1,c,2,m));
    } if (c > 0 && c < m-1){
        ret.push_back(ENCODEPOS(r,c+1,3,m));
        ret.push_back(ENCODEPOS(r,c-1,1,m));
    }
}
 
int diff(int poss,int post, int m){
    int rs, cs, rt,ct;
    DECODECEL(poss,rs,cs,m);
    DECODECEL(post,rt,ct,m);
    return abs(rs-rt) + abs(cs-ct);
}
 
typedef struct{
    int priority,pos;
} node;
 
typedef struct{
    node elems[LIMN*LIMN*4];
    int map_elem[LIMN*LIMN*4];
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
 
bool isPossibleToGo(char A[LIMN][LIMN+2], int n, int m, int rb_org_cell, int merc_cell, int target_cell){
    int merc_r,merc_c;
    int target_r,target_c;
    DECODECEL(merc_cell,merc_r,merc_c,m);
    DECODECEL(target_cell,target_r,target_c,m);
    if(A[target_r][target_c] == '#' || (target_r == merc_r && target_c == merc_c))
        return false;
    vector<bool> visited(LIMN*LIMN,false);
    int queue[LIMN*LIMN],tail = 0,head = 0;
    queue[0] = rb_org_cell;
    visited[rb_org_cell] = true;
    int org_r,org_c;
    DECODECEL(rb_org_cell,org_r,org_c,m);
    while (tail - head + 1 > 0){
        int rb_cell = queue[head++];
        int rb_r,rb_c;
        if (rb_cell == target_cell)
            return true;
        DECODECEL(rb_cell,rb_r,rb_c,m);
        vector<int> ng;
        neighbors_cell(rb_r,rb_c,n,m,ng);
        for(int next_rb_cell:ng){
            int next_rb_r,next_rb_c;
            DECODECEL(next_rb_cell,next_rb_r,next_rb_c,m);
            if (A[next_rb_r][next_rb_c] == '.' && (next_rb_r != merc_r || next_rb_c != merc_c) && !visited[next_rb_cell]){
                visited[next_rb_cell] = true;
                queue[++tail] = next_rb_cell;
            }
        }
    }
    return false;
}
 
        
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int> dist(LIMN*LIMN*4,INF);
    int n,m,M_r,M_c,C_r,C_c;
    int C,M,D;
    char A[LIMN][LIMN+2];
    scanf("%d %d\n",&n,&m);
    for(int i=0;i < n;++i)
        fgets(A[i],m+2,stdin);
    for(int i=0;i < n;++i){
        for(int j=0;j < m;++j){
            if(A[i][j]=='C'){
                C = ENCODECEL(i,j,m);
                C_r = i;
                C_c = j;
                A[i][j] = '.';
            } else if(A[i][j]=='M'){
                M = ENCODECEL(i,j,m);
                M_r = i;
                M_c = j;
                A[i][j] = '.';
            } else if(A[i][j]=='D'){
                D = ENCODECEL(i,j,m);
                A[i][j] = '.';
            }
        }
    }
    heap h;
    make_empty_heap(h);        
    int difft = diff(M,D,m);
    if (M_r > 0){
        int cell_up = ENCODECEL(M_r-1,M_c,m);
        if (isPossibleToGo(A, n, m, C, M, cell_up)){
            int pos_up = ENCODEPOS(M_r,M_c,0,m);
            push_heap(h,pos_up,difft);
            dist[pos_up] = 0;
        }
    } if (M_c < m-1){
        int cell_right = ENCODECEL(M_r,M_c+1,m);
        if (isPossibleToGo(A, n, m, C, M, cell_right)){
            int pos_right = ENCODEPOS(M_r,M_c,1,m);
            push_heap(h,pos_right,difft);
            dist[pos_right] = 0;
        }
    } if (M_r < n-1){
        int cell_down = ENCODECEL(M_r+1,M_c,m);
        if (isPossibleToGo(A, n, m, C, M, cell_down)){
            int pos_down = ENCODEPOS(M_r,M_c,2,m);
            push_heap(h,pos_down,difft);
            dist[pos_down] = 0;
        }
    } if (M_c > 0){
        int cell_left = ENCODECEL(M_r,M_c-1,m);
        if(isPossibleToGo(A, n, m, C, M, cell_left)){
            int pos_left = ENCODEPOS(M_r,M_c,3,m);
            push_heap(h,pos_left,difft);
            dist[pos_left] = 0;
        }
    }
 
    while (h.size > 0){
        int merc_pos = pop_heap(h);
        int merc_r,merc_c,merc_rb;
        DECODEPOS(merc_pos,merc_r,merc_c,merc_rb,m);
        if (ENCODECEL(merc_r,merc_c,m) == D){
            cout << dist[merc_pos] << endl;
            return 0;
        }
        vector<int> ng;
        neighbors_pos(merc_r,merc_c,n,m,ng);
        for(int next_merc_pos:ng){
            int next_merc_r,next_merc_c,next_merc_rb;
            int new_distance = dist[merc_pos] + 1;
            DECODEPOS(next_merc_pos,next_merc_r,next_merc_c,next_merc_rb,m);
            int next_merc_cell = ENCODECEL(next_merc_r,next_merc_c,m);
 
            if (A[next_merc_r][next_merc_c] == '.' && dist[next_merc_pos] > new_distance && isPossibleToGo(A, n, m, get_rb_cell(merc_pos,m), ENCODECEL(merc_r,merc_c,m), get_rb_cell(ENCODEPOS(merc_r,merc_c,next_merc_rb,m),m))){
                int heur = diff(next_merc_cell,D,m)+new_distance;
                if(dist[next_merc_pos] < INF)
                    decrease_priority_heap(h,next_merc_pos,heur);
                else
                    push_heap(h,next_merc_pos,heur);
                dist[next_merc_pos] = new_distance;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
