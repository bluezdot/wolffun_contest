#include <iostream>
using namespace std;


static const int MaxRow = 16;
const int MaxCol = 6;
const int MinLenght = 23;
const int MaxLenght = 25;


void InKetQua(int** matran){
    for(int i = 0; i < MaxRow; i++){
        for(int j = 0; j < MaxCol; j++){
            cout << matran[i][j] << " ";
        }
        cout << endl;
    }
    cout << "============================\n";
}


// Kiểm tra điều kiện không có 4 ô kề nhau
int KiemTraDieuKien4OSatNhau(int** matran, int indexHangKiemTra, int indexCotKiemTra){
    if(matran[indexHangKiemTra][indexCotKiemTra] == 0
    && matran[indexHangKiemTra-1][indexCotKiemTra] > 0)
        return 0;

    return 1;

}


// Kiểm tra đã đến đích chưa
void XuLyO(int** matran, int indexHang, int indexCot, int DoDaiDuongDi);
void KiemTraDieuKienDoDaiDuongDi(int** matran, int indexHang, int indexCot, int DoDaiDuongDi){
    if(matran[indexHang][indexCot] != 0)
        return;
        
    DoDaiDuongDi++;
    matran[indexHang][indexCot] = DoDaiDuongDi;

    if(indexHang == MaxRow - 1 && DoDaiDuongDi >= MinLenght && DoDaiDuongDi <= MaxLenght){
        InKetQua(matran);
    }
    else if(indexHang < MaxRow - 1){
        XuLyO(matran, indexHang, indexCot, DoDaiDuongDi);
    }
    matran[indexHang][indexCot] = 0;
}


// Giải thuật đi tới kiểm tra ô này
void XuLyO(int** matran, int indexHang, int indexCot, int DoDaiDuongDi){
    // Đi tới
    if(matran[indexHang + 1][indexCot] == 0){
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang + 1, indexCot, DoDaiDuongDi);
    }

    // Đi ngang phải
    if(indexCot + 1 < MaxCol && KiemTraDieuKien4OSatNhau(matran, indexHang, indexCot + 1) == 1){
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang, indexCot + 1, DoDaiDuongDi);
    }
        
    // Đi ngang trái
    if(indexCot > 1 && KiemTraDieuKien4OSatNhau(matran, indexHang, indexCot - 1) == 1){
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang, indexCot - 1, DoDaiDuongDi);
    }
}


int main() {
    int **matran = new int*[MaxRow];
    for(int i = 0; i<MaxRow; i++)
       matran[i] = new int[MaxCol];
    for(int i = 0; i < MaxRow; i++){
        for(int j = 0; j < MaxCol; j++){
            matran[i][j] = 0;
        }
    }

    // Chaỵ vòng lặp
    for(int i = 0; i < MaxCol; i++){
        matran[0][i] = 1;
        KiemTraDieuKienDoDaiDuongDi(matran, 1, i, 1);
    }
    
    return 0;
}