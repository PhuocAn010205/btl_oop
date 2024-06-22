#pragma once

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Product {
public:
    string name;
    double price;
    int quantity;

    Product() {}
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

class ProductManager {
private:
    vector<Product> products;
    void load_products();
    void save_products();
public:
    ProductManager();
    void add_product();
    void print_products();
    bool purchase_product(const string& name, int quantity, map<string, pair<int, double>>& cart);
    void print_invoice(const string& customer_name, const string& customer_phone, const map<string, pair<int, double>>& cart);
    bool delete_product(const string& name); // New function
};

#endif

