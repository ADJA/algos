#include <bits/stdc++.h>
using namespace std;

int editDist(char inp[100], char out[100]){
	int dp[101][101] = {};

	int m = strlen(inp);
	int n = strlen(out);
	dp[0][0] = 0;

	for(int i=1;i<=n;i++){
         dp[0][i] = 1 + dp[0][i-1]; 
	}
	for(int j=1;j<=m;j++){
		dp[j][0] = 1 + dp[j-1][0];
	}

	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			int q1 = dp[i-1][j-1]; // replacement
			int q2 = dp[i-1][j];   //deletion
			int q3 = dp[i][j-1];   //insertion
           dp[i][j] = min(q1,min(q2,q3)) + (inp[i-1]!=out[j-1]);

		}
	}
	return dp[m][n];
}

int main()
{
	char inp[100],out[100];

	cin >> inp >> out;

	int ans  = editDist(inp,out);
  cout<<ans;
	return 0;
}
