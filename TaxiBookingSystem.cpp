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

//struct Booking

struct lostProperty {
    string description;
    string submittedBy;

    //constructor
    lostProperty(string d = "tempDescription", string s = "tempName") {
        description = d;
        submittedBy = s;
    }
};

struct lostPropertyClaim {
    string description;
    Customer reportedBy;

    //constructor
    lostPropertyClaim(string d = "tempDescription") {
        description = d;
    }
};

//struct Complaint

//struct Enquiry

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
void customerMenu(Customer user);
void pageBreak();
void submitLostProperty();
vector<lostProperty> readLostPropertyFile();
void updateLostPropertyFile(vector<lostProperty> lostPropertyList);
void displayAllLostProperty();
void contactMenu(Customer user);
void displayUserProfile(Customer c);

int main() //start menu
{
    string userInput, userSelect, userSupport{};
    bool keepRunning{ true };
    pageBreak();
    while (keepRunning) {
        //start menu
        cout << "\nTaxi App" << endl;
        cout << "********" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        getline(cin, userInput);

        if (userInput == "1" || userInput == "r") {
            registerNewLogin();
        }
        else if (userInput == "2" || userInput == "l") {
            login();
        }
        else if (userInput == "3" || userInput == "e") {
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
    while (containsAddressSign == false) {
        cout << "\nEnter email (This will be your username): " << endl;
        cout << "(note: type 'e' to cancel and exit)" << endl;
        getline(cin, unverifiedEmail);

        if (unverifiedEmail == "e") return; //if user types 'e' for exit, they will return to start menu

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
    if (newCustomer.firstName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter last name: ";
    getline(cin, newCustomer.lastName);
    if (newCustomer.lastName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter phone number: ";
    getline(cin, newCustomer.phoneNumber);
    if (newCustomer.phoneNumber == "e") return; //if user types 'e' for exit, they will return to start menu

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
    Customer customer;
    Driver driver;
    Admin admin;

    pageBreak();
    cout << "Login" << endl;
    cout << "*****" << endl;
    string userAuthority = "customer";
    //promt for username and password then look through customerList, driversList and adminList
    bool foundUsernamePasswordMatch = false;
    while (foundUsernamePasswordMatch != true) {
        cout << "\nEnter username (email): ";
        getline(cin, inputUsername);

        if (inputUsername == "e") return; //if user types 'e' for exit, they will return to start menu

        cout << "Enter password: ";
        getline(cin, inputPassword);
        //look in customer list
        for (int i = 0; i < customerList.size(); i++) {
            if (inputUsername == customerList[i].email && inputPassword == customerList[i].password) {
                userAuthority = "customer";
                customer = customerList[i];
                foundUsernamePasswordMatch = true;
            }
        }
        //look in driver list
        for (int i = 0; i < driversList.size(); i++) {
            if (inputUsername == driversList[i].email && inputPassword == driversList[i].password) {
                userAuthority = "driver";
                driver = driversList[i];
                foundUsernamePasswordMatch = true;
            }
        }
        //look in admin list
        for (int i = 0; i < adminList.size(); i++) {
            if (inputUsername == adminList[i].email && inputPassword == adminList[i].password) {
                userAuthority = "admin";
                admin = adminList[i];
                foundUsernamePasswordMatch = true;
            }
        }

        if (foundUsernamePasswordMatch != true) cout << "Incorrect username or password, try again (or enter 'e' to exit)" << endl;
    }

    cout << "correct name and password" << endl;

    if (userAuthority == "customer") {
        customerMenu(customer); 
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

void customerMenu(Customer user) {
    pageBreak();
    string userSelect;
    cout << "Welcome " << user.firstName << " " << user.lastName << ", What would you like to do today? Select from the options below.";

    while (true) {

        cout << "\nUser Options" << endl;
        cout << "********" << endl;
        cout << "1. View/Book Rides" << endl;
        cout << "2. View/Edit User Info" << endl;
        cout << "3. View Transactions" << endl;
        cout << "4. Contact Administration" << endl;
        cout << "5. Log Out" << endl;

        getline(cin, userSelect);

        if (userSelect == "1") {
            // bookRide();
        }
        else if (userSelect == "2") {
            displayUserProfile(user);
        }
        else if (userSelect == "3") {
            // userTransactions();

        }
        else if (userSelect == "4") {
            contactMenu(user);
        }
        else if (userSelect == "5") {
            cout << "User Logged Out Successfully" << endl;
            //keepRunning = false;
            return;
        }
        else {
            cout << "Invalid Input, Choose from the menu" << endl;
        }
    }
}

void contactMenu(Customer user) {
    pageBreak();
    cout << "Select an option your query relates to from the menu below!";

    string userInput;
    string enquiryMessage;
    string driverName;
    string complaintMessage;
    string itemDesc;
    
    cout << "\nAdmin Support" << endl;
    cout << "********" << endl;
    cout << "1. General Enquiries" << endl;
    cout << "2. Complaints" << endl;
    cout << "3. Lost Property" << endl;
    cout << "4. Return to main menu" << endl;

    getline(cin, userInput);

    if (userInput == "1") {
        cout << "General Enquiries";
        cout << "\n-----------------------------\n";
        cout << "Enter enquiry message below or press e to return:";
        getline(cin, enquiryMessage);
        if (enquiryMessage == "e") return; //if user types 'e' for exit, they will return to start menu

    }
    else if (userInput == "2") {
        cout << "Complaints Form";
        cout << "\n-----------------------------\n";
        cout << "Enter Driver Name your complaint is about or press e to return:";
        getline(cin, driverName); 
        if (driverName == "e") return; //if user types 'e' for exit, they will return to start menu
        cout << "Enter your complaint message below or press e to return:";
        getline(cin, complaintMessage);
        if (complaintMessage == "e") return; //if user types 'e' for exit, they will return to start menu
    }
    else if (userInput == "3") {
        cout << "Lost Property Claims";
        cout << "\n-----------------------------\n";
        cout << "Enter item description below or press e to return:";
        getline(cin, itemDesc);
        if (itemDesc == "e") return; //if user types 'e' for exit, they will return to start menu

    }
    else if (userInput == "4") {
        //customerMenu();
        return;
    }
    else {
        cout << "Invalid Input, Choose from the menu" << endl;
        contactMenu(user);
    }
}

void displayUserProfile(Customer c) { //====================================== still need fixing
    pageBreak();
    cout << "Email: " << c.email << endl;
    cout << "Name: " << c.firstName << " " << c.lastName << endl;
    cout << "Ph number: " << c.phoneNumber << endl;
    cout << endl;
}

void pageBreak() {
    //complex line making algorithim 
    cout << "\n-------------------------------------------\n" << endl;
}

void submitLostProperty() {
    //this function promts user to add to the list of lost property and will update the lostProperty.csv
    pageBreak();
    vector<lostProperty> lostPropertyList = readLostPropertyFile();
    lostProperty newLostProperty;

    cout << "Submit lost property" << endl;
    cout << "Enter item description: ";
    getline(cin, newLostProperty.description);

    cout << "Submitted by: ";
    getline(cin, newLostProperty.submittedBy);
    lostPropertyList.push_back(newLostProperty);

    updateLostPropertyFile(lostPropertyList);

}

vector<lostProperty> readLostPropertyFile() {
    //this function will read lostProperty.csv and return vector
    vector<lostProperty> lostPropertyList;
    fstream lostPropertyFile;
    lostProperty tempLostProperty;
    lostPropertyFile.open("lostProperty.csv", ios::in);
    if (lostPropertyFile.is_open()) {
        string line;
        string cell;
        while (getline(lostPropertyFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempLostProperty.description = cell;

            getline(linestream, cell, ',');
            tempLostProperty.submittedBy = cell;

            lostPropertyList.push_back(tempLostProperty);
        }
        lostPropertyFile.close();
    }
    return lostPropertyList;
}

void updateLostPropertyFile(vector<lostProperty> lostPropertyList) {
    //this function updates the lostProperty.csv with the latest information
    fstream lostPropertyFile;
    lostPropertyFile.open("lostProperty.csv", ios::out);
    if (lostPropertyFile.is_open()) {
        for (int i = 0; i < lostPropertyList.size(); i++) {
            lostPropertyFile << lostPropertyList[i].description << "," << lostPropertyList[i].submittedBy << endl;
        }
        lostPropertyFile.close();
    }
}

void displayAllLostProperty() {
    pageBreak();
    vector<lostProperty> lostPropertyList = readLostPropertyFile();

    cout << "lost property" << endl;
    for (auto l : lostPropertyList) {
        cout << l.description << ", submitted by " << l.submittedBy << endl;
    }
}

//void claimLostProperty