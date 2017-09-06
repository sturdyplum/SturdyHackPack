/*
 Not Tested!
*/

/*
This is a compressed 2d binary index tree.
it can only support binary values i.e. 1 or 0.

Operations: O(Q * log(N)^2)
insert x,y: inserts a 1 into position x, y
remove x,y: replaces position x, y with 0.

Query: O(Q * log(N)^2)
sum of sub rectangle

Space complexity O(Q * log(N))
*/
using namespace __gnu_pbds;
const int N = 200010;
struct C2dBIT{
    typedef pair<int,int> ii;
    typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> OST;
    OST bit[N];
    void put(int x, int y, bool v)
    {
        for(int i = 0; i< N; i+= i &-i)
            if(v)bit[i].insert(ii(y,x));
            else bit[i].erase(ii(y,x));
    }
    int query(int x, int y)
    {
        int ans = 0;
        for(int i = x; i >= 0; i -= i & -i)
            ans += bit[i].order_of_key(ii(y+1, 0));
        return ans;
    }
};
