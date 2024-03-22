#define _CRT_SECURE_NO_WARNINGS 1 // Corrected macro name
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Include bool type

#define FILENAME "cars.dat" // Define filename for data file

// The structure for a car
struct Car {
    char registration[10];  // Registration number of the car
    char makeModel[50];     // Make and model of the car
    char color[20];         // Color of the car
    int prevOwners;         // Number of previous owners
    bool reserved;          // Boolean indicating whether the car is reserved or not
    float reserveAmount;    // Amount reserved for the car
    char serviceHistory[100]; // Service history of the car
};

// Define a structure for a linear node in a linked list
struct LinearNode {
    struct Car* element;
    struct LinearNode* next;
};

// Global variables
struct LinearNode* front = NULL; // Pointer to the first node in the linked list
struct LinearNode* last = NULL;  // Pointer to the last node in the linked list

// Function prototypes
void displayMenu();             // Function to display the menu
void loadCarsFromFile();        // Function to load cars from the data file
void saveCarsToFile();          // Function to save cars to the data file
void addCar();                  // Function to add a new car to the showroom
void sellCar();                 // Function to sell a car from the showroom
void reserveUnreserveCar();     // Function to reserve or unreserve a car in the showroom
void viewAllCars();             // Function to view all cars in the showroom
void viewSpecificCar();         // Function to view details of a specific car in the showroom
void updateServiceHistory();    // Function to update service history for a car

int main() {
    int option; // Variable to store user's menu choice

    loadCarsFromFile(); // Load cars from file at the beginning

    // Menu loop
    do {
        displayMenu(); // Display the menu
        scanf("%d", &option); // Get user input for menu option

        // Execute the corresponding menu option
        switch (option) {
        case 1:
            addCar(); // Add a new car
            break;
        case 2:
            sellCar(); // Sell a car
            break;
        case 3:
            reserveUnreserveCar(); // Reserve or unreserve a car
            break;
        case 4:
            viewAllCars(); // View all cars
            break;
        case 5:
            viewSpecificCar(); // View details of a specific car
            break;
        case 6:
            updateServiceHistory(); // Update service history for a car
            break;
        case 7:
            printf("Exiting the system. Saving cars to file...\n");
            saveCarsToFile(); // Save cars to file before exiting
            break;
        default:
            printf("Invalid option. Please enter a number between 1 and 7.\n");
        }

    } while (option != 7); // Continue until user chooses to exit

    return 0;
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add a new car to the showroom\n");
    printf("2. Sell a car from the showroom\n");
    printf("3. Reserve/Unreserve a car in the showroom\n");
    printf("4. View all cars in the showroom\n");
    printf("5. View a specific car in the showroom\n");
    printf("6. Update Service History for a Car\n");
    printf("7. Exit the system\n");
    printf("Enter your choice (1-7): ");
}

// Function to load cars from the data file
void loadCarsFromFile() {
    FILE* file = fopen(FILENAME, "rb"); // Open the file for reading in binary mode

    // Check if the file exists
    if (file == NULL) {
        printf("List of cars doesn't exist. You need to input cars.\n");
        return;
    }

    struct Car car; // Temporary variable to hold car data
    // Read cars from the file and add them to the linked list
    while (fread(&car, sizeof(struct Car), 1, file)) {
        struct LinearNode* newNode = (struct LinearNode*)malloc(sizeof(struct LinearNode)); // Create a new node
        newNode->element = (struct Car*)malloc(sizeof(struct Car)); // Allocate memory for the car
        memcpy(newNode->element, &car, sizeof(struct Car)); // Copy car data to the new node
        newNode->next = NULL; // Set next pointer to NULL

        // Add the new node to the linked list
        if (front == NULL) {
            front = newNode; // If list is empty, set front and last to the new node
            last = newNode;
        }
        else {
            last->next = newNode; // Otherwise, add the new node after the last node
            last = newNode;
        }
    }

    fclose(file); // Close the file
    printf("System has been populated with cars from the data file.\n");
}

// Function to save cars to the data file
void saveCarsToFile() {
    FILE* file = fopen(FILENAME, "wb"); // Open the file for writing in binary mode

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    struct LinearNode* current = front; // Pointer to traverse the linked list
    // Write each car from the linked list to the file
    while (current != NULL) {
        fwrite(current->element, sizeof(struct Car), 1, file); // Write car data to file
        current = current->next; // Move to the next node
    }

    fclose(file); // Close the file
}

