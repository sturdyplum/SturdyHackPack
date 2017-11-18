void ModularGaussian(BitSet[] a, int n, int m) {
		for(int col = 0, row = 0; col < m&&row<n; ++col) {
			for(int i = row; i < n; i++) {
				if(a[i].get(col)) {
					BitSet temp = a[i];
					a[i] = a[row];
					a[row] = temp;
					break;
				}
			}
			if(!a[row].get(col)) {
				continue;
			}
			
			for(int i = 0; i < n; i++) {
				if(i != row && a[i].get(col)) 
					a[i].xor(a[row]);
			}
			++row;
		}
	}
