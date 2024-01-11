#include<bits/stdc++.h>
using namespace std;
 
int main(){
    int t;
    cin>>t;
    while(t--){
     int a[3],i,l,j,k;
     cin>>a[0]>>a[1]>>a[2];
      for(i=0;i<3;i++){
            l=0;
            k=1e9;
        for(j=0;j<3;j++){
            if(j==i)continue;
            else{
                l=l+a[j];
                k=min(k,a[j]);
            }
        }
        if(l%2!=0)cout<<0<<" ";
       // else if((l/2)-k<a[i])cout<<1<<" ";
        else cout<<1<<" ";
      }
      cout<<endl;
     }
    }