// Function to add a new car to the showroom
void addCar() {
    struct LinearNode* aNode; // Pointer to a new node in the linked list
    struct Car* aCar; // Pointer to a new car structure

    // Allocate memory for a new car
    aCar = (struct Car*)malloc(sizeof(struct Car));
    if (aCar == NULL) { // Check if memory allocation was successful
        printf("Error. Car cannot be inserted\n");
        return;
    }

    // Enter car details
    printf("Enter registration number:");
    scanf("%9s", aCar->registration); // Read registration number from user

    printf("Enter make & model:");
    scanf("%49s", aCar->makeModel); // Read make & model from user

    printf("Enter car color:");
    scanf("%19s", aCar->color); // Read color from user

    printf("Enter number of previous owners:");
    scanf("%d", &aCar->prevOwners); // Read number of previous owners from user

    printf("Enter service history:");
    scanf("%99s", aCar->serviceHistory); // Read service history from user

        // Check if the car is reserved
    printf("Is the car reserved? (1 for yes, 0 for no): ");
    int reservedInt;
    scanf("%d", &reservedInt);
    aCar->reserved = reservedInt ? true : false; // Convert integer input to boolean

    // If car is reserved, enter reservation amount
    if (aCar->reserved) {
        printf("Enter car reservation amount:");
        scanf("%f", &aCar->reserveAmount); // Read reservation amount from user
    }
    else {
        aCar->reserveAmount = 0.0; // Set reservation amount to 0 if car is not reserved
    }

    // Allocate memory for a new node in the linked list
    aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));
    if (aNode == NULL) { // Check if memory allocation was successful
        printf("Error. Node cannot be inserted\n");
        free(aCar); // Free allocated memory for the car
        return;
    }

    // Add car to the new node
    aNode->element = aCar;
    aNode->next = NULL;

    // Add the new node to the linked list
    if (front == NULL) {
        front = aNode; // If list is empty, set front and last to the new node
        last = aNode;
    }
    else {
        aNode->next = front; // Otherwise, add the new node at the front
        front = aNode;
    }
}

// Function to sell a car from the showroom
void sellCar() {
    struct LinearNode* aNode; // Pointer to traverse the linked list
    struct Car* aCar; // Pointer to the car to be sold
    char registration[10]; // Variable to store the registration number of the car to be sold

    // Prompt user to enter the registration number of the car to be sold
    printf("Enter the car's registration number for the car you wish to sell: ");
    scanf("%9s", registration); // Read registration number from user

    aNode = front;
    struct LinearNode* prevNode = NULL; // Pointer to track the previous node while traversing the list

    // Search for the car with the specified registration number
    while (aNode != NULL && strcmp(aNode->element->registration, registration) != 0) {
        prevNode = aNode; // Track the previous node
        aNode = aNode->next; // Move to the next node
    }

    // Check if the car with the specified registration number was found
    if (aNode != NULL) {
        // Retrieve car details
        aCar = aNode->element;
        printf("\nCar sold:\n");
        printf("Registration number: %s\n", aCar->registration);
        printf("Car make & model: %s\n", aCar->makeModel);
        printf("Color: %s\n", aCar->color);
        printf("Amount of previous owners: %d\n", aCar->prevOwners);
        printf("Reserved: %s\n", aCar->reserved ? "Reserved" : "Not reserved");
        printf("Reserve amount: %.2f\n\n", aCar->reserveAmount);

        // Remove the sold car from the linked list
        if (prevNode == NULL) {
            front = aNode->next; // If the sold car is the first node
        }
        else {
            prevNode->next = aNode->next; // If the sold car is not the first node
        }

        free(aCar); // Free memory allocated for the car
        free(aNode); // Free memory allocated for the node
    }
    else {
        printf("Unrecognized registration number %s is not in the list\n", registration);
    }
}

