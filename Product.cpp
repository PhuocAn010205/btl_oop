#include "Product.h"
#include <fstream>
#include <iostream>

ProductManager::ProductManager() {
    load_products();
}

void ProductManager::load_products() {
    ifstream file("sanpham.txt");
    if (file.is_open()) {
        Product product;
        while (file >> product.name >> product.quantity >> product.price) {
            products.push_back(product);
        }
        file.close();
    }
}

void ProductManager::save_products() {
    ofstream file("sanpham.txt");
    if (file.is_open()) {
        for (const auto& product : products) {
            file << product.name << " " << product.quantity << " " << product.price << endl;
        }
        file.close();
    }
}

void ProductManager::print_products() {
    cout << "Danh sach san pham trong kho:" << endl;
    for (const auto& product : products) {
        cout << "Ten: " << product.name << ", So luong: " << product.price << ", Gia: " << product.quantity << endl;
    }
}

void ProductManager::add_product() {
    string name;
    int quantity;
    double price;
    cout << "Nhap ten san pham: ";
    cin >> name;
    cout << "Nhap so luong san pham: ";
    cin >> quantity;
    cout << "Nhap gia san pham: ";
    cin >> price;

    products.push_back(Product(name, quantity, price));
    save_products();
}

bool ProductManager::purchase_product(const string& name, int quantity, map<string, pair<int, double>>& cart) {
    for (auto& product : products) {
        if (product.name == name && product.quantity >= quantity) {
            product.quantity -= quantity;
            if (cart.find(name) != cart.end()) {
                cart[name].first += quantity;
            }
            else {
                cart[name] = make_pair(quantity, product.price);
            }
            save_products();
            return true;
        }
    }
    return false;
}

void ProductManager::print_invoice(const string& customer_name, const string& customer_phone, const map<string, pair<int, double>>& cart) {
    cout << "****HOA DON MUA HANG****" << endl;
    cout << "Ten khach hang: " << customer_name << endl;
    cout << "So dien thoai: " << customer_phone << endl;
    cout << "Ngay mua: "; // Implement date functionality if needed
    cout << "San pham mua: " << endl;
    double total_cost = 0.0;
    for (const auto& item : cart) {
        cout << item.first << " - So luong: " << item.second.first << " - Thanh tien: " << item.second.second * item.second.first << endl;
        total_cost += item.second.second * item.second.first;
    }
    cout << "Tong so tien: " << total_cost << endl;
    cout << "****Cam on quy khach!****" << endl;
}

bool ProductManager::delete_product(const string& name) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->name == name) {
            products.erase(it);
            save_products();
            return true;
        }
    }
    return false;
}
