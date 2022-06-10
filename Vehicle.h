#ifndef CPPAD03_VEHICLE_H
#define CPPAD03_VEHICLE_H
#include "Track_base.h"

enum VehicleType {truck, chopper, trooper};
enum State {stopped, parked, off_road, moving};

class Vehicle : public Sim_obj{
protected:
    Track_base tb;
    State state;
public:
    Vehicle(string& name, double x, double y):Sim_obj(name, x, y), tb(x, y), state(stopped){}

    virtual void update(double general_time) override = 0;
    virtual void broadcast_status() = 0;

    void drive(double time=1){
        tb.drive(time);
        Sim_obj::location = tb.getLocation();
    }

    bool check_radius(Point p, int radius) const{
        double delta_x = abs(Sim_obj::location.x - p.x);
        double delta_y = abs(Sim_obj::location.y - p.y);
        if(delta_x > radius || delta_y > radius){
            return false;
        }
        return true;
    }

    State getState() const {
        return state;
    }

    void setState(State st) {
        Vehicle::state = st;
    }

};

#endif
