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

typedef complex<double> base;


int rev[MAXN];
base wlen_pw[MAXN];
 
void fft (base a[], int n, bool invert) {
	for (int i=0; i<n; ++i)
		if (i < rev[i])
			swap (a[i], a[rev[i]]);
 
	for (int len=2; len<=n; len<<=1) {
		double ang = 2*PI/len * (invert?-1:+1);
		int len2 = len>>1;
 
		base wlen (cos(ang), sin(ang));
		wlen_pw[0] = base (1, 0);
		for (int i=1; i<len2; ++i)
			wlen_pw[i] = wlen_pw[i-1] * wlen;
 
		for (int i=0; i<n; i+=len) {
			base t,
				*pu = a+i,
				*pv = a+i+len2, 
				*pu_end = a+i+len2,
				*pw = wlen_pw;
			for (; pu!=pu_end; ++pu, ++pv, ++pw) {
				t = *pv * *pw;
				*pv = *pu - t;
				*pu += t;
			}
		}
	}
 
	if (invert)
		for (int i=0; i<n; ++i)
			a[i] /= n;
}
 
void calc_rev (int n, int log_n) {
	for (int i=0; i<n; ++i) {
		rev[i] = 0;
		for (int j=0; j<log_n; ++j)
			if (i & (1<<j))
				rev[i] |= 1<<(log_n-1-j);
	}
}

