#include "../include/HotelManager.h"
#include "../include/Sorting.h"
#include "../include/FileManager.h"
#include <iostream>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

int parseDateToDays(const char* date) {
    int d, m, y;
    sscanf(date, "%d/%d/%d", &d, &m, &y);
    struct tm tm = {};
    tm.tm_mday = d;
    tm.tm_mon = m - 1;
    tm.tm_year = y - 1900;
    return (int)difftime(mktime(&tm), 0) / 86400;
}

int calculateNights(const char* checkIn, const char* checkOut) {
    int days = parseDateToDays(checkOut) - parseDateToDays(checkIn);
    return days > 0 ? days : 1;
}

void initHotel(HotelManager &hotel) {
    initRoomList(hotel.rooms);
    initGuestTable(hotel.guests);
    initQueue(hotel.reservations);
    initStack(hotel.bills);
    initHotelTree(hotel.hotelMap);
    hotel.nextReservationId = 1;
}

void loadAllData(HotelManager &hotel) {
    loadRoomsFromFile(hotel.rooms, "data/rooms.csv");
    loadGuestsFromFile(hotel.guests, "data/guests.csv");
    loadReservationsFromFile(hotel.reservations, "data/reservations.csv", hotel.nextReservationId);
}

void saveAllData(HotelManager &hotel) {
    saveRoomsToFile(hotel.rooms, "data/rooms.csv");
    saveGuestsToFile(hotel.guests, "data/guests.csv");
    saveReservationsToFile(hotel.reservations, "data/reservations.csv");
}

void roomManagementMenu(HotelManager &hotel) {
    int choice;
    do {
        system("cls");
        cout << "\n===== ROOM MANAGEMENT =====\n";
        cout << "1. Add Room (Front)\n";
        cout << "2. Add Room (Back)\n";
        cout << "3. Add Room at Position\n";
        cout << "4. Delete Room by Number\n";
        cout << "5. Display All Rooms\n";
        cout << "6. Display Available Rooms\n";
        cout << "7. Search Room by Number\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int num; char type[20]; double price;
            cout << "Room Number: "; cin >> num;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Type (Single/Double/Suite): "; cin.getline(type, 20);
            cout << "Price: "; cin >> price;
            RoomElement *e = createRoom(num, type, price);
            addRoomFront(hotel.rooms, e);
            cout << "Room added to front.\n";
        } else if (choice == 2) {
            int num; char type[20]; double price;
            cout << "Room Number: "; cin >> num;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Type (Single/Double/Suite): "; cin.getline(type, 20);
            cout << "Price: "; cin >> price;
            RoomElement *e = createRoom(num, type, price);
            addRoomBack(hotel.rooms, e);
            cout << "Room added to back.\n";
        } else if (choice == 3) {
            int num, pos; char type[20]; double price;
            cout << "Room Number: "; cin >> num;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Type (Single/Double/Suite): "; cin.getline(type, 20);
            cout << "Price: "; cin >> price;
            cout << "Position: "; cin >> pos;
            RoomElement *e = createRoom(num, type, price);
            addRoomAt(hotel.rooms, e, pos);
        } else if (choice == 4) {
            int num;
            cout << "Room Number to delete: "; cin >> num;
            deleteRoomByNumber(hotel.rooms, num);
        } else if (choice == 5) {
            displayAllRooms(hotel.rooms);
        } else if (choice == 6) {
            displayAvailableRooms(hotel.rooms);
        } else if (choice == 7) {
            int num;
            cout << "Room Number: "; cin >> num;
            RoomElement *e = searchRoomByNumber(hotel.rooms, num);
            if (e) {
                cout << "Room " << e->data.roomNumber << " (" << e->data.type
                     << ") - $" << e->data.price
                     << " - " << (e->data.isAvailable ? "Available" : "Booked by " + string(e->data.guestName)) << "\n";
            } else {
                cout << "Room not found.\n";
            }
        }
        if (choice != 0) system("pause");
    } while (choice != 0);
}

void checkInMenu(HotelManager &hotel) {
    system("cls");
    int roomNum;
    char name[50], id[20], date[15];

    displayAvailableRooms(hotel.rooms);

    cout<<"\nEnter room number: ";
    cin>>roomNum;
    cin.clear();
    cin.ignore(1000, '\n');
    cout<<"Guest name: "; cin.getline(name, 50);
    cout<<"Guest ID: "; cin.getline(id, 20);
    cout<<"Check-in date (DD/MM/YYYY): "; cin.getline(date, 15);

    RoomElement *room = searchRoomByNumber(hotel.rooms, roomNum);
    if (room == nullptr) {
        cout<<"Room not found.\n";
        return;
    }
    if (!room->data.isAvailable) {
        cout<<"Room is already booked.\n";
        return;
    }
    if (guestCheckIn(hotel.guests, roomNum, name, id, date)) {
        updateRoomStatus(hotel.rooms, roomNum, false, name);
        cout<<"Check-in successful for "<<name<<" in Room "<<roomNum<<".\n";
        cout<<"Rate: $" << room->data.price<<"/night\n";
    }
    system("pause");
}

