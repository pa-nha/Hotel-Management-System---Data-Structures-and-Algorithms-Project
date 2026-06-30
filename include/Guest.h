#ifndef GUEST_H
#define GUEST_H

const int TABLE_SIZE = 100;

const int EMPTY = 0;
const int OCCUPIED = 1;
const int DELETED = 2;

struct Guest {
    int roomNumber;
    char name[50];
    char id[20];
    char checkIn[15];
    char checkOut[15];
    int status; //0=EMPTY,1=OCCUPIED,2=DELETED
};

struct GuestTable {
    Guest table[TABLE_SIZE];
};

int hashFunction(int roomNumber);
void initGuestTable(GuestTable &gt);
bool guestCheckIn(GuestTable &gt, int roomNumber, const char* name, const char* id, const char* checkIn);
bool guestCheckOut(GuestTable &gt, int roomNumber);
Guest* searchGuest(GuestTable &gt, int roomNumber);
void displayAllGuests(GuestTable &gt);
int countGuests(GuestTable &gt);

#endif
