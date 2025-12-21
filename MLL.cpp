#include "MLL.h"

using namespace std;

string hari[7] = {"Senin","Selasa","Rabu","Kamis","Jum'at","Sabtu","Minggu"};
string bulan[12] = {"Januari","Februari","Maret","April","Mei","Juni","Juli","Agustus","September","Oktober","November","Desember"};
string jenisKejahatan[8] = {"Pembunuhan", "Penganiayaan", "Korupsi", "Narkoba", "Pelecehan", "Terorisme", "Perampokan", "Penggelapan"};

void createPenjara(Penjara &P) {
    P.first = nullptr;
}

void createBlok(adrBlok &B, string namaBlok, int jumlahSel) {
    B = new elmBlok;
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
    V = new elmVonis;
    V->id = idVonis;
    V->jenis = jenis;
    V->next = nullptr;
}

void createNapi(adrNapi &N, string idNapi, infoKependudukan info, tanggal tglMasuk, tanggal tglKeluar, tanggal tglEksekusi, tanggal tglSistem) {
    N = new elmNapi;

    N->id = idNapi;
    N->info = info;
    N->tglMasuk = tglMasuk;
    N->tglKeluar = tglKeluar;
    N->tglEksekusi = tglEksekusi;
    N->firstVonis = nullptr;
    N->firstCatatan = nullptr;
    N->next = nullptr;
}

