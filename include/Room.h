#ifndef ROOM_H
#define ROOM_H

#include <cstring>

struct Room {
    int roomNumber;
    char type[20];
    double price;
    bool isAvailable;
    char guestName[50];
};

struct RoomElement {
    Room data;
    RoomElement *next;
    RoomElement *prev;
};

struct RoomList {
    RoomElement *head;
    RoomElement *tail;
    int n;
};

void initRoomList(RoomList &list);
RoomElement* createRoom(int number, const char* type, double price);
void addRoomFront(RoomList &list, RoomElement *e);
void addRoomBack(RoomList &list, RoomElement *e);
void addRoomAt(RoomList &list, RoomElement *e, int pos);
void deleteRoomFront(RoomList &list);
void deleteRoomBack(RoomList &list);
void deleteRoomAt(RoomList &list, int pos);
void deleteRoomByNumber(RoomList &list, int roomNumber);
RoomElement* searchRoomByNumber(RoomList &list, int roomNumber);
void updateRoomStatus(RoomList &list, int roomNumber, bool available, const char* guestName);
void displayAllRooms(RoomList &list);
void displayAvailableRooms(RoomList &list);
void freeRoomList(RoomList &list);
int countRooms(RoomList &list);

#endif
