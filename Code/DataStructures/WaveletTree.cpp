#include <bits/stdc++.h>

using namespace std;

struct node{
    vector<int> numbers, goneLeft, goneRight;
    node *l = nullptr, *r = nullptr;
    int m;
    bool root = false;
};

struct WaveletTree {
    node* head;

    WaveletTree(vector<int> vals){
        head = makeNodes(vals);
    }

    node * makeNodes(vector<int> vals){
        node *ans = new node;
        vector<int> goneLeft(vals.size(), 0);
        vector<int> goneRight(vals.size(), 0);
        int leftTotal = -1, rightTotal = -1;
        int high = *max_element(vals.begin(), vals.end());
        int low = *min_element(vals.begin(), vals.end());
        if(low == high){
            ans->numbers = vals;
            ans->root = true;
            ans->m = vals[0];
            return ans;
        }
        int m = low + (high-low)/2;
        vector<int> l, r;
        for(int i = 0;i < vals.size(); i++){
            if(vals[i] <= m){
                l.push_back(vals[i]);
                goneLeft[i] = ++leftTotal;
                goneRight[i] = rightTotal;
            }
            else{
                r.push_back(vals[i]);
                goneRight[i] = ++rightTotal;
                goneLeft[i] = leftTotal;
            }
        }
        if(l.size())ans->l = makeNodes(l);
        if(r.size())ans->r = makeNodes(r);
        ans->goneLeft = goneLeft;
        ans->goneRight = goneRight;
        ans->numbers = vals;
        ans->m = m;
        return ans;
    }

    // Gets the amount of occurences of s up until and including index i
    int getRank(int s, int i){
        node *cur = head;

        while(!cur->root){
            if(s <= cur->m){
                i = mapLeft(i, cur->goneLeft);
                cur = cur->l;
            }
            else{
                i = mapRight(i, cur->goneRight);
                cur = cur->r;
            }
            if(i == -1){
                return 0;
            }
        }
        if(cur->m != s) return 0;
        return i+1;
    }

    int mapLeft(int i, vector<int> &leftVals){
        return leftVals[i];
    }

    int mapRight(int i, vector<int> &rightVals){
        return rightVals[i];
    }
};
