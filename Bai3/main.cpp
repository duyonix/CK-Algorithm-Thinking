#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1e6
#define ll long long
#define pii pair<int, int>

using namespace std;

void solution(){
    ll n, m, k;
    cin >> n >> m >> k;
    if (k>n*m){
        return;
    }
    if (k < n+m -1){
        cout<<1;
    }else{
        
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}