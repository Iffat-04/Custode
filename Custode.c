#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_ADMINS 50
#define MAX_ROUTES 50
#define MAX_VEHICLES 50
#define MAX_TRIPS 100
#define MAX_BOOKINGS 500

// Data Structures
struct User { 
    int id; 
    char username[50], password[50]; 
};

struct Admin { 
    int id; 
    char username[50], password[50]; 
};

struct Route { 
    int id; 
    char from[50], to[50]; 
    float distance; 
};

struct Vehicle { 
    int id; 
    char regNumber[20]; 
    int capacity; 
    char type[20]; 
};

struct Trip { 
    int id, routeId, vehicleId; 
    char departure[20]; 
    float fare; 
};

struct Booking { 
    int id, userId, tripId, seats; 
    char status[20]; 
};

// Global Data
struct User users[MAX_USERS]; 
int numUsers = 0;
struct Admin admins[MAX_ADMINS]; 
int numAdmins = 0;
struct Route routes[MAX_ROUTES]; 
int numRoutes = 0;
struct Vehicle vehicles[MAX_VEHICLES]; 
int numVehicles = 0;
struct Trip trips[MAX_TRIPS]; 
int numTrips = 0;
struct Booking bookings[MAX_BOOKINGS]; 
int numBookings = 0;

// Load Data
void loadAllData() {
    FILE* fp;
    
    if ((fp = fopen("users.txt", "r"))) {
        while (numUsers < MAX_USERS && fscanf(fp, "%d %s %s", &users[numUsers].id,
            users[numUsers].username, users[numUsers].password) == 3) 
            numUsers++;
        fclose(fp);
    }
    
    if ((fp = fopen("admins.txt", "r"))) {
        while (numAdmins < MAX_ADMINS && fscanf(fp, "%d %s %s", &admins[numAdmins].id,
            admins[numAdmins].username, admins[numAdmins].password) == 3) 
            numAdmins++;
        fclose(fp);
    }
    
    printf("Loaded: %d users, %d admins\n", numUsers, numAdmins);
}

// Save Data
void saveAllData() {
    FILE* fp = fopen("users.txt", "w");
    if (fp) {
        for (int i = 0; i < numUsers; i++) 
            fprintf(fp, "%d %s %s\n", users[i].id, users[i].username, users[i].password);
        fclose(fp);
    }
    
    fp = fopen("admins.txt", "w");
    if (fp) {
        for (int i = 0; i < numAdmins; i++) 
            fprintf(fp, "%d %s %s\n", admins[i].id, admins[i].username, admins[i].password);
        fclose(fp);
    }
}

// User Sign Up
void userSignUp() {
    char username[50], password[50];
    printf("\n--- User Sign Up ---\n");
    printf("Choose Username: ");
    scanf("%s", username);
    printf("Choose Password: ");
    scanf("%s", password);
    
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists!\n");
            return;
        }
    }
    
    users[numUsers].id = numUsers + 1;
    strcpy(users[numUsers].username, username);
    strcpy(users[numUsers].password, password);
    numUsers++;
    
    saveAllData();
    printf("User registered successfully!\n");
}

// Admin Sign Up
void adminSignUp() {
    char username[50], password[50];
    printf("\n--- Admin Sign Up ---\n");
    printf("Choose Admin Username: ");
    scanf("%s", username);
    printf("Choose Password: ");
    scanf("%s", password);
    
    for (int i = 0; i < numAdmins; i++) {
        if (strcmp(admins[i].username, username) == 0) {
            printf("Admin username already exists!\n");
            return;
        }
    }
    
    admins[numAdmins].id = numAdmins + 1;
    strcpy(admins[numAdmins].username, username);
    strcpy(admins[numAdmins].password, password);
    numAdmins++;
    
    saveAllData();
    printf("Admin registered successfully!\n");
}

// User Login
int userLogin() {
    char username[50], password[50];
    printf("\n--- User Login ---\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful! Welcome %s\n", username);
            return users[i].id;
        }
    }
    printf("Invalid username or password!\n");
    return -1;
}

// Admin Login
int adminLogin() {
    char username[50], password[50];
    printf("\n--- Admin Login ---\n");
    printf("Enter Admin Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    
    for (int i = 0; i < numAdmins; i++) {
        if (strcmp(admins[i].username, username) == 0 && strcmp(admins[i].password, password) == 0) {
            printf("Admin login successful! Welcome %s\n", username);
            return admins[i].id;
        }
    }
    printf("Invalid admin credentials!\n");
    return -1;
}

// Make Booking
int makeBooking(int userId, int tripId, int seats) {
    if (numBookings >= MAX_BOOKINGS) return 0;
    bookings[numBookings].id = numBookings + 1;
    bookings[numBookings].userId = userId;
    bookings[numBookings].tripId = tripId;
    bookings[numBookings].seats = seats;
    strcpy(bookings[numBookings].status, "confirmed");
    numBookings++;
    saveAllData();
    return 1;
}

// User Menu
void userMenu(int userId) {
    int choice;
    printf("\n--- User Menu ---\n");
    printf("1. View Routes\n");
    printf("2. View Vehicles\n");
    printf("3. View Trips\n");
    printf("4. Make Booking\n");
    printf("5. View My Bookings\n");
    printf("0. Logout\n");
    printf("Your Choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        printf("\nAvailable Routes: %d\n", numRoutes);
    }
    else if (choice == 2) {
        printf("\nAvailable Vehicles: %d\n", numVehicles);
    }
    else if (choice == 3) {
        printf("\nAvailable Trips: %d\n", numTrips);
    }
    else if (choice == 4) {
        int tripId, seats;
        printf("Enter Trip ID: ");
        scanf("%d", &tripId);
        printf("Enter Number of Seats: ");
        scanf("%d", &seats);
        if (makeBooking(userId, tripId, seats)) {
            printf("Booking confirmed!\n");
        }
    }
    else if (choice == 5) {
        printf("\nYour Bookings:\n");
        int count = 0;
        for (int i = 0; i < numBookings; i++) {
            if (bookings[i].userId == userId) {
                printf("Booking ID: %d, Trip ID: %d, Seats: %d, Status: %s\n",
                    bookings[i].id, bookings[i].tripId, bookings[i].seats, bookings[i].status);
                count++;
            }
        }
        printf("Total Bookings: %d\n", count);
    }
}

// Main Menu
int main() {
    loadAllData();
    
    printf("_________________________________\n");
    printf("     Transport Booking System    \n");
    printf("_________________________________\n");
    
    int mainChoice = 0;
    
    while (1) {
        printf("\n1. Sign Up\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &mainChoice);
        
        if (mainChoice == 1) {
            int signupChoice;
            printf("\n1. Sign Up as User\n");
            printf("2. Sign Up as Admin\n");
            printf("Your Choice: ");
            scanf("%d", &signupChoice);
            
            if (signupChoice == 1) {
                userSignUp();
            } else if (signupChoice == 2) {
                adminSignUp();
            }
        }
        else if (mainChoice == 2) {
            int loginChoice;
            printf("\n1. User Login\n");
            printf("2. Admin Login\n");
            printf("Your Choice: ");
            scanf("%d", &loginChoice);
            
            if (loginChoice == 1) {
                int userId = userLogin();
                if (userId != -1) {
                    userMenu(userId);
                }
            } else if (loginChoice == 2) {
                adminLogin();
            }
        }
        else if (mainChoice == 3) {
            printf("Thank you for using our system!\n");
            break;
        }
    }
    
    saveAllData();
    return 0;
}
