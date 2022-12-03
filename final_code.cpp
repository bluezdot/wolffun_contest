#include <iostream>
#include <fstream>
using namespace std;

static const int MaxRow = 16;
const int MaxCol = 6;
const int MinLenght = 23;
const int MaxLenght = 25;
const int MAX = 5000;
int *maxPrint;
ofstream file;

void InKetQua(int **matran)
{
    for (int i = 0; i < MaxRow; i++)
    {
        for (int j = 0; j < MaxCol; j++)
        {
            file << matran[i][j] << " ";
        }
    }
}

// Kiểm tra điều kiện không có 4 ô kề nhau
int KiemTraDieuKien4OSatNhau(int **matran, int indexHangKiemTra, int indexCotKiemTra)
{
    if (matran[indexHangKiemTra][indexCotKiemTra] == 0 && matran[indexHangKiemTra - 1][indexCotKiemTra] > 0)
        return 0;

    return 1;
}

// Kiểm tra đã đến đích chưa
void XuLyO(int **matran, int indexHang, int indexCot, int DoDaiDuongDi, int *maxPrint);
void KiemTraDieuKienDoDaiDuongDi(int **matran, int indexHang, int indexCot, int DoDaiDuongDi, int *maxPrint)
{
    if (matran[indexHang][indexCot] != 0)
        return;

    DoDaiDuongDi++;
    matran[indexHang][indexCot] = 1;

    if (indexHang == MaxRow - 1 && DoDaiDuongDi >= MinLenght && DoDaiDuongDi <= MaxLenght)
    {

        InKetQua(matran);

        *maxPrint = *maxPrint + 1;

        if (*maxPrint >= MAX)
        {
            file.close();
            return;
        }
        else
        {
            file << endl;
        }
    }
    else if (indexHang < MaxRow - 1)
    {
        XuLyO(matran, indexHang, indexCot, DoDaiDuongDi, maxPrint);
    }
    matran[indexHang][indexCot] = 0;
}

// Giải thuật đi tới kiểm tra ô này
void XuLyO(int **matran, int indexHang, int indexCot, int DoDaiDuongDi, int *maxPrint)
{
    // Đi tới
    if (matran[indexHang + 1][indexCot] == 0)
    {
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang + 1, indexCot, DoDaiDuongDi, maxPrint);
    }

    // Đi ngang phải
    if (indexCot + 1 < MaxCol && KiemTraDieuKien4OSatNhau(matran, indexHang, indexCot + 1) == 1)
    {
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang, indexCot + 1, DoDaiDuongDi, maxPrint);
    }

    // Đi ngang trái
    if (indexCot > 1 && KiemTraDieuKien4OSatNhau(matran, indexHang, indexCot - 1) == 1)
    {
        KiemTraDieuKienDoDaiDuongDi(matran, indexHang, indexCot - 1, DoDaiDuongDi, maxPrint);
    }
}

int main()
{
    maxPrint = (int *)malloc(sizeof(int));
    *maxPrint = 0;

    file.open("result.txt");

    int **matran = new int *[MaxRow];
    for (int i = 0; i < MaxRow; i++)
        matran[i] = new int[MaxCol];
    for (int i = 0; i < MaxRow; i++)
    {
        for (int j = 0; j < MaxCol; j++)
        {
            matran[i][j] = 0;
        }
    }

    file << MAX << endl;

    // Chaỵ vòng lặp
    for (int i = 0; i < MaxCol; i++)
    {
        matran[0][i] = 1;
        KiemTraDieuKienDoDaiDuongDi(matran, 1, i, 1, maxPrint);
    }

    return 0;
}