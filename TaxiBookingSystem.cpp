#include <iostream>
#include <fstream> //read and write to files
#include <vector> //
#include <string>
#include <sstream>
using namespace std;

struct Customer {
    string email;
    string firstName;
    string lastName;
    string phoneNumber;
    string password;

    //constructor
    Customer(string e = "temp@email.com", string f = "firstName", string l = "lastName", string ph = "phoneNumber", string pa = "password") {
        email = e;
        firstName = f;
        lastName = l;
        phoneNumber = ph;
        password = pa;
    }
};

struct Driver {
    string email;
    string firstName;
    string lastName;
    string phoneNumber;
    string password;
    string licence; //drivers license number
    string registration; //rego license plate number of taxi

    //constructor
    Driver(string e = "temp@email.com", string f = "firstName", string l = "lastName", string ph = "phoneNumber", string pa = "password", string li = "licenceNum", string re = "registrationNum") {
        email = e;
        firstName = f;
        lastName = l;
        phoneNumber = ph;
        password = pa;
        licence = li;
        registration = re;
    }
};

struct Admin {
    string email;
    string firstName;
    string lastName;
    string phoneNumber;
    string password;

    //constructor
    Admin(string e = "temp@email.com", string f = "firstName", string l = "lastName", string ph = "phoneNumber", string pa = "password") {
        email = e;
        firstName = f;
        lastName = l;
        phoneNumber = ph;
        password = pa;
    }
};

//prototypes
void registerNewLogin();
void login();
vector<Customer> readCustomerFile();
vector<Driver> readDriversFile();
vector<Admin> readAdminsFile();
void displayAllCostomers(vector<Customer>customerList);
void displayAllDrivers(vector<Driver>driversList);
void displayAllAdmin(vector<Admin>adminList);
void updateCustomersFile(vector<Customer> customers);
string createAndCheckPassword();
void pageBreak();




