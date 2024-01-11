#include <bits/stdc++.h>
 
using namespace std;
 
 
void solve(){
    bool dir[5] ={};
    int n = 0,sk=0,x,y;
    cin >>n;
    while(n--){
        cin >> x >> y;
        if(x<0&&dir[1]==0){
            dir[1]= 1;
            //cout << 1;
            sk++;
        }
        if(x>0&&dir[2]==0){
            dir[2]= 1;
            //cout << 2;
            sk++;
        }
        if(y>0&&dir[3]==0){
            dir[3]= 1;
            //cout << 3;
            sk++;
        }
        if(y<0&&dir[4]==0){
            dir[4]= 1;
            //cout << 4;
            sk++;
        }
 
    }
    //cout << sk;
    cout << (sk==4?"NO":"Yes");
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
        cout << "\n";
    }
    return 0;
}
