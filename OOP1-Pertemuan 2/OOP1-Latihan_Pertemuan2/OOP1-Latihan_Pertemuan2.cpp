#include <iostream>
#include <iomanip>
using namespace std;

// Parent class
class Karyawan {
public:
    string nama;
    int id;

    Karyawan(string name, int id) { // Constructor
        nama = name;
        id = id;
    }

    virtual int hitungGaji() = 0; // Pure virtual function
    virtual string getJabatan() = 0; // Pure virtual function untuk jabatan
    virtual int getGajiPerJam() { return 0; } // Default 0 jika tidak relevan
    virtual int getBonus() { return 0; } // Default 0 jika tidak relevan
    virtual int getJamKerja() { return 0; } // Default 0 jika tidak relevan
    virtual int getGajiPokok() { return 0; } // Default 0 jika tidak relevan
    virtual int getTunjangan() { return 0; } // Default 0 jika tidak relevan

    void tampilkanGaji() {
        cout << left << setw(10) << nama
            << setw(20) << getJabatan()
            << setw(15) << getGajiPokok()
            << setw(15) << getTunjangan()
            << setw(15) << getGajiPerJam()
            << setw(15) << getJamKerja()
            << setw(15) << getBonus()
            << setw(15) << hitungGaji() << endl;
    }
};

// Child class: Karyawan Tetap
class karyawanTetap : public Karyawan {
public:
    int gajiPokok;
    int tunjangan;

    karyawanTetap(string name, int id, int basicSallary, int allowanceSallary) : Karyawan(name, id) {
        gajiPokok = basicSallary;
        tunjangan = allowanceSallary;
    }

    int hitungGaji() override {
        return gajiPokok + tunjangan;
    }

    string getJabatan() override {
        return "Karyawan Tetap";
    }

    int getGajiPokok() override {
        return gajiPokok;
    }

    int getTunjangan() override {
        return tunjangan;
    }
};

// Child class: Karyawan Kontrak
class karyawanKontrak : public Karyawan {
public:
    int gajiPerjam;
    int jamKerja;

    karyawanKontrak(string name, int id, int hourlySallary, int workingHour) : Karyawan(name, id) {
        gajiPerjam = hourlySallary;
        jamKerja = workingHour;
    }

    int hitungGaji() override {
        return gajiPerjam * jamKerja;
    }

    string getJabatan() override {
        return "Karyawan Kontrak";
    }

    int getGajiPerJam() override {
        return gajiPerjam;
    }

    int getJamKerja() override {
        return jamKerja;
    }
};

// Child class: Manager (Turunan dari Karyawan Tetap)
class Manager : public karyawanTetap {
public:
    int bonus;

    Manager(string name, int id, int basicSallary, int allowanceSallary, int bonusSallary) : karyawanTetap(name, id, basicSallary, allowanceSallary) {
        bonus = bonusSallary;
    }

    int hitungGaji() override {
        return gajiPokok + tunjangan + bonus;
    }

    string getJabatan() override {
        return "Manager";
    }

    int getBonus() override {
        return bonus;
    }
};

int main() {
    karyawanTetap Tari("Tari", 1, 8000000, 2000000);
    karyawanKontrak Dhika("Dhika", 2, 80000, 72);
    Manager Adias("Adias", 3, 90000000, 12000000, 10000000);

    cout << left << setw(10) << "Nama"
        << setw(20) << "Jabatan"
        << setw(15) << "Gaji Pokok"
        << setw(15) << "Tunjangan"
        << setw(15) << "Gaji Per Jam"
        << setw(15) << "Total Jam"
        << setw(15) << "Bonus"
        << setw(15) << "Jumlah Gaji" << endl;
    cout << string(116, '-') << endl;

    Tari.tampilkanGaji();
    Dhika.tampilkanGaji();
    Adias.tampilkanGaji();

    return 0;
}