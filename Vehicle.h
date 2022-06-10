#ifndef CPPAD03_VEHICLE_H
#define CPPAD03_VEHICLE_H
#include "Sim_obj.h"
#include "Track_base.h"

enum VehicleType {truck, chopper, trooper};

class Vehicle : public Sim_obj{
protected:
    Track_base tb;

public:
    Vehicle(string& name, double x, double y):Sim_obj(name, x, y){}

    virtual void update() override = 0;
    virtual void broadcast_status() = 0;

    bool check_radius(Point p, int radius) const{
        double delta_x = abs(Sim_obj::location.x - p.x);
        double delta_y = abs(Sim_obj::location.y - p.y);
        if(delta_x > radius || delta_y > radius){
            return false;
        }
        return true;
    }

};

#endif
