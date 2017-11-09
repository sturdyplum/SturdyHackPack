#include <bits/stdc++.h>

using namespace std;

/*
http://e-maxx.ru/algo/treap#7

UNTESTED
*/

struct Cartesian
{
    struct item {
        int prior, value, cnt, min, minI;
        bool rev;
        item *l, *r;
    };

    item *root;
    Cartesian(int n, vector<int> &orig)
    {
        srand(time(NULL));
        root = new item;
        root->cnt = 1;
        root->min = orig[0];
        root->minI = 0;
        root->prior = rand();
        root->value = 0;
        for(int i = 1; i < n; i++)
        {
            item *ni = new item;
            ni->prior = rand();
            ni->value = i;
            ni->cnt = 1;
            ni->min = orig[i];
            ni->minI = 0;
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
        return it?it->min:2000000000;
    }



    void upd_min (item *it) {
        if (it) {
            it->min = it->value;
            it->minI = cnt(it->l);
            if(getMin(it->l) < it->min)
            {
                it->min = getMin(it->l);
                it->minI = it->l->minI;
            } else if (getMin(it->r) < it->min) {
                it->min = getMin(it->r);
                it->minI = it->r->minI+cnt(it->l)+1;
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
        printf ("% d", t-> value);
        output (t->r);
    }

    void removeSegment (item *t, int l, int r, int nl) {
        item *t1, *t2, *t3, *t4, *t5;
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
        item *t1, *t2, *t3;
        split(t, t1, t2, l);
        split(t2, t2, t3, r-l+1);
        int ans = t2->minI+cnt(t1);
        merge(t, t, t2);
        merge(t, t, t3);
        return ans;
    }
};

int main()
{
    
    return 0;
}
