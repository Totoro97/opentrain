#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define intl long long
using namespace std;

int n,k,A[20],B[20],C[20];
intl f[1 << 16][17],g[1 << 16];

int get_(int a,int b) {
	return ((a >> b) & 1);
}

int main() {
	//freopen("C.in","r",stdin);
	//freopen("C.out","w",stdout);
	scanf("%d %d",&n,&k);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d",&A[i],&B[i],&C[i]);
	}
	for (int st = 1; st < (1 << n); st++) {
		int x = 0, y = 0;
		for (int i = 0; i < n; i++) {
			if (!get_(st, i)) continue;
			x = max(x, A[i]);
			y = max(y, B[i]);
		}
		intl z = 0;
		for (int i = 0; i < n; i++) {
			if (!get_(st, i)) continue;
			z += ((intl) x * (intl) y - (intl) A[i] * (intl) B[i]) * (intl) C[i]; 
		}
		g[st] = z;
	}

	memset(f,-1,sizeof(f));
	f[0][0] = 0;
	for (int j = 1; j <= k; j++) {
		f[0][j] = 0;
		for (int st = 1; st < (1 << n); st++) {
			f[st][j] = g[st];
			for (int ts = st; ts; ts = (ts - 1) & st) {
				if (f[ts][j - 1] == -1) continue;
				f[st][j] = min(f[st][j], f[ts][j - 1] + g[ts ^ st]);
			}
		}
	}
	cout << f[(1 << n)- 1][k] << endl;
	return 0;
}