// Function to reserve or unreserve a car in the showroom
void reserveUnreserveCar() {
    char registration[10]; // Variable to store the registration number of the car
    int reserveChoice; // Variable to store the reserve choice (1 for reserve, 0 for unreserve)

    // Prompt user to enter the registration number of the car
    printf("Enter the car's registration number: ");
    scanf("%9s", registration); // Read registration number from user

    struct LinearNode* current = front;

    // Search for the car with the specified registration number
    while (current != NULL && strcmp(current->element->registration, registration) != 0) {
        current = current->next; // Move to the next node
    }

    // Check if the car with the specified registration number was found
    if (current != NULL) {
        // Retrieve car details
        struct Car* car = current->element;
        printf("Current reservation status of the car:\n");
        printf("Registration number: %s\n", car->registration);
        printf("Make & model: %s\n", car->makeModel);
        printf("Reserved: %s\n", car->reserved ? "Yes" : "No");

        // Prompt user for reserve choice
        printf("Do you want to reserve this car? (1 for yes, 0 for no): ");
        scanf("%d", &reserveChoice);

        // Update reservation status based on user choice
        if (reserveChoice == 1) {
            car->reserved = true;
            printf("Car has been reserved.\n");
        } else if (reserveChoice == 0) {
            car->reserved = false;
            printf("Car has been unreserved.\n");
        } else {
            printf("Invalid choice.\n");
        }
    } else {
        printf("Car with registration number %s not found.\n", registration);
    }
}

// Function to view all cars in the showroom
void viewAllCars() {
    struct LinearNode* current = front; // Pointer to traverse the linked list
    int numCars = 0; // Counter for the number of cars in the showroom

    // Count the number of cars in the showroom
    while (current != NULL) {
        numCars++;
        current = current->next;
    }

    if (numCars == 0) {
        printf("The showroom is empty. No cars to display.\n");
        return;
    }

    printf("All cars in the showroom:\n");
    current = front; // Reset pointer to the beginning of the linked list
    // Display details of each car in the showroom
    while (current != NULL) {
        printf("Registration: %s, Make and Model: %s, Color: %s, Owners: %d, Reserved: %s, Reserve Amount: %.2f, Service History: %s\n",
            current->element->registration, current->element->makeModel, current->element->color,
            current->element->prevOwners, current->element->reserved ? "Yes" : "No", 
            current->element->reserveAmount, current->element->serviceHistory);
        current = current->next;
    }
}

// Function to view details of a specific car in the showroom
void viewSpecificCar() {
    char targetRegistration[10]; // Variable to store the registration of the car to view
    struct LinearNode* current = front; // Pointer to traverse the linked list
        int found = 0; // Flag to indicate if the car with the specified registration number is found

    if (current == NULL) {
        printf("The showroom is empty. No cars to display.\n");
        return;
    }

    // Input the registration of the car to view
    printf("Enter the registration of the car to view: ");
    scanf("%9s", targetRegistration); // Read the registration from the user

    // Search for the car in the showroom
    while (current != NULL) {
        if (strcmp(current->element->registration, targetRegistration) == 0) {
            found = 1;
            printf("Car details:\n");
            printf("Registration: %s\n", current->element->registration);
            printf("Make and Model: %s\n", current->element->makeModel);
            printf("Color: %s\n", current->element->color);
            printf("Owners: %d\n", current->element->prevOwners);
            printf("Reserved: %s\n", current->element->reserved ? "Yes" : "No");
            printf("Reserve Amount: %.2f\n", current->element->reserveAmount);
            printf("Service History: %s\n", current->element->serviceHistory);
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Car with registration number %s not found.\n", targetRegistration);
    }
}

// Function to update service history for a car
void updateServiceHistory() {
    char targetRegistration[10]; // Variable to store the registration of the car to update service history
    struct LinearNode* current = front; // Pointer to traverse the linked list
    int found = 0; // Flag to indicate if the car with the specified registration number is found

    if (current == NULL) {
        printf("The showroom is empty. No cars to update service history.\n");
        return;
    }

    // Input the registration of the car to update service history
    printf("Enter the registration of the car to update service history: ");
    scanf("%9s", targetRegistration); // Read the registration from the user

    // Search for the car in the showroom
    while (current != NULL) {
        if (strcmp(current->element->registration, targetRegistration) == 0) {
            found = 1;
            // Prompt the user to enter the new service entry
            printf("Enter new service entry for car with registration %s: ", targetRegistration);
            scanf("%99s", current->element->serviceHistory); // Read the service history from the user
            printf("Service history updated for car with registration %s.\n", targetRegistration);
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Car with registration number %s not found. Cannot update service history.\n", targetRegistration);
    }
}



