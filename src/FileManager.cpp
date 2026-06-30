#include "../include/FileManager.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void saveRoomsToFile(RoomList &list, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open " << filename << " for writing.\n";
        return;
    }
    file << "roomNumber,type,price,isAvailable,guestName\n";
    RoomElement *cur = list.head;
    while (cur != nullptr) {
        file << cur->data.roomNumber << ","
             << cur->data.type << ","
             << cur->data.price << ","
             << cur->data.isAvailable << ","
             << cur->data.guestName << "\n";
        cur = cur->next;
    }
    file.close();
}

void loadRoomsFromFile(RoomList &list, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    { char header[256]; file.getline(header, 256); }
    int num;
    char type[20], guest[50];
    double price;
    bool avail;
    char comma;

    while (file >> num >> comma) {
        file.getline(type, 20, ',');
        file >> price >> comma;
        file >> avail >> comma;
        file.getline(guest, 50);
        RoomElement *e = createRoom(num, type, price);
        e->data.isAvailable = avail;
        strcpy(e->data.guestName, guest);
        addRoomBack(list, e);
    }
    file.close();
}

void saveGuestsToFile(GuestTable &gt, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open " << filename << " for writing.\n";
        return;
    }
    file << "roomNumber,name,id,checkIn,checkOut\n";
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (gt.table[i].status == OCCUPIED || gt.table[i].status == DELETED) {
            file << gt.table[i].roomNumber << ","
                 << gt.table[i].name << ","
                 << gt.table[i].id << ","
                 << gt.table[i].checkIn << ","
                 << gt.table[i].checkOut << "\n";
        }
    }
    file.close();
}

void loadGuestsFromFile(GuestTable &gt, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    { char header[256]; file.getline(header, 256); }
    int rn;
    char name[50], id[20], checkIn[15], checkOut[15], comma;
    while (file >> rn >> comma) {
        file.getline(name, 50, ',');
        file.getline(id, 20, ',');
        file.getline(checkIn, 15, ',');
        file.getline(checkOut, 15);
        if (strlen(checkOut) > 0) {
            guestCheckOut(gt, rn);
            Guest *g = searchGuest(gt, rn);
            if (g) strcpy(g->checkOut, checkOut);
        } else {
            guestCheckIn(gt, rn, name, id, checkIn);
        }
    }
    file.close();
}

void saveReservationsToFile(ReservationQueue &q, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open " << filename << " for writing.\n";
        return;
    }
    file << "id,guestName,contact,roomType,date\n";
    int idx = q.front;
    for (int i = 0; i < q.count; i++) {
        file << q.items[idx].id << ","
             << q.items[idx].guestName << ","
             << q.items[idx].contact << ","
             << q.items[idx].roomType << ","
             << q.items[idx].date << "\n";
        idx = (idx + 1) % MAX_QUEUE;
    }
    file.close();
}

void loadReservationsFromFile(ReservationQueue &q, const char* filename, int &nextId) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    { char header[256]; file.getline(header, 256); }
    int id, rtype, maxId = 0;
    char name[50], contact[20], date[15], comma;
    while (file >> id >> comma) {
        file.getline(name, 50, ',');
        file.getline(contact, 20, ',');
        file >> rtype >> comma;
        file.getline(date, 15);
        Reservation r;
        r.id = id;
        strcpy(r.guestName, name);
        strcpy(r.contact, contact);
        r.roomType = rtype;
        strcpy(r.date, date);
        enqueue(q, r);
        if (id > maxId) maxId = id;
    }
    if (maxId >= nextId) nextId = maxId + 1;
    file.close();
}
