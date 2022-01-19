// Cho đa giác lồi n đỉnh có tọa độ nguyên xi,yi. 
// Các đỉnh được liệt kê ngược chiều kim đồng hồ và không có 3 đỉnh nào thẳng hàng. 
// Chỉ ra một cách kẻ 1 đường chéo đi qua 2 đỉnh và 
// chia đa giác thành 2 phần có diện tích chênh lệch nhau ít nhất. 
#include <iostream>
#include <fstream>
#include<tuple> 
#include <vector>
using namespace std;
typedef vector<tuple<int,int> > tuple_list;

// Tính diện tích đa giác lồi (truyền vào list các tọa độ)
// Độ phức tạp: chạy 1 vòng lặp từ 0->n : O(n)
float CalculateConvexPolygonArea(tuple_list polygon){
    int n=polygon.size()-1;
    float result=(  get<0>(polygon.at(n))*get<1>(polygon.at(0)))
         - (get<1>(polygon.at(n)) * get<0>(polygon.at(0)));
    for (int i=0;i<n;i++){
        result+= (  get<0>(polygon.at(i))*get<1>(polygon.at(i+1)))
         - (get<1>(polygon.at(i)) * get<0>(polygon.at(i+1)));
  
    }
    return abs(result)/2;
}

// Độ chênh lệch 2 đa giác tạo ra cắt bởi đỉnh i và j
// Độ phức tạp: tạo 2 đa giác mới: 2 vòng lặp (mỗi lặp nửa cái n) : O(n)
//              tính diện tích 2 đa giác: O(2n)
// => Tổng cộng là: O(3n) ~ O(n)
float CalculateDifferenceOf2Polygons(tuple_list polygon, int i, int j){
    // if (j>i){
    //     swap(i,j);
    // }
    tuple_list pol1;
    for(int k=i;k<=j;k++){
        pol1.push_back(polygon.at(k));
    }
    tuple_list pol2;
    for(int k=j;k<polygon.size();k++){
        pol2.push_back(polygon.at(k));
    }
    for(int k=0;k<=i;k++){
        pol2.push_back(polygon.at(k));
    }
    float area1=CalculateConvexPolygonArea(pol1);
    float area2=CalculateConvexPolygonArea(pol2);
    return abs(area1-area2);
}

// Ý tưởng: cố đỉnh lần lượt mỗi đỉnh i trong n đỉnh
// Ban đầu min= INFINITY
// Với mỗi đỉnh i, ta xét đỉnh đối diện nó trong đa giác -> tìm độ chênh lệch 2 đa giác tác tạo ra
//                                                                      -> Nếu < min, cập nhật min, lưu 2 đỉnh
//                 lần lượt mở rộng về phía bên trái, bên phải đỉnh i -> nếu độ chênh lệch của 2 đa giác tạo ra < min, cập nhật min, lưu 2 đỉnh
//                                                                                                         > min, dừng mở rộng phía đó
// Lặp lại cho tới khi hết hết các đỉnh i=0->n: tìm được độ chênh lệch đa giác min
// Trả về 1 tuple<int,int> là 2 đỉnh cần tìm 
// Cuối hàm cộng 2 đỉnh cho 1 (tại output đề cho là đỉnh đếm từ 1)
// 
// Độ phức tạp:
// Duyệt n đỉnh: O(n)
//          Mỗi lần duyệt: duyệt mở rộng ra 2 bên dần (vì tính chất sẽ đến 1 lúc nào đó thì 2 đa giác chênh lệch tăng dân) -> Log(n) (cái này cần nói rõ hơn)
//                      Mỗi lần mở rộng tính độ chênh lệnh: O(n)
// => O(n * log(n) *  n) = O(n^2 log(n))
tuple<int,int> solution(tuple_list polygon){
    // Gán độ chênh lệch  2 đa giác ban đầu là Cộng vô cùng nhe
    float min=99999;
    // biến tạm trong quá trình tính toán
    float diff_=min;
    // kết quả cặp đỉnh sẽ trả về
    tuple<int,int> result=make_tuple(0,0);
    float index_left,index_right;
    int n=polygon.size()-1;
    int right; //temp

    // Chọn từng đỉnh i, lần lượt như sau:
    for(int i=0;i<n;i++){
        // mid là đỉnh đối của i trong đa giác polygon
        int mid= (n-i)/2+i+1;
        // diff là diện tích chênh lệch của 2 đa giác cắt bởi cắp đỉnh (i,mid)
        float diff=CalculateDifferenceOf2Polygons(polygon,i,mid);
        // nếu mà cặp đỉnh (i,mid) cho ra chênh lệch ít hơn min thì cập nhật lại min, lưu 2 đỉnh
        if (diff<min)
        {
            min=diff;
            get<0>(result)=i;
            get<1>(result)=mid;
        }

        // lần lượt từ đỉnh mid+1 trở về sau, kiểm tra độ chênh lệch của 2 đa giác cách bởi (i,...) sao cho 
        // nếu nhỏ hơn thì cập nhật lại min, lưu 2 đỉnh
        // lớn hơn thì dừng
        right=1;
        index_right=(mid+right)%(n+1);
        while(diff_<min && index_right<=i-2){
            right++;
            index_right=(mid+right) % (n+1);
            diff_=CalculateDifferenceOf2Polygons(polygon,i,index_right);
            // nếu chênh lệch của (i,right) lớn hơn min hiện tại -> thoát vòng lặp while
            if (diff_>min)
                break;
            // nếu chênh lệch của (i,right) nhỏ hơn min hiện tại -> cập nhật lại
           if (diff_<min)
            {
                min=diff_;
              get<0>(result)=i;
                get<1>(result)=index_right;
            }
        }
        // lần lượt từ đỉnh mid-1 trở về trước, kiểm tra độ chênh lệch của 2 đa giác cách bởi (....,i) sao cho 
        // nếu nhỏ hơn thì cập nhật lại min, lưu 2 đỉnh
        // lớn hơn thì dừng
        index_left=mid;
        while(diff_<min && index_left>=i+2){
            index_left++;
            diff_=CalculateDifferenceOf2Polygons(polygon,i,index_left);
            if(diff_>min)
                break;
            if (diff_<min)
            {
                min=diff_;
                get<0>(result)=i;
                get<1>(result)=index_left;
            }
        }
    }
    get<0>(result)++;;
    get<1>(result)++;
    return result;
}

int main()
{
    // Read input file
    ifstream filein("input.txt");
    if(!filein){
        cerr << "Error: cannot open this file.";
        return -1;
    }

    int n;
    tuple_list polygon;
    filein >> n;
    for(int i=0;i<n;i++){
        int a,b;
        filein >>a>>b;
        polygon.push_back(tuple<int, int>(a,b) );
    }
    tuple<int,int> result=solution(polygon);
    // Write result to output file
    ofstream fileout("output.txt");
    fileout << get<0>(result) << " "<<  get<1>(result);

    return 0;
}