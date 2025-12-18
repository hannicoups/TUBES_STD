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

string hari[7] = {"Senin","Selasa","Rabu","Kamis","Jum'at","Sabtu","Minggu"}
string bulan[12] = {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};
string jenisKejahatan[8] = {"Pembunuhan", "Penganiayaan", "Korupsi", "narkoba", "pelecehan", "terorisme", "perampokan", "penggelapan"};

//Info Alamat
struct infoAlamat {
    string rtRw;
    string kelDesa;
    string kecamatan;
};

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
    infoAlamat alamat;
    string statusPerkawinan;
    string pekerjaan;
    string kewarganegaraan;
};

//Struct Narapidana
struct elmNapi {
    string id;
    infoKependudukan info;
    tanggal tglMasuk;
    tanggal tglKeluar;
    tanggal tglEksekusi;
    infoAlamat lokasiPenjara;
    adrVonis firstVonis;
    string status;
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
    string id;
    string jenis;         
    string keterangan;
    int remisi;
    adrCatatan next;
};

//Struct Sel
struct elmSel {
    string nomor;
    int kapasitas;
    adrNapi firstNapi;
    adrSel next;
};

//Struct Blok
struct elmBlok {
    string id;
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
void createBlok (adrBlok &B);
void createSel (adrSel &S);
void createNapi (adrNapi &N);
void createVonis (adrVonis &V, string idVonis, string jenis);
adrCatatan createCatatan(string idCatatan, string jenis, string keterangan, int remisi);


//Insert
void insertBlok (Penjara &P, adrBlok B);          
void insertSel (Penjara &P, adrBlok B, adrSel S);     
void insertNapi (Penjara &P, adrSel S, adrNapi N);       
void insertCatatan (Penjara &P, adrNapi, adrCatatan C);    
void insertVonis (Penjara P, adrNapi &N, adrVonis V);

//Cari                                        
adrSel cariSel (adrSel S, string idSel);                                    
adrNapi cariNapi (adrSel S, string idNapi);
adrNapi cariNamaNapi(Penjara P, string namaDiCari);

//Hapus
void hapusNapi (Penjara &P, string idNapi);

//Display
void displaySel (adrSel S); 
void displayBlok (adrBlok B);            
void displayNapi (adrNapi N);        
void displayAll (Penjara P);
void menuUtama (Penjara &P); //Menu Prioritas
void menuGenerasi (Penjara &P); //Menu Prioritas
void menuNarapidana (Penjara &P); //Menu Prioritas
void menuJebloskan (Penjara &P);
void menuCatatan (Penjara &P);
void menuCari (Penjara &P); //Menu Prioritas
void menuCariSel (Penjara &P);
void menuCariNapibyId (Penjara &P);
void menuCariNapibyName (Penjara &P);

#endif
