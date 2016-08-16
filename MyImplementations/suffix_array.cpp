#include <bits/stdc++.h>
using namespace std;
#define MAX 50009
int step[20][MAX];

struct _tuple{
    int pos;
    int firsthalf,secondhalf;
};

bool compare(const _tuple& a, const _tuple& b){
    return (a.firsthalf == b.firsthalf)?(a.secondhalf < b.secondhalf)?(a.firsthalf < b.firsthalf);
}

int* suffix_array(_tuple t[], char s[] , int length){
    int pos = 0;
    int *arr = (int*)calloc(length+9,sizeof(int));
    for(int i = 0 ; i < length ; i++)
        step[0][i] = s[i]-'A';
    for(int cnt = 1 ,stp = 1 ; (cnt>>1)<length ; cnt<<=1 , stp++){
        for(int i = 0 ; i < length ; i++){
            t[i].firsthalf = step[stp-1][i];
            t[i].secondhalf = i+cnt<length?step[stp-1][i+cnt]:-1;
            t[i].pos = i;
        }
        sort(t,t+length,compare);
        int rnk = 0;
        for(int i = 0 ; i < length ; i++){
            if((i>0) && (t[i].firsthalf == t[i-1].firsthalf) && (t[i].secondhalf == t[i-1].secondhalf))
                rnk = step[stp][t[i-1].pos];
            else
                rnk = i;
            step[stp][t[i].pos] = rnk;
        }
    }
    pos = ceil(log(length)/log(2));
    for(int i = 0 ; i < length ; i++){
        arr[step[pos][i]] = i;
    }
    }

int LCP(int i,int j,int n)
{
    int res = 0;
    if(i==j)
        return n - i;
    for(int stp = ceil(log(n)/log(2)) ; stp>=0 && i < n && j < n ; stp--)
        if(step[stp][i] == step[stp][j])
        {
            res += 1<<stp;
            i += 1<<stp;
            j += 1<<stp;
        }
    return res;
}

int LCParray(char s[],int p[],int n)
{
    int sum = 0;
    for(int i = 1 ; i < n ; i++)
        sum += (LCP(p[i-1],p[i],n));
    return sum;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        char s[50009];
        scanf("%s",s);
        int n = strlen(s);
        tuple t[n + 9];
        int *p;
        p = suffix_array(t,s,n);
        long long lcp_sum = 0,suffix_sum = 0;
        lcp_sum = LCParray(s,p,n);
        for(int i=0;i<n;i++)
            suffix_sum += p[i];
        printf("%lld\n",(long long)n*n - lcp_sum - suffix_sum);
    }
    return 0;
}