void checkOutMenu(HotelManager &hotel) {
    system("cls");
    int roomNum;
    cout<<"Enter room number for check-out: ";
    cin>>roomNum;

    Guest *g = searchGuest(hotel.guests, roomNum);
    if (g == nullptr) {
        cout<<"No guest found in room "<<roomNum<<".\n";
        return;
    }

    cout<<"\nGuest: "<<g->name<<"\n";
    cout<<"Check-in: "<<g->checkIn<<"\n";

    char date[15];
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Check-out date (DD/MM/YYYY): ";
    cin.getline(date, 15);
    strcpy(g->checkOut, date);

    if (guestCheckOut(hotel.guests, roomNum)) {
        int nights = calculateNights(g->checkIn, date);
        RoomElement *room = searchRoomByNumber(hotel.rooms, roomNum);
        double totalRoomCost = room ? room->data.price * nights : 0;
        char desc[60];
        strcpy(desc, (string("Room ") +to_string(roomNum)+" (" + to_string(nights)+" night"+(nights>1 ? "s":"")+")").c_str());
        pushCharge(hotel.bills, roomNum, desc, totalRoomCost);

        updateRoomStatus(hotel.rooms, roomNum, true, "");
        cout << "Check-out successful for Room " << roomNum << ".\n";
        cout << "\n--- FINAL INVOICE ---\n";
        displayBillForRoom(hotel.bills, roomNum);
    }
    system("pause");
}

void reservationMenu(HotelManager &hotel) {
    int choice;
    do {
        system("cls");
        cout << "\n===== RESERVATIONS =====\n";
        cout << "1. Add Reservation\n";
        cout << "2. Process Next Reservation\n";
        cout << "3. View Next Reservation\n";
        cout << "4. Display All Reservations\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Reservation r = {};
            r.id = hotel.nextReservationId++;
            cout << "Guest Name: "; cin.getline(r.guestName, 50);
            cout << "Contact: "; cin.getline(r.contact, 20);
            do {
                cout << "Room Type (1=Single, 2=Double, 3=Suite): "; cin >> r.roomType;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (r.roomType < 1 || r.roomType > 3)
                    cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            } while (r.roomType < 1 || r.roomType > 3);
            cout << "Check-in Date (DD/MM/YYYY): "; cin.getline(r.date, 15);
            enqueue(hotel.reservations, r);
            cout << "Reservation #" << r.id << " added to queue.\n";
        } else if (choice == 2) {
            Reservation r = dequeue(hotel.reservations);
            if (r.id != 0) {
                cout << "Processing reservation for " << r.guestName << " (" << r.date << ")\n";
                cout << "Please assign a room manually from Room Management.\n";
            }
        } else if (choice == 3) {
            Reservation r = peekFront(hotel.reservations);
            if (r.id != 0) {
                cout << "Next: " << r.guestName << " - "
                     << (r.roomType == 1 ? "Single" : r.roomType == 2 ? "Double" : r.roomType == 3 ? "Suite" : "Unknown")
                     << " - " << r.date << "\n";
            }
        } else if (choice == 4) {
            displayQueue(hotel.reservations);
        }
        if (choice != 0) system("pause");
    } while (choice != 0);
}

void billingMenu(HotelManager &hotel) {
    int choice;
    do {
        system("cls");
        cout << "\n===== BILLING / INVOICE =====\n";
        cout << "1. Add Charge\n";
        cout << "2. Remove Last Charge\n";
        cout << "3. View Last Charge\n";
        cout << "4. Display Full Invoice\n";
        cout << "5. Clear Bill\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "\n--- Currently Occupied Rooms ---\n";
            RoomElement *curr = hotel.rooms.head;
            bool hasOccupied = false;
            while (curr) {
                if (!curr->data.isAvailable) {
                    cout << "Room " << curr->data.roomNumber << " - " << curr->data.guestName << "\n";
                    hasOccupied = true;
                }
                curr = curr->next;
            }
            if (!hasOccupied) cout << "(none)\n";

            int roomNum; char desc[1000]; double amt;
            cout << "\nRoom Number: "; cin >> roomNum;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Charge Description: "; cin.getline(desc, 50);
            cout << "Amount: $"; cin >> amt;
            char fullDesc[60];
            strcpy(fullDesc, (string("Room ") + to_string(roomNum) + " - " + desc).c_str());
            pushCharge(hotel.bills, roomNum, fullDesc, amt);
        } else if (choice == 2) {
            Charge c = popCharge(hotel.bills);
            if (c.amount != 0) {
                cout << "Removed: " << c.description << " - $" << c.amount << "\n";
            }
        } else if (choice == 3) {
            Charge c = peekCharge(hotel.bills);
            if (c.amount != 0) {
                cout << "Last charge: " << c.description << " - $" << c.amount << "\n";
            }
        } else if (choice == 4) {
            displayBill(hotel.bills);
        } else if (choice == 5) {
            clearBill(hotel.bills);
        }
        if (choice != 0) system("pause");
    } while (choice != 0);
}

