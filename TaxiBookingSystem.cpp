#include <iostream>
#include <fstream> // read and write to files
#include <vector> // 
#include <string>
#include <sstream>
#include <algorithm>
#include <ctype.h> // isdigit()
#include <ctime>
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
    float driverStart;
    float driverFinish;

    //constructor
    Driver(string e = "temp@email.com", string f = "firstName", string l = "lastName", string ph = "phoneNumber", string pa = "password", string li = "licenceNum", string re = "registrationNum", float dS = 0, float dF = 0) {
        email = e;
        firstName = f;
        lastName = l;
        phoneNumber = ph;
        password = pa;
        licence = li;
        registration = re;
        driverStart = dS;
        driverFinish = dF;
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

struct Booking {
    string bookingRef;
    Customer customer;
    Driver driver;
    string date;
    string time;
    int duration; //minutes
    string startLocation;
    string endLocation;
    float cost;

    //constructor
    Booking(string b = "refTemp", string d = "tempDate", string t = "tempTime", int du = 0, string sL = "tempStartLocation", string eL = "tempEndLocation", float c = 0) {
        bookingRef = b;
        date = d;
        time = t;
        duration = du;
        startLocation = sL;
        endLocation = eL;
        cost = c;
    }

};

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

struct complaintOrEnquiry {
    string enquiryType;
    string note;

    //constructor
    complaintOrEnquiry(string n = "") {
        note = n;
    }
};

//prototypes
void registerNewLogin();
void registerNewDriver();
void registerNewAdmin();
void login();
vector<Customer> readCustomerFile(); 
vector<Driver> readDriversFile();
vector<Admin> readAdminsFile();
void displayAllCostomers(vector<Customer>customerList);
void displayAllDrivers(vector<Driver>driversList);
void displayAllAdmin(vector<Admin>adminList);
void updateCustomersFile(vector<Customer> customers);
void updateAdminFile(vector<Admin> admin);
void updateDriversFile(vector<Driver> drivers);
string createAndCheckPassword();
void customerMenu(Customer user);
void driverMenu(Driver user);
void adminMenu(Admin user);
void pageBreak();
void submitLostProperty();
vector<lostProperty> readLostPropertyFile();
vector<lostPropertyClaim> readLostPropertyClaimsFile();
void displayAllLostPropertyClaims(vector<lostPropertyClaim> claims);
void updateLostPropertyFile(vector<lostProperty> lostPropertyList);
void displayAllLostProperty();
void claimLostProperty(Customer user);
void updateLostPropertyClaimsFile(vector<lostPropertyClaim> claims);
void contactMenu(Customer user);
void displayUserProfile(Customer c);
void displayAdminProfile(Admin a);
void  displayDriverProfile(Driver user);
void makeBooking(Customer user);
vector<Booking> readBookingsFile();
void displayAllBookings(vector<Booking> bookings);
Driver getDriverByEmail(string email);
Customer getCustomerByEmail(string email);
void updateBookingsFile(vector<Booking> bookings);
void updateSchedule(vector<vector<string>> availableTimes, string filename);
void createNewSchedule(string filename);
string getDriverAvailabilityByTime(Driver driver, string time);
void bookingOverflow(string driverEmail, string date, float halfHourBlocksOverflow, string bookingRef);
string incrementDate(string date);
void checkForSchedule(string filename);
vector<vector<string>> readSchedule(string filename);
vector<vector<string>> addNewDriversToSchedule(vector<vector<string>> schedule);
bool hasDatePassed(string date);
bool isDateWithinTimeFrame(string date, int timeFrame);
void displayThisCustomersTransactions(Customer user);
void displayAllTransactions();
void makeComplaintOrEnquiry(string enquiryType);
vector<complaintOrEnquiry> readEnquiriesFile();
void updateEnquiriesFile(vector<complaintOrEnquiry> enquiries);
void displayEnquiries(vector<complaintOrEnquiry> enquiries);
void DisplayThisDriversTransactions(Driver user);
void displayThisDriversScheduleToday(Driver user);
string getTodaysDateAsString();
Customer chooseCustomer(vector<Customer> customers);
Admin chooseAdmin(vector<Admin> admin);
Driver chooseDriver(vector<Driver> drivers);
void displayFullSchedule(string date);
string promtForDate();


// to do:     replace(myString.begin(), myString.end(), ',', ' ');


int main() //start menu
{
    pageBreak();
    cout << "== Taxi services Wellington ==" << endl;
    cout << "******************************" << endl;

    string userInput, userSelect, userSupport{};
    bool keepRunning{ true };
    while (keepRunning) {
        //start menu
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;

        getline(cin, userInput);

        if (userInput == "1" || userInput == "r") {
            pageBreak();
            cout << "\nRegister as new customer" << endl;
            cout << "************************" << endl;
            registerNewLogin();
            cout << "You're all signed up! Now you can login" << endl << endl;
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
        pageBreak();
    }

    return 0;
}

void registerNewLogin() {
    

    //read customers.csv and put in vector
    vector<Customer> customerList = readCustomerFile();

    //add new customer to customerList
    Customer newCustomer;
    string unverifiedEmail;
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
}

void registerNewDriver() {


    //read drivers.csv and put in vector
    vector<Driver> driversList = readDriversFile();
    displayAllDrivers(driversList);
    //cout << "Start: " << driversList.at(1).driverStart << " Finish: " << driversList.at(1).driverFinish << endl;
    //add new driver to driversList
    Driver newDriver;
    string unverifiedEmail;
    bool containsAddressSign{ false };

    //promt user to enter email
    while (containsAddressSign == false) {
        cout << "\nEnter email (This will be the drivers username): " << endl;
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
    for (auto d : driversList) {
        if (d.email == unverifiedEmail) {
            cout << "Email address already exists" << endl;
            return;
        }
    }

    //get new driver details
    string userInputTime;
    double numUserInputTime;
    newDriver.email = unverifiedEmail;
    cout << "Enter first name: ";
    getline(cin, newDriver.firstName);
    if (newDriver.firstName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter last name: ";
    getline(cin, newDriver.lastName);
    if (newDriver.lastName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter phone number: ";
    getline(cin, newDriver.phoneNumber);
    if (newDriver.phoneNumber == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter drivers liscence number: ";
    getline(cin, newDriver.licence);
    if (newDriver.licence == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter taxi registration number: ";
    getline(cin, newDriver.registration);
    if (newDriver.registration == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "\nYour almost there... Input work hours for new driver" << endl;
    cout << "Note: Times must be entered in 24hr time, 0.00 to 23.30" << endl;
    cout << "and must be divisible by the half hour. For example, 01.00, 05.30, 13.00, 17.30 etc" << endl << endl;

    bool isDriverHoursValid = false;
    while (isDriverHoursValid == false) {
        bool keepRunning = true;
        while (keepRunning) {
            //promt for time format ( HH.MM ) and round up to hh.00 or hh.30
            //newDriver.driverStart 
            cout << "Enter time that driver starts each day: ";
            getline(cin, userInputTime);
            if (userInputTime == "e") return; //if user types 'e' for exit, they will return to start menu
            // HH.MM

            if (userInputTime.length() == 4)
                userInputTime = "0" + userInputTime;

            if (userInputTime.length() == 5) {

                if (isdigit(userInputTime[0]) && isdigit(userInputTime[1]) && userInputTime[2] == '.' && (userInputTime[3] == '3' || userInputTime[3] == '0') && userInputTime[4] == '0') {
                    istringstream ssUserInputTime(userInputTime);
                    ssUserInputTime >> numUserInputTime;
                    if (numUserInputTime >= 0.0 && numUserInputTime < 24.0)
                        keepRunning = false;
                }
            }
        }
        cout << "userInput time start:" << numUserInputTime << endl;
        newDriver.driverStart = numUserInputTime;


        keepRunning = true;
        while (keepRunning) {
            //newDriver.driverFinish
            cout << "Enter time that driver finishes each day: ";
            getline(cin, userInputTime);
            if (userInputTime == "e") return; //if user types 'e' for exit, they will return to start menu
            if (userInputTime.length() == 4)
                userInputTime = "0" + userInputTime;

            if (userInputTime.length() == 5) {

                if (isdigit(userInputTime[0]) && isdigit(userInputTime[1]) && userInputTime[2] == '.' && (userInputTime[3] == '3' || userInputTime[3] == '0') && userInputTime[4] == '0') {
                    istringstream ssUserInputTime(userInputTime);
                    ssUserInputTime >> numUserInputTime;
                    if (numUserInputTime >= 0.0 && numUserInputTime < 24.0)
                        keepRunning = false;
                }
            }
        }
        cout << "userInput time finish:" << numUserInputTime << endl;
        newDriver.driverFinish = numUserInputTime;

        //make sure driver hours do not exceed 12 hours
        //driver finish plus 12 //if driver finish < driver start : driver finish += 12 // if (driver finish - driver start < 12 break loop)
        double startTime = newDriver.driverStart;
        double endTime = newDriver.driverFinish;
        if (endTime <= newDriver.driverStart) {
            endTime += 12;
            startTime -= 12;
        }

        double totalHours = endTime - startTime;

        if (totalHours < 12) {
            isDriverHoursValid = true;
        }
        else {
            cout << "Driver hours cannot exceed 12 hours" << endl;
        }

    }

    //check password    

    newDriver.password = createAndCheckPassword();
    driversList.push_back(newDriver);


    //update drivers.csv
    updateDriversFile(driversList);
}

void registerNewAdmin() {

    //read customers.csv and put in vector
    vector<Admin> adminList = readAdminsFile();

    //add new customer to customerList
    Admin newAdmin;
    string unverifiedEmail;
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
    for (auto a : adminList) {
        if (a.email == unverifiedEmail) {
            cout << "Email address already exists. Go to login menu." << endl;
            return;
        }
    }

    //get new customer details
    newAdmin.email = unverifiedEmail;
    cout << "Enter first name: ";
    getline(cin, newAdmin.firstName);
    if (newAdmin.firstName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter last name: ";
    getline(cin, newAdmin.lastName);
    if (newAdmin.lastName == "e") return; //if user types 'e' for exit, they will return to start menu

    cout << "Enter phone number: ";
    getline(cin, newAdmin.phoneNumber);
    if (newAdmin.phoneNumber == "e") return; //if user types 'e' for exit, they will return to start menu

    //check password    

    newAdmin.password = createAndCheckPassword();
    adminList.push_back(newAdmin);

    

    //update customers.csv
    updateAdminFile(adminList);
    cout << "New admin created" << endl;
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

        if (foundUsernamePasswordMatch != true) 
            cout << "Incorrect username or password, try again" << 
            "\nif you have forgotten your password please call us at 0800 468 456 816 (or enter 'e' to exit)" << endl;
    }

    cout << "correct name and password" << endl;

    if (userAuthority == "customer") {
        customerMenu(customer); 
    }
    else if (userAuthority == "driver") {
        //cout << "You are a driver" << endl;
        driverMenu(driver);
    }
    else if (userAuthority == "admin") {
        //cout << "You are admin" << endl;
        adminMenu(admin);
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

            getline(linestream, cell, ',');
            stringstream ssDriverStart(cell);
            ssDriverStart >> tempDriver.driverStart;

            getline(linestream, cell, ',');
            stringstream ssDriverFinish(cell);
            ssDriverFinish >> tempDriver.driverFinish;


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
    pageBreak();
    //displays all customers and their details from a vector
    for (auto c : customerList) {
        cout << "Email: " << c.email << endl;
        cout << "Name: " << c.firstName << " " << c.lastName << endl;
        cout << "Ph number: " << c.phoneNumber << endl;
        cout << endl;
    }
    cout << "Press enter to continue..." << endl;
    string contin;
    getline(cin, contin);
}

void displayAllDrivers(vector<Driver>driversList) {
    //displays all customers and their details from a vector
    for (auto d : driversList) {
        cout << "Email: " << d.email << endl;
        cout << "Name: " << d.firstName << " " << d.lastName << endl;
        cout << "Ph number: " << d.phoneNumber << endl;
        cout << "License number: " << d.licence << endl;
        cout << "Registration: " << d.registration << endl;
        cout << "Start: " << d.driverStart << endl;
        cout << "Finish: " << d.driverFinish << endl;
        cout << endl;
    }
    cout << "Press enter to continue..." << endl;
    string contin;
    getline(cin, contin);
}

void displayAllAdmin(vector<Admin>adminList) {
    //displays all admin and their details from a vector
    for (auto a : adminList) {
        cout << "Email: " << a.email << endl;
        cout << "Name: " << a.firstName << " " << a.lastName << endl;
        cout << "Ph number: " << a.phoneNumber << endl;
        cout << endl;
    }
    cout << "Press enter to continue..." << endl;
    string contin;
    getline(cin, contin);
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

void updateAdminFile(vector<Admin> admin) {
    fstream adminFile;
    adminFile.open("admin.csv", ios::out);
    if (adminFile.is_open()) {
        for (int i = 0; i < admin.size(); i++) {
            adminFile << admin[i].email << "," << admin[i].firstName << ","
                << admin[i].lastName << "," << admin[i].phoneNumber << "," << admin[i].password << endl;
        }
        adminFile.close();
    }
}

void updateDriversFile(vector<Driver> drivers) {
    fstream driversFile;
    driversFile.open("drivers.csv", ios::out);
    if (driversFile.is_open()) {
        for (int i = 0; i < drivers.size(); i++) {
            driversFile << drivers[i].email << "," << drivers[i].firstName << ","
                << drivers[i].lastName << "," << drivers[i].phoneNumber << "," << drivers[i].password << ","
                << drivers[i].licence << "," << drivers[i].registration << "," << drivers[i].driverStart 
                << "," << drivers[i].driverFinish << endl;
        }
        driversFile.close();
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
    cout << "Logged in as customer" << endl;
    cout << "Welcome " << user.firstName << " " << user.lastName << ", What would you like to do today? Select from the options below.";

    while (true) {

        cout << "\nUser Options" << endl;
        cout << "********" << endl;
        cout << "1. Book a ride" << endl;
        cout << "2. View/Edit User Info" << endl;
        cout << "3. View Transactions or cancel a booking" << endl;
        cout << "4. Contact Administration" << endl;
        cout << "5. Log Out" << endl;

        getline(cin, userSelect);

        if (userSelect == "1") {
            makeBooking(user);
        }
        else if (userSelect == "2") {
            displayUserProfile(user);
        }
        else if (userSelect == "3") {
            displayThisCustomersTransactions(user);

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

void driverMenu(Driver user) {
    pageBreak();
    bool keepRunning = true;
    while (keepRunning) {
        cout << "Logged in as Driver" << endl;
        cout << "*******************" << endl;
        cout << "Welcome " << user.firstName << " " << user.lastName << endl;
        cout << "1. View Todays Schedule" << endl;
        cout << "2. Display your transactions" << endl;
        cout << "3. Submit lost property" << endl;
        cout << "4. Edit driver details" << endl;
        cout << "5. Log out" << endl;
        cout << "Enter option: ";
        string userInput;
        getline(cin, userInput);

        int numUserInput = 0;
        istringstream ssUserInput(userInput);
        ssUserInput >> numUserInput;

        switch (numUserInput)
        {
        case 1:
            displayThisDriversScheduleToday(user);

            break;
        case 2:
            DisplayThisDriversTransactions(user);
            break;
        case 3:
            submitLostProperty();
            break;
        case 4:
            displayDriverProfile(user);

            break;
        case 5:
            keepRunning = false;
            return;
            break;
        default:
            cout << "Invalid input" << endl;
            break;
        }
    }




}

void adminMenu(Admin user) {
    bool keepRunning = true;

    while (keepRunning) {
        pageBreak();
        vector<Customer> customers = readCustomerFile();
        vector<Driver> drivers = readDriversFile();
        vector<Admin> admin = readAdminsFile();
        vector<lostPropertyClaim> claims = readLostPropertyClaimsFile();
        vector<complaintOrEnquiry> enquiries = readEnquiriesFile();
        Customer editCustomer;
        Driver editDriver;
        Admin editAdmin;
        string todaysDate = getTodaysDateAsString();
        string chosenDate;



        cout << "Logged in as Admin" << endl;
        cout << "Welcome " << user.firstName << " " << user.lastName << endl;
        //viewAllUsers
        cout << "\n1. View all customers" << endl;
        cout << "2.  Add customers" << endl;
        cout << "3.  Edit customers details" << endl;
        cout << "4.  View all Drivers" << endl;
        cout << "5.  Add driver" << endl;
        cout << "6.  Edit driver details" << endl;
        cout << "7.  View schedule for a given day (all drivers)" << endl;
        cout << "8.  View schedule today (all drivers)" << endl;
        cout << "9.  View all transactions/cancel a booking" << endl;
        cout << "10. Make booking" << endl;
        cout << "11. View all complaints / enquiries" << endl;
        cout << "12. View lost property" << endl;
        cout << "13. Add lost property" << endl;
        cout << "14. View lost property claims" << endl;
        cout << "15. View admin" << endl;
        cout << "16. Add admin" << endl;
        cout << "17. Edit admin" << endl;
        cout << "18. Log out" << endl;
        cout << "Enter option: ";
        string userInput;
        getline(cin, userInput);

        int numUserInput = 0;
        istringstream ssUserInput(userInput);
        ssUserInput >> numUserInput;


        switch (numUserInput) {
        case 1:
            displayAllCostomers(customers);
            break;
        case 2:
            pageBreak();
            cout << "Add new customer" << endl;
            cout << "****************" << endl;
            registerNewLogin(); // the last promt is not suitable for admin to see
            cout << "User added" << endl;
            break;
        case 3:
            pageBreak();
            cout << "Edit customer" << endl;
            cout << "*************" << endl;
            //choose customer
            editCustomer = chooseCustomer(customers);
            //display customer and give options to edit
            displayUserProfile(editCustomer);
            break;
        case 4:
            pageBreak();
            cout << "All Drivers" << endl;
            cout << "***********" << endl;

            displayAllDrivers(drivers);
            break;
        case 5:
            //add driver
            cout << "Register new Driver" << endl;
            cout << "*******************" << endl;
            registerNewDriver();
            break;
        case 6:
            pageBreak();
            cout << "Edit Driver" << endl;
            cout << "***********" << endl;
            //choose driver
            editDriver = chooseDriver(drivers);
            //display customer and give options to edit
            displayDriverProfile(editDriver);
            break;
        case 7:
            // display full schedule for a given day
            chosenDate = promtForDate();
            displayFullSchedule(chosenDate);
            break;
        case 8:
            displayFullSchedule(todaysDate);
            break;
        case 9:
            displayAllTransactions();
            break;
        case 10:
            // make booking
            cout << "\nChoose customer" << endl;
            cout << "***************" << endl;
            //choose customer
            editCustomer = chooseCustomer(customers);
            makeBooking(editCustomer);
            break;
        case 11:
            //view all complaints / enquiries
            cout << "\nComplaints and enquiries" << endl;
            cout << "************************" << endl;
            displayEnquiries(enquiries);
            break;
        case 12:
            //view lost property
            displayAllLostProperty();
            break;
        case 13:
            //add lostProperty
            submitLostProperty();
            break;
        case 14:
            //view lost property claims
            displayAllLostPropertyClaims(claims);
            break;
        case 15:
            //View admin
            pageBreak();
            cout << "All admin" << endl;
            cout << "*********" << endl;
            displayAllAdmin(admin);
            break;
        case 16:
            //Add admin
            //add driver
            cout << "Register new admin" << endl;
            cout << "******************" << endl;
            registerNewAdmin();
            break;
        case 17:
            //Edit admin
            pageBreak();
            cout << "Edit admin" << endl;
            cout << "**********" << endl;
            //choose admin
            editAdmin = chooseAdmin(admin);
            //display admin and give options to edit
            displayAdminProfile(editAdmin);
            break;
        case 18:
            //Log out
            keepRunning = false;
            break;

        default:
            cout << "Invalid input" << endl;
            break;
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
    cout << "4. View company Contact details" << endl;
    cout << "5. Return to main menu" << endl;

    getline(cin, userInput);

    if (userInput == "1") {
        pageBreak();
        cout << "General Enquiries" << endl;
        cout << "*****************" << endl;
        makeComplaintOrEnquiry("enquiry");

    }
    else if (userInput == "2") {
        pageBreak();
        cout << "Complaints" << endl;
        cout << "**********" << endl;
        makeComplaintOrEnquiry("complaint");
    }
    else if (userInput == "3") {
        
        claimLostProperty(user);

    }
    else if (userInput == "4") {
        pageBreak();
        cout << "== Taxi services Wellington ==" << endl;
        cout << "50 Centre st, Wellington" << endl;
        cout << "Ph: 0800 123 456 7890" << endl << endl;
        cout << "press enter to continue...";
        string contin;
        getline(cin, contin);

    }
    else if (userInput == "5") {
        //customerMenu();
        return;
    }
    else {
        cout << "Invalid Input, Choose from the menu" << endl;
        contactMenu(user);
    }
}

void displayUserProfile(Customer c) { 
    pageBreak();
    vector<Customer> customers = readCustomerFile();
    // find matching customer in vector
    int thisCustomer = 0;
    for (int i = 0; i < customers.size(); i++) {
        if (customers.at(i).email == c.email)
            thisCustomer = i;
    }

    cout << "User profile" << endl;
    cout << "Email: " << customers.at(thisCustomer).email << endl;
    cout << "Name: " << customers.at(thisCustomer).firstName << " " << customers.at(thisCustomer).lastName << endl;
    cout << "Ph number: " << customers.at(thisCustomer).phoneNumber << endl;
    cout << endl;
    cout << "*note: email cannot be changed. If you need to change email you must make a new account" << endl;
    cout << "\nWould you like to update this information? (Y/N): ";

    bool keepRunning = true;
    while (keepRunning) {

        string userInput;
        getline(cin, userInput);
        if (userInput == "Y" or userInput == "y") {

            // promt user to update customer details
            //cout << "cutomer at i: " << thisCustomer << ": " << customers.at(thisCustomer).email << endl;
            cout << "Update Information for " << customers.at(thisCustomer).firstName << " " << customers.at(thisCustomer).lastName << endl << endl;
            cout << "Enter first name: ";
            getline(cin, customers.at(thisCustomer).firstName);
            cout << "Enter last name: ";
            getline(cin, customers.at(thisCustomer).lastName);
            cout << "Enter ph number: ";
            getline(cin, customers.at(thisCustomer).phoneNumber);
            updateCustomersFile(customers);
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "e") {
            keepRunning = false;
        }
        else {
            cout << "Invalid Input (Y/N)" << endl;
        }
    }
}

void displayAdminProfile(Admin a) {
    pageBreak();
    vector<Admin> admin = readAdminsFile();
    // find matching customer in vector
    int thisAdmin = 0;
    for (int i = 0; i < admin.size(); i++) {
        if (admin.at(i).email == a.email)
            thisAdmin = i;
    }

    cout << "User profile" << endl;
    cout << "Email: " << admin.at(thisAdmin).email << endl;
    cout << "Name: " << admin.at(thisAdmin).firstName << " " << admin.at(thisAdmin).lastName << endl;
    cout << "Ph number: " << admin.at(thisAdmin).phoneNumber << endl;
    cout << endl;
    cout << "*note: email cannot be changed. If you need to change email you must make a new account" << endl;
    cout << "\nWould you like to update this information? (Y/N): ";

    bool keepRunning = true;
    while (keepRunning) {

        string userInput;
        getline(cin, userInput);
        if (userInput == "Y" or userInput == "y") {

            // promt user to update customer details
            //cout << "cutomer at i: " << thisCustomer << ": " << customers.at(thisCustomer).email << endl;
            cout << "Update Information for " << admin.at(thisAdmin).firstName << " " << admin.at(thisAdmin).lastName << endl << endl;
            cout << "Enter first name: ";
            getline(cin, admin.at(thisAdmin).firstName);
            cout << "Enter last name: ";
            getline(cin, admin.at(thisAdmin).lastName);
            cout << "Enter ph number: ";
            getline(cin, admin.at(thisAdmin).phoneNumber);
            updateAdminFile(admin);
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "e") {
            keepRunning = false;
        }
        else {
            cout << "Invalid Input (Y/N)" << endl;
        }
    }
}

void  displayDriverProfile(Driver user) {
    pageBreak();
    vector<Driver> drivers = readDriversFile();
    // find matching customer in vector
    int thisDriver = 0;
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers.at(i).email == user.email)
            thisDriver = i;
    }

    cout << "User profile" << endl;
    cout << "Email: " << drivers.at(thisDriver).email << endl;
    cout << "Name: " << drivers.at(thisDriver).firstName << " " << drivers.at(thisDriver).lastName << endl;
    cout << "Ph number: " << drivers.at(thisDriver).phoneNumber << endl;
    cout << "Taxi Rego: " << drivers.at(thisDriver).registration << endl;
    cout << endl;
    cout << "*note: email cannot be changed. If you need to change email you must make a new account" << endl;
    cout << "\nWould you like to update this information? (Y/N): ";

    bool keepRunning = true;
    while (keepRunning) {

        string userInput;
        getline(cin, userInput);
        if (userInput == "Y" or userInput == "y") {

            // promt user to update customer details
            //cout << "cutomer at i: " << thisCustomer << ": " << customers.at(thisCustomer).email << endl;
            cout << "Update Information for " << drivers.at(thisDriver).firstName << " " << drivers.at(thisDriver).lastName << endl << endl;
            cout << "Enter first name: ";
            getline(cin, drivers.at(thisDriver).firstName);
            cout << "Enter last name: ";
            getline(cin, drivers.at(thisDriver).lastName);
            cout << "Enter ph number: ";
            getline(cin, drivers.at(thisDriver).phoneNumber);
            updateDriversFile(drivers);
            cout << "Information saved" << endl;
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "e") {
            keepRunning = false;
        }
        else {
            cout << "Invalid Input (Y/N)" << endl;
        }
    }
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

vector<lostPropertyClaim> readLostPropertyClaimsFile() {
    //this function will read lostPropertyClaims.csv and return vector
    vector<lostPropertyClaim> lostPropertyClaimsList;
    vector<Customer> customers = readCustomerFile();

    fstream lostPropertyClaimsFile;
    lostPropertyClaim tempLostPropertyClaim;
    lostPropertyClaimsFile.open("lostPropertyClaims.csv", ios::in);
    if (lostPropertyClaimsFile.is_open()) {
        string line;
        string cell;
        Customer tempCustomer;
        while (getline(lostPropertyClaimsFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempLostPropertyClaim.description = cell;

            getline(linestream, cell, ',');
            for (int i = 0; i < customers.size(); i++) {
                if (cell == customers.at(i).email) {
                    tempCustomer = customers.at(i);
                }
            }

            tempLostPropertyClaim.reportedBy = tempCustomer;

            lostPropertyClaimsList.push_back(tempLostPropertyClaim);
        }
        lostPropertyClaimsFile.close();
    }
    return lostPropertyClaimsList;
}

void displayAllLostPropertyClaims(vector<lostPropertyClaim> claims) {
    pageBreak();
    cout << "Pending lost property claims" << endl;
    cout << "****************************" << endl;
    for (auto c : claims) {
        cout << c.description << endl;
        cout << "Claim by " << c.reportedBy.firstName << " " << c.reportedBy.lastName << endl;
        cout << c.reportedBy.email << "\t" << c.reportedBy.phoneNumber << endl << endl;
    }
    //propmt user to delete
    bool keepRunning = true;
    string userInput;
    while (keepRunning) {
        cout << "\nWould you like to remove an item? (Y/N): ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n") {
            return;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
    cout << "\nChoose claim to aprove" << endl;
    for (int i = 0; i < claims.size(); i++) {
        cout << i + 1 << ". " << claims.at(i).reportedBy.email << ", " << claims.at(i).description << endl;
    }
    keepRunning = true;
    int numUserInput;
    while (keepRunning) {
        cout << "Enter by list number: ";
        getline(cin, userInput);
        // convert user input to number

        if (isdigit(userInput[0])) {

            istringstream ssUserInput(userInput);
            ssUserInput >> numUserInput;
            numUserInput--;

            if (numUserInput >= 0 && numUserInput < claims.size()) {
                keepRunning = false;
            }

        }
    }
    // use number to delete an item from list
    claims.erase(claims.begin() + numUserInput);

    // displayEnquiries(enquiries);

    updateLostPropertyClaimsFile(claims);

    cout << "Claim aproved" << endl;

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
    cout << "Lost property" << endl;
    cout << "*************\n" << endl;
    vector<lostProperty> lostPropertyList = readLostPropertyFile();

    cout << "lost property" << endl;
    for (auto l : lostPropertyList) {
        cout << l.description << ", submitted by " << l.submittedBy << endl;
    }
    //prompt to remove
    bool keepRunning = true;
    string userInput;
    while (keepRunning) {
        cout << "\nWould you like to remove an item? (Y/N): ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n") {
            return;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
    cout << "\nChoose item to remove" << endl;
    for (int i = 0; i < lostPropertyList.size(); i++) {
        cout << i + 1 << ". " << lostPropertyList.at(i).description << endl;
    }
    keepRunning = true;
    int numUserInput;
    while (keepRunning) {
        cout << "Enter by list number: ";
        getline(cin, userInput);
        // convert user input to number

        if (isdigit(userInput[0])) {

            istringstream ssUserInput(userInput);
            ssUserInput >> numUserInput;
            numUserInput--;

            if (numUserInput >= 0 && numUserInput < lostPropertyList.size()) {
                keepRunning = false;
            }

        }
    }
    // use number to delete an item from list
    lostPropertyList.erase(lostPropertyList.begin() + numUserInput);

    // displayEnquiries(enquiries);

    updateLostPropertyFile(lostPropertyList);

    cout << "Lost item has been removed" << endl;

}

void claimLostProperty(Customer user) {
    pageBreak();

    vector<lostPropertyClaim> lostPropertyClaims = readLostPropertyClaimsFile();
    lostPropertyClaim newLostPropertyClaim;

    cout << "Lost property claims" << endl;
    cout << "********************" << endl << endl;
    cout << "Enter a description of the item you lost: ";
    getline(cin, newLostPropertyClaim.description);
    newLostPropertyClaim.reportedBy = user;

    lostPropertyClaims.push_back(newLostPropertyClaim);

    updateLostPropertyClaimsFile(lostPropertyClaims);
    cout << "Thankyou. We will contact you if we find anything :)" << endl;
}

void updateLostPropertyClaimsFile(vector<lostPropertyClaim> claims) {
    //this function updates the lostProperty.csv with the latest information
    fstream lostPropertyClaimsFile;
    lostPropertyClaimsFile.open("lostPropertyClaims.csv", ios::out);
    if (lostPropertyClaimsFile.is_open()) {
        for (int i = 0; i < claims.size(); i++) {
            lostPropertyClaimsFile << claims[i].description << "," << claims[i].reportedBy.email << endl;
        }
        lostPropertyClaimsFile.close();
    }
}

void makeBooking(Customer user) {
    pageBreak();
    // ==================================================================================================================================================
    // this function requires Customer user as parameter
    // will promt user to choose a date, then promt user to enter booking details
    // the booking details will be written into bookings.csv and to the schedule/ directory in a time schedule named by the date ( schedule/ DD-MM-YY.csv )
    // ==================================================================================================================================================

    // promt user to input date, then validate date format ( DD/MM/YY )
    string userInputDate = "12345678";
    int digitCount = 0;
    bool isDateValid = true;
    string sMonth;
    int month = 0;
    string sDay;
    int day = 0;
    string sYear;
    int year = 0;
    vector<int> daysInEachMonth = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int timeFrame = 90;

    do {
        isDateValid = true;
        digitCount = 0;
        // promt user
        cout << "Type a date to see availability (DD/MM/YY): ";
        getline(cin, userInputDate);
        if (userInputDate == "E" || userInputDate == "e") return;

        // validate length
        if (userInputDate.length() == 8) {

            // check for 2 instances of '/'
            if (userInputDate[2] != '/' || userInputDate[5] != '/') {
                isDateValid = false;
                cout << "Incorrect '/'" << endl;

            }

            // ensure digit count is 6
            // loop through userInputDate to ensure 6 integers were used
            for (int i = 0; i < userInputDate.length(); i++) {
                if (isdigit(userInputDate[i])) {
                    digitCount++;
                }
            }
            if (digitCount != 6) {
                isDateValid = false;
            }

            // validate date exists, for exmaple, the 31st of February is invalid
            if (isdigit(userInputDate[0]) && isdigit(userInputDate[1]) && isdigit(userInputDate[3]) && isdigit(userInputDate[4]) && isdigit(userInputDate[6]) && isdigit(userInputDate[7])) // to ensure program does not crash
            {
                //validate date hasn't already passed
                if (hasDatePassed(userInputDate)) {
                    isDateValid = false;
                    cout << "The date you have entered has already passed" << endl;
                }
                //validate date isn't too far in the future

                if (isDateWithinTimeFrame(userInputDate, timeFrame) == false && hasDatePassed(userInputDate) == false) {
                    isDateValid = false;
                    cout << "The date you entered is too far in the future, enter a date less than " << timeFrame << " days away" << endl;
                }

                string sMonth = userInputDate.substr(3, 2);
                stringstream ssMonth(sMonth);
                ssMonth >> month;
                string sDay = userInputDate.substr(0, 2);
                stringstream ssDay(sDay);
                ssDay >> day;
            }
            // month cannot be over 12
            // cout << "month: " << month << endl;
            if (month < 1 || month > 12) {
                isDateValid = false;
                cout << "Invalid month" << endl;
            }
            // Day cannot be over 28,30,31 depending on month                                                //======= test this more ==========
            if (month < 13) {
                //cout << "day: " << day << endl;
                if (day < 1 || day > daysInEachMonth.at(month - 1)) {
                    isDateValid = false;
                    cout << "month " << month << ", does not contain " << day << " days" << endl;
                }
            }
        }
        else {
            isDateValid = false;
            cout << "Date format not valid" << endl;
        }

    } while (isDateValid == false);

    
    string date = userInputDate;

    // converting date format ( DD/MM/YY ) to a schedule filename ( schedule/ DD-MM-YY.csv )
    replace(date.begin(), date.end(), '/', '-');
    vector <vector <string>> availableTimes = {
        {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    };
    string directory = "schedule/";
    string extension = ".csv";
    string filename = directory + date + extension;             //look for availibilityfile, if there is no file, then make one before opening

    // check for a schedule with this filename (schedule / DD - MM - YY.csv) 
    // if no such schedule is found for this date then it will have to be created
    checkForSchedule(filename);

    // find schedule for this date and input to vector<string> availableTimes
    availableTimes = readSchedule(filename);

    // update availableTimes vector with any new drivers have been added
    availableTimes = addNewDriversToSchedule(availableTimes);

    // display available times for chosen date
    cout << "\nAvailable times: " << endl << endl;
    for (int i = 0; i < availableTimes.size(); i++) {
        int driversAvailable = 0;
        for (int j = 0; j < availableTimes[i].size(); j++) {
            if (j == 0) cout << availableTimes[i][0] << ": ";

            if (availableTimes[i][j] == "available") {
                driversAvailable++;
            }
        }
        if (driversAvailable > 0) cout << "available " << endl;
        else cout << "Booking full " << endl;
    }

    // promt user to choose time

    string userInputTime;
    bool isUserInputValid = false;
    string availableDriverEmail;
    string* availableSlot = nullptr;

    cout << "note: type 'e' at any stage to exit and cancel booking" << endl;

    cout << "\nEnter time to make a booking (hour.mins):\nmust enter half hour block: ";
    while (isUserInputValid == false) // loop checks if user chose a vailid time that is also not booked
    {
        getline(cin, userInputTime);
        if (userInputTime == "e") return;

        cout << userInputTime << " ";

        // counting how many drivers are available for chosen time
        int driversAvailable = 0;
        for (int i = 0; i < availableTimes.size(); i++) {
            if (availableTimes[i][0] == userInputTime) {
                //cout << "found " << endl;
                for (int j = 0; j < availableTimes.at(i).size(); j++) {
                    if (availableTimes[i][j] == "available") {
                        availableDriverEmail = availableTimes[i][j - 1];
                        availableSlot = &availableTimes[i][j];
                        // available 
                        driversAvailable++;
                    }
                }
            }
        }

        // if amount of drivers available is greater than 0, the user may make the booking
        if (driversAvailable > 0) {
            cout << "\nslot free to make booking" << endl;
            isUserInputValid = true;
        }
        else cout << "either invalid input or slot is not free, please choose another time: ";
    }

    // input bookings.csv to vector<Booking> bookings 
    // promt user to enter details for their booking
    
    vector<Booking> bookings = readBookingsFile();
    Booking newBooking;
    string userInput;

    cout << "\nMake booking for " << user.firstName << " " << user.lastName << endl;
    cout << "date: " << date << "\t" << userInputTime << endl;
    newBooking.bookingRef = "ref";
    newBooking.bookingRef += to_string(bookings.size() + 1);
    newBooking.customer = user;

    newBooking.driver = getDriverByEmail(availableDriverEmail);

    newBooking.date = date;
    newBooking.time = userInputTime;
    cout << "How long will your trip be? (in minutes, trip duration will be rounded to the next half hour): ";

    // stop people from booking too long // maximum trip duration, 180mins
    int maxTripDuration = 180;
    int userInputDuration = 0, roundedUp = 0;
    while (userInputDuration > maxTripDuration || userInputDuration == 0) {
        getline(cin, userInput);
        if (userInput == "e") return;

        stringstream ss(userInput);

        ss >> userInputDuration;

        if (userInputDuration > maxTripDuration) {
            cout << "Trip duration cannot be more than " << maxTripDuration << " minutes" << endl;
            cout << "How long will your trip be?" << endl;
        }
        else if (userInputDuration == 0) {
            cout << "Trip duration cannot be 0" << endl;
            cout << "How long will your trip be?" << endl;

        }

    }
    // round new booking duration up to nearest 30mins
    if (userInputDuration % 30 == 0) {
        roundedUp = userInputDuration;
    }
    else {
        roundedUp = ((userInputDuration / 30) * 30) + 30;
    }


    newBooking.duration = roundedUp;

    cout << "Enter pickup location: ";
    getline(cin, newBooking.startLocation);
    if (newBooking.startLocation == "e") return;

    cout << "Enter dropoff location: ";
    getline(cin, newBooking.endLocation);
    if (newBooking.endLocation == "e") return;

    newBooking.cost = (newBooking.duration * 2.0);

    // display new booking
    cout << "\n--new Booking details--" << endl << endl;
    cout << "Booking reference: " << newBooking.bookingRef << "\tDate: " << newBooking.date << endl;
    cout << "Email: " << newBooking.customer.email << "\tTime: " << newBooking.time << "\tTrip duration: " << newBooking.duration << " minutes" << endl;
    cout << "Pick up location: " << newBooking.startLocation << "\tDrop off location: " << newBooking.endLocation << "\tCost: $" << newBooking.cost << endl;
    cout << "Driver: " << newBooking.driver.firstName << endl;

    // promt user to confirm new booking ( Y/N )
    bool isUserSure = false;
    while (isUserSure == false) {

        cout << "\nAre you sure you want to make this booking? (Y/N) ";
        getline(cin, userInput);
        //toupper(userInput);

        if (userInput == "Y") {
            isUserSure = true;
        }
        else if (userInput == "N" || userInput == "e") {
            cout << "cancelling booking" << endl;
            return;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }

    // push newBooking to bookings
    bookings.push_back(newBooking);
    // upadate bookings.csv to latest information
    updateBookingsFile(bookings);

    // Update schedule ( vector<vector<string>> availableTimes ) with new booking references
    // Check if trip duration will extend from one day into the next, 
        // if so this will call the function booking overflow to ensure two schedule files are updated, one for the day chosen by user and one for the following day
        // for example if user books a 60 minute ride for 31/01/22 at 13.30, their booking will extend into the next day. this code will update two days 

    int halfHourBlocks = newBooking.duration / 30; //need to do rounding somehow
    int halfHourBlocksLeftThisDay = 1;
    int halfHourBlocksOverflow = 0;
    float convertedTime;
    istringstream ssTime(newBooking.time);
    ssTime >> convertedTime;
    halfHourBlocksLeftThisDay = (24.0 - convertedTime) * 2;
    halfHourBlocksOverflow = halfHourBlocks - halfHourBlocksLeftThisDay;

    if (halfHourBlocksOverflow > 0) {
        bookingOverflow(newBooking.driver.email, date, halfHourBlocksOverflow, newBooking.bookingRef);
    }

    // somehow need to make this code easier to look at === come back to this later ===
    // updating availableTimes with new references
    for (int i = 0; i < availableTimes.size(); i++) {
        if (availableTimes.at(i).at(0) == userInputTime) { //look for time chosen by user
            for (int j = 0; j < availableTimes.at(i).size(); j++) {
                if (availableTimes.at(i).at(j) == newBooking.driver.email) { //finding driver by email for given time
                    for (int k = 0; k < halfHourBlocks && k < halfHourBlocksLeftThisDay; k++) {
                        availableTimes.at(i + k).at(j + 1) = newBooking.bookingRef;           
                    }
                }
            }
        }
    }
    // output to schedule/ ( DD-MM-YY ).csv with update availableTimes
    updateSchedule(availableTimes, filename);
    cout << "Booking successful" << endl;
}

vector<Booking> readBookingsFile() {
    //this function will read bookings.csv and return vector
    vector<Booking> bookings;
    fstream bookingsFile;
    Booking tempBooking;
    bookingsFile.open("bookings.csv", ios::in);
    if (bookingsFile.is_open()) {
        string line;
        string cell;
        while (getline(bookingsFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempBooking.bookingRef = cell;

            getline(linestream, cell, ',');
            string tempCustomerEmail = cell;
            tempBooking.customer = getCustomerByEmail(tempCustomerEmail);


            getline(linestream, cell, ',');
            string tempDriverEmail = cell;
            tempBooking.driver = getDriverByEmail(tempDriverEmail);

            getline(linestream, cell, ',');
            tempBooking.date = cell;

            getline(linestream, cell, ',');
            tempBooking.time = cell;

            getline(linestream, cell, ',');
            stringstream ssDuration(cell);
            ssDuration >> tempBooking.duration;


            getline(linestream, cell, ',');
            tempBooking.startLocation = cell;

            getline(linestream, cell, ',');
            tempBooking.endLocation = cell;

            getline(linestream, cell, ',');
            stringstream ssCost(cell);
            ssCost >> tempBooking.cost;


            bookings.push_back(tempBooking);
        }
        bookingsFile.close();
    }
    return bookings;
}

void displayAllBookings(vector<Booking> bookings) {
    // displays al Bookings from a vector
    //cout << "\nDisplay all bookings" << endl;
    for (auto b : bookings) {
        cout << b.bookingRef << ", " << b.customer.firstName << " " << b.customer.lastName << ", Driver: " << b.driver.firstName << endl;
        cout << b.date << ", " << b.time << ", " << b.duration << ", " << b.startLocation << ", " << b.endLocation << ", $" << b.cost << endl << endl; 
    }
}

Driver getDriverByEmail(string email) {
    Driver chosenDriver;
    vector<Driver> drivers = readDriversFile();
    //for loop, search for email match
    for (int i = 0; i < drivers.size(); i++) {
        if (drivers[i].email == email)
            chosenDriver = drivers[i];
    }

    return chosenDriver;
}

Customer getCustomerByEmail(string email) {
    Customer customer;
    vector<Customer> customers = readCustomerFile();
    //for loop, search for email match
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].email == email)
            customer = customers[i];
    }

    return customer;
}

void updateBookingsFile(vector<Booking> bookings) {
    fstream bookingsFile;
    bookingsFile.open("bookings.csv", ios::out);
    if (bookingsFile.is_open()) {
        for (int i = 0; i < bookings.size(); i++) {
            bookingsFile << bookings[i].bookingRef << "," << bookings[i].customer.email << "," << bookings[i].driver.email << "," << bookings[i].date << "," << bookings[i].time <<
                "," << bookings[i].duration << "," << bookings[i].startLocation << "," << bookings[i].endLocation << "," << bookings[i].cost << endl;
        }
        bookingsFile.close();
    }
}

void updateSchedule(vector<vector<string>> availableTimes, string filename) {
    fstream scheduleFile;
    scheduleFile.open(filename, ios::out);
    if (scheduleFile.is_open()) {
        for (int i = 0; i < availableTimes.size(); i++) {
            for (int j = 0; j < availableTimes[i].size(); j++) {
                scheduleFile << availableTimes[i][j] << ",";

            }
            scheduleFile << endl;
        }
        scheduleFile.close();
    }
}

void createNewSchedule(string filename) {
    // function creates a new driver schedule as a vector of vector<string> with the name, filename that was passed in
    // this will then be output to a new driver schedule .csv file
    // driver schedule is a csv file containing each drivers availabilty for each half hour block of the day
    vector<vector<string>> newSchedule = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, };
    vector<Driver> drivers = readDriversFile();
    vector<string> row;

    int hour = 0;
    string h = "";
    string time = "";

    for (int i = 0; i < 48; i++) { //loop through all rows
        // create half hour blocks as "hour.00" or "hour.30"
        if (i % 2 == 0) {
            h = to_string(hour);
            string mins = "00";
            time = h + "." + mins;
        }
        else {
            h = to_string(hour);
            string mins = "30";
            time = h + "." + mins;
            hour++;
        }
        // popuate 1st of each for with time
        newSchedule.at(i).push_back(time);

        //loop through list of drivers for given time, input the driver email followed by the drivers availability
        string availability = "temp";
        for (int d = 0; d < drivers.size(); d++) {
            //availability = to_string(drivers.at(d).driverFinish); //code possibly rubbish
            availability = getDriverAvailabilityByTime(drivers.at(d), time); // get driver availability for a given time
            newSchedule.at(i).push_back(drivers.at(d).email); // pushing drivers email to vector
            newSchedule.at(i).push_back(availability);  // pushing drivers availabilty to vector
        }
    }

    updateSchedule(newSchedule, filename); 

}

string getDriverAvailabilityByTime(Driver driver, string time) {
    string availability = "available";
    vector<float> availableTimes = { 0.0,0.3,1.0,1.3,2.0,2.3,3.0,3.3,4.0,4.3,5.0,5.3,6.0,6.3,7.0,7.3,8.0,8.3,9.0,9.3,
        10.0,10.3,11.0,11.3,12.0,12.3,13.0,13.3,14.0,14.3,15.0,15.3,16.0,16.3,17.0,17.3,18.0,18.3,19.0,19.3,20.0,20.3,21.0,21.3,22.0,22.3,23.0,23.3,0.0,0.3,1.0,1.3,2.0,2.3,3.0,3.3,4.0,4.3,5.0,5.3,6.0,6.3,7.0,7.3,8.0,8.3,9.0,9.3,
        10.0,10.3,11.0,11.3,12.0,12.3,13.0,13.3,14.0,14.3,15.0,15.3,16.0,16.3,17.0,17.3,18.0,18.3,19.0,19.3,20.0,20.3,21.0,21.3,22.0,22.3,23.0,23.3 };


        //find driver start, cut every thing before it
    int removeEverythingBefore = 0;
    for (int i = 0; i < availableTimes.size(); i++) {
        if (availableTimes.at(i) == driver.driverStart) {
            removeEverythingBefore = i;
            break;
        }
    }
    availableTimes.erase(availableTimes.begin(), availableTimes.begin() + removeEverythingBefore);
    int removeEverythingAfter = 0;
    for (int i = 0; i < availableTimes.size(); i++) {
        if (availableTimes.at(i) == driver.driverFinish) {
            removeEverythingAfter = i;
            break;
        }
    }
    availableTimes.erase(availableTimes.begin() + removeEverythingAfter, availableTimes.end());

// covert string time to float
    float convertedTime;
    stringstream ssTime(time);
    ssTime >> convertedTime;

    //check if time is in vector
    for (int i = 0; i < availableTimes.size(); i++) {
        if (availableTimes.at(i) == convertedTime) {
            availability = "available";
            break;
        }
        else {
            availability = "unstaffed";
        }
    }

    return availability;
}

void bookingOverflow(string driverEmail, string date, float halfHourBlocksOverflow, string bookingRef) {
    //checkforfile, ?makefile  // readSchedule //replace availability for a driver for time 0.00 and following halfHourBlocks depending on halfHourBlocksOverflow
    string followingDate = "";
    followingDate = incrementDate(date);
    
    //check for file containing following date 
    string directory = "schedule/";
    string extension = ".csv";


    //string filename = "schedule/14-06-22.csv";
    string filename = directory + followingDate + extension;
    checkForSchedule(filename);
    //change schedule
    vector<vector<string>> schedule = readSchedule(filename);

    //============================================================= updateNewDrivers
    schedule = addNewDriversToSchedule(schedule);

    //from time 0
    for (int i = 0; i < schedule.size() && i < halfHourBlocksOverflow; i++) {
        //loop through to find driver email // update following cell to ref
        for (int j = 0; j < schedule.at(i).size(); j++) {
            if (schedule.at(i).at(j) == driverEmail) {
                schedule.at(i).at(j + 1) = bookingRef;          
            }
        }

    }

    updateSchedule(schedule, filename);

}

string incrementDate(string date) {
    // pass in a date and this function will return the following date
    string newDate = "newDate";

    string sDay = date.substr(0, 2);
    stringstream ssDay(sDay);
    int day;
    ssDay >> day;

    string sMonth = date.substr(3, 2);
    stringstream ssMonth(sMonth);
    int month;
    ssMonth >> month;

    string sYear = date.substr(6, 2);
    stringstream ssYear(sYear);
    int year;
    ssYear >> year;

    vector<int> daysInEachMonth = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    day++;
    if (day >= daysInEachMonth.at(month - 1)) {
        day = day - daysInEachMonth.at(month - 1);
        month++;
        if (month == 13) {
            month = 1;
            year++;
        }
    }

    sDay = to_string(day);
    if (sDay.length() == 1) {
        sDay = "0" + sDay;
    }

    sMonth = to_string(month);
    if (sMonth.length() == 1) {
        sMonth = "0" + sMonth;
    }
    sYear = to_string(year);
    if (sYear.length() == 1) {
        sYear = "0" + sYear;
    }

    newDate = sDay + "-" + sMonth + "-" + sYear;
    
    return newDate; //must return (DD-MM-YY)
}

void checkForSchedule(string filename) {
    fstream checkForScheduleFile;
    string checkLine;
    checkForScheduleFile.open(filename, ios::in);
    if (checkForScheduleFile.is_open()) {

        getline(checkForScheduleFile, checkLine);

        checkForScheduleFile.close();
    }

    if (checkLine.length() > 0) {
        //fileExists
    }
    else {
        //must create file
        createNewSchedule(filename);
    }
}

vector<vector<string>> readSchedule(string filename) {
    vector<vector<string>> schedule = {
        {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    };
    vector<Driver> drivers = readDriversFile();

    fstream availabiltyFile;
    availabiltyFile.open(filename, ios::in);
    if (availabiltyFile.is_open()) {
        string line;
        string cell;
        int i = 0;
        int rowSize = 11; //this wil be (amount of drivers * 2) + 1
        rowSize = (drivers.size() * 2) + 1;

        while (getline(availabiltyFile, line) && i < schedule.size()) {
            istringstream linestream(line);

            for (int j = 0; j < rowSize; j++) {
                getline(linestream, cell, ',');
                schedule.at(i).push_back(cell);
            }
            i++;
        }

        availabiltyFile.close();
    }

    return schedule;
}

vector<vector<string>> addNewDriversToSchedule(vector<vector<string>> schedule) {
    vector<Driver> drivers = readDriversFile();

    int cellsToBeUpdated = 0; // amount of cells at end of each row that need updating
    // find 1st empty space in schedule.at(0) row
    for (int i = 0; i < schedule.at(0).size(); i++) {
        if (schedule.at(0).at(i) == "") {
            cellsToBeUpdated++;
            schedule.at(0).at(i) = "temp";
        }
    }

    //loop through rows
    for (int i = 0; i < schedule.size(); i++) {
        //loop from end of each row
        int k = 0;
        for (int j = 0; j < cellsToBeUpdated; j++) {
            if (j % 2 == 0) {
                schedule.at(i).at(schedule.at(i).size() - 1 - j) = getDriverAvailabilityByTime(drivers.at(drivers.size() - 1 - k), schedule.at(i).at(0));

            }
            else {
                schedule.at(i).at(schedule.at(i).size() - 1 - j) = drivers.at(drivers.size() - 1 - k).email;
                k++;
            }

        }
    }



    return schedule;
}

bool hasDatePassed(string date) {
    //cout << "========================================\n\thasDatePassed function called...\n" << endl;
    bool dateHasPassed = false;
    // date =  "DD/MM/YY"
    int day = 0;
    int month = 0;
    int year = 0;

    string sMonth = date.substr(3, 2);
    stringstream ssMonth(sMonth);
    ssMonth >> month;
    string sDay = date.substr(0, 2);
    stringstream ssDay(sDay);
    ssDay >> day;
    string sYear = date.substr(6, 2);
    stringstream ssYear(sYear);
    ssYear >> year;

    //cout << "date entered: " << day << "-" << month << "-" << year << endl;

    // get todays date
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    // convert todays date
    //cout << "Todays date: " << endl;
    ////cout << "now: " << now << endl;
    //cout << "day: " << newtime.tm_mday << endl;
    //cout << "Month: " << 1 + newtime.tm_mon << endl;
    //cout << "year: " << ( -100) + newtime.tm_year << endl;

    // compare year 
    if (year < ((-100) + newtime.tm_year)) {
        dateHasPassed = true;
    }

    // compare month // only if we are comparing the same year
    if (month < (1 + newtime.tm_mon) && year == ((-100) + newtime.tm_year)) {
        dateHasPassed = true;
    }

    // compare day // only if we are comparing the same year and the same month
    if (day < newtime.tm_mday && month == (1 + newtime.tm_mon) && year == ((-100) + newtime.tm_year)) {
        dateHasPassed = true;
    }

    //cout << "\n\thasDatePassed function ended...\n========================================" << endl;
    return dateHasPassed;
}

bool isDateWithinTimeFrame(string date, int timeFrame) {
    bool withinTimeFrame = true;
    // date entered =  "DD/MM/YY"
    // convert date entered to integers
    int day = 0;
    int month = 0;
    int year = 0;

    string sDay = date.substr(0, 2);
    stringstream ssDay(sDay);
    ssDay >> day;
    string sYear = date.substr(6, 2);
    string sMonth = date.substr(3, 2);
    stringstream ssMonth(sMonth);
    ssMonth >> month;
    stringstream ssYear(sYear);
    ssYear >> year;

    // get todays date

    
    
    //cout << "Today: " << todaysDate << endl;

    // use incrementDate function in a loop?
    string cutOffDate = getTodaysDateAsString();
    for (int i = 0; i < timeFrame; i++) {
        cutOffDate = incrementDate(cutOffDate);
    }
    //cout << "cut off date = " << cutOffDate << endl;

    // ensure that date entered into function is less than the cut off date
    int cutOffDay = 0;
    int cutOffMonth = 0;
    int cutOffYear = 0;

    string sCutOffDay = cutOffDate.substr(0, 2);
    stringstream ssCutOffDay(sCutOffDay);
    ssCutOffDay >> cutOffDay;

    string sCutOffMonth = cutOffDate.substr(3, 2);
    stringstream ssCutOffMonth(sCutOffMonth);
    ssCutOffMonth >> cutOffMonth;

    string sCutOffYear = cutOffDate.substr(6, 2);
    stringstream ssCutOffYear(sCutOffYear);
    ssCutOffYear >> cutOffYear;

    // compare year // if year entered is more than cutoff year then withinTimeFrame = false
    if (year > cutOffYear) {
        withinTimeFrame = false;
        //cout << "cut off year exceeded. cutOffYear: " << cutOffYear << endl;
    }

    // compare month
    if (month > cutOffMonth && year == cutOffYear) {
        withinTimeFrame = false;
        //cout << "cut off month exceeded. cutOffMonth: " << cutOffMonth << endl;
    }

    // compare day
    if (day > cutOffDay && year == cutOffYear && month == cutOffMonth) {
        withinTimeFrame = false;
        //cout << "cut off day exceeded. cutOffDay: " << cutOffDay << endl;

    }

    return withinTimeFrame;
}

void displayThisCustomersTransactions(Customer user) {
    vector<Booking> bookings = readBookingsFile();
    vector<Booking> userBookingsPast;
    vector<Booking> userBookingsFuture;

    for (int i = 0; i < bookings.size(); i++) {
        if (bookings.at(i).customer.email == user.email) {
            // if past or else future
            if (hasDatePassed(bookings.at(i).date) == false && bookings.at(i).startLocation != "CANCELLED") {
                userBookingsFuture.push_back(bookings.at(i));
            }
            else {
                userBookingsPast.push_back(bookings.at(i));
            }
        }
    }

    //display bookings only with this person's email
    cout << "\nYour Transactions" << endl;
    cout << "**********" << endl;
    cout << "\n";

    // display past rides

    // display future rides
    if (userBookingsPast.size() == 0) {
        cout << "No past bookings to show" << endl;
    }
    else {
        cout << "Past transactions\n" << endl;
        displayAllBookings(userBookingsPast);

    }
    if (userBookingsFuture.size() == 0) {
        cout << "No future bookings to show" << endl;
        cout << "press enter to continue...";
        string contin;
        getline(cin, contin);
        return;
    }
    else {
        cout << "\nFuture transactions\n" << endl;
        displayAllBookings(userBookingsFuture);
    }

    string userInput;
    bool keepRunning = true;
    while (keepRunning) {
        cout << "Would you like to delete an upcoming booking? (Y/N): ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "E" || userInput == "e") {
            return;
        }
        else {
            cout << "Invalid input (Y/N):";
        }
    }
    // display future bookings again with a list number

    for (int i = 0; i < userBookingsFuture.size(); i++) {
        cout << i + 1 << ". Reference: " << userBookingsFuture.at(i).bookingRef << "  Date: " << userBookingsFuture.at(i).date << "  Time: " << userBookingsFuture.at(i).time;
        cout << "  Pickup: " << userBookingsFuture.at(i).startLocation << "  Dropoff: " << userBookingsFuture.at(i).endLocation << endl;
    }

    int numUserInput = 0;
    keepRunning = true;
    while (keepRunning) {
        // promt user to choose a list number
        cout << "Enter which booking you would like to cancel (enter by list number): ";
        getline(cin, userInput);

        // 
        if(isdigit(userInput[0])) {
            istringstream ssUserInput(userInput);
            ssUserInput >> numUserInput;
            if (numUserInput <= userBookingsFuture.size() && numUserInput > 0) {
                keepRunning = false;
            }
        }
        else {
            cout << "Invalid input: " << endl;
        }
    }

    // find ref to be cancelled
    keepRunning = true;
    while(keepRunning) {
        cout << "Are you shure you want to cancel booking reference (Y/N): " << userBookingsFuture.at(numUserInput - 1).bookingRef << "? ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "E" || userInput == "e") {
            return;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    // dont delete booking, keep ref number and replace all information with "CANCELLED"
    // find ref number in bookings
    string cancelDate;
    for (int i = 0; i < bookings.size(); i++) {
        if (bookings.at(i).bookingRef == userBookingsFuture.at(numUserInput - 1).bookingRef) {
            bookings.at(i).cost = 0.0;
            bookings.at(i).duration = 0;
            bookings.at(i).startLocation = "CANCELLED";
            bookings.at(i).endLocation = "CANCELLED";
            cancelDate = bookings.at(i).date;
        }
    }

    // updateBookings
    updateBookingsFile(bookings);

    // upDateSchedule to driver being available

    string directory = "schedule/";
    string extension = ".csv";
    string filename = directory + cancelDate + extension;

    vector<vector<string>> schedule = readSchedule(filename);

    // loop through to replace all ref numbers with "available"
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule.at(i).size(); j++) {
            if (schedule.at(i).at(j) == userBookingsFuture.at(numUserInput - 1).bookingRef) {
                schedule.at(i).at(j) = "available";
            }
        }
    }
    updateSchedule(schedule, filename);
    cout << "Booking cancelled" << endl;

}

void displayAllTransactions() {
    vector<Booking> bookings = readBookingsFile();
    vector<Booking> userBookingsPast;
    vector<Booking> userBookingsFuture;

    for (int i = 0; i < bookings.size(); i++) {
            // if past or else future
            if (hasDatePassed(bookings.at(i).date) == false && bookings.at(i).startLocation != "CANCELLED") {
                userBookingsFuture.push_back(bookings.at(i));
            }
            else {
                userBookingsPast.push_back(bookings.at(i));
            }
        
    }

    //display bookings only with this person's email
    cout << "\nYour Transactions" << endl;
    cout << "**********" << endl;
    cout << "\n";

    // display past rides

    // display future rides
    if (userBookingsPast.size() == 0) {
        cout << "No past bookings to show" << endl;
    }
    else {
        cout << "Past transactions\n" << endl;
        displayAllBookings(userBookingsPast);

    }
    if (userBookingsFuture.size() == 0) {
        cout << "No future bookings to show" << endl;
        cout << "press enter to continue...";
        string contin;
        getline(cin, contin);
        return;
    }
    else {
        cout << "\nFuture transactions\n" << endl;
        displayAllBookings(userBookingsFuture);
    }

    string userInput;
    bool keepRunning = true;
    while (keepRunning) {
        cout << "Would you like to delete an upcoming booking? (Y/N): ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "E" || userInput == "e") {
            return;
        }
        else {
            cout << "Invalid input (Y/N):";
        }
    }
    // display future bookings again with a list number

    for (int i = 0; i < userBookingsFuture.size(); i++) {
        cout << i + 1 << ". Reference: " << userBookingsFuture.at(i).bookingRef << "  Date: " << userBookingsFuture.at(i).date << "  Time: " << userBookingsFuture.at(i).time;
        cout << "  Pickup: " << userBookingsFuture.at(i).startLocation << "  Dropoff: " << userBookingsFuture.at(i).endLocation << endl;
    }

    int numUserInput = 0;
    keepRunning = true;
    while (keepRunning) {
        // promt user to choose a list number
        cout << "Enter which booking you would like to cancel (enter by list number): ";
        getline(cin, userInput);

        // 
        if (isdigit(userInput[0])) {
            istringstream ssUserInput(userInput);
            ssUserInput >> numUserInput;
            if (numUserInput <= userBookingsFuture.size() && numUserInput > 0) {
                keepRunning = false;
            }
        }
        else {
            cout << "Invalid input: " << endl;
        }
    }

    // find ref to be cancelled
    keepRunning = true;
    while (keepRunning) {
        cout << "Are you shure you want to cancel booking reference (Y/N): " << userBookingsFuture.at(numUserInput - 1).bookingRef << "? ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n" || userInput == "E" || userInput == "e") {
            return;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }
    // dont delete booking, keep ref number and replace all information with "CANCELLED"
    // find ref number in bookings
    string cancelDate;
    for (int i = 0; i < bookings.size(); i++) {
        if (bookings.at(i).bookingRef == userBookingsFuture.at(numUserInput - 1).bookingRef) {
            bookings.at(i).cost = 0.0;
            bookings.at(i).duration = 0;
            bookings.at(i).startLocation = "CANCELLED";
            bookings.at(i).endLocation = "CANCELLED";
            cancelDate = bookings.at(i).date;
        }
    }

    // updateBookings
    updateBookingsFile(bookings);

    // upDateSchedule to driver being available

    string directory = "schedule/";
    string extension = ".csv";
    string filename = directory + cancelDate + extension;

    vector<vector<string>> schedule = readSchedule(filename);

    // loop through to replace all ref numbers with "available"
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule.at(i).size(); j++) {
            if (schedule.at(i).at(j) == userBookingsFuture.at(numUserInput - 1).bookingRef) {
                schedule.at(i).at(j) = "available";
            }
        }
    }
    updateSchedule(schedule, filename);
    cout << "Booking cancelled" << endl;

}

void makeComplaintOrEnquiry(string enquiryType) {
    if (enquiryType != "complaint" && enquiryType != "enquiry") {
        cout << "enquiryType \"" << enquiryType << "\" not valid" << endl;
        return;
    }

    vector<complaintOrEnquiry> enquiries = readEnquiriesFile();
    complaintOrEnquiry newEnquiry;
    string userInput;

    newEnquiry.enquiryType = enquiryType;

    if (enquiryType == "complaint") {
        cout << "Enter message, if you need us to contact you please include your details in the message otherwise you will remain anonymous: " << endl;
    }
    else {
        cout << "Enter name, or press enter to skip: ";
        getline(cin, userInput);
        newEnquiry.note += (userInput);
        cout << "Enter ph number, or press enter to skip: ";
        getline(cin, userInput);
        newEnquiry.note += (" " + userInput);
        cout << "Enter email, or press enter to skip: ";
        getline(cin, userInput);
        newEnquiry.note += (" " + userInput + " ");
        cout << "Enter message: ";
    }
    getline(cin, userInput);

    newEnquiry.note += userInput;

    enquiries.push_back(newEnquiry);

    updateEnquiriesFile(enquiries);

    cout << "Message sent. Thankyou for choosing Taxi services Wellington" << endl;
}

vector<complaintOrEnquiry> readEnquiriesFile() {
    //this function will read admin.csv and return vector
    vector<complaintOrEnquiry> enquiries;
    fstream enquiriesFile;
    complaintOrEnquiry tempEnquiry;
    enquiriesFile.open("enquiries.csv", ios::in);
    if (enquiriesFile.is_open()) {
        string line;
        string cell;
        while (getline(enquiriesFile, line)) {
            istringstream linestream(line);

            getline(linestream, cell, ',');
            tempEnquiry.enquiryType = cell;

            getline(linestream, cell, ',');
            tempEnquiry.note = cell;

            enquiries.push_back(tempEnquiry);
        }
        enquiriesFile.close();
    }
    return enquiries;
}

void updateEnquiriesFile(vector<complaintOrEnquiry> enquiries) {
    //this function updates the enquiries.csv with the latest information
    fstream enquiriesFile;
    enquiriesFile.open("enquiries.csv", ios::out);
    if (enquiriesFile.is_open()) {
        for (int i = 0; i < enquiries.size(); i++) {
            enquiriesFile << enquiries[i].enquiryType << "," << enquiries[i].note << endl;
        }
        enquiriesFile.close();
    }
}

void displayEnquiries(vector<complaintOrEnquiry> enquiries) {

    cout << endl;
    for (auto e : enquiries) {
        cout << e.enquiryType << endl;
        cout << e.note << endl;
        cout << endl;
    }
    bool keepRunning = true;
    string userInput;
    while (keepRunning) {
        cout << "\nWould you like to delete an enquiry? (Y/N): ";
        getline(cin, userInput);

        if (userInput == "Y" || userInput == "y") {
            keepRunning = false;
        }
        else if (userInput == "N" || userInput == "n") {
            return;
        }
        else {
            cout << "Invalid input" << endl;
        }
    }
    cout << "\nChoose complaint/enquiry to delete" << endl;
    for (int i = 0; i < enquiries.size(); i++) {
        cout << i + 1 << ". " << enquiries.at(i).enquiryType;
        cout << ": " << enquiries.at(i).note << endl;
    }
    keepRunning = true;
    int numUserInput;
    while (keepRunning) {
        cout << "Enter by list number: ";
        getline(cin, userInput);
        // convert user input to number

        if (isdigit(userInput[0])) {

            istringstream ssUserInput(userInput);
            ssUserInput >> numUserInput;
            numUserInput--;

            if (numUserInput >= 0 && numUserInput < enquiries.size()) {
                keepRunning = false;
            }

        }
    }
    // use number to delete an item from list
    enquiries.erase(enquiries.begin() + numUserInput);

   // displayEnquiries(enquiries);

    updateEnquiriesFile(enquiries);
    
    cout << "complaint/enquiry deleted" << endl;

}

void DisplayThisDriversTransactions(Driver user) {
    pageBreak();
    vector<Booking> bookings = readBookingsFile();
    vector<Booking> userBookingsPast;
    vector<Booking> userBookingsFuture;

    for (int i = 0; i < bookings.size(); i++) {
        if (bookings.at(i).driver.email == user.email) {
            // if past or else future
            if (hasDatePassed(bookings.at(i).date) == false ) {
                userBookingsFuture.push_back(bookings.at(i));
            }
            else {
                userBookingsPast.push_back(bookings.at(i));
            }
        }
    }

    //display bookings only with this person's email
    cout << "\nYour Transactions" << endl;
    cout << "**********" << endl;
    cout << "\n";

    // display past rides

    // display future rides
    if (userBookingsPast.size() == 0) {
        cout << "No past bookings to show" << endl;
    }
    else {
        cout << "Past transactions\n" << endl;
        displayAllBookings(userBookingsPast);

    }
    if (userBookingsFuture.size() == 0) {
        cout << "No future bookings to show" << endl;
        cout << "press enter to continue...";
        string contin;
        getline(cin, contin);
        return;
    }
    else {
        cout << "\nFuture transactions\n" << endl;
        displayAllBookings(userBookingsFuture);
    }
}

void displayThisDriversScheduleToday(Driver user) {
    // get todays date
    string date = getTodaysDateAsString();

    // convert todays date
    //cout << "Todays date: " << endl;
    ////cout << "now: " << now << endl;
    //cout << "day: " << newtime.tm_mday << endl;
    //cout << "Month: " << 1 + newtime.tm_mon << endl;
    //cout << "year: " << ( -100) + newtime.tm_year << endl;

    // check if there is a chedule for todays date
    replace(date.begin(), date.end(), '/', '-');

    //cout << "Today: " << date << endl;
    



    // converting date format ( DD/MM/YY ) to a schedule filename ( schedule/ DD-MM-YY.csv )
    
    vector <vector <string>> schedule = {
        {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    };
    vector<Booking> bookings = readBookingsFile();
    vector<Customer> customers = readCustomerFile();
    string directory = "schedule/";
    string extension = ".csv";
    string filename = directory + date + extension;             //look for availibilityfile, if there is no file, then make one before opening

    // check for a schedule with this filename (schedule / DD - MM - YY.csv) 
    // if no such schedule is found for this date then it will have to be created
    checkForSchedule(filename);

    // find schedule for this date and input to vector<string> availableTimes
    schedule = readSchedule(filename);

    // update availableTimes vector with any new drivers have been added
    schedule = addNewDriversToSchedule(schedule);


    // make a new vector with time(only show If Working), ref(or no booking), booking.start, booking.end, customer name, customer phone, customer email
    vector<vector<string>> personalDriverSchedule;
    vector<string> row;
    string tempRef;
    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule.at(i).size(); j++) {
            if (user.email == schedule.at(i).at(j)) {
                if (schedule.at(i).at(j + 1) != "unstaffed") {
                    row.clear();
                    row.push_back(schedule.at(i).at(0));
                    tempRef = "no booking";
                    if (schedule.at(i).at(j + 1) != "available") {
                        tempRef = schedule.at(i).at(j + 1);
                    }
                    row.push_back(tempRef);
                    personalDriverSchedule.push_back(row);
                }
            }
        }
    }

    // use ref number (personalDriverSchedule.at(i).at(1)) to find Booking and Customer, 
    // use  booking.start, booking.end, customer name, customer phone, customer email
    for (int i = 0; i < personalDriverSchedule.size(); i++) {
        for (int j = 0; j < bookings.size(); j++) {
            if (personalDriverSchedule.at(i).at(1) == bookings.at(j).bookingRef) {
                personalDriverSchedule.at(i).push_back(bookings.at(j).startLocation);
                personalDriverSchedule.at(i).push_back(bookings.at(j).endLocation);
                personalDriverSchedule.at(i).push_back(bookings.at(j).customer.firstName);
                personalDriverSchedule.at(i).push_back(bookings.at(j).customer.lastName);
                personalDriverSchedule.at(i).push_back(bookings.at(j).customer.phoneNumber);
                personalDriverSchedule.at(i).push_back(bookings.at(j).customer.email);                
            }
        }
    }

    // display personalDriverSchedule
    pageBreak();
    cout << "Todays trips" << endl;
    cout << "************" << endl << endl;
         
    for (int i = 0; i < personalDriverSchedule.size(); i++) {
        for (int j = 0; j < personalDriverSchedule.at(i).size(); j++) {
            cout << personalDriverSchedule.at(i).at(j) << ", ";
        }cout << endl;
    }

    // promt driver to exit, or reject booking // no actually only admin can do this
    cout << "press enter to continue...\n";
    string contin;
    getline(cin, contin);
}

string getTodaysDateAsString() {
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    // convert todays date to string (DD/MM/YY)
    string nowDay = to_string(newtime.tm_mday);
    if (nowDay.length() == 1) {
        nowDay = "0" + nowDay;
    }

    string nowMonth = to_string(1 + newtime.tm_mon);
    if (nowMonth.length() == 1) {
        nowMonth = "0" + nowMonth;
    }

    string nowYear = to_string((-100) + newtime.tm_year);
    if (nowYear.length() == 1) {
        nowYear = "0" + nowYear;
    }

    string todaysDate = nowDay + "/" + nowMonth + "/" + nowYear;
    return todaysDate;
}

Customer chooseCustomer(vector<Customer> customers) {
    Customer ChosenCustomer;

    cout << "All customers" << endl;
    for (int i = 0; i < customers.size(); i++) {
        cout << i + 1 << ". " << customers.at(i).firstName << " " << customers.at(i).lastName << ", email: " << customers.at(i).email << endl;
        
    }
    string userInput;
    int numUserInput = 0;
    bool isValidInput = false;
    while (isValidInput == false) {
        cout << "\nChoose customer you would like to edit by list number: ";

        getline(cin, userInput);
        istringstream ssUserInput(userInput);

        if (isdigit(userInput[0])) {
            ssUserInput >> numUserInput;
            if(numUserInput > 0 && numUserInput < customers.size()+1)
                isValidInput = true;
        }
    }

    ChosenCustomer = customers.at(numUserInput - 1);

    return ChosenCustomer;
}

Admin chooseAdmin(vector<Admin> admin) {
    Admin chosenAdmin;

    cout << "All admin" << endl;
    for (int i = 0; i < admin.size(); i++) {
        cout << i + 1 << ". " << admin.at(i).firstName << " " << admin.at(i).lastName << ", email: " << admin.at(i).email << endl;

    }
    string userInput;
    int numUserInput = 0;
    bool isValidInput = false;
    while (isValidInput == false) {
        cout << "\nChoose admin you would like to edit by list number: ";

        getline(cin, userInput);
        istringstream ssUserInput(userInput);

        if (isdigit(userInput[0])) {
            ssUserInput >> numUserInput;
            if (numUserInput > 0 && numUserInput < admin.size() + 1)
                isValidInput = true;
        }
    }

    chosenAdmin = admin.at(numUserInput - 1);

    return chosenAdmin;
}


Driver chooseDriver(vector<Driver> drivers) {
    Driver ChosenDriver;

    cout << "All drivers" << endl;
    for (int i = 0; i < drivers.size(); i++) {
        cout << i + 1 << ". " << drivers.at(i).firstName << " " << drivers.at(i).lastName << ", email: " << drivers.at(i).email << endl;

    }
    string userInput;
    int numUserInput = 0;
    bool isValidInput = false;
    while (isValidInput == false) {
        cout << "\nChoose driver you would like to edit by list number: ";

        getline(cin, userInput);
        istringstream ssUserInput(userInput);

        if (isdigit(userInput[0])) {
            ssUserInput >> numUserInput;
            if (numUserInput > 0 && numUserInput < drivers.size()+1)
                isValidInput = true;
        }
    }

    ChosenDriver = drivers.at(numUserInput - 1);

    return ChosenDriver;
}

void displayFullSchedule(string date) {
    // convert todays date
   //cout << "Todays date: " << endl;
   ////cout << "now: " << now << endl;
   //cout << "day: " << newtime.tm_mday << endl;
   //cout << "Month: " << 1 + newtime.tm_mon << endl;
   //cout << "year: " << ( -100) + newtime.tm_year << endl;

   // check if there is a chedule for todays date
    replace(date.begin(), date.end(), '/', '-');

    //cout << "Today: " << date << endl;




    // converting date format ( DD/MM/YY ) to a schedule filename ( schedule/ DD-MM-YY.csv )

    vector <vector <string>> schedule = {
        {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    };
    vector<Booking> bookings = readBookingsFile();
    vector<Customer> customers = readCustomerFile();
    string directory = "schedule/";
    string extension = ".csv";
    string filename = directory + date + extension;             //look for availibilityfile, if there is no file, then make one before opening

    // check for a schedule with this filename (schedule / DD - MM - YY.csv) 
    // if no such schedule is found for this date then it will have to be created
    checkForSchedule(filename);

    // find schedule for this date and input to vector<string> availableTimes
    schedule = readSchedule(filename);

    // update availableTimes vector with any new drivers have been added
    schedule = addNewDriversToSchedule(schedule);




    // use ref number (personalDriverSchedule.at(i).at(1)) to find Booking and Customer, 


    // display personalDriverSchedule
    pageBreak();
    cout << "Schedule for " << date << endl;
    cout << "***************" << endl << endl;

    for (int i = 0; i < schedule.size(); i++) {
        for (int j = 0; j < schedule.at(i).size(); j++) {
            cout << schedule.at(i).at(j) << ", ";
        }cout << endl;
    }

    // promt driver to exit, or reject booking // no actually only admin can do this
    cout << "press enter to continue...\n";
    string contin;
    getline(cin, contin);
}

string promtForDate() {
    string userInputDate = "12345678";
    int digitCount = 0;
    bool isDateValid = true;
    string sMonth;
    int month = 0;
    string sDay;
    int day = 0;
    string sYear;
    int year = 0;
    vector<int> daysInEachMonth = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int timeFrame = 90;

    do {
        isDateValid = true;
        digitCount = 0;
        // promt user
        cout << "Type a date to see availability (DD/MM/YY): ";
        getline(cin, userInputDate);
        //if (userInputDate == "E" || userInputDate == "e") return "void";

        // validate length
        if (userInputDate.length() == 8) {

            // check for 2 instances of '/'
            if (userInputDate[2] != '/' || userInputDate[5] != '/') {
                isDateValid = false;
                cout << "Incorrect '/'" << endl;

            }

            // ensure digit count is 6
            // loop through userInputDate to ensure 6 integers were used
            for (int i = 0; i < userInputDate.length(); i++) {
                if (isdigit(userInputDate[i])) {
                    digitCount++;
                }
            }
            if (digitCount != 6) {
                isDateValid = false;
            }

            // validate date exists, for exmaple, the 31st of February is invalid
            if (isdigit(userInputDate[0]) && isdigit(userInputDate[1]) && isdigit(userInputDate[3]) && isdigit(userInputDate[4]) && isdigit(userInputDate[6]) && isdigit(userInputDate[7])) // to ensure program does not crash
            {
                string sMonth = userInputDate.substr(3, 2);
                stringstream ssMonth(sMonth);
                ssMonth >> month;
                string sDay = userInputDate.substr(0, 2);
                stringstream ssDay(sDay);
                ssDay >> day;
            }
            // month cannot be over 12
            // cout << "month: " << month << endl;
            if (month < 1 || month > 12) {
                isDateValid = false;
                cout << "Invalid month" << endl;
            }
            // Day cannot be over 28,30,31 depending on month                                                //======= test this more ==========
            if (month < 13) {
                //cout << "day: " << day << endl;
                if (day < 1 || day > daysInEachMonth.at(month - 1)) {
                    isDateValid = false;
                    cout << "month " << month << ", does not contain " << day << " days" << endl;
                }
            }
        }
        else {
            isDateValid = false;
            cout << "Date format not valid" << endl;
        }

    } while (isDateValid == false);


    return userInputDate;
    
}