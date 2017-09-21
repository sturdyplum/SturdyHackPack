/* implementation details

ok so make sure you set your maxlen

below is included the solution of k-inverse, this problem did not modify the fft code at all so we good on that, the main shows how to implement you a, b,c array and stuff, the k-inverse problem didn't ask for a mod but when you do the c mult you mod there and I got wrong ans when I removed it so its def part of the alg don't fuck with it. This code was found on http://e-maxx.ru/algo/fft_multiply which is in russian lol.
*/

#include <bits/stdc++.h>
#define MAX_LEN 1000000

using namespace std;

typedef long long ll;
//not really sure what these do so don't mess with them lol
const ll mod = 5 * (1 << 25) + 1;
const ll root = 243;
const ll root_1 = 114609789;
const ll root_pw = 1<<25;

ll gcd(ll a, ll b, ll &s, ll &t) { // a*s+b*t = g
  if (b==0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
  } else { ll g = gcd(b, a%b, t, s);  t -= a/b*s;  return g; }
}

ll inverse(ll n, ll mod)
{
  ll s, t;
  gcd(n, mod, s, t);
  return (s > 0) ? s : s + mod;
}

void fft (vector<ll> & a, bool invert) {
	int n = (int) a.size();

	for (int i=1, j=0; i<n; ++i) {
		int bit = n >> 1;
		for (; j>=bit; bit>>=1)
			j -= bit;
		j += bit;
		if (i < j)
			swap (a[i], a[j]);
	}

	for (int len=2; len<=n; len<<=1) {
		ll wlen = invert ? root_1 : root;
		for (ll i=len; i<root_pw; i<<=1)
			wlen = ll (wlen * 1ll * wlen % mod);
		for (int i=0; i<n; i+=len) {
			ll w = 1;
			for (int j=0; j<len/2; ++j) {
				ll u = a[i+j],  v = ll (a[i+j+len/2] * 1ll * w % mod);
				a[i+j] = u+v < mod ? u+v : u+v-mod;
				a[i+j+len/2] = u-v >= 0 ? u-v : u-v+mod;
				w = ll (w * 1ll * wlen % mod);
			}
		}
	}
	//cout <<"ASDASDAS" << endl;
	if (invert) {
		ll nrev = inverse(n, mod);
		for (int i=0; i<n; ++i)
			a[i] = ll (a[i] * 1ll * nrev % mod);
	}
}

int main()
{
    string s; cin >> s;
    int n = s.length();
    int fft_len = 1;
    while (fft_len < 2*MAX_LEN)
        fft_len *= 2;
    vector<ll> a(fft_len,0), b(fft_len,0), c(fft_len,0);
    for(int i =0;i < n; i++) a[i] = s[i] == 'A' ? 1:0;
    for(int i =0;i < n; i++) b[n-i] = s[i] == 'B' ? 1:0;

    fft(a,false);
    fft(b,false);

    for(int i = 0; i < fft_len; i++) c[i] = a[i] * b[i] % mod;

    fft(c,true);

    for(int i =n+1; i < 2*n; i++) cout << c[i] << endl;

    return 0;
}






// Non interger FFT
//==================================================================
 
typedef long double ld;
 
#define pb push_back
#define mp make_pair
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define sz(x) ((int)(x).size())
#define TASKNAME "text"
 
const ld pi = acos((ld) -1);
 
//BEGIN ALGO
namespace FFT {
  struct com {
    ld x, y;
 
    com(ld _x = 0, ld _y = 0) : x(_x), y(_y) {}
 
    inline com operator + (const com &c) const {
      return com(x + c.x, y + c.y);
    }
    inline com operator - (const com &c) const {
      return com(x - c.x, y - c.y);
    }
    inline com operator * (const com &c) const {
      return com(x * c.x - y * c.y, x * c.y + y * c.x);
    }
    inline com conj() const {
      return com(x, -y);
    }
  };
 
  const static int maxk = 21, maxn = (1 << maxk) + 1;
  com ws[maxn];
  int dp[maxn];
  com rs[maxn];
  int n, k;
  int lastk = -1;
 
  void fft(com *a, bool torev = 0) {
    if (lastk != k) {
      lastk = k;
      dp[0] = 0;
 
      for (int i = 1, g = -1; i < n; ++i) {
        if (!(i & (i - 1))) {
          ++g;
        }
        dp[i] = dp[i ^ (1 << g)] ^ (1 << (k - 1 - g));
      }
 
      ws[1] = com(1, 0);
      for (int two = 0; two < k - 1; ++two) {
        ld alf = pi / n * (1 << (k - 1 - two));
        com cur = com(cos(alf), sin(alf));
 
        int p2 = (1 << two), p3 = p2 * 2;
        for (int j = p2; j < p3; ++j) {
          ws[j * 2 + 1] = (ws[j * 2] = ws[j]) * cur;
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      if (i < dp[i]) {
        swap(a[i], a[dp[i]]);
      }
    }
    if (torev) {
      for (int i = 0; i < n; ++i) {
        a[i].y = -a[i].y;
      }
    }
    for (int len = 1; len < n; len <<= 1) {
      for (int i = 0; i < n; i += len) {
        int wit = len;
        for (int it = 0, j = i + len; it < len; ++it, ++i, ++j) {
          com tmp = a[j] * ws[wit++];
          a[j] = a[i] - tmp;
          a[i] = a[i] + tmp;
        }
      }
    }
  }
 
  com a[maxn];
  int mult(int na, int *_a, int nb, int *_b, long long *ans) {
    if (!na || !nb) {
      return 0;
    }
    for (k = 0, n = 1; n < na + nb - 1; n <<= 1, ++k) ;
    assert(n < maxn);
    for (int i = 0; i < n; ++i) {
      a[i] = com(i < na ? _a[i] : 0, i < nb ? _b[i] : 0);
    }
    fft(a);
    a[n] = a[0];
    for (int i = 0; i <= n - i; ++i) {
      a[i] = (a[i] * a[i] - (a[n - i] * a[n - i]).conj()) * com(0, (ld) -1 / n / 4);
      a[n - i] = a[i].conj();
    }
    fft(a, 1);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      long long val = (long long) round(a[i].x);
      assert(abs(val - a[i].x) < 1e-1);
      if (val) {
        assert(i < na + nb - 1);
        while (res < i) {
          ans[res++] = 0;
        }
        ans[res++] = val;
      }
    }
    return res;
  }
};
