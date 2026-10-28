#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
using namespace std;

#define total_seats 30

struct node {
    int seatno;
    string name;
    int age;
    char gender;
    struct node *next;
};

struct node *start = NULL, *ptr;
int *seat;

void displaymenu();
void bookticket();
void cancelticket();
void trainstatus();
void passengerlist();
void freememory();

int main() {
    seat = (int*)malloc(total_seats * sizeof(int));

    if (seat == NULL) {
        cout << "Memory allocation failed";
        return 1;
    }

    for (int i = 0; i < total_seats; i++) {
        seat[i] = 0;
    }

    int choice;

   
                freememory();
                cout << "Thank you for using Railway Reservation System.\n";
                break;
            default:
                cout << "Invalid choice. Please select 1 to 5.\n";
        } do {
        displaymenu();
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                bookticket();
                break;
            case 2:
                cancelticket();
                break;
            case 3:
                trainstatus();
                break;
            case 4:
                passengerlist();
                break;
            case 5:
    } while (choice != 5);

    return 0;
}

void displaymenu() {
    cout << "\n===== RAILWAY RESERVATION SYSTEM =====\n";
    cout << "1. Book Ticket\n";
    cout << "2. Cancel Ticket\n";
    cout << "3. View Train Status\n";
    cout << "4. View Passenger List\n";
    cout << "5. Exit\n";
}

void bookticket() {
    int i, seatno = -1;

    for (i = 0; i < total_seats; i++) {
        if (seat[i] == 0) {
            seatno = i + 1;
            break;
        }
    }

    if (seatno == -1) {
        cout << "All seats are booked. No seat available.\n";
        return;
    }

    string name;
    int age;
    char gender;

    cout << "Enter passenger name: ";
    getline(cin, name);

    cout << "Enter age: ";
    while (!(cin >> age) || age <= 0) {
        cout << "Enter age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter gender (M/F/OTH): ";
    cin >> gender;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    struct node *newnode = new node;
    newnode->seatno = seatno;
    newnode->name = name;
    newnode->age = age;
    newnode->gender = gender;
    newnode->next = NULL;

    if (start == NULL) {
        start = newnode;
    } else {
        ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newnode;
    }

    seat[seatno - 1] = 1;
    cout << "Ticket booked successfully! Seat No: " << seatno << "\n";
}

void cancelticket() {
    int seatno;
    cout << "Enter seat number to cancel (1-" << total_seats << "): ";

    if (!(cin >> seatno)) {
        cout << "Invalid seat number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (seatno < 1 || seatno > total_seats) {
        cout << "Invalid seat number.\n";
        return;
    }

    ptr = start;
    struct node *prev = NULL;

    while (ptr != NULL && ptr->seatno != seatno) {
        prev = ptr;
        ptr = ptr->next;
    }

    if (ptr == NULL) {
        cout << "This seat is not booked.\n";
        return;
    }

    if (prev == NULL) {
        start = ptr->next;
    } else {
        prev->next = ptr->next;
    }

    delete ptr;
    seat[seatno - 1] = 0;
    cout << "Ticket cancelled successfully. Seat " << seatno << " is now available.\n";
}

void trainstatus() {
    cout << "\n===== TRAIN STATUS =====\n";
    for (int i = 0; i < total_seats; i++) {
        cout << "Seat " << i + 1 << ": ";
        if (seat[i] == 0) {
            cout << "Available\n";
        } else {
            cout << "Booked\n";
        }
    }
}

void passengerlist() {
    cout << "\n===== PASSENGER LIST =====\n";

    if (start == NULL) {
        cout << "No passengers booked.\n";
        return;
    }

    ptr = start;
    while (ptr != NULL) {
        cout << "Seat No: " << ptr->seatno
             << " | Name: " << ptr->name
             << " | Age: " << ptr->age
             << " | Gender: " << ptr->gender << "\n";
        ptr = ptr->next;
    }
}

void freememory() {
    cout << "Releasing memories...\n";
    ptr = start;

    while (ptr != NULL) {
        struct node *nextnode = ptr->next;
        delete ptr;
        ptr = nextnode;
    }

    start = NULL;
    free(seat);
    seat = NULL;
    cout << "All allocated memory freed.\n";
}
