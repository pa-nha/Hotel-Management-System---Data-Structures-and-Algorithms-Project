#ifndef HOTELMANAGER_H
#define HOTELMANAGER_H

#include "Room.h"
#include "Guest.h"
#include "Reservation.h"
#include "Billing.h"
#include "Tree.h"

struct HotelManager {
    RoomList rooms;
    GuestTable guests;
    ReservationQueue reservations;
    BillStack bills;
    HotelTree hotelMap;
    int nextReservationId;
};

void initHotel(HotelManager &hotel);
void loadAllData(HotelManager &hotel);
void saveAllData(HotelManager &hotel);
void mainMenu(HotelManager &hotel);

void roomManagementMenu(HotelManager &hotel);
void checkInMenu(HotelManager &hotel);
void checkOutMenu(HotelManager &hotel);
void reservationMenu(HotelManager &hotel);
void billingMenu(HotelManager &hotel);
void sortingMenu(HotelManager &hotel);
void floorMapMenu(HotelManager &hotel);

#endif
