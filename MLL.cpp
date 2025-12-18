#include "MLL.h"

using namespace std;

void createPenjara(Penjara &P) {
    P.first = nullptr;
}

void createBlok(adrBlok &B, string idBlok, string namaBlok, string jumlahSel) {
    B = new elmBlok;
    B->id = idBlok;
    B->nama = namaBlok;
    B->jumlahSel = jumlahSel;
    B->firstSel = nullptr;
    B->next = nullptr;
}

void createSel(adrSel &S, int nomorSel, int kapasitas) {
    S = new elmSel;
    S->nomor = nomorSel;
    S->kapasitas = kapasitas;
    S->firstNapi = nullptr;
    S->next = nullptr;
}

void createVonis(adrVonis &V, string idVonis, string jenis) {

    bool isNotValid = true;
    int i = 0;

    while(i < NMAX && isNotValid){
        if(jenisKejahatan[i]==jenis){
            isNotValid = false;
        }
        i++;
    }

    if(!isNotValid){
        V = new elmVonis;
        V->id = idVonis;
        V->jenis = jenis;
        V->next = nullptr;
        cout << "Elemen Vonis Telah Dibuat." << endl;
    } else {
        cout << "Jenis Kejahatan Tidak Valid, Elemen Vonis Gagal Dibuat." << endl;
    }
}

void createNapi(adrNapi &N, string idNapi, infoKependudukan info, tanggal tglMasuk, tanggal tglKeluar, tanggal tglEksekusi, infoAlamat lokasiPenjara) {
    N = new elmNapi;
    string cek, idVonis, jenisVonis, status;
    adrVonis V;
    N->id = idNapi;
    
    N->id = idNapi;
    N->info = info;
    N->tglMasuk = tglMasuk;
    N->tglKeluar = tglKeluar;
    N->tglEksekusi = tglEksekusi;
    N->lokasiPenjara = lokasiPenjara;
    cout << "---------------------------------------------------" << endl;
    cout << "BUAT ELEMEN VONIS UNTUK DIINPUTKAN PADA ELEMEN NAPI" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "PETUNJUK: ENTER 'YES' UNTUK KELUAR" << endl;
    cout << endl;
    while(cek != "EXIT"){
        cout << "ID Vonis: ";
        cin >> idVonis;
        cout << endl;
        cout << "Jenis Vonis: ";
        cin >> jenisKejahatan;
        cout << endl;
        createVonis(V,idVonis,jenisVonis);
        insertVonis(N,V);
        cout << "Keluar (YES/ANY KEY)? ";
        cin >> cek;
        cout << endl;
    }
    cout << endl;
    cout << "PETUNJUK: 'BAIK' ATAU 'BURUK'" << endl;
    cout << endl;

    while(status != "BAIK" && status != "BURUK"){
        cout << "Status:";
        cin >> prilaku;
        cout << endl;
    }
    N->statusPrilaku = prilaku;
    N->firstCatatan = nullptr;
    N->next = nullptr;
}

adrCatatan createCatatan(string idCatatan, string jenis, string keterangan, int remisi) {
    adrCatatan C = new elmCatatan;
    C->id = idCatatan;
    C->jenis = jenis;
    C->keterangan = keterangan;
    C->remisi = remisi; //Dalam bulan
    C->next = nullptr;
    return C;
}

void insertBlok(Penjara &P, adrBlok B) {
    if (P.first == nullptr) {
        P.first = B;
    } else {
        adrBlok Q = P.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = B;
    }
}

void insertSel(Penjara &P, adrSel S) {
    if (P.first == nullptr) {
        cout << "Belum ada blok penjara. Tambahkan blok terlebih dahulu!" << endl;
        return;
    }

    adrBlok B = P.first;
    while (B->next != nullptr) {
        B = B->next;
    }

    if (B->firstSel == nullptr) {
        B->firstSel = S;
    } else {
        adrSel Q = B->firstSel;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = S;
    }
}

void insertNapi(Penjara &P, adrSel S, adrNapi N){
    adrNapi Nkosong;
    if(S->firstNapi == nullptr){
        S->firstNapi = N;
    } else {
        Nkosong = S->firstNapi;
        while(S)
    }
}

void insertVonis(adrNapi &N, adrVonis V) {
// F.S. Elemen vonis yang diinput menjadi elemen terakhir pada adNapi.
    if(N->firstVonis == nullptr){
        N->firstVonis = V;
    } else if(N->firstVonis->next == nullptr){
        N->firstVonis->next = V;
    } else {
        adrVonis V2 = N->firstVonis;
        while(V2->next != nullptr){
            V2->next = V;
        }
    }
}

