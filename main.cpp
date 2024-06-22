#include "Product.h"
#include "User.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

void register_customer(UserManager& userManager) {
    string username, password, phone;
    cout << "Dang ky tai khoan khach hang" << endl;
    cout << "Nhap ten dang nhap: ";
    cin >> username;
    cout << "Nhap mat khau: ";
    cin >> password;
    cout << "Nhap so dien thoai: ";
    cin >> phone;

    userManager.register_customer(username, password, phone);
    cout << "Dang ky thanh cong. Ban co the dang nhap." << endl;
}

int show_manager_menu() {
    int choice;
    cout << "=============== MENU QUAN LY ==================" << endl;
    cout << "1. Xem danh sach khach hang" << endl;
    cout << "2. Xem danh sach quan ly" << endl;
    cout << "3. Xem danh sach san pham trong kho" << endl;
    cout << "4. Them san pham moi" << endl;
    cout << "5. Xoa tai khoan khach hang" << endl;
    cout << "6. Xoa san pham" << endl; // New option
    cout << "7. Tao tai khoan quan ly" << endl; // New option
    cout << "0. Dang xuat" << endl;
    cout << "Lua chon cua ban la: ";
    cin >> choice;

    return choice;
}

int show_customer_menu() {
    int choice;
    cout << "=============== MENU KHACH HANG ==================" << endl;
    cout << "1. Xem danh sach san pham" << endl;
    cout << "2. Mua san pham" << endl;
    cout << "0. Dang xuat" << endl;
    cout << "Lua chon cua ban la: ";
    cin >> choice;

    return choice;
}

void display_product_menu(ProductManager& manager, UserManager& userManager, const string& username) {
    map<string, pair<int, double>> cart;

    while (true) {
        int customer_choice = show_customer_menu();
        switch (customer_choice) {
        case 1:
            manager.print_products();
            break;
        case 2: {
            while (true) {
                string product_name;
                int quantity;
                cout << "Nhap ten san pham: ";
                cin >> product_name;
                cout << "Nhap so luong muon mua: ";
                cin >> quantity;
                if (manager.purchase_product(product_name, quantity, cart)) {
                    cout << "Mua thanh cong!" << endl;
                }
                else {
                    cout << "San pham khong du so luong hoac khong ton tai!" << endl;
                }

                int continue_choice;
                cout << "Ban co muon tiep tuc mua hang hay thanh toan?" << endl;
                cout << "1. Tiep tuc mua hang" << endl;
                cout << "2. Thanh toan" << endl;
                cout << "Lua chon cua ban: ";
                cin >> continue_choice;

                if (continue_choice == 1) {
                    continue;
                }
                else if (continue_choice == 2) {
                    string customer_name = userManager.get_customer_details(username).username;
                    string customer_phone = userManager.get_customer_details(username).phone;
                    manager.print_invoice(customer_name, customer_phone, cart);
                    cart.clear(); // Clear the cart after checkout
                    cout << "Nhan phim bat ky de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    return;
                }
                else {
                    cout << "Lua chon khong hop le. Thoat khoi mua hang." << endl;
                    return;
                }
            }
        }
        case 0:
            cout << "Dang xuat..." << endl;
            return;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai." << endl;
            break;
        }
    }
}

void display_manager_menu(ProductManager& manager, UserManager& userManager) {
    while (true) {
        int manager_choice = show_manager_menu();
        switch (manager_choice) {
        case 1:
            userManager.display_customers();
            break;
        case 2:
            userManager.display_managers();
            break;
        case 3:
            manager.print_products();
            break;
        case 4:
            manager.add_product();
            break;
        case 5: {
            string customer_username;
            cout << "Nhap ten dang nhap khach hang muon xoa: ";
            cin >> customer_username;
            if (userManager.delete_customer(customer_username)) {
                cout << "Xoa khach hang thanh cong!" << endl;
            }
            else {
                cout << "Khach hang khong ton tai!" << endl;
            }
            break;
        }
        case 6: { // Delete product
            string product_name;
            cout << "Nhap ten san pham muon xoa: ";
            cin >> product_name;
            if (manager.delete_product(product_name)) {
                cout << "Xoa san pham thanh cong!" << endl;
            }
            else {
                cout << "San pham khong ton tai!" << endl;
            }
            break;
        }
        case 7: { // Register manager
            string username, password;
            cout << "Nhap ten dang nhap quan ly moi: ";
            cin >> username;
            cout << "Nhap mat khau: ";
            cin >> password;
            userManager.register_manager(username, password);
            cout << "Tao tai khoan quan ly thanh cong!" << endl;
            break;
        }
        case 0:
            cout << "Dang xuat..." << endl;
            return;
        default:
            cout << "Lua chon khong hop le. Vui long thu lai." << endl;
            break;
        }
        cout << "Nhan phim bat ky de tiep tuc...";
        cin.ignore();
        cin.get();
    }
}

int main() {
    ProductManager manager;
    UserManager userManager;

    userManager.add_manager("uy", "uy12345");
    userManager.add_manager("an", "an12345");

    int choice;
    string role;

    while (true) {
        cout << "Ban la:" << endl;
        cout << "1. Quan ly" << endl;
        cout << "2. Khach hang" << endl;
        cout << "0. Thoat" << endl;
        cout << "Lua chon cua ban: ";
        cin >> choice;

        if (choice == 0) {
            break;
        }
        else if (choice == 1) {
            string username, password;
            cout << "Ten dang nhap: ";
            cin >> username;
            cout << "Mat khau: ";
            cin >> password;

            if (userManager.login(username, password, role) && role == "manager") {
                display_manager_menu(manager, userManager);
            }
            else {
                cout << "Dang nhap that bai. Vui long thu lai." << endl;
            }
        }
        else if (choice == 2) {
            int sub_choice;
            cout << "1. Dang nhap khach hang" << endl;
            cout << "2. Dang ky khach hang" << endl;
            cout << "Lua chon cua ban: ";
            cin >> sub_choice;

            if (sub_choice == 1) {
                string username, password;
                cout << "Ten dang nhap: ";
                cin >> username;
                cout << "Mat khau: ";
                cin >> password;

                if (userManager.login(username, password, role) && role == "customer") {
                    display_product_menu(manager, userManager, username);
                }
                else {
                    cout << "Dang nhap that bai. Vui long thu lai." << endl;
                }
            }
            else if (sub_choice == 2) {
                register_customer(userManager);
            }
            else {
                cout << "Lua chon khong hop le. Vui long thu lai." << endl;
            }
        }
        else {
            cout << "Lua chon khong hop le. Vui long thu lai." << endl;
        }
    }

    return 0;
}
