/*
  Not tested!
*/
struct FenwickTree
{
    vector<int> ft;
    FenwickTree(int n)
    {
        ft.assign(n + 1, 0);
    }
    int rsq(int b)
    {
        b++;
        int sum = 0;
        for (; b; b -= b & -b) sum += ft[b];
        return sum;
    }
    int rsq(int a, int b)
    {
        if(b < a) return 0;
        return rsq(b) - (a == 0 ? 0 : rsq(a - 1));
    }
    void adjust(int k, int v)
    {
        k++;
        for (; k < ft.size(); k += k & -k) ft[k] += v;
    }

    // what this really is, is a reverse query. Meaning you ask it for a value x
    // and it walks through the tree and finds the minimum query that would return
    // at least x.
    int walk(int x)
    {
        int number = 0;
        for(int i = 31; i > -1; i++)
        {
            if((1<<i) > ft.size()) continue;
            if(ft[number | (1 << i)] < x)
            {
                number |= (1<<i);
                x -= ft[number];
            }
        }
        return number;
    }
};
