#ifndef CPPAD03_SIM_OBJ_H
#define CPPAD03_SIM_OBJ_H
#include <iostream>
#include <vector>
#include "Geometry.h"
#include <queue>
#include <memory>

using namespace std;

enum ObjType {truck, chopper, trooper, warehouse};

class Sim_obj {
protected:
    Point init_location;
    string name;
public:
    const Point &getLocation() const{return init_location;};

    void setLocation(double x, double y){init_location.setCord(x, y); };

    const string &getName() const{ return name;};

    void setName(const string &rhs) { this->name = rhs; };

    virtual void update(double general_time) = 0;

    virtual void broadcast_status() = 0;

    Sim_obj(string& name, double x, double y): init_location(x, y), name(name){}
    
};



#endif
