#include <vector>
#include <iostream>
 
#define LIMN 100'000
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    vector<vector<int> > G(n,vector<int>());
    vector<int> inDegree(n,0);
    for (int k=0;k < m;++k){
        int i,j;
        cin >> i >> j;
        G[i].push_back(j);
        ++inDegree[j];
    }
    int q[LIMN],top = -1;
    for (int i = 0; i < n; ++i){
        if (inDegree[i] == 0)
            q[++top] = i;
    }
    int order[LIMN];
    int order_size=0;
 
    while (top >= 0){
        int v = q[top--];
        order[order_size++] = v;
        for (unsigned int k =0;k < G[v].size();++k){
            int w = G[v][k];
            if (--inDegree[w] == 0)
                q[++top] = w;
        }
    }
    cout << order[0];
    for(int i=1;i < order_size;++i)
        cout << " " << order[i];
    cout << endl;
    return 0;
}
