#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Interface Notifikasi
class INotification {
public:
    virtual void kirimNotifikasi(const string& penerima, const string& pesan) = 0;
    virtual ~INotification() = default;
};

// Implementasi Email Notifikasi
class EmailNotification : public INotification {
public:
    void kirimNotifikasi(const string& penerima, const string& pesan) override {
        cout << "Mengirim Email ke " << penerima << ": " << pesan << endl;
    }
};

// Implementasi SMS Notifikasi
class SMSNotification : public INotification {
public:
    void kirimNotifikasi(const string& penerima, const string& pesan) override {
        cout << "Mengirim SMS ke " << penerima << ": " << pesan << endl;
    }
};

// Implementasi Push Notifikasi dengan Nama Aplikasi
class PushNotification : public INotification {
public:
    void kirimNotifikasi(const string& namaAplikasi, const string&) override {
        string pesan;
        if (namaAplikasi == "WhatsApp") {
            pesan = "Anda memiliki pesan baru di WhatsApp!";
        }
        else if (namaAplikasi == "Instagram") {
            pesan = "Ada notifikasi baru di Instagram!";
        }
        else if (namaAplikasi == "Twitter") {
            pesan = "Tweet terbaru telah diposting!";
        }
        else if (namaAplikasi == "TikTok") {
            pesan = "Ada video baru yang mungkin Anda suka di TikTok!";
        }
        else {
            pesan = "Anda memiliki notifikasi baru!";
        }
        cout << "Mengirim Push Notification dari " << namaAplikasi << ": " << pesan << endl;
    }
};

int main() {
    int pilihan;
    string penerima, pesan, namaAplikasi;

    cout << "Pilih jenis notifikasi:\n";
    cout << "1. Email\n2. SMS\n3. Push Notification\n";
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    cin.ignore(); // Untuk menghindari masalah dengan getline

    if (pilihan == 3) {
        cout << "Masukkan nama aplikasi (WhatsApp, Instagram, Twitter, TikTok): ";
        getline(cin, namaAplikasi);
    }
    else {
        cout << "Masukkan penerima: ";
        getline(cin, penerima);
        cout << "Masukkan pesan: ";
        getline(cin, pesan);
    }

    INotification* notifikasi = nullptr;

    if (pilihan == 1) {
        notifikasi = new EmailNotification();
    }
    else if (pilihan == 2) {
        notifikasi = new SMSNotification();
    }
    else if (pilihan == 3) {
        notifikasi = new PushNotification();
        notifikasi->kirimNotifikasi(namaAplikasi, "");
        delete notifikasi;
        return 0;
    }
    else {
        cout << "Pilihan tidak valid!" << endl;
        return 1;
    }

    notifikasi->kirimNotifikasi(penerima, pesan);
    delete notifikasi; // Dealokasi memori

    return 0;
}