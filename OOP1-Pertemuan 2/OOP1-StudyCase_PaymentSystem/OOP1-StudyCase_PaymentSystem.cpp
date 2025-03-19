#include <iostream>
#include <string>

using namespace std;

// Parent class: Payment
class Payment {
protected:
    int id;
    double amount;
    string date;
    string status;

public:
    Payment(int id, double amount, string date)
        : id(id), amount(amount), date(date), status("Menunggu") {
    }

    virtual ~Payment() {} // Virtual destructor

    virtual void processPayment() = 0;
    virtual bool validatePayment() = 0;
    virtual void refundPayment() = 0;

    void displayPaymentDetails() {
        cout << "\n-----------------------------" << endl;
        cout << "ID Pembayaran  : " << id << endl;
        cout << "Jumlah         : Rp " << amount << endl;
        cout << "Tanggal        : " << date << endl;
        cout << "Status         : " << status << endl;
        cout << "-----------------------------\n";
    }

    string getStatus() {
        return status;
    }

protected:
    void setStatus(string newStatus) {
        status = newStatus;
    }
};

// Child class 1: CreditCardPayment
class CreditCardPayment : public Payment {
private:
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    CreditCardPayment(int id, double amount, string date, string cardNumber, string expiryDate, string cvv)
        : Payment(id, amount, date), cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {
    }

    void processPayment() override {
        cout << "Memproses pembayaran dengan Kartu Kredit..." << endl;
        if (cvv.length() != 3) {
            setStatus("Gagal (CVV Salah)");
            cout << "Pembayaran gagal: CVV harus 3 digit!" << endl;
        }
        else if (expiryDate < "04/25") {
            setStatus("Gagal (Kartu Kadaluarsa)");
            cout << "Pembayaran gagal: Kartu kredit kadaluarsa!" << endl;
        }
        else {
            setStatus("Diproses");
            cout << "Pembayaran berhasil!" << endl;
        }
    }

    bool validatePayment() override {
        return getStatus() == "Diproses";
    }

    void refundPayment() override {
        if (validatePayment()) {
            cout << "Mengembalikan dana pembayaran Kartu Kredit..." << endl;
            setStatus("Dikembalikan");
        }
        else {
            cout << "Refund gagal: Pembayaran belum berhasil." << endl;
        }
    }
};

// Child class 2: BankTransfer
class BankTransfer : public Payment {
private:
    string accountNumber;
    string bankName;
    string transferCode;

public:
    BankTransfer(int id, double amount, string date, string accountNumber, string bankName, string transferCode)
        : Payment(id, amount, date), accountNumber(accountNumber), bankName(bankName), transferCode(transferCode) {
    }

    void processPayment() override {
        cout << "Memproses transfer bank ke " << bankName << "..." << endl;
        if (bankName != "Bank BRI" && bankName != "Bank BNI" && bankName != "Bank Mandiri") {
            setStatus("Gagal (Bank Tidak Didukung)");
            cout << "Pembayaran gagal: Bank tidak tersedia dalam sistem!" << endl;
        }
        else {
            setStatus("Diproses");
            cout << "Pembayaran berhasil!" << endl;
        }
    }

    bool validatePayment() override {
        return getStatus() == "Diproses";
    }

    void refundPayment() override {
        if (validatePayment()) {
            cout << "Mengembalikan dana transfer bank dari " << bankName << "..." << endl;
            setStatus("Dikembalikan");
        }
        else {
            cout << "Refund gagal: Pembayaran belum berhasil." << endl;
        }
    }
};

// Child class 3: DigitalWallet
class DigitalWallet : public Payment {
private:
    string walletId;
    string provider;
    string phoneNumber;

public:
    DigitalWallet(int id, double amount, string date, string walletId, string provider, string phoneNumber)
        : Payment(id, amount, date), walletId(walletId), provider(provider), phoneNumber(phoneNumber) {
    }

    void processPayment() override {
        cout << "Memproses pembayaran dengan " << provider << "..." << endl;
        if (phoneNumber.substr(0, 2) != "08") {
            setStatus("Gagal (Nomor HP Salah)");
            cout << "Pembayaran gagal: Nomor HP harus diawali dengan 08!" << endl;
        }
        else {
            setStatus("Diproses");
            cout << "Pembayaran berhasil!" << endl;
        }
    }

    bool validatePayment() override {
        return getStatus() == "Diproses";
    }

    void refundPayment() override {
        if (validatePayment()) {
            cout << "Mengembalikan dana pembayaran dari " << provider << "..." << endl;
            setStatus("Dikembalikan");
        }
        else {
            cout << "Refund gagal: Pembayaran belum berhasil." << endl;
        }
    }
};

// Fungsi untuk memilih metode pembayaran
Payment* pilihMetodePembayaran(int id, double amount, string date) {
    int pilihan;
    cout << "\nPilih metode pembayaran:\n";
    cout << "1. Kartu Kredit\n2. Transfer Bank\n3. Dompet Digital\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        string cardNumber, expiryDate, cvv;
        cout << "Masukkan nomor kartu kredit: ";
        getline(cin, cardNumber);
        cout << "Masukkan tanggal kadaluarsa (MM/YY): ";
        getline(cin, expiryDate);
        cout << "Masukkan CVV: ";
        getline(cin, cvv);
        return new CreditCardPayment(id, amount, date, cardNumber, expiryDate, cvv);
    }
    else if (pilihan == 2) {
        string accountNumber, bankName, transferCode;
        cout << "Masukkan nomor rekening: ";
        getline(cin, accountNumber);
        cout << "Masukkan nama bank (Bank BRI, Bank BNI, Bank Mandiri): ";
        getline(cin, bankName);
        cout << "Masukkan kode transfer: ";
        getline(cin, transferCode);
        return new BankTransfer(id, amount, date, accountNumber, bankName, transferCode);
    }
    else if (pilihan == 3) {
        string walletId, provider, phoneNumber;
        cout << "Masukkan ID dompet digital: ";
        getline(cin, walletId);
        cout << "Masukkan penyedia dompet digital (GoPay, OVO, ShopeePay): ";
        getline(cin, provider);
        cout << "Masukkan nomor HP: ";
        getline(cin, phoneNumber);
        return new DigitalWallet(id, amount, date, walletId, provider, phoneNumber);
    }
    else {
        cout << "Pilihan tidak valid!\n";
        return nullptr;
    }
}

int main() {
    int id = 2812;
    double amount;
    string date;

    cout << "Masukkan jumlah pembayaran: Rp ";
    cin >> amount;
    cin.ignore();
    cout << "Masukkan tanggal transaksi (YYYY-MM-DD): ";
    getline(cin, date);

    Payment* payment = pilihMetodePembayaran(id, amount, date);
    if (payment == nullptr) return 0;

    payment->processPayment();
    payment->displayPaymentDetails();

    char refund;
    cout << "Apakah Anda ingin refund? (y/n): ";
    cin >> refund;

    if (refund == 'y' || refund == 'Y') {
        payment->refundPayment();
        payment->displayPaymentDetails();
    }

    delete payment;
    return 0;
}