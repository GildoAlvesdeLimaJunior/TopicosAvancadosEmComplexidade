#include <vector>
#include <iostream>
 
#define LIMN 100'000
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    vector<vector<int> > Grev(n,vector<int>());
    vector<int> outDegree(n,0);
    for (int k=0;k < m;++k){
        int i,j;
        cin >> i >> j;
        Grev[j].push_back(i);
        ++outDegree[i];
    }
 
    int q[LIMN],top = -1;
    for (int i = 0; i < n; ++i){
        if (outDegree[i] == 0)
            q[++top] = i;
    }
    vector<bool> order(n,false);
    int order_size = 0;
 
    while (top >= 0){
        int v = q[top--];
        order[v] = true;
        ++order_size;
        for (unsigned int k =0;k < Grev[v].size();++k){
            int w = Grev[v][k];
            if (--outDegree[w] == 0)
                q[++top] = w;
        }
    }
    cout << order_size;
    for(int i = 0;i < n;++i){
        if (order[i])
            cout << " " << i;
    }
    cout << endl;
    return 0;
}
