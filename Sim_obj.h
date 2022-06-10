//
// Created by Itamar on 08/06/2022.
//

#ifndef CPPAD03_SIM_OBJ_H
#define CPPAD03_SIM_OBJ_H
#include <iostream>
#include <vector>

using namespace std;

class Sim_obj {
private:
    pair<float,float> location;
    string name;
public:
    const pair<float, float> &getLocation() const{return location;};

    void setLocation(const pair<float, float> &rhs){ this->location = rhs;};

    const string &getName() const{ return name;};

    void setName(const string &rhs) { this->name = rhs; };

    
};



#endif //CPPAD03_SIM_OBJ_H
