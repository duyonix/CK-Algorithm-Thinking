#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1e3
#define ll long long
#define pii pair<int, int>

using namespace std;
vector<int> primeNumbers;
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)
        return false;
    for (int i: primeNumbers){
        if ( n%i == 0 ) {
            return false;
        }
    }
    return true;
}

void buildPrimeArray(int n = MAX){
    for(int i =1; i< 2*n; ++i){
        if(isPrime(i)){
            primeNumbers.push_back(i);
        }
    }
}

ll g(int n){
    if (n==2){
        return 1; //g(2)
    }else{
        ll res = 0;
        for(int i=0; i< n; ++i){
            for(int j=i; j<n; ++j){
                if(primeNumbers[i] + primeNumbers[j]==2*n){
                    // printf("[%d,%d] ",primeNumbers[i], primeNumbers[j]);
                    ++res;
                }
            }
        }
        return res;
    }
}

ll f(int n){
    if (n==2){
        return 1; //f(2)=g(2)=2+2
    }else{
        return f(n-1)+g(n);
    }
}

void solution(){
    int n;
    cin >> n;
    buildPrimeArray(2*n);
    cout << f(n);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}