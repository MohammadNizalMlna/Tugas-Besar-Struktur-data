// Daffa Falih Aqilah - 2311102137
// Mohammad Nizal Maulana - 2311102150

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <stack>

using namespace std;

// Struktur untuk menyimpan informasi rekening
struct akunBank {
    int NomorRekening;
    string UserName;
    string saldo;

    akunBank(int norek, string user, string saldoAkun) {
        NomorRekening = norek;
        UserName = user;
        saldo = saldoAkun;
    }
};

// Struktur untuk menyimpan informasi transaksi
struct transaksi {
    int norekAsal;
    int norekTujuan;
    int jumlah;

    transaksi(int asal, int tujuan, int jml) {
        norekAsal = asal;
        norekTujuan = tujuan;
        jumlah = jml;
    }
};

// Strukrur untuk menyimpan riwayat transaksi
struct RiwayatTransaksi{
    string jenisTransaksi;
    int norekAsal;
    int norekTujuan;
    int jumlah;
};

// Class untuk mengelola daftar akun dan transaksi
class Bank {
private:
    vector<akunBank> akun;
    vector<transaksi> transaksiList;
    stack<RiwayatTransaksi> riwayatTransaksi;

public:
    // Menambahkan akun baru ke dalam daftar
    void tambahAkun(int norek, string user, string saldoAkun) {
        akunBank akunBaru(norek, user, saldoAkun);
        akun.push_back(akunBaru);
    }

    // Menampilkan informasi akun
    void informasiAkun(int norek) {
        bool temukanAkun = false;
        for (const auto& acc : akun) {
            if (acc.NomorRekening == norek) {
                cout << left << setw(20) << "Nomor Rekening"
                    << left << setw(20) << "Username"
                    << left << setw(20) << "Saldo" << endl;
                cout << left << setw(20) << acc.NomorRekening
                    << left << setw(20) << acc.UserName
                    << left << setw(20) << "Rp" + acc.saldo << endl;
                temukanAkun = true;
                break;
            }
        }
        cout << endl;
        if (!temukanAkun) {
            cout << "Tidak ada akun dengan nomor rekening tersebut" << endl;
        }
        cout << endl;
    }

    // Mengembalikan status apakah ada akun yang sudah ditambahkan
    bool akunSudahDitambahkan() {
        return !akun.empty();
    }

    // Mengubah nomor rekening
    void UbahNomorRekening(int norekLama, int norekBaru) {
        for (auto& acc : akun) {
            if (acc.NomorRekening == norekLama) {
                acc.NomorRekening = norekBaru;
                break;
            }
        }
    }

    // Transfer saldo dari satu akun ke akun yang lain
    void transferSaldo(int norekAsal, int norekTujuan, int jumlah) {
        akunBank* akunAsal = nullptr;
        akunBank* akunTujuan = nullptr;

        // Cari akun asal dan tujuan
        for (auto& acc : akun) {
            if (acc.NomorRekening == norekAsal) {
                akunAsal = &acc;
            }
            if (acc.NomorRekening == norekTujuan) {
                akunTujuan = &acc;
            }
        }
        if (akunAsal != nullptr && akunTujuan != nullptr) {
            int saldoAsal = stoi(akunAsal->saldo); // stoi untuk mengubah tipe data string menjadi int
            int saldoTujuan = stoi(akunTujuan->saldo); // stoi untuk mengubah tipe data string menjadi int

            if (saldoAsal >= jumlah) {
                saldoAsal -= jumlah;
                saldoTujuan += jumlah;
                akunAsal->saldo = to_string(saldoAsal); // untuk mengubah tipe data int kembali ke string
                akunTujuan->saldo = to_string(saldoTujuan); // untuk mengubah tipe data int kembali ke string
                cout << "Transfer sukses" << endl;
                
                // Tambahkan transaksi ke dalam daftar transaksi
                transaksi baruTransaksi(norekAsal, norekTujuan, jumlah);
                transaksiList.push_back(baruTransaksi);

                // Tampilkan bukti transaksi
                cout << "==================================================" << endl;
                cout << "|                BUKTI TRANSAKSI                 |" << endl;
                cout << "|================================================|" << endl;
                cout << "| " << left << setw(23) << "Nomor Rekening Asal" << ": " << left << setw(21) << norekAsal << " |" << endl;
                cout << "| " << left << setw(23) << "Nomor Rekening Tujuan" << ": " << left << setw(21) << norekTujuan << " |" << endl;
                cout << "| " << left << setw(23) << "Jumlah" << ": Rp" << left << setw(19) << jumlah << " |" << endl;
                cout << "==================================================" << endl;

            } else {
                cout << "Saldo akun anda tidak mencukupi" << endl;
            }
            cout << endl;
            return;
        } else {
            cout << "Nomor rekening yang anda masukan dan tuju tidak valid" << endl;
        }
        cout << endl;
    }

