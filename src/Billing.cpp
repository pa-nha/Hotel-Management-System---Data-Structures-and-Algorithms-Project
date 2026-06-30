#include "../include/Billing.h"
#include <iostream>
#include <cstring>
using namespace std;

void initStack(BillStack &s) {
    s.top = -1;
}

bool isStackEmpty(BillStack &s) {
    return s.top == -1;
}

bool isStackFull(BillStack &s) {
    return s.top == MAX_STACK - 1;
}

void pushCharge(BillStack &s, int roomNumber, const char* desc, double amount) {
    if (isStackFull(s)) {
        cout << "Bill stack is full.\n";
        return;
    }
    s.top++;
    s.items[s.top].roomNumber = roomNumber;
    strcpy(s.items[s.top].description, desc);
    s.items[s.top].amount = amount;
    cout << "Charge added: " << desc << " - $" << amount << "\n";
}

Charge popCharge(BillStack &s) {
    if (isStackEmpty(s)) {
        cout << "No charges in bill.\n";
        Charge empty = {0, "", 0};
        return empty;
    }
    Charge c = s.items[s.top];
    s.top--;
    return c;
}

Charge peekCharge(BillStack &s) {
    if (isStackEmpty(s)) {
        cout << "No charges in bill.\n";
        Charge empty = {0, "", 0};
        return empty;
    }
    return s.items[s.top];
}

void displayBill(BillStack &s) {
    if (isStackEmpty(s)) {
        cout << "No charges on this bill.\n";
        return;
    }
    cout << "\n=== ALL CHARGES (Most Recent First) ===\n";
    cout << "Room\tDescription\t\t\tAmount\n";
    cout << "----------------------------------------\n";
    for (int i = s.top; i >= 0; i--) {
        cout << "[" << s.items[i].roomNumber << "]\t" << s.items[i].description << "\t\t\t$" << s.items[i].amount << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "TOTAL:\t\t\t\t\t$" << calculateTotal(s) << "\n";
}

void displayBillForRoom(BillStack &s, int roomNumber) {
    bool hasCharges = false;
    cout << "\n=== INVOICE FOR ROOM " << roomNumber << " ===\n";
    cout << "Description\t\t\tAmount\n";
    cout << "----------------------------------------\n";
    for (int i = s.top; i >= 0; i--) {
        if (s.items[i].roomNumber == roomNumber) {
            cout << s.items[i].description << "\t\t$" << s.items[i].amount << "\n";
            hasCharges = true;
        }
    }
    if (!hasCharges) {
        cout << "No charges for this room.\n";
        return;
    }
    cout << "----------------------------------------\n";
    cout << "TOTAL:\t\t\t\t$" << calculateTotalForRoom(s, roomNumber) << "\n";
}

double calculateTotal(BillStack &s) {
    double total = 0;
    for (int i = 0; i <= s.top; i++) {
        total += s.items[i].amount;
    }
    return total;
}

double calculateTotalForRoom(BillStack &s, int roomNumber) {
    double total = 0;
    for (int i = 0; i <= s.top; i++) {
        if (s.items[i].roomNumber == roomNumber)
            total += s.items[i].amount;
    }
    return total;
}

void clearBill(BillStack &s) {
    s.top = -1;
    cout << "Bill cleared.\n";
}
