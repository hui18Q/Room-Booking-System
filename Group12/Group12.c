#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAX_LINE_LENGTH 100
#define MAX_BOOKINGS 100
#define MAX_STRING_LENGTH 50

// Struct to hold booking details
struct Booking {
    char type[10];  // Local or Foreigner
    char name[MAX_STRING_LENGTH];
    char id[MAX_STRING_LENGTH];  // IC or Passport
    char phone[MAX_STRING_LENGTH];
    char email[MAX_STRING_LENGTH];
    char booking_date[MAX_STRING_LENGTH];
    char room_type[MAX_STRING_LENGTH];
    int num_days;
    float total_charge;
};

struct Booking bookings[MAX_BOOKINGS];
int num_bookings = 0;

// Function prototypes
void inputBookingDetails();
void writeBookingDetailsToFile();
void displayBookingDetailsFromFile();
float calculateTotalCharge(float pricePerNight, int numDays);
void main_menu();
void admin_menu();
void customer_menu();
void edit_price();
void readPrices(float *singlePrice, float *twinPrice, float *deluxePrice);
void writePrices();
void updatePrices(float *singlePrice, float *twinPrice, float *deluxePrice);

float singlePrice , twinPrice , deluxePrice ;

int main ()
{
    main_menu();
}

// Displays the main menu and navigates to Admin or Customer menus
void main_menu(){
    system("cls");
    int role;
    
    do {
        printf("--------------------------------------\n");
        printf("         Room Booking System          \n");
        printf("--------------------------------------\n");
        printf("What is your role?\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("3. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your role (1, 2 or 3):");
        scanf("%d", &role);
        
        if (role != 1 && role != 2 && role != 3) {
            system("cls");
            printf("Invalid input! Please enter 1 for Admin, 2 for Customer or 3 to Exit.\n");
            getchar();
        }
    } while(role != 1 && role != 2 && role != 3);
    
    if (role == 1) {
        int password;
        do {
            system("cls");
            printf("Enter admin password (-1 to exit):");
            scanf("%d", &password);
            if (password == -1) {
                main_menu();
            } else if (password != 1234) {
                printf("Wrong Password\n");
            }
            getchar();
        } while (password != 1234);
        
        admin_menu();
    } else if (role == 2) {
        customer_menu();
    } else {
        exit(0);  // Exit the program if the user chooses 3
    }
}

// Displays the admin menu and allows navigation to edit prices or display booking details
void admin_menu(){
    int action;
    do {
        system("cls");
        printf("--------------------------------------\n");
        printf("              Admin Menu              \n");
        printf("--------------------------------------\n");
        printf("What you want to do?\n");
        printf("1. Edit Price\n");
        printf("2. Display Booking Detail\n");
        printf("3. Exit\n");
        printf("--------------------------------------\n");
        printf("Select action (1,2 or 3):");
        scanf("%d", &action);
        
        if (action != 1 && action != 2 && action != 3) {
            system("cls");
            printf("Invalid input! Please enter 1 for Edit Price or 2 for Display Booking Details.\n");
            getchar();
        }
    } while (action != 1 && action != 2 && action != 3);
    
    if (action == 1) {
        edit_price();
    } else if (action == 2) {
        displayBookingDetailsFromFile();
    } else {
        main_menu();
    }
}

// Reads current prices from file, allows admin to update them, and writes back to file
void edit_price(){
    // Read current prices from the file
    readPrices(&singlePrice, &twinPrice, &deluxePrice);
    // Display current prices
    printf("Current prices:\n");
    printf("Single: %.2f\n", singlePrice);
    printf("Twin: %.2f\n", twinPrice);
    printf("Deluxe: %.2f\n", deluxePrice);

    // Update prices based on user input
    updatePrices(&singlePrice, &twinPrice, &deluxePrice);
    
    // Write the updated prices back to the file
    writePrices();
    
    admin_menu();
}

// Reads room prices from "price.txt" file
void readPrices(float *singlePrice, float *twinPrice, float *deluxePrice) {
    FILE *file = fopen("price.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char roomType[20];
        float price;
        sscanf(line, "%s %f", roomType, &price);

        if (strcmp(roomType, "Single") == 0) {
            *singlePrice = price;
        } else if (strcmp(roomType, "Twin") == 0) {
            *twinPrice = price;
        } else if (strcmp(roomType, "Deluxe") == 0) {
            *deluxePrice = price;
        }
    }

    fclose(file);
}

// Writes updated room prices to "price.txt" file
void writePrices() {
    FILE *file = fopen("price.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "Single %.2f\n", singlePrice);
    fprintf(file, "Twin %.2f\n", twinPrice);
    fprintf(file, "Deluxe %.2f\n", deluxePrice);

    fclose(file);
}

// Updates room prices based on user input
void updatePrices(float *singlePrice, float *twinPrice, float *deluxePrice) {
    char choice;
    printf("Do you want to update the prices? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y') {
        printf("Enter new price for Single: ");
        scanf("%f", singlePrice);  
        printf("Enter new price for Twin: ");
        scanf("%f", twinPrice);    
        printf("Enter new price for Deluxe: ");
        scanf("%f", deluxePrice); 
    }
}

// Takes user input for booking details and stores them in the bookings array
void inputBookingDetails() {
    char choice;
    
    do {
        system("cls");
        
        readPrices(&singlePrice, &twinPrice, &deluxePrice);
   		 // Display prices
    	printf("Price List:\n");
    	printf("Single: %.2f\n", singlePrice);
    	printf("Twin: %.2f\n", twinPrice);
    	printf("Deluxe: %.2f\n", deluxePrice);
    	
        printf("Are you a local or foreigner? (L for Local, F for Foreigner): ");
        scanf(" %s", bookings[num_bookings].type);
        getchar();  

        printf("Enter your name: ");
        fgets(bookings[num_bookings].name, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].name[strcspn(bookings[num_bookings].name, "\n")] = '\0';

        printf("Enter your IC number or Passport number: ");
        fgets(bookings[num_bookings].id, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].id[strcspn(bookings[num_bookings].id, "\n")] = '\0'; 

        printf("Enter your phone number: ");
        fgets(bookings[num_bookings].phone, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].phone[strcspn(bookings[num_bookings].phone, "\n")] = '\0';

        printf("Enter your email: ");
        fgets(bookings[num_bookings].email, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].email[strcspn(bookings[num_bookings].email, "\n")] = '\0'; 

        printf("Enter booking date (YYYY-MM-DD): ");
        fgets(bookings[num_bookings].booking_date, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].booking_date[strcspn(bookings[num_bookings].booking_date, "\n")] = '\0'; 

        printf("Enter room type (Deluxe, Twin, Single): ");
        fgets(bookings[num_bookings].room_type, MAX_STRING_LENGTH, stdin);
        bookings[num_bookings].room_type[strcspn(bookings[num_bookings].room_type, "\n")] = '\0'; 

        printf("Enter number of days staying: ");
        scanf("%d", &bookings[num_bookings].num_days);

        num_bookings++; // Increment number of bookings
        // Display the booking just made
        printf("\n-------------------------------------------------------------------\n");
        printf("Type: %s\n", bookings[num_bookings - 1].type);
        printf("\nBooking Details:\n");
        printf("Name: %s\n", bookings[num_bookings - 1].name);
        printf("ID: %s\n", bookings[num_bookings - 1].id);
        printf("Phone: %s\n", bookings[num_bookings - 1].phone);
        printf("Email: %s\n", bookings[num_bookings - 1].email);
        printf("Booking Date: %s\n", bookings[num_bookings - 1].booking_date);
        printf("Room Type: %s\n", bookings[num_bookings - 1].room_type);
        printf("Number of Days: %d\n", bookings[num_bookings - 1].num_days);

        // Calculate and display total charge
        readPrices(&singlePrice, &twinPrice, &deluxePrice);
        float price;
        if (strcmp(bookings[num_bookings - 1].room_type, "Single") == 0) {
            price = singlePrice;
        } else if (strcmp(bookings[num_bookings - 1].room_type, "Twin") == 0) {
            price = twinPrice;
        } else if (strcmp(bookings[num_bookings - 1].room_type, "Deluxe") == 0) {
            price = deluxePrice;
        }
        bookings[num_bookings - 1].total_charge = calculateTotalCharge(price, bookings[num_bookings - 1].num_days);
        printf("Total Charge: %.2f\n", bookings[num_bookings - 1].total_charge);
        writeBookingDetailsToFile();
        printf("-------------------------------------------------------------------");

        printf("\nDo you want to enter another booking? (Y/N): ");
        scanf(" %c", &choice);
        getchar();  

    } while (choice == 'Y' || choice == 'y');
}

// Writes the booking details to "bookingDetails.txt" file
void writeBookingDetailsToFile() {
    FILE *file = fopen("bookingDetails.txt", "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", "bookingDetails.txt");
        exit(1);
    }
	int i = 0;
    // Append each booking to the file
    while(i < num_bookings) {
        fprintf(file, "%-15s%-30s%-20s%-20s%-30s%-20s%-15s%-15d%-15.2f\n",
            bookings[i].type,
            bookings[i].name,
            bookings[i].id,
            bookings[i].phone,
            bookings[i].email,
            bookings[i].booking_date,
            bookings[i].room_type,
            bookings[i].num_days,
            bookings[i].total_charge 
        );
         ++i;
    }

    fclose(file);
}

// Displays booking details from "bookingDetails.txt" file
void displayBookingDetailsFromFile() {
    FILE *file = fopen("bookingDetails.txt", "r");
    if (file == NULL) {
        printf("Error opening file %s for reading.\n", "bookingDetails.txt");
        exit(1);
    }

    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("\nPress Enter to return to the menu...");
    while (getchar() != '\n');  // Wait for Enter key press
    getchar();
    main_menu();
}

// Displays customer menu and allows navigation to make a booking or exit
void customer_menu() {
    int choice;
    do {
        system("cls");
        printf("--------------------------------------\n");
        printf("         Customer Menu                \n");
        printf("--------------------------------------\n");
        printf("What would you like to do?\n");
        printf("1. Make a booking\n");
        printf("2. Exit\n");
        printf("--------------------------------------\n");
        printf("Enter your choice (1 or 2): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputBookingDetails();
                break;
            case 2:
                main_menu();
                break;
            default:
                printf("Invalid choice. Please enter 1 for booking or 2 for exit.\n");
                break;
        }
    } while(choice != 2);
}

// Calculates total charge based on price per night and number of days
float calculateTotalCharge(float pricePerNight, int numDays) {
    return pricePerNight * numDays;
}

