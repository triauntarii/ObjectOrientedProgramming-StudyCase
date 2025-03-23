#include <iostream>
#include <vector>
using namespace std;

class GameCharacter {
public:
    virtual void tampilkanKarakter() = 0;
    virtual ~GameCharacter() {}
};

class Fairy : public GameCharacter {
public:
    string nama;
    int Health = 100;
    int kekuatanSerang = 10;

    Fairy(string namaPemain) : nama(namaPemain) {}

    void tampilkanKarakter() override {
        cout << "Health " << nama << ": " << Health << " HP | ";
        cout << "Power Attack: " << kekuatanSerang << " Damage" << endl;
    }
};

class Witch : public GameCharacter {
public:
    int Health = 100;
    int kekuatanSerang = 12;

    void tampilkanKarakter() override {
        if (Health > 0) {
            cout << "Health Penyihir: " << Health << " HP | ";
            cout << "Power Attack: " << kekuatanSerang << " Damage" << endl;
        }
        else {
            cout << "Penyihir telah dikalahkan!" << endl;
        }
    }

    void serang(Fairy& fairy) {
        if (Health > 0) {
            fairy.Health -= kekuatanSerang;
            if (fairy.Health < 0) fairy.Health = 0;
            cout << "Penyihir menyerang! Memberikan " << kekuatanSerang << " Damage!" << endl;
        }
    }
};

class SmallDragon : public GameCharacter {
public:
    bool masihHidup = true;
    int Health = 50;
    int kekuatanSerang = 8;

    virtual void berikanHadiah(Fairy& fairy) = 0;

    void serang(Fairy& fairy) {
        if (masihHidup) {
            fairy.Health -= kekuatanSerang;
            if (fairy.Health < 0) fairy.Health = 0;
            cout << "Naga menyerang balik! Memberikan " << kekuatanSerang << " Damage!" << endl;
        }
    }
};

class RedSmallDragon : public SmallDragon {
public:
    void tampilkanKarakter() override {
        if (masihHidup)
            cout << "Health Naga Kecil Merah: " << Health << " HP" << endl;
        else
            cout << "Naga Kecil Merah telah dikalahkan!" << endl;
    }

    void berikanHadiah(Fairy& fairy) override {
        fairy.kekuatanSerang += 10;
        cout << "Power Attack bertambah +10!" << endl;
    }
};

class BlueSmallDragon : public SmallDragon {
public:
    void tampilkanKarakter() override {
        if (masihHidup)
            cout << "Health Naga Kecil Biru: " << Health << " HP" << endl;
        else
            cout << "Naga Kecil Biru telah dikalahkan!" << endl;
    }

    void berikanHadiah(Fairy& fairy) override {
        fairy.Health += 20;
        cout << "Health bertambah +20 HP!" << endl;
    }
};

int main() {
    string namaPemain;
    cout << "Masukkan nama karakter Anda: ";
    cin >> namaPemain;

    Fairy peri(namaPemain);
    Witch penyihir;
    RedSmallDragon nagaMerah;
    BlueSmallDragon nagaBiru;
    int pilihan;

    cout << "Selamat datang dalam pertempuran " << namaPemain << "!" << endl;

    while (peri.Health > 0 && (penyihir.Health > 0 || nagaMerah.masihHidup || nagaBiru.masihHidup)) {
        cout << "\n=== Status Karakter Saat Ini ===" << endl;
        peri.tampilkanKarakter();
        penyihir.tampilkanKarakter();
        nagaMerah.tampilkanKarakter();
        nagaBiru.tampilkanKarakter();

        cout << "\nPilihan Anda:" << endl;
        cout << "1. Serang Naga Kecil Merah" << endl;
        cout << "2. Serang Naga Kecil Biru" << endl;
        cout << "3. Serang Penyihir" << endl;
        cout << "4. Akhiri Pertempuran" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        if (pilihan == 1 && nagaMerah.masihHidup) {
            cout << namaPemain << " menyerang! Memberikan " << peri.kekuatanSerang << " Damage!" << endl;
            nagaMerah.Health -= peri.kekuatanSerang;
            if (nagaMerah.Health <= 0) {
                nagaMerah.masihHidup = false;
                cout << "Naga Kecil Merah telah dikalahkan!" << endl;
                nagaMerah.berikanHadiah(peri);
            }
            else {
                nagaMerah.serang(peri);
            }
        }
        else if (pilihan == 2 && nagaBiru.masihHidup) {
            cout << namaPemain << " menyerang! Memberikan " << peri.kekuatanSerang << " Damage!" << endl;
            nagaBiru.Health -= peri.kekuatanSerang;
            if (nagaBiru.Health <= 0) {
                nagaBiru.masihHidup = false;
                cout << "Naga Kecil Biru telah dikalahkan!" << endl;
                nagaBiru.berikanHadiah(peri);
            }
            else {
                nagaBiru.serang(peri);
            }
        }
        else if (pilihan == 3 && penyihir.Health > 0) {
            cout << namaPemain << " menyerang! Memberikan " << peri.kekuatanSerang << " Damage!" << endl;
            penyihir.Health -= peri.kekuatanSerang;
            if (penyihir.Health > 0) {
                penyihir.serang(peri);
            }
            else {
                cout << "Penyihir telah dikalahkan sepenuhnya!" << endl;
            }
        }
        else if (pilihan == 4) {
            cout << namaPemain << " telah menyerah, pertempuran berakhir." << endl;
            break;
        }
        else {
            cout << "Pilihan tidak valid!" << endl;
        }

        if (peri.Health <= 0) {
            cout << namaPemain << " telah dikalahkan! Pertempuran berakhir." << endl;
            break;
        }
    }

    if (peri.Health > 0 && !penyihir.Health && !nagaMerah.masihHidup && !nagaBiru.masihHidup) {
        cout << "Selamat! " << namaPemain << " telah memenangkan pertempuran!" << endl;
    }

    return 0;
}