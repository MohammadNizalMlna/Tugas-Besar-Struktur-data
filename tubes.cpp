//Daffa Falih Aqilah - 2311102137
//Mohammad Nizal Maulana - 2311102150

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Struktur untuk menyimpan informasi rekening
struct akunBank{
    int NomorRekening;
    string UserName;
    string saldo;

    akunBank(int norek,string user,string saldoAkun){
        NomorRekening = norek;
        UserName = user;
        saldo = saldoAkun;
    }
};

//Class untuk mengelola daftar akun
class Bank{
    private:
    vector<akunBank>akun;

    public:
    //Menambahkan akun baru kedalam daftar
    void tambahAkun(int norek,string user,string saldoAkun){
        akunBank akunBaru(norek, user, saldoAkun);
        akun.push_back(akunBaru);
    }
    //Menampilkan informasi akun
    void informasiAkun(int norek){
        bool temukanAkun = false;
        for(const auto& acc : akun){
            if(acc.NomorRekening == norek){
                cout << "Nomor Rekening: "<< acc.NomorRekening <<endl;
                cout << "Username: " << acc.UserName<<endl;
                cout << "Saldo: Rp" <<acc.saldo<<endl;
                temukanAkun = true;
                break;
            }
        }
        if (!temukanAkun){
            cout << "Tidak ada akun dengan nomor rekening tersebut"<<endl;
        }
    }

    //Mengembalikan status apakahh ada akun yang sudah ditambahkan
    bool akunSudahDitambahkan(){
        return !akun.empty();
    }

    //Mengubah nomor rekening
    void UbahNomorRekening(int norekLama, int norekBaru){
        for(auto& acc : akun){
            if(acc.NomorRekening == norekLama){
                acc.NomorRekening = norekBaru;
                break;
            }
        }
    }

    // Transfer saldo dari satu akun ke akun yang lain
    void transferSaldo(int norekAsal, int norekTujuan, int jumlah){
        akunBank* akunAsal = nullptr;
        akunBank* akunTujuan = nullptr;

        //cari akun asal dan tujuan
        for (auto& acc : akun) {
            if (acc.NomorRekening == norekAsal){
                akunAsal = &acc;
            }
            if (acc.NomorRekening == norekTujuan){
                akunTujuan = &acc;
            }
        }
        if (akunAsal != nullptr && akunTujuan != nullptr){
            int saldoAsal = stoi(akunAsal->saldo); //stoi untuk mengubah tipe data string menjadi int
            int saldoTujuan = stoi(akunTujuan->saldo); //stoi untuk mengubah tipe data string menjadi int

            if (saldoAsal >= jumlah){
                saldoAsal -= jumlah;
                saldoTujuan += jumlah;
                akunAsal->saldo = to_string(saldoAsal);// untuk mengubah tipe data int kembali ke string
                akunTujuan->saldo = to_string(saldoTujuan); // untuk mengubah tipe data int kembali ke string
                cout << "Transfer sukses" <<endl;
            }else{
                cout << "Saldo akun anda tidak mencukupi"<<endl;
            }
        }else{
            cout << "Nomor rekening yang anda masukan dan tuju tidak valid" <<endl;
        }
    }
};

int main(){
    Bank bank;
    int pilih,NomorRekening,norekBaru,norekTujuan,jumlah,norekAsal;
    string UserName;
    string saldo;
    string jumlahSaldo;

    menu:
    cout << "Aplikasi Transfer Bank" <<endl;
    cout << "1. Tambah Akun Bank" <<endl;
    cout << "2. Munculkan Informasi akun" <<endl;
    cout << "3. Ubah nomor rekening" <<endl;
    cout << "4. Transfer saldo "<<endl;
    cout << "5. Keluar" <<endl;
    cout << "Pilih operasi: ";
    cin >> pilih;

    switch(pilih){
        case 1:
            cout << "Masukkan Nomor Rekening: ";
            cin >> NomorRekening;
            cout << "Masukkan Username: ";
            cin >> UserName;
            cout << "Masukkan Saldo Bank: ";
            cin >> saldo;
            bank.tambahAkun(NomorRekening,UserName,saldo);
            cout << "Akun Berhasil ditambahkan"<<endl;
            goto menu;
            break;
        case 2:
            if (!bank.akunSudahDitambahkan()){
                cout << "Silahkan tambah akun terlebih dahulu" <<endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening akun yang dicari: "; cin >> NomorRekening;
            bank.informasiAkun(NomorRekening);
            goto menu;
            break;
        case 3:
            if (!bank.akunSudahDitambahkan()){
                cout << "Silahkan tambahkan akun terlebih dahulu"<<endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening yang ingin diubah: "; cin >>NomorRekening;
            cout << "Masukkan nomor rekening baru: "; cin >> norekBaru;
            bank.UbahNomorRekening (NomorRekening,norekBaru);
            cout << "Nomor rekening " << NomorRekening << " Telah diganti menjadi " << norekBaru <<endl;
            goto menu;
            break;
        case 4 :
            if (!bank.akunSudahDitambahkan()){
                cout << "Silahkan tambahkan akun terlebih dahulu" <<endl;
                goto menu;
            }
            cout << "Masukkan nomor rekening asal: "; cin >> norekAsal;
            cout << "Masukkan nomor rekening tujuan: "; cin >> norekTujuan;
            cout << "Masukkan jumlah saldo yang ingin ditransfer: "; cin >> jumlah;
            bank.transferSaldo(norekAsal, norekTujuan, jumlah);
            goto menu;
            break;
        case 5 :
            cout << "Keluar dari program" <<endl;
            break;
        default:
            cout << "Pilihan anda tidak tersedia" <<endl;
            break;
    }
    return 0;
}