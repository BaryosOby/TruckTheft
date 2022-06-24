#ifndef EXC03_VEHICLEFACTORY_H
#define EXC03_VEHICLEFACTORY_H

#include "Truck.h"
#include "Chopper.h"
#include "StateTrooper.h"

class VehicleFactory {
public:
    VehicleFactory() = default;

    shared_ptr<Vehicle> createVehicle(ObjType vt, string &name, double x, double y) {
        switch (vt) {
            case truck:
                return make_shared<Truck>(Truck(name, x, y));
            case chopper:
                return make_shared<Chopper>(Chopper(name, x, y));
            case trooper:
                return make_shared<StateTrooper>(StateTrooper(name, x, y));
        }
    }
};


#endif
