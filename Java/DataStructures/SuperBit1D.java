
public class SuperBit1D {
	long mul[], add[];
	int n;
	SuperBit1D(int N) {
		n = N;
		mul = new long[N+1];
		add = new long[N+1];
	}

	void pointUpdate(int t, int x, long val) {
	  for (int i = x; i <= n; i += i & -i)
	  {		  
		  if(t == 0)mul[i] += val;
		  else add[i] += val;
	  }
	}
	
	void preUpdate(int x, long val) { // v[x] += val
	  pointUpdate(0, 1, val);
	  pointUpdate(0, x + 1, -val);
	  pointUpdate(1, x + 1, x * val);
	}
	
	long getPre(int x) { // get sum v[1..x]
	  long  a = 0, b = 0;
	  for (int i = x; i > 0; i -= i & -i) {
		  a += mul[i];
		  b += add[i];
	  }
	  return a * x + b;
	}
	void rangeUpdate(int l, int r, long val) { // v[l..r] += val
	  preUpdate(l - 1, -val);
	  preUpdate(r, val);
	}
	long getRange(int l, int r) { // get sum v[l..r]
	  return getPre(r) - getPre(l - 1);
	}
}
