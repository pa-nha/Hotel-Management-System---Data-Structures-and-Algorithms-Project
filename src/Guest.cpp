#include "../include/Guest.h"
#include <iostream>
#include <cstring>
using namespace std;

int hashFunction(int roomNumber) {
    return roomNumber % TABLE_SIZE;
}

void initGuestTable(GuestTable &gt) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        gt.table[i].status = EMPTY;
    }
}

bool guestCheckIn(GuestTable &gt, int roomNumber, const char* name, const char* id, const char* checkIn) {
    int index = hashFunction(roomNumber);
    int start = index;

    while (gt.table[index].status == OCCUPIED) {
        if (gt.table[index].roomNumber == roomNumber) {
            cout << "Room " << roomNumber << " is already occupied.\n";
            return false;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) {
            cout << "Guest table is full.\n";
            return false;
        }
    }
    gt.table[index].roomNumber = roomNumber;
    strcpy(gt.table[index].name, name);
    strcpy(gt.table[index].id, id);
    strcpy(gt.table[index].checkIn, checkIn);
    gt.table[index].checkOut[0] = '\0';
    gt.table[index].status = OCCUPIED;
    return true;
}

bool guestCheckOut(GuestTable &gt, int roomNumber) {
    int index = hashFunction(roomNumber);
    int start = index;

    while (gt.table[index].status != EMPTY) {
        if (gt.table[index].roomNumber == roomNumber) {
            gt.table[index].status = DELETED;
            return true;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) break;
    }
    cout << "Guest in room " << roomNumber << " not found.\n";
    return false;
}

Guest* searchGuest(GuestTable &gt, int roomNumber) {
    int index = hashFunction(roomNumber);
    int start = index;

    while (gt.table[index].status != EMPTY) {
        if (gt.table[index].status == OCCUPIED && gt.table[index].roomNumber == roomNumber) {
            return &gt.table[index];
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start) break;
    }
    return nullptr;
}

void displayAllGuests(GuestTable &gt) {
    cout << "\n=== CURRENT GUESTS ===\n";
    bool found = false;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (gt.table[i].status == OCCUPIED) {
            cout << "Room " << gt.table[i].roomNumber
                 << " | " << gt.table[i].name
                 << " | ID: " << gt.table[i].id
                 << " | In: " << gt.table[i].checkIn << "\n";
            found = true;
        }
    }
    if (!found) cout << "No guests currently checked in.\n";
}

int countGuests(GuestTable &gt) {
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (gt.table[i].status == OCCUPIED) count++;
    }
    return count;
}
