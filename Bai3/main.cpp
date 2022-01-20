#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1e6
#define ll long long
#define pii pair<int, int>

using namespace std;
ll n, m, k;

// O(nm*log(nm))
void sol1(){
    vector<ll> arr;
    ll s;
    for(int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            arr.push_back(i*i + j*j);
        }
    }
    sort(arr.begin(), arr.end());
    for (ll x: arr){
        cout<< x<<" ";
    }
    cout<<endl;
    cout << arr[k-1];
}

void sol2(){
    // dp not solve
}

void solution(){
    cin >> n >> m >> k;
    if(n*m<1e6){
        sol1();
    }else{
        sol2();
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}