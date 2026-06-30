#ifndef SORTING_H
#define SORTING_H

#include "Room.h"

void bubbleSortByPrice(Room arr[], int n);
void selectionSortByRoomNumber(Room arr[], int n);
void insertionSortByPrice(Room arr[], int n);
void mergeSortByPrice(Room arr[], int left, int right);
void quickSortByRoomNumber(Room arr[], int low, int high);

void copyListToArray(RoomList &list, Room arr[], int &n);
void displaySortedRooms(Room arr[], int n);

#endif
