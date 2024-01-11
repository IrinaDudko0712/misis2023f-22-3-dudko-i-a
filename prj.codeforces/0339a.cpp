#include <bits/stdc++.h>
 
using namespace std;
 
int main(){
    string s;
    cin>>s;
    string h;
    for (int i=0;i<s.size();i+=2){
        h+=s[i];
    }
    sort(h.begin(),h.end());
    for (int i=0;i<h.size();i++){
        cout<<h[i];
        if(i!=h.size()-1){
            cout<<'+';
        }
    }
    
}
