#include <iostream>
#include <string>
using namespace std;

class Jurusan {
private:
    string nama;
    string kaprodi;
};

class Mahasiswa {
private:
    string nama;
    string nim;
    Jurusan jurusan;
    float IPK;

public:
    string jurusan;

    Mahasiswa(string a, string b) {
        this->nama = a;
        this->nim = b;
    }

    void updateName(string nama) {
        this->nama = nama;
    }

    void setIPK(float ipk) {
        if (ipk > 4 || ipk < 0) {
            cout << "error" << endl;
        }
        else {
            this->IPK = ipk;
        }
    }
    void cetakDetail() {
        cout << "Nama: " << nama << endl;
        cout << "NIM: " << nim << endl;
        cout << "IPK: " << IPK << endl;
    }
};

int main() {
    Mahasiswa fauzan = Mahasiswa("Fauzan", "123");
    Mahasiswa khidhir = Mahasiswa("Khidhir", "456");
    khidhir.updateName("Aguan");

    fauzan.setIPK(50.0);
    khidhir.setIPK(3.99);

    khidhir.cetakDetail();