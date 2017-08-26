point pivot(0, 0);
bool angleCmp(point a, point b) {
// angle-sorting function
if (collinear(pivot, a, b))
// special case
return dist(pivot, a) < dist(pivot, b);
// check which one is closer
double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }
// compare two angles
vector<point> CH(vector<point> P) {
// the content of P may be reshuffled
int i, j, n = (int)P.size();
if (n <= 3) {
if (!(P[0] == P[n-1])) P.push_back(P[0]); // safeguard from corner case
return P; }
// special case, the CH is P itself
// first, find P0 = point with lowest Y and if tie: rightmost X
int P0 = 0;
for (i = 1; i < n; i++)
if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
P0 = i;
point temp = P[0]; P[0] = P[P0]; P[P0] = temp;
// swap P[P0] with P[0]
// second, sort points by angle w.r.t. pivot P0
pivot = P[0];
// use this global variable as reference
sort(++P.begin(), P.end(), angleCmp);
// we do not sort P[0]
vector<point> S;
S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
// initial S
i = 2;
// then, we check the rest
while (i < n) {
// note: N must be >= 3 for this method to work
j = (int)S.size()-1;
if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]); // left turn, accept
else S.pop_back(); }
// or pop the top of S until we have a left turn
return S; 

}
