#ifndef RESERVATION_H
#define RESERVATION_H

const int MAX_QUEUE = 100;

struct Reservation {
    int id;
    char guestName[50];
    char contact[20];
    int roomType; // 1=Single, 2=Double, 3=Suite
    char date[15];
};

struct ReservationQueue {
    Reservation items[MAX_QUEUE];
    int front;
    int rear;
    int count;
};

void initQueue(ReservationQueue &q);
bool isQueueEmpty(ReservationQueue &q);
bool isQueueFull(ReservationQueue &q);
void enqueue(ReservationQueue &q, Reservation r);
Reservation dequeue(ReservationQueue &q);
Reservation peekFront(ReservationQueue &q);
void displayQueue(ReservationQueue &q);
int queueSize(ReservationQueue &q);

#endif
