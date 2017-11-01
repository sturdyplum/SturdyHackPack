const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};
---------------------------------------------------------------------------------------------
// convex hull, minimum
vector<ll> M, B;
int ptr;
bool bad(int a,int b,int c) {
  // use deterministic comuputation with long long if sufficient
  return (long double)(B[c]-B[a])*(M[a]-M[b])<(long double)(B[b]-B[a])*(M[a]-M[c]);
}
// insert with non-increasing m
void insert(ll m, ll b) {
  M.push_back(m);
  B.push_back(b);
  while (M.size() >= 3 && bad(M.size()-3, M.size()-2, M.size()-1)) {
    M.erase(M.end()-2);
    B.erase(B.end()-2);
  }
}
ll get(int i, ll x) {
  return M[i]*x + B[i];
}
// query with non-decreasing x
ll query(ll x) {
  ptr=min((int)M.size()-1,ptr);
  while (ptr<M.size()-1 && get(ptr+1,x)<get(ptr,x))
    ptr++;
  return get(ptr,x);
}
