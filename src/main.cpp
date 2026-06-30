#include "../include/HotelManager.h"
#include "../include/Typewriter.h"
#include <iostream>
using namespace std;

int main() {
    TypewriterBuf tw;

    HotelManager hotel;
    initHotel(hotel);
    loadAllData(hotel);

    mainMenu(hotel);

    freeRoomList(hotel.rooms);
    return 0;
}