void sortingMenu(HotelManager &hotel) {
    if (hotel.rooms.n == 0) {
        system("cls");
        cout << "No rooms to sort.\n";
        system("pause");
        return;
    }

    Room arr[200];
    int n;
    copyListToArray(hotel.rooms, arr, n);

    int choice;
    do {
        system("cls");
        cout << "\n===== SEARCH & SORT =====\n";
        cout << "1. Sort by Price\n";
        cout << "2. Sort by Room Number\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            copyListToArray(hotel.rooms, arr, n);
        }

        if (choice == 1) bubbleSortByPrice(arr, n);
        else if (choice == 2) selectionSortByRoomNumber(arr, n);
        else if (choice == 3) insertionSortByPrice(arr, n);
        else if (choice == 4) mergeSortByPrice(arr, 0, n - 1);
        else if (choice == 5) quickSortByRoomNumber(arr, 0, n - 1);

        if (choice >= 1 && choice <= 6) {
            displaySortedRooms(arr, n);
        }
        if (choice != 0) system("pause");
    } while (choice != 0);
}

void floorMapMenu(HotelManager &hotel) {
    int choice;
    do {
        system("cls");
        cout << "\n===== HOTEL FLOOR MAP (BST) =====\n";
        cout << "1. Add Floor\n";
        cout << "2. Search Floor\n";
        cout << "3. Delete Floor\n";
        cout << "4. Display Inorder\n";
        cout << "5. Display Preorder\n";
        cout << "6. Display Postorder\n";
        cout << "7. Total Floors\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int num; char desc[50];
            cout << "Floor Number: "; cin >> num;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Description (e.g. Ground Floor): "; cin.getline(desc, 50);
            hotel.hotelMap.root = insert(hotel.hotelMap.root, num, desc);
            cout << "Floor " << num << " added.\n";
        } else if (choice == 2) {
            int num;
            cout << "Floor Number: "; cin >> num;
            if (!search(hotel.hotelMap.root, num))
                cout << "Floor " << num << " not found.\n";
        } else if (choice == 3) {
            int num;
            cout << "Floor Number: "; cin >> num;
            deleteNode(hotel.hotelMap.root, num);
        } else if (choice == 4) {
            if (hotel.hotelMap.root == nullptr)
                cout << "No floors.\n";
            else {
                cout << "\n=== FLOORS (Inorder) ===\n";
                inorder(hotel.hotelMap.root);
            }
        } else if (choice == 5) {
            if (hotel.hotelMap.root == nullptr)
                cout << "No floors.\n";
            else {
                cout << "\n=== FLOORS (Preorder) ===\n";
                preorder(hotel.hotelMap.root);
            }
        } else if (choice == 6) {
            if (hotel.hotelMap.root == nullptr)
                cout << "No floors.\n";
            else {
                cout << "\n=== FLOORS (Postorder) ===\n";
                postorder(hotel.hotelMap.root);
            }
        } else if (choice == 7) {
            cout << "Total floors: " << getSize(hotel.hotelMap.root) << "\n";
        }
        if (choice != 0) system("pause");
    } while (choice != 0);
}

void mainMenu(HotelManager &hotel) {
    int choice;
    do {
        system("cls");
        cout << "\n====================================\n";
        cout << "   HOTEL MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Room Management \n";
        cout << "2. Reservation Queue\n";
        cout << "3. Guest Check-In \n";
        cout << "4. Guest Check-Out\n";
        cout << "5. Billing / Invoice \n";
        cout << "6. Search & Sort Rooms\n";
        cout << "7. View Hotel Floor Map \n";
        cout << "8. Save & Exit\n";
        cout << "0. Exit Without Saving\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: roomManagementMenu(hotel); break;
            case 2: reservationMenu(hotel); break;
            case 3: checkInMenu(hotel); break;
            case 4: checkOutMenu(hotel); break;
            case 5: billingMenu(hotel); break;
            case 6: sortingMenu(hotel); break;
            case 7: floorMapMenu(hotel); break;
            case 8:
                saveAllData(hotel);
                cout << "Data saved. Thank you!\n";
                choice = 0;
                break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}
