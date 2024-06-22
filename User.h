#pragma once
#include <string>
#include <vector>

using namespace std;

class User {
public:
    string username;
    string password;
    string phone;
    string role;

    User() {}
    User(string u, string p, string ph, string r) : username(u), password(p), phone(ph), role(r) {}
};

class UserManager {
private:
    vector<User> customers;
    vector<User> managers;
    void load_users();
    void save_users();
public:
    UserManager();
    void add_manager(const string& username, const string& password);
    void register_customer(const string& username, const string& password, const string& phone);
    bool login(const string& username, const string& password, string& role);
    void display_customers();
    void display_managers();
    User get_customer_details(const string& username);
    bool delete_customer(const string& username);
    void register_manager(const string& username, const string& password); // New function
};
