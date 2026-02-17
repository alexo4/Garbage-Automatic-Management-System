#include <iostream>
#include "../Headers/GarbageLocations.h"
#include "../Headers/displayToUser.h"

using namespace std;

int main() {

    displayToUser *dtu = new displayToUser();
    dtu->displayInformation();

    return 0;
}
