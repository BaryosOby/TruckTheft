#ifndef CPPAD03_SIM_OBJ_H
#define CPPAD03_SIM_OBJ_H
#include <iostream>
#include <vector>
#include "Geometry.h"
#include <queue>
#include <memory>

using namespace std;

class Sim_obj {
protected:
    Point location;
    string name;
public:
    const Point &getLocation() const{return location;};

    void setLocation(double x, double y){location.setCord(x, y); };

    const string &getName() const{ return name;};

    void setName(const string &rhs) { this->name = rhs; };

    virtual void update() = 0;

    virtual void broadcast_status() = 0;

    Sim_obj(string& name, double x, double y):location(x, y), name(name){}
    
};



#endif
