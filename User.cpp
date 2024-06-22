#include "User.h"
#include <fstream>
#include <iostream>

UserManager::UserManager() {
    load_users();
}

void UserManager::load_users() {
    ifstream customer_file("user.txt");
    if (customer_file.is_open()) {
        string username, password, phone, role;
        while (customer_file >> username >> password >> phone >> role) {
            if (role == "customer") {
                customers.push_back(User(username, password, phone, role));
            }
        }
        customer_file.close();
    }

    ifstream manager_file("manager.txt");
    if (manager_file.is_open()) {
        string username, password, role;
        while (manager_file >> username >> password >> role) {
            if (role == "manager") {
                managers.push_back(User(username, password, "", role));
            }
        }
        manager_file.close();
    }
}

void UserManager::save_users() {
    ofstream customer_file("user.txt");
    if (customer_file.is_open()) {
        for (const auto& user : customers) {
            customer_file << user.username << " " << user.password << " " << user.phone << " " << user.role << endl;
        }
        customer_file.close();
    }

    ofstream manager_file("manager.txt");
    if (manager_file.is_open()) {
        for (const auto& user : managers) {
            manager_file << user.username << " " << user.password << " " << user.role << endl;
        }
        manager_file.close();
    }
}

void UserManager::add_manager(const string& username, const string& password) {
    managers.push_back(User(username, password, "", "manager"));
    save_users();
}

void UserManager::register_customer(const string& username, const string& password, const string& phone) {
    customers.push_back(User(username, password, phone, "customer"));
    save_users();
}

bool UserManager::login(const string& username, const string& password, string& role) {
    for (const auto& user : customers) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }
    for (const auto& user : managers) {
        if (user.username == username && user.password == password) {
            role = user.role;
            return true;
        }
    }
    return false;
}

void UserManager::display_customers() {
    cout << "Danh sach khach hang:" << endl;
    for (const auto& user : customers) {
        if (user.role == "customer") {
            cout << "Ten: " << user.username << ", So dien thoai: " << user.phone << endl;
        }
    }
}

void UserManager::display_managers() {
    cout << "Danh sach quan ly:" << endl;
    for (const auto& user : managers) {
        if (user.role == "manager") {
            cout << "Ten: " << user.username << endl;
        }
    }
}

User UserManager::get_customer_details(const string& username) {
    for (const auto& user : customers) {
        if (user.username == username) {
            return user;
        }
    }
    return User();
}

bool UserManager::delete_customer(const string& username) {
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->username == username && it->role == "customer") {
            customers.erase(it);
            save_users();
            return true;
        }
    }
    return false;
}

void UserManager::register_manager(const string& username, const string& password) {
    managers.push_back(User(username, password, "", "manager"));
    save_users();
}
