#include "../include/Reservation.h"
#include <iostream>
#include <cstring>
using namespace std;

void initQueue(ReservationQueue &q) {
    q.front = 0;
    q.rear = -1;
    q.count = 0;
}

bool isQueueEmpty(ReservationQueue &q) {
    return q.count == 0;
}

bool isQueueFull(ReservationQueue &q) {
    return q.count == MAX_QUEUE;
}

void enqueue(ReservationQueue &q, Reservation r) {
    if (isQueueFull(q)) {
        cout << "Reservation queue is full.\n";
        return;
    }
    q.rear = (q.rear + 1) % MAX_QUEUE;
    q.items[q.rear] = r;
    q.count++;
}

Reservation dequeue(ReservationQueue &q) {
    if (isQueueEmpty(q)) {
        cout << "No reservations in queue.\n";
        Reservation empty = {0, "", "", 0, ""};
        return empty;
    }
    Reservation r = q.items[q.front];
    q.front = (q.front + 1) % MAX_QUEUE;
    q.count--;
    return r;
}

Reservation peekFront(ReservationQueue &q) {
    if (isQueueEmpty(q)) {
        cout << "No reservations in queue.\n";
        Reservation empty = {0, "", "", 0, ""};
        return empty;
    }
    return q.items[q.front];
}

void displayQueue(ReservationQueue &q) {
    if (isQueueEmpty(q)) {
        cout << "No reservations in queue.\n";
        return;
    }
    cout << "\n=== RESERVATION QUEUE ===\n";
    cout << "ID\tGuest\t\tRoom Type\tDate\n";
    cout << "----------------------------------------\n";
    int idx = q.front;
    for (int i = 0; i < q.count; i++) {
        cout << q.items[idx].id << "\t" << q.items[idx].guestName
             << "\t\t" << (q.items[idx].roomType == 1 ? "Single" :
                           q.items[idx].roomType == 2 ? "Double" :
                           q.items[idx].roomType == 3 ? "Suite" : "Unknown")
             << "\t\t" << q.items[idx].date << "\n";
        idx = (idx + 1) % MAX_QUEUE;
    }
    cout << "Total reservations: " << q.count << "\n";
}

int queueSize(ReservationQueue &q) {
    return q.count;
}
