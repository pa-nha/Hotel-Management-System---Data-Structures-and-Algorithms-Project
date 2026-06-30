#include "../include/Sorting.h"
#include <iostream>
using namespace std;
// using Bubble Sort
void bubbleSortByPrice(Room arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                Room temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    cout << "Sorted by price.\n";
}
// using Selection Sort
void selectionSortByRoomNumber(Room arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].roomNumber < arr[minIdx].roomNumber) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Room temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
    cout << "Sorted by room number.\n";
}
// using Insertion Sort
void insertionSortByPrice(Room arr[], int n) {
    for (int i = 1; i < n; i++) {
        Room key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].price > key.price) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    cout << "Sorted by price.\n";
}

void Merge(Room a[], int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    Room b[n];

    while (i <= mid && j <= ub) {
        if (a[i].price < a[j].price) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }

    while (i <= mid) {
        b[k++] = a[i++];
    }

    while (j <= ub) {
        b[k++] = a[j++];
    }

    for (k = 0; k < n; k++) {
        a[lb + k] = b[k];
    }
}

void mergeSortByPrice(Room arr[], int lb, int ub) {
    if (lb < ub) {
        int mid = (lb + ub) / 2;
        mergeSortByPrice(arr, lb, mid);
        mergeSortByPrice(arr, mid + 1, ub);
        Merge(arr, lb, mid, ub);
    }
}

int Partition(Room a[], int lb, int ub) {
    int pivot = a[lb].roomNumber;
    int start = lb;
    int end = ub;

    while (start < end) {
        while (a[start].roomNumber <= pivot && start <= ub) {
            start++;
        }
        while (a[end].roomNumber > pivot && end >= lb) {
            end--;
        }
        if (start < end) {
            Room temp = a[start];
            a[start] = a[end];
            a[end] = temp;
        }
    }

    Room temp = a[lb];
    a[lb] = a[end];
    a[end] = temp;
    return end;
}

void quickSortByRoomNumber(Room arr[], int lb, int ub) {
    if (lb < ub) {
        int pos = Partition(arr, lb, ub);
        quickSortByRoomNumber(arr, lb, pos - 1);
        quickSortByRoomNumber(arr, pos + 1, ub);
    }
}

void copyListToArray(RoomList &list, Room arr[], int &n) {
    n = 0;
    RoomElement *cur = list.head;
    while (cur != nullptr && n < 200) {
        arr[n] = cur->data;
        n++;
        cur = cur->next;
    }
}

void displaySortedRooms(Room arr[], int n) {
    if (n == 0) {
        cout << "No rooms to display.\n";
        return;
    }
    cout << "\n=== SORTED ROOMS ===\n";
    cout << "RN\tType\t\tPrice\tStatus\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i].roomNumber << "\t" << arr[i].type
             << "\t\t$" << arr[i].price
             << "\t" << (arr[i].isAvailable ? "Avail" : "Booked") << "\n";
    }
}
