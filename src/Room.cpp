#include "../include/Room.h"
#include <iostream>
#include <cstring>
using namespace std;

void initRoomList(RoomList &list) {
    list.head = nullptr;
    list.tail = nullptr;
    list.n = 0;
}

RoomElement* createRoom(int number, const char* type, double price) {
    RoomElement *e = new RoomElement;
    e->data.roomNumber = number;
    strcpy(e->data.type, type);
    e->data.price = price;
    e->data.isAvailable = true;
    e->data.guestName[0] = '\0';
    e->next = nullptr;
    e->prev = nullptr;
    return e;
}

void addRoomFront(RoomList &list, RoomElement *e) {
    if (list.n == 0) {
        list.head = e;
        list.tail = e;
    } else {
        e->next = list.head;
        list.head->prev = e;
        list.head = e;
    }
    list.n++;
}

void addRoomBack(RoomList &list, RoomElement *e) {
    if (list.n == 0) {
        list.head = e;
        list.tail = e;
    } else {
        e->prev = list.tail;
        list.tail->next = e;
        list.tail = e;
    }
    list.n++;
}

void addRoomAt(RoomList &list, RoomElement *e, int pos) {
    if (pos < 0 || pos > list.n) {
        cout << "Invalid position!\n";
        delete e;
        return;
    }
    if (pos == 0) {
        addRoomFront(list, e);
        return;
    }
    if (pos == list.n) {
        addRoomBack(list, e);
        return;
    }
    RoomElement *cur = list.head;
    for (int i = 0; i < pos; i++) {
        cur = cur->next;
    }
    e->next = cur;
    e->prev = cur->prev;
    cur->prev->next = e;
    cur->prev = e;
    list.n++;
}

void deleteRoomFront(RoomList &list) {
    if (list.n == 0) {
        cout << "No rooms to delete.\n";
        return;
    }
    RoomElement *temp = list.head;
    if (list.n == 1) {
        list.head = nullptr;
        list.tail = nullptr;
    } else {
        list.head = list.head->next;
        list.head->prev = nullptr;
    }
    delete temp;
    list.n--;
    cout << "Room deleted from front.\n";
}

void deleteRoomBack(RoomList &list) {
    if (list.n == 0) {
        cout << "No rooms to delete.\n";
        return;
    }
    RoomElement *temp = list.tail;
    if (list.n == 1) {
        list.head = nullptr;
        list.tail = nullptr;
    } else {
        list.tail = list.tail->prev;
        list.tail->next = nullptr;
    }
    delete temp;
    list.n--;
    cout << "Room deleted from back.\n";
}

void deleteRoomAt(RoomList &list, int pos) {
    if (list.n == 0 || pos < 0 || pos >= list.n) {
        cout << "Invalid position!\n";
        return;
    }
    if (pos == 0) {
        deleteRoomFront(list);
        return;
    }
    if (pos == list.n - 1) {
        deleteRoomBack(list);
        return;
    }
    RoomElement *cur = list.head;
    for (int i = 0; i < pos; i++) {
        cur = cur->next;
    }
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    list.n--;
    cout << "Room deleted at position " << pos << ".\n";
}

void deleteRoomByNumber(RoomList &list, int roomNumber) {
    RoomElement *cur = list.head;
    int pos = 0;
    while (cur != nullptr) {
        if (cur->data.roomNumber == roomNumber) {
            deleteRoomAt(list, pos);
            return;
        }
        cur = cur->next;
        pos++;
    }
    cout << "Room " << roomNumber << " not found.\n";
}

RoomElement* searchRoomByNumber(RoomList &list, int roomNumber) {
    RoomElement *cur = list.head;
    while (cur != nullptr) {
        if (cur->data.roomNumber == roomNumber) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

void updateRoomStatus(RoomList &list, int roomNumber, bool available, const char* guestName) {
    RoomElement *e = searchRoomByNumber(list, roomNumber);
    if (e == nullptr) {
        cout << "Room " << roomNumber << " not found.\n";
        return;
    }
    e->data.isAvailable = available;
    if (available) {
        e->data.guestName[0] = '\0';
    } else {
        strcpy(e->data.guestName, guestName);
    }
}

void displayAllRooms(RoomList &list) {
    if (list.n == 0) {
        cout << "No rooms available.\n";
        return;
    }
    cout << "\n=== ALL ROOMS ===\n";
    cout << "RN\tType\t\tPrice\tStatus\tGuest\n";
    cout << "----------------------------------------\n";
    RoomElement *cur = list.head;
    while (cur != nullptr) {
        cout << cur->data.roomNumber << "\t" << cur->data.type
             << "\t\t$" << cur->data.price
             << "\t" << (cur->data.isAvailable ? "Avail" : "Booked")
             << "\t" << cur->data.guestName << "\n";
        cur = cur->next;
    }
    cout << "Total: " << list.n << " rooms\n";
}

void displayAvailableRooms(RoomList &list) {
    int count = 0;
    RoomElement *cur = list.head;
    cout << "\n=== AVAILABLE ROOMS ===\n";
    while (cur != nullptr) {
        if (cur->data.isAvailable) {
            cout << "Room " << cur->data.roomNumber << " (" << cur->data.type << ") - $"
                 << cur->data.price << "\n";
            count++;
        }
        cur = cur->next;
    }
    if (count == 0) cout << "No available rooms.\n";
}

void freeRoomList(RoomList &list) {
    while (list.head != nullptr) {
        deleteRoomFront(list);
    }
}

int countRooms(RoomList &list) {
    return list.n;
}
