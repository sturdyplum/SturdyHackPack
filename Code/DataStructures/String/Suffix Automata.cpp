/*

  Suffix automata taken from: http://e-maxx.ru/algo/suffix_automata
  Space Complexity O(N)
  Build Complexity O(N)

  Querys:
  - Check if string contains certain substring
    p = substring
    O(p)= complexity
    start at initial state and walk to next letter until there 
    you cant walk anymore or you find all of p
  
  - Check if string contains certain suffix
    p = suffix
    O(p)= complexity
    start at initial state and walk to next letter until there 
    you cant walk anymore or you find all of p, check that the final
    place is a terminal state. This requires you to run the calc terminals function
    
  - Number of unique substrings
    O(N) = complexity
    In a suffix automata, any substring corresponds to a path that starts at t0. Therefore
    the answer will be the number of different paths in the graph. Since the graph is acyclic,
    the number of paths can be retrieved using dynamic programming. For some node v, 
    d[v] = 1 + sum(d[w]) where d[w] are the nodes it has an edge to. The answer will be d[0]-1, 
    since the empty substring should be ignored.
    
  - Sum of lengths of all unique substrings
    O(N) = complexity.
    First generate d[v] using the teqnique discussed above. Then we will calculate ans[v], thier 
    total length as such. ans[v] = sum(d[w] + ans[w]) where w is all connecting nodes.
    
    Think of it this way, everytime you get a new substring, you will need to add its length 
    to every one of its ancestors. This way guarantees that happens. TRUST
    
  - Find the Kth substring
    O(length(ans) * alphabet) = complexity
    This problem is related to the one that counts the number of paths
    (look up to number of unique substrings). The trick is since you know how many paths
    are down each node, you can use that to do a dfs in which you prune paths that dont have
    enough paths. Be careful with the implementation here.
    
  - Finding the smallest cyclic shift
    O(N)
    Add the string to itself and find the lex first path of length N
  
  - Number of occurences of a substring
    O(N) = preprocessing
    O(P) = query
    To do this query, you will need to keep track of which states are not clones.
    For all states that are not clones, (t0 is not one of these states), cnt[u] =1. For 
    all other states including t0, cnt[x] = 0. Now run through the states in DESCENDING order
    of thier lengths and do cnt[link[u]] += cnt[u]. Watch out for t0 since cnt[-1] can cause RTE.

*/

struct suffixAutomaton{
    struct state {
        int len, link;
        map<char,int> next;
    };

    static const int MAXLEN = 100000;
    state st[MAXLEN*2];
    int sz, last;
    vector<int> terminals;

    suffixAutomaton(string s) {
        sz = last = 0;
        st[0].len = 0;
        st[0].link = -1;
        ++sz;
        for(char c: s) addChar(c);
        calculateTerminals(); // Only if you need to know the terminals.
    }

    void addChar (char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p;
        for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
            st[p].next[c] = cur;
        if (p == -1)
            st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len)
                st[cur].link = q;
            else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
                    st[p].next[c] = clone;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
    
    void calculateTerminals()
    {
        terminals.clear();
        int p = last;
        while(p > 0)
        {
            terminals.push_back(p);
            p = st[last].link;
        }
    }
};
