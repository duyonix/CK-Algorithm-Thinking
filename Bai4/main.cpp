#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1e3
#define ll long long
#define pii pair<int, int>

using namespace std;
vector<int> initArray;

ll g(int n){
    if (n==1){
        return 0;
    }else{
        ll res = 0;
        for(int i=0; i< n; ++i){
            // find n-arr[i] in i+1 -> n
            for(int j=i+1; j<n; ++j){
                if(initArray[i] + initArray[j]==n){
                    // printf("[%d,%d] ",primeNumbers[i], primeNumbers[j]);
                    ++res;
                }
            }
        }
        return res;
    }
}

ll f(int n){
    if (n==1){
        return 0;
    }else{
        return f(n-1)+g(n);
    }
}

void solution(){
    int n, m;
    cin >> n >> m;
    int x;
    for (int i=0; i<n; ++i){
        cin >> x;
        initArray.push_back(x);
    }
    cout << f(m);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}