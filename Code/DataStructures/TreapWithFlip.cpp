#include <bits/stdc++.h>

using namespace std;

/*
http://e-maxx.ru/algo/treap#7
*/
int n;
struct Cartesian
{
    vector<int> oa;
    struct item {
        int prior, value, cnt, min;
        bool rev;
        item *l, *r;

        ~item()
        {
            delete l;
            delete r;
        }
    };

    item *root;
    Cartesian(int n, vector<int> &orig)
    {
        oa = orig;
        srand(time(NULL));
        root = new item;
        root->cnt = 1;
        root->min = 0;
        root->prior = rand();
        root->value = 0;
        root->l = NULL;
        root->r = NULL;
        for(int i = 1; i < n; i++)
        {
            item *ni = new item;
            ni->prior = rand();
            ni->value = i;
            ni->cnt = 1;
            ni->min = i;
            ni->l = NULL;
            ni->r = NULL;
            merge(root, root, ni);

        }
    }

    int cnt (item *it) {
        return it? it->cnt: 0;
    }

    void upd_cnt (item *it) {
        if (it)
            it-> cnt = cnt (it-> l) + cnt (it-> r) + 1;
    }

    int getMin (item *it) {
        return it?oa[it->min]:2000000000;
    }

    void upd_min (item *it) {
        if (it) {
            push(it);
            it->min = it->value;
            if(getMin(it->l) <= getMin(it))
            {
                if(getMin(it->l) == getMin(it))
                {
                    it->min = min(it->min, it->l->min);
                }
                else
                {
                    it->min = it->l->min;
                }
            }
            if (getMin(it->r) <=getMin(it)){
                if(getMin(it->r) == getMin(it))
                {
                    it->min= min(it->min, it->r->min);
                }
                else
                {
                    it->min = it->r->min;
                }
            }
        }
    }

    void push (item *it) {
        if (it && it-> rev) {
            it-> rev = false;
            swap (it-> l, it-> r);
            if (it-> l) it->l->rev ^= true;
            if (it-> r) it->r->rev ^= true;
        }
    }

    void merge (item *&t, item *l, item *r) {

        push (l);
        push (r);
        if (! l ||! r)
            t = l? l: r;
        else if (l-> prior> r-> prior)
            merge (l-> r, l-> r, r), t = l;
        else
            merge (r-> l, l, r-> l), t = r;
        upd_cnt (t);
        upd_min (t);
    }

    void split (item *t, item *&l, item *&r, int key, int add = 0) {

        if (! t)
            return void (l = r = 0);
        push (t);
        int cur_key = add + cnt(t-> l);
        if (key <= cur_key)
            split (t-> l, l, t-> l, key, add), r = t;
        else
            split (t-> r, t-> r, r, key, add + 1 + cnt (t-> l)), l = t;
        upd_cnt (t);
        upd_min (t);
    }

    void reverse (item *t, int l, int r) {
        item *t1, *t2, *t3;
        t1 = t2 = t3 =NULL;
        split (t, t1, t2, l);
        split (t2, t2, t3, r-l + 1);
        t2->rev ^= true;
        merge (t, t1, t2);
        merge (t, t, t3);

    }

    void output (item *t) {
        if (!t) return;
        push (t);
        output (t->l);
        cout << oa[t->value]<< " ";
        output (t->r);
    }

    void removeSegment (item *t, int l, int r, int nl) {
        push(t);
        item *t1, *t2, *t3, *t4, *t5;
        t1 = t2 = t3 =t4=t5 = NULL;
        split(t, t1, t2, l);
        split(t2,t2,t3,r-l + 1);
        merge(t, t1, t3);
        if(nl >= l) nl = max(l, nl - (r - l));
        split(t, t4, t5, nl);
        merge(t, t4, t2);
        merge(t, t, t5);
    }

    int queryMin(item *t, int l, int r)
    {
        push(t);
        item *t1, *t2, *t3;
        t1 = t2 =t3 = NULL;
        split(t, t1, t2, l);
        split(t2, t2, t3, r-l+1);
        int ans = go(t2);

        merge(t, t1, t2);
        merge(t, t, t3);

        return ans;
    }

    int go(item *t)
    {
        push(t);
        if(oa[t->value] < getMin(t->l) and oa[t->value] < getMin(t->r)) return cnt(t->l);
        bool left = 1;
        if(getMin(t->r) < getMin(t->l)) left = 0;
        else if(getMin(t->r) == getMin(t->l))
        {
            if(t->r->min < t->l->min) left = 0;
        }
        if(left and oa[t->value] == getMin(t->l) and t->value < t->l->min)return cnt(t->l);
        if(!left and oa[t->value] == getMin(t->r) and t->value < t->r->min)return cnt(t->l);
        if(left) return go(t->l);
        return go(t->r) + 1 + cnt(t->l);

    }

    void getArr(item *t,vector<int> &arr)
    {
        if(!t) return;
        getArr(t->l, arr);
        arr.push_back(oa[t->value]);
        getArr(t->r, arr);
    }

    ~Cartesian()
    {
        delete root;
    }

};

int main()
{
    while(scanf("%d", &n), n)
    {
        vector<int> numbers(n);
        int i;
        for(i = 0; i < n; i++){

            cin >> numbers[i];
        }
        Cartesian t(n, numbers);


        for(int i = 0; i < n; i++){
            int loc = t.queryMin(t.root,i,n-1);
            if(i) cout <<" ";
            cout << loc+1+i;


            if(loc)
            {
                t.reverse(t.root, i, loc+i);
            }
        }
        vector<int> tt;
        t.getArr(t.root, tt);
        for(int i = 0; i < n-1; i++)
        {
            assert(tt[i] <= tt[i+1]);
        }
        cout << endl;
    }
    return 0;
}

