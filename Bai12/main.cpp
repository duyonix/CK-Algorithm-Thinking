// https://www.proofwiki.org/wiki/Integer_as_Sum_of_Two_Squares
// https://www.geeksforgeeks.org/check-whether-number-can-represented-sum-two-squares/
// https://blogmath123.wordpress.com/2014/07/07/dinh-ly-cua-fermat-ve-tong-cua-hai-binh-phuong/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_map>
using namespace std;

#define MAX 1e3
#define ll long long
#define pii pair<int, int>

pii add(pii p, int i, int j){
    pii r;
    r.first = p.first + i;
    r.second = p.second + j;
    return r;
}

void printSquare(int i, int j){
    int _min = min(i, j);
    j += i; i = _min; j -= _min; // i < j
    vector<pii> p(4);
    pii o = {0,0};
    o.first = -(i+j)/2;
    o.second = -(i+j)/2;
    p[0] = add(o, i, j);
    p[1] = add(p[0], i, j);
    p[2] = add(p[1], j, -1*i);
    p[3] = add(p[2], -1*i, -1*j);
    for(pii _p: p){
        cout<<_p.first<<" "<<_p.second<<endl;
    }
}

// Fermat Theorem: 
// O(sqrt(n)log(n))
bool checkByFermatTheorem(int s){
    for (int i = 2; i * i <= s; i++) {
        int count = 0;
        if (s % i == 0) {
            // Count all the prime factors.
            while (s % i == 0) {
                count++;
                s /= i;
            }
            // Ifany prime factor of the form (4k+3)(4k+3) occurs an odd number of times.
            if (i % 4 == 3 && count % 2 != 0)
                return 0;
        }
    }    
    // If s itself is a x prime number and can be expressed in the form of 4k + 3 we return false.
    return s % 4 != 3;  
}

void solution(){
    int s;
    cin >> s;

    // O(n)
    // for(int i=0; i<=sqrt(s)+1; ++i){
    //     for(int j=0; j<=sqrt(s)+1; ++j){
    //         if(i*i+j*j==s){
    //             printSquare(i, j);
    //             return;
    //         }
    //     }
    // }

    // O(sqrt(n))
    unordered_map<int, int> set;
    for (int i = 0; i * i <= s; ++i) {
 
        // store square value in hashmap
        set[i * i] = 1;
        if (set.find(s - i * i) != set.end()) {
            printSquare(sqrt(s - i * i), i);
            return;
        }
    }
    // --------------
    cout<<"Impossible";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solution();
    return 0;
}