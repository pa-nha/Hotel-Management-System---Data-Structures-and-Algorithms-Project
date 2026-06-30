#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Room.h"
#include "Guest.h"
#include "Reservation.h"
#include "Billing.h"

void saveRoomsToFile(RoomList &list, const char* filename);
void loadRoomsFromFile(RoomList &list, const char* filename);
void saveGuestsToFile(GuestTable &gt, const char* filename);
void loadGuestsFromFile(GuestTable &gt, const char* filename);
void saveReservationsToFile(ReservationQueue &q, const char* filename);
void loadReservationsFromFile(ReservationQueue &q, const char* filename, int &nextId);

#endif