    // Menarik uang dari akun bank
    void tarikUang(int norek, int jumlah) {
        for (auto& acc : akun) {
            if (acc.NomorRekening == norek) {
                int saldoAkun = stoi(acc.saldo);
                if (saldoAkun >= jumlah) {
                    saldoAkun -= jumlah;
                    acc.saldo = to_string(saldoAkun); 
                    cout << "Penarikan sukses" << endl;
                } else {
                    cout << "Saldo akun tidak mencukupi " << endl;
                }
                cout << endl;
                return;
            }
        }
        cout << "Nomor rekening tidak ditemukan" << endl;
        cout << endl;
    }

    // Menabung uang ke akun
    void menabung(int norek, int jumlah) {
        for (auto& acc : akun) {
            if (acc.NomorRekening == norek) {
                int saldoAkun = stoi(acc.saldo);
                saldoAkun += jumlah;
                acc.saldo = to_string(saldoAkun);
                cout << "Menabung sukses" << endl;
                cout << endl;
                return;
            }
        }
        cout << "Nomor rekening tidak ditemukan " << endl;
        cout << endl;
    }
    // mencari informasi akun berdasarkan nomor rekening
    int cariNomorRekening(int norek){
        for(int i=0; i < akun.size(); i++){
            if(akun[i].NomorRekening == norek){
                return 1;
            }
        }
        return -1;
    }

    void tambahRiwayat(string jenis, int norekAsal, int norekTujuan, int jumlah){
        RiwayatTransaksi transaksi;
        transaksi.jenisTransaksi = jenis;
        transaksi.norekAsal = norekAsal;
        transaksi.norekTujuan = norekTujuan;
        transaksi.jumlah = jumlah;
        riwayatTransaksi.push(transaksi);
    }

    // menampilkan riwayat transaksi
    void tampilkanRiwayat(){
        stack<RiwayatTransaksi>tempStack = riwayatTransaksi;
        cout << "====== RIWAYAT TRANSAKSI ======" <<endl;
        while(!tempStack.empty()){
            RiwayatTransaksi transaksi = tempStack.top();
            cout << "Jenis Transaksi: " << transaksi.jenisTransaksi << endl;
            cout << "Nomor Rekening : " << transaksi.norekAsal << endl;
            cout << "Tujuan         : " << transaksi.norekTujuan << endl;
            cout << "Jumlah         : " << transaksi.jumlah << endl;
            cout << "-------------------------------------------"<<endl;
            tempStack.pop();
        }
        cout << "==============================================="<<endl;
    }
};

