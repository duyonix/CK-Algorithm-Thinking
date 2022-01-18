//Cho n đoạn giá trị (x_i,y_i ) phủ tất cả giá trị từ L đến R.
// Hãy loại bỏ 1 đoạn trong số n đoạn sao cho n-1 đoạn còn lại 
//cũng phủ được tất cả giá trị từ L đến R và đoạn loại bỏ có độ dài lớn nhất.

#include <iostream>
#include <fstream>
#include<tuple> 
#include <vector>
using namespace std;
typedef vector<tuple<int,int> > tuple_list;

// Tìm đoạn có độ dài dài nhất trong list
// Giải thích condition:
// condition là 1 mảng điều kiện sao cho tại condition[i]=true thì ta sẽ không xét đoạn thứ i
int findMaxLength(tuple_list list,bool* condition1=NULL, bool* condition2=NULL)
{
    int maxLength=0,length;

    if(!condition1 && !condition2)
    { 
        for (int k=0;k<list.size();k++){
            length= get<1>(list.at(k)) - get<0>(list.at(k));
            if (length>maxLength)
                maxLength=length;
        }
    }
    else if (!condition2)
    {    
        for (int k=0;k<list.size() & condition1[k]==false ;k++){
            length= get<1>(list.at(k)) - get<0>(list.at(k));
            if (length>maxLength)
                maxLength=length;
        }
    }
    else 
    {     
        for (int k=0;k<list.size() ,condition1[k]==0 , condition2[k]==0;k++){
            cout << "k = " << k <<endl;
            length= get<1>(list.at(k)) - get<0>(list.at(k));
            if (length>maxLength){
                maxLength=length;
            }
        }
    }
    return maxLength;

}


int main()
{
    // Read input file
    ifstream filein("input.txt");
    if(!filein){
        cerr << "Error: cannot open this file.";
        return -1;
    }
    int n, L, R;
    tuple_list list;
    filein >> n >> L >> R;
    for (int i=0;i<n;i++){
        int a,b;
        filein >> a>> b;
        list.push_back(tuple<int, int>(a,b) );
    }

    bool contain_L[n]={false};
    bool contain_R[n]={false};
    int count_L=0;
    int count_R=0;

    // Create contain_L and contain_R array
    for (int i=0;i<n;i++){
        if (get<0>(list.at(i)) <= L && L<= get<1>(list.at(i) ) )  {
            contain_L[i]=true;
            count_L++;
        }
        if (   get<0>(list.at(i)) <= R && R<= get<1>(list.at(i)) ){
            contain_R[i]=true;
            count_R++;
        }
    }

    // Check result of count_L and count_R to find ( , )
    int result=0; // length of ( , )
    if (count_R==1 && count_L==1){
        // 
            result=findMaxLength(list,contain_L,contain_R);
    } 
    else if (count_R>1 && count_L>1){
        result=findMaxLength(list);
    }
    else{
        if (count_R==1 and count_L >1){
            result=findMaxLength(list,contain_R);
        }
        else{
            result=findMaxLength(list,contain_L);
        }
    }

    // Write result to output file
    ofstream fileout("output.txt");
    fileout << result;

    return 0;
}