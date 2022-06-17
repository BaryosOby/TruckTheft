#ifndef CPPAD03_VEHICLE_H
#define CPPAD03_VEHICLE_H
#include "Track_base.h"

enum State {stopped, parked, off_road, moving_dest, moving_course};

class Vehicle : public Sim_obj{
protected:
    Track_base tb;
    State state;
public:
    Vehicle(string& name, double x, double y):Sim_obj(name, x, y), tb(x, y), state(stopped){}

    virtual void course(double deg){
        state = moving_course;
        tb.setCourseByDeg(deg);
    }
    virtual void position(double  x, double y){
        state = moving_dest;
        tb.setDestination(x, y);
    }

    virtual void update(double general_time) override = 0;
    virtual void broadcast_status() = 0;

    void drive(double time=1){
        tb.drive(time);
    }

    bool check_radius(Point p, int radius) const{
        double delta_x = abs(tb.getLocation().x - p.x);
        double delta_y = abs(tb.getLocation().y - p.y);
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
