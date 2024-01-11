#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
   ll n;
   cin>>n;
   ll a[n];
   ll sum1=0;
   ll sum2=0;
   ll count=0;
   for(ll i=0;i<n;i++){
       cin>>a[i];
       sum1+=a[i];
   }
   sort(a,a+n);
    for(ll i=n-1;i>=0;i--){
       sum2+=a[i];
       count++;
       if(sum2>sum1/2){ 
           break;
       }
   }
   cout<<count<<endl;
}
