#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

class Product {
private:
    int productId;
    string productName;
    double productPrice; // Harga dalam jutaan
    int productStock;

    string formatPrice(double price) {
        ostringstream oss;
        oss.imbue(locale(""));
        oss << fixed << setprecision(0) << price;
        return oss.str();
    }

public:
    Product(int productId, string productName, double productPrice, int productStock) :
        productId(productId), productName(productName), productPrice(productPrice), productStock(productStock) {
    }

    void updatePriceProduct(double newPrice) {
        productPrice = newPrice;
        cout << "Harga diubah menjadi : " << formatPrice(productPrice * 1000000) << endl;
    }

    void displayInfoProduct() {
        cout << "ID Produk : " << productId << endl;
        cout << "Nama Produk : " << productName << endl;
        cout << "Harga Produk : " << formatPrice(productPrice * 1000000) << endl;
        cout << "Stok Produk : " << productStock << endl;
    }

    void updateStockProduct(int newProductStock) {
        productStock = newProductStock;
        cout << "Stok ditambah menjadi : " << productStock << endl;
    }

    double calculateDiscountProduct(double percentage) {
        double discountAmount = productPrice * percentage / 100;
        double discountedPrice = productPrice - discountAmount;
        cout << "Harga setelah diskon " << percentage << "% : " << formatPrice(discountedPrice * 1000000) << endl;
        return discountedPrice;
    }
};

int main() {
    Product handphone(1, "Iphone 13", 13.0, 10);
    Product handphone2(2, "Iphone 15 Pro Max", 19.0, 11);

    handphone.displayInfoProduct();
    handphone.updatePriceProduct(15.0);
    handphone.updateStockProduct(100);
    handphone.calculateDiscountProduct(10);

    cout << "" << endl;

    handphone2.displayInfoProduct();
    handphone2.updatePriceProduct(20.0);
    handphone2.updateStockProduct(50);
    handphone2.calculateDiscountProduct(15);

    return 0;
}