int main() {
    Bank bank;
    int pilih, NomorRekening, norekBaru, norekTujuan, jumlah, norekAsal,indeks;
    string UserName;
    string saldo;
    string jumlahSaldo;

    menu:
    cout << "====================================" << endl;
    cout << "|       Aplikasi Transfer Bank     |" << endl;
    cout << "====================================" << endl;
    cout << "| 1. Tambah Akun Bank              |" << endl;
    cout << "| 2. Munculkan Informasi akun      |" << endl;
    cout << "| 3. Ubah nomor rekening           |" << endl;
    cout << "| 4. Transfer saldo                |" << endl;
    cout << "| 5. Tarik uang                    |" << endl;
    cout << "| 6. Menabung                      |" << endl;
    cout << "| 7. Riwayat Transaksi             |" << endl;
    cout << "| 8. Keluar                        |" << endl;
    cout << "====================================" << endl;
    cout << "Pilih operasi: ";
    cin >> pilih;

    switch (pilih) {
        case 1:
            cout << "Masukkan Nomor Rekening: ";
            cin >> NomorRekening;
            cout << "Masukkan Username: ";
            cin >> UserName;
            cout << "Masukkan Saldo Bank: ";
            cin >> saldo;
            bank.tambahAkun(NomorRekening, UserName, saldo);
            cout << "Akun Berhasil ditambahkan" << endl;
            cout << endl;
            goto menu;
            break;
        case 2:
            if (!bank.akunSudahDitambahkan()) {
                cout << "Silahkan tambah akun terlebih dahulu" << endl;
                cout << endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening akun yang dicari: "; cin >> NomorRekening;
            indeks = bank.cariNomorRekening(NomorRekening);
            if (indeks != -1){
                bank.informasiAkun(NomorRekening);
            }else{
                cout << "Akun dengan nomor rekening tersebut tidak ditemukan" << endl;
            }
            goto menu;
            break;
        case 3:
            if (!bank.akunSudahDitambahkan()) {
                cout << "Silahkan tambahkan akun terlebih dahulu" << endl;
                cout << endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening yang ingin diubah: "; cin >> NomorRekening;
            cout << "Masukkan nomor rekening baru: "; cin >> norekBaru;
            bank.UbahNomorRekening(NomorRekening, norekBaru);
            cout << "Nomor rekening " << NomorRekening << " Telah diganti menjadi " << norekBaru << endl;
            goto menu;
            break;
        case 4:
            if (!bank.akunSudahDitambahkan()) {
                cout << "Silahkan tambahkan akun terlebih dahulu" << endl;
                cout << endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening asal: "; cin >> norekAsal;
            cout << "Masukkan nomor rekening tujuan: "; cin >> norekTujuan;
            cout << "Masukkan jumlah saldo yang ingin ditransfer: "; cin >> jumlah;
            bank.transferSaldo(norekAsal, norekTujuan, jumlah);
            bank.tambahRiwayat("Transfer",norekAsal,norekTujuan,jumlah);
            goto menu;
            break;
        case 5:
            if (!bank.akunSudahDitambahkan()) {
                cout << "Silahkan tambahkan akun terlebih dahulu" << endl;
                cout << endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening: ";
            cin >> NomorRekening;
            cout << "Masukkan Jumlah uang yang ingin ditarik: ";
            cin >> jumlah;
            bank.tarikUang(NomorRekening, jumlah);
            bank.tambahRiwayat("Penarikan",NomorRekening,0,jumlah);
            goto menu;
            break;
        case 6:
            if (!bank.akunSudahDitambahkan()) {
                cout << "Silahkan tambahkan akun terlebih dahulu " << endl;
                cout << endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening: ";
            cin >> NomorRekening;
            cout << "Masukkan jumlah uang yang ingin ditabung: ";
            cin >> jumlah;
            bank.menabung(NomorRekening, jumlah);
            bank.tambahRiwayat("Menabung",NomorRekening,0,jumlah);
            goto menu;
            break;
        case 7:
            if(!bank.akunSudahDitambahkan()){
                cout << "silahkan tambahkan akun terlebih dahulu " <<endl;
                cout << endl;
                goto menu;
            }
            bank.tampilkanRiwayat();
            goto menu;
            break;
        case 8:
            cout << "Keluar dari program" << endl;
            break;
        default:
            cout << "Pilihan anda tidak tersedia" << endl;
            break;
    }
    return 0;
}
