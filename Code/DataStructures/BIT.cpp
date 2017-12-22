// Treat as 0 indexed and it converts it to 1 indexed for you.
struct FenwickTree
{
    vector<int> ft;
    FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }
    int rsq(int b) {
        b++;
        int sum = 0;
        for (; b; b -= b & -b) sum += ft[b];
        return sum;
    }
    int rsq(int a, int b) {
        if(b < a) return 0;
        return rsq(b) - (a == 0 ? 0 : rsq(a - 1));
    }
    void adjust(int k, int v) {
        k++;
        for (; k < ft.size(); k += k & -k) ft[k] += v;
    }
};