string converterBulan(int n){
    return bulan[n-1];
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

bool cekTanggal(int hari, int bulan, int tahun){
    if(0 <= tahun && 0 < bulan && bulan <= 12 && 0 < hari){
        if(bulan == 2){
            if(tahun%4 == 0 && hari <= 29){
                return true;
            } else if(hari <= 28) {
                return true;
            } else {
                return false;
            }
        } else if(bulan % 2 == 0){
            if(hari <= 31){
                return true;
            }else{
                return false;
            }
        } else {
            if(hari <= 30){
                return true;
            }else{
                return false;
            }
        }
    } else if((hari == 0 && bulan == 0 && tahun == 0) || hari == 999 && bulan == 999 && tahun == 999){
        return true;
    } else {
        return false;
    }
}

bool cekTanggal2(tanggal tgl, tanggal tglSistem){
    if((tgl.hari == 0 && tgl.bulan == 0 && tgl.tahun == 0) || tgl.hari == 999 && tgl.bulan == 999 && tgl.tahun == 999){
        return true;
    }

    if(tgl.tahun < tglSistem.tahun){
        return true;
    }else if(tgl.tahun == tglSistem.tahun && tgl.bulan < tglSistem.bulan){
        return true;
    }else if(tgl.tahun == tglSistem.tahun && tgl.bulan == tglSistem.bulan && tgl.hari < tglSistem.hari){
        return true;
    }else{
        return false;
    }
}

bool cekTanggal3(tanggal tgl, tanggal tglSistem){
    if((tgl.hari == 0 && tgl.bulan == 0 && tgl.tahun == 0) || tgl.hari == 999 && tgl.bulan == 999 && tgl.tahun == 999){
        return true;
    }

    if(tgl.tahun > tglSistem.tahun){
        return true;
    }else if(tgl.tahun == tglSistem.tahun && tgl.bulan > tglSistem.bulan){
        return true;
    }else if(tgl.tahun == tglSistem.tahun && tgl.bulan == tglSistem.bulan && tgl.hari > tglSistem.hari){
        return true;
    }else{
        return false;
    }
}

bool cekTanggal4(tanggal tglLahir, tanggal tgl){

    return(tgl.tahun-tglLahir.tahun >= 1);
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

void insertSel (Penjara &P, adrBlok B, adrSel S){
    adrSel Stemp;

    if(B->firstSel == nullptr){
        B->firstSel = S;
    } else {
        Stemp = B->firstSel;
        while(Stemp->next != nullptr){
            Stemp = Stemp->next;
        }
        Stemp->next = S;
    }
}

void insertNapi(Penjara &P, adrSel S, adrNapi N){
    adrNapi Ntemp;

    Ntemp = S->firstNapi;

    if(Ntemp == nullptr){
        S->firstNapi = N;
    } else {
        while(Ntemp->next == nullptr){
            Ntemp = Ntemp->next;
        }
        Ntemp->next = N;
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

void insertCatatan(Penjara &P, adrNapi N, adrCatatan C) {
    if(N->firstCatatan == nullptr){
        N->firstCatatan == C;
    } else {
        adrCatatan C2;
        C2 = N->firstCatatan;
        while(N->next != nullptr){
            C2 = C2->next;
        }
        C2->next = C;
    }
}

adrBlok cariBlok(Penjara P, string nama){
    adrBlok B;
    bool isFound = false;
    B = P.first;
    while(B != nullptr && !isFound){
        if(B->nama == nama){
            isFound = true;
        } else {
            B = B->next;
        }
    }
    return B;
}

adrSel cariSel(adrBlok B, int Nomor) {
    adrSel S = B->firstSel;
    bool isNotFound = true;

    while(S != nullptr && isNotFound){
        if(S->nomor == Nomor){
            isNotFound = false;
        } else {
            S = S->next;
        }
    }

    return S;
}

void cariNapi(Penjara P, adrBlok &B, adrSel &S, adrNapi &N, string idNapi) {
    bool isFound = false;
    B = P.first;
    while(B != nullptr && !isFound){
        S = B->firstSel;
        while(S != nullptr && !isFound){
            N = S->firstNapi;
            while(N != nullptr && !isFound){
                if(N->id == idNapi){
                    isFound = true;
                } else {
                    N = N->next;
                }
            }
            if(!isFound){
                S = S->next;
            }
        }
        if(!isFound){
            B = B->next;
        }
    }

    if(!isFound){
        cout << "Narapidana dengan id diberikan tidak ditemukan." << endl;
    } else {
        cout << "Narapidana ditemukan!" << endl;
    }
}

void hapusNapi(Penjara &P, adrSel S, adrNapi N) {
    adrNapi prec;
    adrVonis v;
    adrCatatan c;

    if(S->firstNapi == N){
        S->firstNapi = N->next;
        N->next = nullptr;
        v = N->firstVonis;
        while(v != nullptr){
            N->firstVonis = N->firstVonis->next;
            delete v;
            v = N->firstVonis;
        }
        c = N->firstCatatan;
        while(c != nullptr){
            N->firstCatatan = N->firstCatatan->next;
            delete c;
            c = N->firstCatatan;
        }
        delete N;
    } else {
        prec = S->firstNapi;
        while(prec->next != N){
            prec = prec->next;
        }
        prec = N->next;
        N->next = nullptr;
        delete N;
        while(v != nullptr){
            N->firstVonis = N->firstVonis->next;
            delete v;
            v = N->firstVonis;
        }
        c = N->firstCatatan;
        while(c != nullptr){
            N->firstCatatan = N->firstCatatan->next;
            delete c;
            c = N->firstCatatan;
        }
        delete N;
    }
}


void displayNapi(adrNapi N) {
    cout << "--------------------------------" << endl;
    cout << "              NAPI              " << endl;
    cout << "--------------------------------" << endl;
    cout << "Id Narapidana    : " << N -> id << endl;
    cout << "Nama             : " << N->info.nama << endl;
    cout << "Tanggal Lahir    : " << N->info.tglLahir.hari << " " << converterBulan(N->info.tglLahir.bulan) << " " << N->info.tglLahir.tahun << endl;
    cout << "Jenis Kelamin    : " << N->info.jenisKelamin << endl;
    cout << "Tanggal Masuk    : " << N->tglMasuk.hari << " " << converterBulan(N->tglMasuk.bulan) << " " << N->tglMasuk.tahun << endl;
    cout << "Tanggal Keluar   : " << N->tglKeluar.hari << " " << converterBulan(N->tglKeluar.bulan) << " " << N->tglKeluar.tahun << endl;
    cout << "Tanggal Eksekusi : " << N->tglEksekusi.hari << " " << converterBulan(N->tglEksekusi.bulan) << " " << N->tglEksekusi.tahun << endl;
}

void displaySel(adrSel S) {
    cout << "-------------------------------" << endl;
    cout << "              SEL              " << endl;
    cout << "-------------------------------" << endl;
    cout << "Nomor      : " << S->nomor << endl;
    cout << "Kapasitas  : " << S->kapasitas << endl;
    cout << "Narapidana : " << endl;
    adrNapi N;
    int i = 1;
    N = S->firstNapi;
    while(N != nullptr){
        cout << "Id Narapidana   " << i << " : " << N->id << endl;
        cout << "Nama Narapidana " << i << " : " << N->info.nama << endl;
    }
}

void displayAll(Penjara P) {
    cout << "Penjara" << endl;
    adrBlok B = P.first;
    adrSel S;
    adrNapi N;
    while(B != nullptr){
        cout << "  " << B->nama << endl;
        S = B->firstSel;
        while(S != nullptr){
            cout << "    " << S->nomor << endl;
            N = S->firstNapi;
            while(N != nullptr){
                cout << "      " << N->info.nama << endl;
                N = N->next;
            }
            S = S->next;
        }
        B = B->next;
    }
}


bool isFullBlok (adrBlok B){
    adrSel S = B->firstSel;
    adrNapi N;
    int i1,i2;
    while (S->next != nullptr){
        S = S->next;
    }

    if(isFullSel(S)){
        return true;
    } else {
        return false;
    }

}

bool isFullSel (adrSel S){
    adrNapi N;
    int i1, i2;
    N = S->firstNapi;
    i1 = 0;
    i2 = S->kapasitas;
    while(N != nullptr){
        i1++;
        N = N->next;
    }

    if(i1 == i2){
        return true;
    } else {
        return false;
    }
}

void jebloskanNapi (Penjara &P, adrNapi N, tanggal tglSistem){
    if(18 > (tglSistem.tahun - N->info.tglLahir.tahun)){
        if(isFullBlok (cariBlok(P,"D"))){
            cout << endl;
            cout << "Blok penuh" << endl;
            cout << endl;
            adrVonis v = N->firstVonis;
            if(v==nullptr){
            } else if(v->next == nullptr){
                N->firstVonis = nullptr;
                delete v;
            } else {
                while(v!=nullptr){
                N->firstVonis=v->next;
                delete v;
                v = N->firstVonis;
                }
            }
            delete N;
        } else {
            adrBlok B;
            adrSel S;
            B = cariBlok(P,"D");
            S = B->firstSel;
            while(isFullSel(S)){
                S = S->next;
            }
            insertNapi(P,S,N);
        }
    } else if(N->info.jenisKelamin == "Perempuan"){
        if(isFullBlok (cariBlok(P,"C"))){
            cout << endl;
            cout << "Blok penuh" << endl;
            cout << endl;
            adrVonis v = N->firstVonis;
            if(v==nullptr){
            } else if(v->next == nullptr){
                N->firstVonis = nullptr;
                delete v;
            } else {
                while(v!=nullptr){
                N->firstVonis=v->next;
                delete v;
                v = N->firstVonis;
                }
            }
            delete N;
        } else {
            adrBlok B;
            adrSel S;
            B = cariBlok(P,"C");
            S = B->firstSel;
            while(isFullSel(S)){
                S = S->next;
            }
            insertNapi(P,S,N);
        }
    } else if((N->tglEksekusi.tahun == 0 && N->tglEksekusi.bulan == 0 && N->tglEksekusi.hari == 0) || (N->tglKeluar.tahun == 999 && N->tglKeluar.bulan == 999 && N->tglKeluar.hari == 999)){
        if(isFullBlok (cariBlok(P,"A"))){
            cout << endl;
            cout << "Blok penuh" << endl;
            cout << endl;
            adrVonis v = N->firstVonis;
            if(v==nullptr){
            } else if(v->next == nullptr){
                N->firstVonis = nullptr;
                delete v;
            } else {
                while(v!=nullptr){
                N->firstVonis=v->next;
                delete v;
                v = N->firstVonis;
                }
            }
            delete N;
        } else {
            adrBlok B;
            adrSel S;
            B = cariBlok(P,"B");
            S = B->firstSel;
            while(isFullSel(S)){
                S = S->next;
            }
            insertNapi(P,S,N);
        }
    } else {
        if(isFullBlok (cariBlok(P,"B"))){
            cout << endl;
            cout << "Blok penuh" << endl;
            cout << endl;
            adrVonis v = N->firstVonis;
            if(v==nullptr){
            } else if(v->next == nullptr){
                N->firstVonis = nullptr;
                delete v;
            } else {
                while(v!=nullptr){
                N->firstVonis=v->next;
                delete v;
                v = N->firstVonis;
                }
            }
            delete N;
        } else {
            adrBlok B;
            adrSel S;
            B = cariBlok(P,"A");
            S = B->firstSel;
            while(isFullSel(S)){
                S = S->next;
            }
            insertNapi(P,S,N);
        }
    }
}

void tambahCatatan(Penjara &P, adrSel S, adrNapi N, adrCatatan C, tanggal tglSistem){
    insertCatatan(P,N,C);

    if(C->jenis == "Remisi" && tglSistem.tahun>=(N->tglKeluar.tahun)-(C->remisi/12) && tglSistem.bulan>=(N->tglKeluar.bulan)-(C->remisi%12)){
        hapusNapi(P,S,N);
    } else if(C->jenis == "Mutasi"){
        hapusNapi(P,S,N);
    }
}

void menuUtama(Penjara &P, tanggal tglSistem) {
    int opsi = -1;
    bool isChosen = false;
    while(opsi != 0){
        isChosen = false;
        cout << "---------------------" << endl;
        cout << "      MENU UTAMA     " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Generasi Penjara" << endl;
        cout << " 2.Kelola Narapidana" << endl;
        cout << " 3.Tampilkan" << endl;
        cout << " 0.Keluar" << endl;
        cout << "--------------------" << endl;

        while(opsi != 0 && !isChosen){
            cout << "Pilih : ";
            cin >> opsi;
            cout << endl;

            switch(opsi){
                case 1:
                    menuGenerasi(P,tglSistem);
                    isChosen = true;
                    break;
                case 2:
                    if(P.first == nullptr){
                        cout << endl;
                        cout << "Penjara belum digenerasi!" << endl;
                        cout << endl;
                    } else {
                        menuNarapidana(P,tglSistem);
                    }
                    isChosen = true;
                    break;
                case 3:
                    if(P.first == nullptr){
                        cout << endl;
                        cout << "Penjara belum digenerasi!" << endl;
                        cout << endl;
                    } else {
                        menuTampil(P,tglSistem);
                    }
                    isChosen = true;
                    break;
                case 0:
                    isChosen = true;
                    break;
                default:
                    isChosen = true;
                    cout << endl;
                    cout << "Opsi tidak valid" << endl;
                    cout << endl;
            }
        }
    }
}

void menuGenerasi (Penjara &P, tanggal tglSistem){
    if(P.first == nullptr){
        adrBlok B;
        adrSel S;

        int i,n1,n2;

        cout << "----------------------------------------------------" << endl;
        cout << "                  GENERASI PENJARA                  " << endl;
        cout << "----------------------------------------------------" << endl;
        cout << "PETUNJUK: TENTUKAN KUANTITAS SEL PADA SETIAP BLOK" << endl;
        cout << "[INFORMASI] BLOK SUDAH TERDEFINISI SEBAGAI BERIKUT:" << endl;
        cout << "            BLOK A UNTUK KRIMINAL BERBAHAYA" << endl;
        cout << "            BLOK B UNTUK KRIMINAL PRIA" << endl;
        cout << "            BLOK C UNTUK KRIMINAL WANITA" << endl;
        cout << "            BLOK D UNTUK KRIMINAL DI BAWAH UMUR" << endl;
        cout << endl;
        cout << "[TENTUKAN QUANTITAS DAN KAPASITAS SEL (CONTOH: '5  2')]" << endl;
        i = 1;
        cout << "BLOK A: ";
        cin >> n1 >> n2;
        cout << endl;
        createBlok(B,"A",n1);
        insertBlok(P, B);
        while(i <= n1){
            createSel(S,i,n2);
            insertSel(P,B,S);
            i++;
        }

        i = 1;
        cout << "BLOK B: ";
        cin >> n1 >> n2;
        cout << endl;
        createBlok(B,"B",n1);
        insertBlok(P, B);
        while(i <= n1){
            createSel(S,i,n2);
            insertSel(P,B,S);
            i++;
        }

        i = 1;
        cout << "BLOK C: ";
        cin >> n1 >> n2;
        cout << endl;
        createBlok(B,"C",n1);
        insertBlok(P, B);
        while(i <= n1){
            createSel(S,i,n2);
            insertSel(P,B,S);
            i++;
        }

        i = 1;
        cout << "BLOK D: ";
        cin >> n1 >> n2;
        cout << endl;
        createBlok(B,"D",n1);
        insertBlok(P, B);
        while(i <= n1){
            createSel(S,i,n2);
            insertSel(P,B,S);
            i++;
        }

        cout << endl;
        cout << "PENJARA SUKSES DIGENERASI!" << endl;
        cout << endl;
    } else {
        cout << endl;
        cout << "PENJARA SUDAH DIGENERASI." << endl;
        cout << endl;
    }
    return;
}

void menuNarapidana (Penjara &P, tanggal tglSistem){
    int opsi = -1;
    bool isChosen = false;
    while(opsi != 3){
        isChosen = false;
        cout << "---------------------" << endl;
        cout << "   MENU NARAPIDANA   " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Tambah Narapidana" << endl;
        cout << " 2.Tambah Catatan" << endl;
        cout << " 3.Kembali" << endl;
        cout << "---------------------" << endl;

        while(opsi != 3){
            cout << "Pilih : ";
            cin >> opsi;
            cout << endl;

            switch(opsi){
                case 1: {
                    isChosen = true;
                    int n;
                    cout << "PETUNJUK: TANGGAL DIISI DALAM BILANGAN BULAT." << endl;
                    cout << "PETUNJUK: JENIS KELAMIN DIISI 'Perempuan' ATAU 'Laki-laki'." << endl;
                    cout << "PETUNJUK: ISI HARI = 0, BULAN = 0, TAHUN = 0 UNTUK PENGOSONGAN." << endl;
                    cout << "PETUNJUK: ISI HARI = 999, BULAN = 999, TAHUN = 999 UNTUK PENANDAAN SEUMUR HIDUP." << endl;
                    cout << endl;
                    int i1 = 0;
                    string idNapi;
                    infoKependudukan info;
                    tanggal tglMasuk,tglKeluar,tglEksekusi;
                    bool isValid = false;
                    cout << "Berapa narapidana yang ingin ditambahkan (Jawab dalam integer)? ";
                    cin >> n;
                    cout << endl;
                    while(i1 < n){
                        cout << "ID Narapidana: ";
                        cin >> idNapi;
                        cout << "Nama Narapidana: ";
                        cin >> info.nama;
                        while(!isValid){
                            cout << "Tanggal Lahir Narapidana: " << endl;
                            cout << "Hari: ";
                            cin >> info.tglLahir.hari;
                            cout << "Bulan: ";
                            cin >> info.tglLahir.bulan;
                            cout << "Tahun: ";
                            cin >> info.tglLahir.tahun;
                            if(cekTanggal(info.tglLahir.hari,info.tglLahir.bulan,info.tglLahir.tahun) && cekTanggal2(info.tglLahir,tglSistem)){
                                cout << endl;
                                cout << "Tanggal valid." << endl;
                                cout << endl;
                                isValid = true;
                            } else {
                                cout << endl;
                                cout << "Tanggal tidak valid!" << endl;
                                cout << endl;
                            }
                        }
                        isValid = false;
                        while(!isValid){
                            cout << "Jenis Kelamin Narapidana: ";
                            cin >> info.jenisKelamin;
                            cout << endl;
                            if(info.jenisKelamin == "Laki-laki" || info.jenisKelamin == "Perempuan"){
                                cout << "Jenis kelamin valid." << endl;
                                cout << endl;
                                isValid = true;
                            } else {
                                cout << "Jenis kelamin tidak valid!" << endl;
                                cout << endl;
                            }
                        }
                        isValid = false;
                        while(!isValid){
                            cout << "Tanggal Masuk Narapidana: " << endl;
                            cout << "Hari: ";
                            cin >> tglMasuk.hari;
                            cout << endl;
                            cout << "Bulan: ";
                            cin >> tglMasuk.bulan;
                            cout << endl;
                            cout << "Tahun: ";
                            cin >> tglMasuk.tahun;
                            cout << endl;
                            if(cekTanggal(tglMasuk.hari,tglMasuk.bulan,tglMasuk.tahun) && cekTanggal2(tglMasuk,tglSistem) && cekTanggal4(info.tglLahir,tglMasuk)){
                                cout << "Tanggal valid." << endl;
                                cout << endl;
                                isValid = true;
                            } else {
                                cout << "Tanggal tidak valid!" << endl;
                                cout << endl;
                            }
                        }
                        isValid = false;
                        while(!isValid){
                            cout << "Tanggal Keluar Narapidana: " << endl;
                            cout << "Hari: ";
                            cin >> tglKeluar.hari;
                            cout << endl;
                            cout << "Bulan: ";
                            cin >> tglKeluar.bulan;
                            cout << endl;
                            cout << "Tahun: ";
                            cin >> tglKeluar.tahun;
                            cout << endl;
                            if(cekTanggal(tglKeluar.hari,tglKeluar.bulan,tglKeluar.tahun) && cekTanggal3(tglKeluar,tglSistem) && cekTanggal4(info.tglLahir,tglMasuk)){
                                cout << "Tanggal valid." << endl;
                                cout << endl;
                                isValid = true;
                            } else {
                                cout << "Tanggal tidak valid!" << endl;
                                cout << endl;
                            }
                        }
                        isValid = false;
                        if(tglKeluar.hari == 0 && tglKeluar.bulan == 0 && tglKeluar.tahun == 0){
                            while(!isValid){
                                cout << "Tanggal Eksekusi Narapidana: " << endl;
                                cout << "Hari: ";
                                cin >> tglEksekusi.hari;
                                cout << endl;
                                cout << "Bulan: ";
                                cin >> tglEksekusi.bulan;
                                cout << endl;
                                cout << "Tahun: ";
                                cin >> tglEksekusi.tahun;
                                cout << endl;
                                if(cekTanggal(tglEksekusi.hari,tglEksekusi.bulan,tglEksekusi.tahun) && cekTanggal3(tglEksekusi,tglSistem) && cekTanggal4(info.tglLahir,tglMasuk)){
                                    cout << "Tanggal valid." << endl;
                                    cout << endl;
                                    isValid = true;
                                } else {
                                    cout << "Tanggal tidak valid!" << endl;
                                    cout << endl;
                                }
                            }
                        } else {
                            tglEksekusi.hari = 0;
                            tglEksekusi.bulan = 0;
                            tglEksekusi.tahun = 0;
                        }
                        adrNapi N;
                        string cek, idVonis, jenisVonis;
                        adrVonis V;
                        bool isNotValid;
                        int i2;

                        createNapi(N,idNapi,info,tglMasuk,tglKeluar,tglEksekusi,tglSistem);
                        cout << "---------------------------------------------------" << endl;
                        cout << "BUAT ELEMEN VONIS UNTUK DIINPUTKAN PADA ELEMEN NAPI" << endl;
                        cout << "---------------------------------------------------" << endl;
                        cout << endl;
                        while(cek != "YES"){
                            isNotValid = true;
                            cout << "ID Vonis: ";
                            cin >> idVonis;
                            cout << endl;
                            while(isNotValid){
                                i2 = 0;
                                cout << "Jenis Vonis: ";
                                cin >> jenisVonis;
                                cout << endl;
                                while(i2 < 8 && isNotValid){
                                    if(jenisKejahatan[i2]==jenisVonis){
                                        isNotValid = false;
                                    }
                                    i2++;
                                }
                                if(isNotValid){
                                    cout << endl;
                                    cout << "Jenis Kejahatan Tidak Valid." << endl;
                                    cout << endl;
                                }
                            }
                            createVonis(V,idVonis,jenisVonis);
                            insertVonis(N,V);
                            cout << "Keluar (YES/ANY KEY(NO))? ";
                            cin >> cek;
                            cout << endl;
                        }
                        jebloskanNapi(P,N,tglSistem);

                        cout << endl;
                        cout << "Narapidan berhasil ditambahkan!" << endl;
                        cout << endl;
                        i1++;
                    }
                    break;
                }
                case 2: {
                    isChosen = true;
                    adrNapi N;
                    adrSel S;
                    adrBlok B;
                    adrCatatan C;
                    string idNapi;
                    string idCatatan, jenis, keterangan;
                    int remisi;
                    cout << "Id Narapidana: " << endl;
                    cin >> idNapi;
                    cout << endl;
                    cout << "Id Catatan: " << endl;
                    cin >> idCatatan;
                    cout << endl;
                    cout << "jenis Catatan (Remisi/Mutasi): " << endl;
                    cin >> jenis;
                    cout << endl;
                    cout << "Remisi (dalam Bulan): " << endl;
                    cin >> remisi;
                    cout << endl;
                    cout << "Keterangan Catatan (Bebas): " << endl;
                    cin >> keterangan;
                    cout << endl;
                    createCatatan(idCatatan,jenis,keterangan,remisi);
                    cariNapi(P,B,S,N,idNapi);
                    tambahCatatan(P,S,N,C,tglSistem);
                    cout << "Catatan berhasil ditambahkan!" << endl;
                    break;
                }
                case 3:
                    isChosen = true;
                    break;
                default:
                    isChosen = true;
                    cout << endl;
                    cout << "Opsi tidak valid" << endl;
                    cout << endl;
            }
        }
    }
    return;
}

void menuTampil(Penjara P, tanggal tglSistem){
    int opsi = -1;
    bool isChosen = false;
    while(opsi != 4){
        isChosen = false;
        cout << "---------------------" << endl;
        cout << "     MENU TAMBAH     " << endl;
        cout << "---------------------" << endl;
        cout << " 1.Tampil Semua" << endl;
        cout << " 2.Tampil Narapidana" << endl;
        cout << " 3.Tampil Blok" << endl;
        cout << " 4.Kembali" << endl;
        cout << "---------------------" << endl;

        while(opsi != 4 && !isChosen){
            cout << "Pilih : ";
            cin >> opsi;
            cout << endl;

            switch(opsi){
                case 1:
                    isChosen = true;
                    displayAll(P);
                    break;
                case 2:{
                    isChosen = true;
                    string idNapi;
                    adrBlok B;
                    adrSel S;
                    adrNapi N;
                    cout << endl;
                    cout << "Id Napi: ";
                    cin >> idNapi;
                    cout << endl;
                    cariNapi(P,B,S,N,idNapi);
                    if(N == nullptr){
                        cout << "Narapidana dengan Id terkait tidak ditemukan!" << endl;
                    } else {
                        cout << endl;
                        cout << "Blok : " << B->nama << endl;
                        cout << "Sel  : " << S->nomor << endl;
                        displayNapi(N);
                    }
                    break;
                }
                case 3: {
                    isChosen = true;
                    adrBlok B;
                    adrSel S;
                    string namaBlok;
                    cout << "Blok: ";
                    cin >> namaBlok;
                    cout << endl;
                    B = cariBlok(P, namaBlok);
                    S = B->firstSel;
                    while(S != nullptr){
                        displaySel(S);
                        S = S->next;
                    }
                    break;
                }
                case 4:
                    isChosen = true;
                    break;
                default:
                    isChosen = true;
                    cout << endl;
                    cout << "Opsi tidak valid" << endl;
                    cout << endl;
            }
        }
    }
    return;
}