int main() //start menu
{
    string userInput{};
    bool keepRunning{true};
    pageBreak();
    while (keepRunning) {
        //start menu
        cout << "\nTaxi App" << endl;
        cout << "********" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        getline(cin, userInput);

        if (userInput == "1") {
            registerNewLogin();
        }
        else if (userInput == "2") {
            login();
        }
        else if (userInput == "3") {
            cout << "Bye for now" << endl;
            keepRunning = false;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }

    return 0;
}

void registerNewLogin() {
    pageBreak();

    //read customers.csv and put in vector
    vector<Customer> customerList = readCustomerFile();

    //add new customer to customerList
    Customer newCustomer;
    string unverifiedEmail;
    cout << "\nRegister as new customer" << endl;
    cout << "************************" << endl;
    bool containsAddressSign{ false };

    //promt user to enter email
    while(containsAddressSign == false) {
        cout << "\nEnter email (This will be your username): ";
        getline(cin, unverifiedEmail);

        //make sure email has '@' symbol and a '.' symbol 
        if (unverifiedEmail.find('@') != string::npos && unverifiedEmail.find('.') != string::npos) {
            containsAddressSign = true;
        }
        else cout << "Invalid email, example: johnappleseed@email.com" << endl;
    }

    //verify that email is not a conflict
    for (auto c : customerList) {
        if (c.email == unverifiedEmail) {
            cout << "Email address already exists. Go to login menu." << endl;
            return;
        }
    }

    //get new customer details
    newCustomer.email = unverifiedEmail;
    cout << "Enter first name: ";
    getline(cin, newCustomer.firstName);
    cout << "Enter last name: ";
    getline(cin, newCustomer.lastName);
    cout << "Enter phone number: ";
    getline(cin, newCustomer.phoneNumber);

    //check password    
    
    newCustomer.password = createAndCheckPassword();
    customerList.push_back(newCustomer);

    //update customers.csv
    updateCustomersFile(customerList);
    cout << "You're all signed up! Now you can login" << endl;
}

void login() {
    //read customers.csv
    vector<Customer> customerList = readCustomerFile();
    //read staff.csv
    vector<Driver> driversList = readDriversFile();
    //read admin.csv
    vector<Admin> adminList = readAdminsFile();

    string inputUsername;
    string inputPassword;
    pageBreak();
    cout << "Login" << endl;
    cout << "*****" << endl;
    string userAuthority = "customer";
    //promt for username and password then look through customerList, driversList and adminList
    bool foundUsernamePasswordMatch = false;
    while (foundUsernamePasswordMatch != true) {
        cout << "\nEnter username (email): ";
        getline(cin, inputUsername);
        cout << "Enter password: ";
        getline(cin, inputPassword);
        //look in customer list
        for (int i = 0; i < customerList.size(); i++) {
            if (inputUsername == customerList[i].email && inputPassword == customerList[i].password) {
                userAuthority = "customer";
                foundUsernamePasswordMatch = true;
            }
        }
        //look in driver list
        for (int i = 0; i < driversList.size(); i++) {
            if (inputUsername == driversList[i].email && inputPassword == driversList[i].password) {
                userAuthority = "driver";
                foundUsernamePasswordMatch = true;
            }
        }
        //look in admin list
        for (int i = 0; i < adminList.size(); i++) {
            if (inputUsername == adminList[i].email && inputPassword == adminList[i].password) {
                userAuthority = "admin";
                foundUsernamePasswordMatch = true;
            }
        }

        if(foundUsernamePasswordMatch != true) cout << "Incorrect username or password, try again" << endl;
    }

    cout << "correct name and password" << endl;

    if (userAuthority == "customer") {
        cout << "You are a customer" << endl;
        //customerMenu(userName); 
    }
    else if (userAuthority == "driver") {
        cout << "You are a driver" << endl;
        //driverMenu(userName);
    }
    else if (userAuthority == "admin") {
        cout << "You are admin" << endl;
        //adminMenu(userName);

    }
}

vector<Customer> readCustomerFile() {
    //this function will read customers.csv and return vector
    vector<Customer> customers;
    fstream customersFile;
    Customer tempCustomer;
    customersFile.open("customers.csv", ios::in);
    if (customersFile.is_open()) {
        string line;
        string cell;
        while (getline(customersFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempCustomer.email = cell;

            getline(linestream, cell, ',');
            tempCustomer.firstName = cell;

            getline(linestream, cell, ',');
            tempCustomer.lastName = cell;

            getline(linestream, cell, ',');
            tempCustomer.phoneNumber = cell;

            getline(linestream, cell, ',');
            tempCustomer.password = cell;
            customers.push_back(tempCustomer);
        }
        customersFile.close();
    }
    return customers;
}

vector<Driver> readDriversFile() {
    //this function will read drivers.csv and return vector
    vector<Driver> drivers;
    fstream driversFile;
    Driver tempDriver;
    driversFile.open("drivers.csv", ios::in);
    if (driversFile.is_open()) {
        string line;
        string cell;
        while (getline(driversFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempDriver.email = cell;

            getline(linestream, cell, ',');
            tempDriver.firstName = cell;

            getline(linestream, cell, ',');
            tempDriver.lastName = cell;

            getline(linestream, cell, ',');
            tempDriver.phoneNumber = cell;

            getline(linestream, cell, ',');
            tempDriver.password = cell;

            getline(linestream, cell, ',');
            tempDriver.licence = cell;

            getline(linestream, cell, ',');
            tempDriver.registration = cell;

            drivers.push_back(tempDriver);
        }
        driversFile.close();
    }
    return drivers;
}

vector<Admin> readAdminsFile() {
    //this function will read admin.csv and return vector
    vector<Admin> admin;
    fstream adminFile;
    Admin tempAdmin;
    adminFile.open("admin.csv", ios::in);
    if (adminFile.is_open()) {
        string line;
        string cell;
        while (getline(adminFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempAdmin.email = cell;

            getline(linestream, cell, ',');
            tempAdmin.firstName = cell;

            getline(linestream, cell, ',');
            tempAdmin.lastName = cell;

            getline(linestream, cell, ',');
            tempAdmin.phoneNumber = cell;

            getline(linestream, cell, ',');
            tempAdmin.password = cell;
            admin.push_back(tempAdmin);
        }
        adminFile.close();
    }
    return admin;
}

void displayAllCostomers(vector<Customer>customerList) {
    //displays all customers and their details from a vector
    for (auto c : customerList) {
        cout << "Email: " << c.email << endl;
        cout << "Name: " << c.firstName << " " << c.lastName << endl;
        cout << "Ph number: " << c.phoneNumber << endl;
        cout << endl;
    }
}

void displayAllDrivers(vector<Driver>driversList) {
    //displays all customers and their details from a vector
    for (auto d : driversList) {
        cout << "Email: " << d.email << endl;
        cout << "Name: " << d.firstName << " " << d.lastName << endl;
        cout << "Ph number: " << d.phoneNumber << endl;
        cout << "License number: " << d.licence << endl;
        cout << "Registration: " << d.registration << endl;
        cout << endl;
    }
}

void displayAllAdmin(vector<Admin>adminList) {
    //displays all admin and their details from a vector
    for (auto a : adminList) {
        cout << "Email: " << a.email << endl;
        cout << "Name: " << a.firstName << " " << a.lastName << endl;
        cout << "Ph number: " << a.phoneNumber << endl;
        cout << endl;
    }
};

void updateCustomersFile(vector<Customer> customers) {
    fstream customersFile;
    customersFile.open("customers.csv", ios::out);
    if (customersFile.is_open()) {
        for (int i = 0; i < customers.size(); i++) {
            customersFile << customers[i].email << "," << customers[i].firstName << ","
                << customers[i].lastName << "," << customers[i].phoneNumber << "," << customers[i].password << endl;
        }
        customersFile.close();
    }
}

string createAndCheckPassword() {
    //ask user to create password, then asks them to enter in password again to return password
    string tempPassword{ "temp" };
    string checkPassword{ "check" };
    while (tempPassword != checkPassword) {
        cout << "Enter password: ";
        getline(cin, tempPassword);
        cout << "Enter password again: ";
        getline(cin, checkPassword);
        if (tempPassword != checkPassword)
            cout << "Passwords not the same, please try again" << endl;
    }
    return tempPassword;
}

void pageBreak() {
    //complex line making algorithim 
    cout << "\n-------------------------------------------\n" << endl;
}

