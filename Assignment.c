#define CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // bool type

// list size
#define SIZE 5

// The structure for a car
struct Car {
    char registration[10];
    char makeModel[50];
    char color[20];
    int prevOwners;
    bool reserved;
    float reserveAmount;
    
};

// Structure for one node
struct LinearNode {
    struct Car* element;
    struct LinearNode* next;
}

// Global variables 
struct LinearNode {
    struct LinearNode* front = NULL; //front
    struct LinearNode* last = NULL; //last in list

}

// Function prototypes
void addCar(struct Car showroom[], int *numCars);
void sellCar(struct Car showroom[], int *numCars);
void reserveUnreserveCar(struct Car showroom[], int *numCars);
void viewAllCars(struct Car showroom[], int numCars);
void viewSpecificCar(struct Car showroom[], int numCars);

int main() {
    struct Car showroom[5]; // Maximum capacity for the showroom
    int numCars = 0;        // Number of cars currently in the showroom

    int option;
    do {
        // Display the menu
        printf("\nMenu:\n");
        printf("1. Add a new car to the showroom\n");
        printf("2. Sell a car from the showroom\n");
        printf("3. Reserve/Unreserve a car in the showroom\n");
        printf("4. View all cars in the showroom\n");
        printf("5. View a specific car in the showroom\n");
        printf("6. This should be an appropriate option that you provide\n");
        printf("7. Exit the system\n");

        // Get user input for menu option
        printf("Enter your choice (1-7): ");
        scanf("%d", &option);

        // Execute the corresponding menu option
        switch (option) {
            case 1:
                addCar();
                break;
            case 2:
                //sellCar();
                break;
            case 3:
                //reserveUnreserveCar();
                break;
            case 4:
                viewAllCars();
                break;
            case 5:
                viewSpecificCar();
                break;
            case 6:
                // Add your appropriate option implementation here
                printf("Option 6 selected. Implement your custom functionality.\n");
                break;
            case 7:
                printf("Exiting the system.\n");
                break;
            default:
                printf("Invalid option. Please enter a number between 1 and 7.\n");
        }

    } while (option != 7);

    // You can add more code for other functionalities and testing

    return 0;
}

void addCar() {
    struct LinearNode* aNode;
    struct Car* aCar;

    print("Test\n");

    // Car memory 
    aCar = (struct Car*)malloc(sizeof(struct Car));
    if (aCar == NULL) {
        printf("Error. Car can not be inserted\n")
        return;
    }
       

       //Enter car details
       printf("Enter registration number:");
       scanf("%s", aCar->registration);

       printf("Enter make & model:");
       scanf("%s", aCar->make_model);

       printf("Enter car color:");
       scanf("%s", aCar->color);

       printf("Enter number of previous owners:");
       scanf("%s", aCar->num_previous_owners);

       printf("Is the car reserved? (1 for yes, 2 for no): ");
       scanf("%s", aCar->reserved);

       if (aCar->reserved) {
        printf("Enter car reservation amount:");
        scanf("%f", &aCar->reserve_amount);
       }
       else{
        aCar->reserve_amount = 0.0; // amount = 0 if no reservation
       }

       // Add space for node 
       aNode = (struct LinearNode*)malloc(sizeof(struct LinearNode));
       if(aNode == NULL) {
        printf("Error. Node can not be inserted\n");
        free(aCar);
        return;
       }

       // Add car to new node
       aNode->element = aCar;
       aNode->next = NULL;

       // Add node to list
       if (isEmpty()) {
        front = aNode;
        last = aNode;
       }
       else {
        aNode->next = front;
        front = aNode;
       }
}

// Function to view all cars in the showroom
void viewAllCars(struct Car showroom[], int numCars) {
    if (numCars == 0) {
        printf("The showroom is empty. No cars to display.\n");
        return;
    }

    printf("All cars in the showroom:\n");
    for (int i = 0; i < numCars; i++) {
        printf("Registration: %s, Make and Model: %s, Color: %s, Owners: %d, Reserved: %s, Reserve Amount: %.2f\n",
               showroom[i].registration, showroom[i].makeModel, showroom[i].color, showroom[i].prevOwners,
               showroom[i].reserved ? "Yes" : "No", showroom[i].reserveAmount);
    }
}

// Function to view a specific car in the showroom
void viewSpecificCar(struct Car showroom[], int numCars) {
    if (numCars == 0) {
        printf("The showroom is empty. No cars to display.\n");
        return;
    }

    char targetRegistration[10];
    int found = 0;

    // Input the registration of the car to view
    printf("Enter the registration of the car to view: ");
    scanf("%s", targetRegistration);

    // Search for the car in the showroom
    for (int i = 0; i < numCars; i++) {
        if (strcmp(showroom[i].registration, targetRegistration) == 0) {
            printf("Car details:\n");
            printf("Registration: %s, Make and Model: %s, Color: %s, Owners: %d, Reserved: %s, Reserve Amount: %.2f\n",
                   showroom[i].registration, showroom[i].makeModel, showroom[i].color, showroom[i].prevOwners,
                   showroom[i].reserved ? "Yes" : "No", showroom[i].reserveAmount);
            found = 1;
            break; // Exit the loop after processing the car
        }
    }

    if (!found) {
        printf("Error: Car not found. Cannot view.\n");
    }
}


int main() {
    // ...

    int option;
    do {
    
    menu();

    } while (option != 7);

    // ...
}

// Implementation of the custom functionality
void customFunction() {
    printf("Executing the custom functionality. You can define your own behavior here!\n");
}

