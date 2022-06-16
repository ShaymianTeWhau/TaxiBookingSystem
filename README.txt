Run the program if you like, you can register as a new user and login.
Or if you want to login as an existing user (customer, driver or admin), 
just check the .csv files for an existing username (username is email address) and password.

At the moment the program will just display what type of user you are, until submenu's are made.




==================================================================================================================

This login system has 3 users.
- Customer
- Driver
- Admin
There are seperate .csv files for each.

void login();
All 3 users login in the same place but the program will figure out 
which type of user you are depending on which .csv file it found the user in.
We can easily change this to seperate portals if you like.
 
At the end of the login() function there is a switch statement with functions i have commented out.
They would go to different sub menus deppending on what kind of user you are. 
We could pass in their name maybe?

readCustomersFile(), readDriversFile(), readAdminsFile() are all functions that read .csv files and return a vector.
However I couldn't figure out how to condense these to one function. 

The same goes for displayAllCostomers(vector<Customer>customerList), 
displayAllDrivers(vector<Driver>driversList), displayAllAdmin(vector<Admin>adminList).
