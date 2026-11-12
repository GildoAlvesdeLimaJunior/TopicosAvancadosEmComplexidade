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
    vector<int> max_exp(n);
    vector<int> max_func(n);
    for (int i=0;i < n;++i){
        cin >> max_exp[i];
        max_func[i] = i;
    }
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

 
    while (top >= 0){
        int v = q[top--];
        
        for (unsigned int k =0;k < G[v].size();++k){
            int w = G[v][k];
            if (max_exp[v] > max_exp[w]){
                max_exp[w] = max_exp[v];
                max_func[w] = max_func[v];
            }
            if (--inDegree[w] == 0)
                q[++top] = w;
        }
    }
    cout << max_func[0];
    for(int i=1;i < n;++i)
        cout << " " << max_func[i];
    cout << endl;
    return 0;
}
