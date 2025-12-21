#include "MLL.h"

using namespace std;

int main()
{
    tanggal tglSistem;
    bool isValid = false;

    while(!isValid){
        cout << "Tentukan Tanggal Sistem (Dalam Bilangan Bulat): " << endl;
        cout << "Tanggal Hari: ";
        cin >> tglSistem.hari;

        cout << "Tanggal Bulan: ";
        cin >> tglSistem.bulan;

        cout << "Tanggal Tahun: ";
        cin >> tglSistem.tahun;
        cout << endl;
        if(cekTanggal(tglSistem.hari, tglSistem.bulan, tglSistem.tahun)){
            isValid = true;
            cout << "Tanggal sudah valid!" << endl;
        } else {
            cout << "Tanggal tidak valid!" << endl;
        }
        cout << endl;
    }
    Penjara P;
    createPenjara(P);
    menuUtama(P,tglSistem);
}
