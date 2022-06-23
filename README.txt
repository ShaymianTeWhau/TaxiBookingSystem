TAXI SERVICES WELLINGTON
=========================================================================================================================================================

=login system=

This login system has 3 types of users.
- Customer
- Driver
- Admin
All 3 users login in at the same place but the program will figure out 
which type of user you are depending on which .csv file it found the user in. 

There are seperate .csv files containing information for each user, including their respective passwords ( "customers.csv", "drivers.csv", "admin.csv" ).

If you would like to log in as a customer you could simply register a new login, and then login with the user you just created.
Alternatively if you want to log in as an existing customer, driver or admin, you can check the respective .csv files for a username(email) and password,
or use one of the examples below.

example customer login:
- username: lisasimpson@gmail.com 
- password: saxophone

example driver login:
- username: driver2@gmail.com
- password: password

example admin login:
- username: admin@gmail.com
- password: admin123


=Bookings=

When bookings are created, Bookings are kept on the file, bookings.csv and are also shown on the driver schedule.

Driver schedules are in the folder "schedule/" , and are named by the date ( DD-MM-YY ). 
The application creates a driver schedule whenever a new booking is made, or whenever a specific day needs to be viewed.