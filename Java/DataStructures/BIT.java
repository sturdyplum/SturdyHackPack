public class BIT {
	private static int ft[], sum, maxi, N;
	BIT(int n) {
		ft = new int[n+1];
		maxi = -1;
		while((1 << maxi) == n+1) {
			maxi++;
		}
		maxi--;
		n = N;
	}
	
	public static int rsq(int b) {
		b++;sum = 0;
		for(;b!=0;b -= b &-b) sum += ft[b];
		return sum;
	}
	
	public static int rsq(int a, int b) {
		if(b < a) return 0;
		return rsq(b) - (a==0?0:rsq(a-1));
	}
	
	void adjust(int k, int v) {
		k++;
		for(;k < ft.length; k += k&-k) ft[k] += v;
	}
	
	int kth(int k) {
		int ans = 0;
		for (int i = maxi; i >= 0; --i) {
			if(ans + (1<<i) <= N && ft[ans] + (1<<i) < k) {
				ans += 1<<i;
				k -= ft[ans];
			}
		}
		return ans+1;
	}

}