void insertCatatan(Penjara &P, adrCatatan C) {
    adrBlok B = P.first;
    adrNapi lastNapi = nullptr;

    while (B != nullptr) {
        adrSel S = B->firstSel;
        while (S != nullptr) {
            adrNapi N = S->firstNapi;
            while (N != nullptr) {
                lastNapi = N;
                N = N->next;
            }
            S = S->next;
        }
        B = B->next;
    }

    if (lastNapi == nullptr) {
        cout << "Tidak ada napi" << endl;
    } else {
        if (lastNapi->firstCatatan == nullptr) {
            lastNapi->firstCatatan = C;
        } else {
            adrCatatan Q = lastNapi->firstCatatan;
            while (Q->next != nullptr) {
                Q = Q->next;
            }
            Q->next = C;
        }
    }
}

adrSel cariSel(adrSel S, string idSel) {
    adrSel P = S;
    while (P != nullptr) {
        if (P->nomor == idSel) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

adrNapi cariNapi(adrSel K, string idNapi) {
    adrNapi N = K->firstNapi;
    while (N != nullptr) {
        if (N->id == idNapi) {
            return N;
        }
        N = N->next;
    }
    return nullptr;
}

adrNapi cariNamaNapi(Penjara P, string namaDiCari) {
    adrBlok B = P.first;
    while (B != nullptr) {
        adrSel S = B->firstSel;
        while (S != nullptr) {
            adrNapi N = S->firstNapi;
            while (N != nullptr) {
                if (N->info.nama == namaDiCari) {
                    return N;
                }
                N = N->next;
            }
            S = S->next;
        }
        B = B->next;
    }
    return nullptr;
}

void hapusNapi(Penjara &P, string idNapi) {
    adrBlok B = P.first;

    while (B != nullptr) {
        adrSel S = B->firstSel;
        while (S != nullptr) {
            adrNapi prev = nullptr;
            adrNapi N = S->firstNapi;

            while (N != nullptr) {
                if (N->id == idNapi) {
                    if (prev == nullptr) {
                        S->firstNapi = N->next;
                    } else {
                        prev->next = N->next;
                    }
                    delete N;
                    cout << "Napi berhasil dihapus" << endl;
                    // lanjut cek napi lain (kalau ada id sama, tapi biasanya unik)
                    break;
                }
                prev = N;
                N = N->next;
            }
            S = S->next;
        }
        B = B->next;
    }
}


void displayNapi(adrNapi N) {
    cout << "ID Napi : " << N->id << endl;
    cout << "Nama    : " << N->info.nama << endl;
    cout << "Masuk   : " 
         << N->tglMasuk.hari << "-"
         << N->tglMasuk.bulan << "-"
         << N->tglMasuk.tahun << endl;
    cout << "Status  : " << N->statusPrilaku << endl;
    cout << "Kelas   : " << N->kelasKriminal << endl;
    cout << "-------------------------------" << endl;
}

void displaySel(adrSel S) {
    while (S != nullptr) {
        cout << "  Sel " << S->nomor << " (kapasitas: " << S->kapasitas << ")" << endl;
        adrNapi N = S->firstNapi;
        if (N == nullptr) {
            cout << "    (Tidak ada napi)" << endl;
        }
        while (N != nullptr) {
            cout << "    ";
            displayNapi(N);
            N = N->next;
        }
        S = S->next;
    }
}

void displayBlok(adrBlok B) {
    while (B != nullptr) {
        cout << "Blok " << B->nama << " (ID: " << B->id << ", jumlah sel: " << B->jumlahSel << ")" << endl;
        displaySel(B->firstSel);
        cout << "======================================" << endl;
        B = B->next;
    }
}

void displayAll(Penjara P) {
    if (P.first == nullptr) {
        cout << "Penjara kosong\n";
    } else {
        displayBlok(P.first);
    }
}

void menuUtama() {
    int opsi = -1; 
    while(opsi != 0){
        cout << "---------------------" << endl;
        cout << "      MENU UTAMA     " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Generasi Penjara" << endl;
        cout << " 2.Kelola Narapidana" << endl;
        cout << " 3.Query" << endl;
        cout << " 0.Keluar" << endl;
        cout << "--------------------" << endl;
    
        while(opsi != 0){
            cout << "Pilih : ";
            cin >> opsi;
            cout << endl;

            switch(opsi){
                case 1: 
                    menuGenerasi(P);
                    break;
                case 2:
                    menuNarapidana(P);
                    break;
                case 3:
                    menuCari(P);
                    break;
                case 0:
                    break;
                default:
                    cout << endl;
                    cout << "Opsi tidak valid" << endl;
                    cout << endl;
            }
        }
    }
}

void menuGenerasi (Penjara &P){
    if(P.first == nullptr){
        i = 0;
        adrBlok B;
        string idBlok,namaBlok;
        int qtySel;
        cout << "------------------" << endl;
        cout << " GENERASI PENJARA " << endl;
        cout << "------------------" << endl;
        cout << "PETUNJUK: TENTUKAN KUANTITAS SEL PADA SETIAP BLOK"
        while(i < 4){
            cout << "Id Blok: "
            cin >> idBlok;
            cout << endl;
        }
    } else {

    }
}

void menuNarapidana (Penjara &P){
    int opsi = -1;
    while(opsi != 3){
        cout << "---------------------" << endl;
        cout << "   MENU NARAPIDANA   " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Tambah Narapidana" << endl;
        cout << " 2.Tambah Catatan" << endl;
        cout << " 3.return" << endl;
        cout << "--------------------" << endl;      
        
        while(opsi != 3){
            cout << "Pilih : ";
            cin >> opsi;
            cout << endl;

            switch(opsi){
                case 1: 
                    menuJebloskan(P);
                    break;
                case 2:
                    menuCatatan(P);
                    break;
                case 3:
                    break;
                default:
                    cout << endl;
                    cout << "Opsi tidak valid" << endl;
                    cout << endl;
            }
        }
    }   
    return 
}

void menuJebloskan (Penjara &P){
    int opsi = -1;
    while(opsi != 0){
        cout << "---------------------" << endl;
        cout << "    MENU JEBLOSKAN  " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Masukkan Napi ke Sel" << endl;
        cout << " 0.return" << endl;
        cout << "--------------------" << endl;        
        cout << "Pilih : ";
        cin >> opsi;

        switch(opsi){
            case 1: 
                string idBlok, nomorSel, idNapi;
                adrBlok = P.first;
                adrSel S;
                adrNapi N;

                infoKependudukan info;
                tanggal tglMasuk, tglKeluar, tglEksekusi;
                infoAlamat lokasi;
                
                
                cout << "ID Blok : "; 
                cin >> idBlok;
                while (B != nullptr && B->id != idBlok){
                    B = B->next;
                }
                if(B == nullptr){
                    cout << "Blok tidak ditemukan!" << endl;
                    break;
                }


                cout << "Nomor Sel : ";
                cin >> nomorSel;
            
                S = cariSel(B->firstSel, nomorSel);
                if(S == nullptr){
                    cout << "Sel tidak ditemukan!" << endl;
                    break;
                }

                cout << "ID Napi : ";
                cin >> idNapi;

                cout << "Nama    : ";
                cin >> info.nama;

                cout << "Tanggal Masuk (dd mm yyyy): ";
                cin >> tglMasuk.hari >> tglMasuk.bulan >> tglMasuk.tahun;

                cout << "Tanggal Keluar (dd mm yyyy): ";
                cin >> tglKeluar.hari >> tglKeluar.bulan >> tglKeluar.tahun;

                cout << "Tanggal Eksekusi (dd mm yyyy): ";
                cin >> tglEksekusi.hari >> tglEksekusi.bulan >> tglEksekusi.tahun;

                cout << "RT/RW        : ";
                cin >> lokasi.rtRw;
                cout << "Kel/Desa     : ";
                cin >> lokasi.kelDesa;
                cout << "Kecamatan    : ";
                cin >> lokasi.kecamatan;

                createNapi(N, idNapi, info, tglMasuk, tglKeluar, tglEksekusi, lokasi);
                insertNapi(P, S, N);
                cout << "Narapidana berhasil dimasukkan ke sel" << endl; 


            case 0: 
                break;

            default:
                cout << endl;
                cout << "Opsi tidak valid" << endl;
                cout << endl;
                    
        }
    }    
}

void menuCatatan (Penjara &P){

}
void menuCari (Penjara &P){

}
void menuCariSel (Penjara &P){

}
void menuCariNapibyId (Penjara &P){

}
void menuCariNapibyName (Penjara &P){

}
void menuHapus (Penjara &P){

}