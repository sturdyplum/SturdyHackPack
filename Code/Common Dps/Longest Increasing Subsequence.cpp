#include <bits/stdc++.h>

#define ii pair<int,int>
#define vi vector<int>
#define forall(i,n) for(int i = 0; i <n;i++)
#define inf 2000000000
using namespace std;


int main() {
    int n; cin >> n;
    vi list(n), lis(n,inf);
    forall(i,n)
    {
        cin >> list[i];
    }
    
    forall(i,n)
    {
        *lower_bound(lis.begin(),lis.end(),list[i]) = list[i];    
    }
    int ans = -1;
    forall(i,n)
    {
        if(lis[i] != inf) ans = i;
    }
    ans++;
    cout << ans << endl;
    return 0;
}


