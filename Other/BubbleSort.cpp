/*Sorts the array in Ascending Order*/

#include<bits/stdc++.h>
using namespace std;

vector<int> bubble_sort(vector<int> arr){
    for(int i=0;i<arr.size();i++){
        for(int j=1;j<arr.size();j++){
            if(arr[j-1]>arr[j]) swap(arr[j-1],arr[j]);
        }
        
    }
    return(arr);
}

int main(){
    int n;
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    vector<int> num(n);
    cout<<"Enter the numbers:\n";
    for(int i=0;i<n;i++){
        cin>>num[i];
    }
    vector<int> ans;
    ans=bubble_sort(num);
    cout<<"The sorted array is:\n"
;    for(int i=0;i<n;i++) cout<<ans[i]<<" ";
    return(0);
}
