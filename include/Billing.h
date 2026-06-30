#ifndef BILLING_H
#define BILLING_H

const int MAX_STACK = 100;

struct Charge {
    int roomNumber;
    char description[50];
    double amount;
};

struct BillStack {
    Charge items[MAX_STACK];
    int top;
};

void initStack(BillStack &s);
bool isStackEmpty(BillStack &s);
bool isStackFull(BillStack &s);
void pushCharge(BillStack &s, int roomNumber, const char* desc, double amount);
Charge popCharge(BillStack &s);
Charge peekCharge(BillStack &s);
void displayBill(BillStack &s);
void displayBillForRoom(BillStack &s, int roomNumber);
double calculateTotal(BillStack &s);
double calculateTotalForRoom(BillStack &s, int roomNumber);
void clearBill(BillStack &s);

#endif
