#ifndef MLL_H
#define MLL_H
#include <string>
#include <iostream>
using namespace std;

typedef struct elmCatatan *adrCatatan;
typedef struct elmNapi *adrNapi;
typedef struct elmVonis *adrVonis;
typedef struct elmSel *adrSel;
typedef struct elmBlok *adrBlok;

//Info tanggal
struct tanggal{
    int hari;
    int bulan;
    int tahun;
};

//Info Kependudukan
struct infoKependudukan {
    string nama;
    tanggal tglLahir;
    string jenisKelamin;
};

//Struct Narapidana
struct elmNapi {
    string id;
    infoKependudukan info;
    tanggal tglMasuk;
    tanggal tglKeluar;
    tanggal tglEksekusi;
    adrVonis firstVonis;
    adrCatatan firstCatatan;
    adrNapi next;
};

//Struct Vonis
struct elmVonis {
    string id;
    string jenis;
    adrVonis next;
};

//Struct Catatan Perihal Narapidana
struct elmCatatan {
    string jenis;
    string keterangan;
    int remisi;
    adrCatatan next;
};

//Struct Sel
struct elmSel {
    int nomor;
    int kapasitas;
    adrNapi firstNapi;
    adrSel next;
};

//Struct Blok
struct elmBlok {
    string nama;
    int jumlahSel;
    adrSel firstSel;
    adrBlok next;
};

//Struct Penjara
struct Penjara {
    adrBlok first;
};

//Create
void createPenjara (Penjara &P);
void createBlok (adrBlok &B, string namaBlok, string jumlahSel);
void createSel (adrSel &S, int nomorSel, int kapasitas);
void createNapi (adrNapi &N, string idNapi, infoKependudukan info, tanggal tglMasuk, tanggal tglKeluar, tanggal tglEksekusi, tanggal tglSistem);
void createVonis (adrVonis &V, string idVonis, string jenis);
adrCatatan createCatatan (string jenis, string keterangan, int remisi);


//Insert
void insertBlok (Penjara &P, adrBlok B);
void insertSel (Penjara &P, adrBlok B, adrSel S);
void insertNapi (Penjara &P, adrSel S, adrNapi N);
void insertCatatan (Penjara &P, adrNapi N, adrCatatan C);
void insertVonis (adrNapi &N, adrVonis V);
void jebloskanNapi (Penjara &P,adrNapi N, tanggal tglSistem);
void tambahCatatan (Penjara &P, adrSel S, adrNapi N, adrCatatan C, tanggal tglSistem);

//Cari
adrBlok cariBlok (Penjara P, string nama);
adrSel cariSel (adrBlok B, string nomor);
void cariNapi (Penjara P, adrBlok &B, adrSel &S, adrNapi &N, string idNapi);

//Hapus
void hapusNapi (Penjara &P, adrSel S, adrNapi N);
void hapusSemuaVonis (adrNapi &N);
void hapusSemuaCatatan (adrNapi &N);

//Boolean
bool isFullBlok (adrBlok B);
bool isFullSel (adrSel S);
bool cekTanggal(int hari, int bulan, int tahun);
bool cekTanggal2(tanggal tgl, tanggal tglSistem);
bool cekTanggal3(tanggal tgl, tanggal tglSistem);
bool cekTanggal4(tanggal tglLahir, tanggal tgl);
bool isUniqueNapi(Penjara P, string idNapi);
bool isUniqueVonis(Penjara P, string idVonis);
bool isEmptyPenjara(Penjara P);

//Display
void displaySel (adrSel S);
void displayNapi (adrNapi N);
void displayAll (Penjara P);
void menuUtama (Penjara &P, tanggal tglSistem); //Menu Prioritas
void menuGenerasi (Penjara &P, tanggal tglSistem); //Menu Prioritas
void menuNarapidana (Penjara &P, tanggal tglSistem); //Menu Prioritas
void menuTampil (Penjara P, tanggal tglSistem); //Menu Prioritas

//Converter
string converterHari(int n);
string converterBulan(int n);

#endif
