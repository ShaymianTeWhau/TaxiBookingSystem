#include <iostream>
#include <fstream> //read and write to files
#include <vector> //
#include <string>
#include <sstream>
#include <algorithm>
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

//struct Booking

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

//struct Complaint

//struct Enquiry

//prototypes
void registerNewLogin();
void login();
vector<Customer> readCustomerFile(); 
vector<Driver> readDriversFile(); //update
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
            makeBooking(user);
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

void displayUserProfile(Customer c) { 
    pageBreak();
    cout << "User profile" << endl;
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


void makeBooking(Customer user) {
    pageBreak();

    string userInputDate = "12345678";
    while (userInputDate.length() != 8 || userInputDate[2] != '/' || userInputDate[5] != '/') {
        cout << "Type a date to see availability (DD/MM/YY): ";
        getline(cin, userInputDate);
    }

    string date = userInputDate;


    //enter date (DD/MM/YY) to display availability 
    replace(date.begin(), date.end(), '/', '-');
    vector <vector <string>> availableTimes = {
        {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    };
    string directory = "schedule/";
    string extension = ".csv";

    //string filename = "schedule/14-06-22.csv";
    string filename = directory + date + extension;             //look for availibilityfile, if there is no file, then make one before opening

    checkForSchedule(filename);

    availableTimes = readSchedule(filename);

    // update old schedule to include new drivers
        //

    availableTimes = addNewDriversToSchedule(availableTimes);

    cout << "\nAvailable times: " << endl << endl;
    for (int i = 0; i < availableTimes.size(); i++) {
        int driversAvailable = 0;
        for (int j = 0; j < availableTimes[i].size(); j++) {
            if (j == 0) cout << availableTimes[i][0] << ": ";

            if (availableTimes[i][j] == "available") {
                //cout << "driver available ";
                driversAvailable++;
            }
        }
        if (driversAvailable > 0) cout << "available " << endl;
        else cout << "Booking full " << endl;
    }

    // type in time to make booking

    string userInputTime;
    bool isUserInputValid = false;
    string availableDriverEmail;
    string* availableSlot = nullptr;

    cout << "\nEnter time to make a booking (hour.mins):\nmust enter half hour block: ";
    while (isUserInputValid == false)
    {
        getline(cin, userInputTime);
        cout << userInputTime << " ";

        // is time free? if no then try again
        int driversAvailable = 0;
        for (int i = 0; i < availableTimes.size(); i++) {
            if (availableTimes[i][0] == userInputTime) {
                //cout << "found " << endl;
                for (int j = 0; j < availableTimes.at(i).size(); j++) {
                    if (availableTimes[i][j] == "available") {
                        availableDriverEmail = availableTimes[i][j - 1];
                        availableSlot = &availableTimes[i][j];
                        //cout << "and available" << endl;
                        driversAvailable++;
                    }
                }
            }
        }

        if (driversAvailable > 0) {
            cout << "\nslot free to make booking" << endl;
            isUserInputValid = true;
        }
        else cout << "slot is not free, please choose another time: ";
    }


    vector<Booking> bookings = readBookingsFile();
    //displayAllBookings(bookings);
    // make newBooking 
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
    int userInputDuration = 0, roundedUp = 0;
    getline(cin, userInput);
    stringstream ss(userInput);

    // round new booking duration up to nearest 30mins
    ss >> userInputDuration;
    roundedUp = ((userInputDuration / 30) * 30) + 30;

    newBooking.duration = roundedUp;

    cout << "Enter pickup location: ";
    getline(cin, newBooking.startLocation);
    cout << "Enter dropoff location: ";
    getline(cin, newBooking.endLocation);
    newBooking.cost = (newBooking.duration * 2.0);

    cout << "\n--new Booking details--" << endl << endl;
    cout << newBooking.bookingRef << "\t" << newBooking.customer.email << "\t" << newBooking.date << "\t" << newBooking.time << "\t"
        << newBooking.duration << "\t" << newBooking.startLocation << "\t" << newBooking.endLocation << "\t$" << newBooking.cost << "\t" << newBooking.driver.email << endl;

    //ask user to confirm Y/N
    bool isUserSure = false;
    while (isUserSure == false) {

        cout << "\nAre you sure you want to make this booking? (Y/N) ";
        getline(cin, userInput);
        //toupper(userInput);

        if (userInput == "Y") {
            isUserSure = true;
        }
        else if (userInput == "N") {
            cout << "cancelling booking" << endl;
            return;
        }
        else {
            cout << "Invalid Input" << endl;
        }
    }


    // push newBooking to bookings
    bookings.push_back(newBooking);

    updateBookingsFile(bookings);

    //put ref into available slot in availableTimes
    //for loop to find time, driver, put in ref for start slot and following slots depending on booking.duration

    int halfHourBlocks = newBooking.duration / 30; //need to do rounding somehow
    //bool willBookingOverFlow;
    int halfHourBlocksLeftThisDay = 1;
    // newBooking.time   24.00
    int halfHourBlocksOverflow = 0;
    float convertedTime;
    istringstream ssTime(newBooking.time);
    ssTime >> convertedTime;
    halfHourBlocksLeftThisDay = (24.0 - convertedTime) * 2;

    halfHourBlocksOverflow = halfHourBlocks - halfHourBlocksLeftThisDay;

    if (halfHourBlocksOverflow > 0) {
        bookingOverflow(newBooking.driver.email, date, halfHourBlocksOverflow, newBooking.bookingRef);     //checkforfile, ?makefile  // readSchedule //replace availanility for a driver for time 0.00 and following halfHourBlocks depending on halfHourBlocksOverflow
    }

    for (int i = 0; i < availableTimes.size(); i++) {
        if (availableTimes.at(i).at(0) == userInputTime) {
            for (int j = 0; j < availableTimes.at(i).size(); j++) {
                if (availableTimes.at(i).at(j) == newBooking.driver.email) {
                    for (int k = 0; k < halfHourBlocks && k < halfHourBlocksLeftThisDay; k++) {


                        availableTimes.at(i + k).at(j + 1) = newBooking.bookingRef;           //must fix or break app                //currently won't overflow days
                    }
                }
            }
        }
    }

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

            /*
            string bookingRef;
            Customer customer;
            Driver driver;
            string date;
            string time;
            string duration;
            string startLocation;
            string endLocation;
            float cost;
            */

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
    cout << "\nDisplay all bookings" << endl;
    for (auto b : bookings) {
        cout << b.bookingRef << ", " << b.customer.email << ", " << b.driver.email << ", " << b.date << ", " << b.time << ", " << b.duration << ", " << b.startLocation << ", " << b.endLocation << ", $" << b.cost << endl;
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
    vector<vector<string>> newSchedule = { {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {},
        {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, };
    //newSchedule.reserve(100);
    vector<Driver> drivers = readDriversFile();
    vector<string> row;

    int hour = 0;
    string h = "";
    string time = "";

    for (int i = 0; i < 48; i++) { //loop through all times

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
        //cout << time << endl;
        newSchedule.at(i).push_back(time);

        //loop through list of drivers x 2? get email followed by "temp";
        string availability = "temp";
        for (int d = 0; d < drivers.size(); d++) {
            //cout << drivers.at(d).email << ", " << availability << ", ";
            availability = to_string(drivers.at(d).driverFinish);
            availability = getDriverAvailabilityByTime(drivers.at(d), time);
            //getDriverAvailabilityByTime(time) return a string{ available, unstaffed }

            newSchedule.at(i).push_back(drivers.at(d).email);
            newSchedule.at(i).push_back(availability);
        }
        //break; //delete this line
    }

    updateSchedule(newSchedule, filename); // change to filename when ready

}


string getDriverAvailabilityByTime(Driver driver, string time) {
    string availability = "available";
    vector<float> availableTimes = { 0.0,0.3,1.0,1.3,2.0,2.3,3.0,3.3,4.0,4.3,5.0,5.3,6.0,6.3,7.0,7.3,8.0,8.3,9.0,9.3,
        10.0,10.3,11.0,11.3,12.0,12.3,13.0,13.3,14.0,14.3,15.0,15.3,16.0,16.3,17.0,17.3,18.0,18.3,19.0,19.3,20.0,20.3,21.0,21.3,22.0,22.3,23.0,23.3,0.0,0.3,1.0,1.3,2.0,2.3,3.0,3.3,4.0,4.3,5.0,5.3,6.0,6.3,7.0,7.3,8.0,8.3,9.0,9.3,
        10.0,10.3,11.0,11.3,12.0,12.3,13.0,13.3,14.0,14.3,15.0,15.3,16.0,16.3,17.0,17.3,18.0,18.3,19.0,19.3,20.0,20.3,21.0,21.3,22.0,22.3,23.0,23.3 };

    //cout << driver.firstName << " works from " << driver.driverStart << " to " << driver.driverFinish << endl;

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

    //find driver end, cut everything after

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
                schedule.at(i).at(j + 1) = bookingRef;          //change temp to ref
            }
        }

    }

    updateSchedule(schedule, filename);

}

string incrementDate(string date) {
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


