#ifndef EXC03_MODEL_H
#define EXC03_MODEL_H

#include "View.h"


class Model {
private:
    vector<shared_ptr<Sim_obj>> objs;
    vector<weak_ptr<Truck>> trucks;
    vector<weak_ptr<Chopper>> choppers;
    vector<weak_ptr<StateTrooper>> troops;
    vector<weak_ptr<Warehouse>> warehouses;
    shared_ptr<View> view;
    double time{};

    Model();

    bool findObj(Sim_obj& obj);

    void attacks();


public:

    Model(Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&) = delete;
    Model& operator=(Model&&) = delete;

    static Model& getInstance();

    void update();

    void pushObj(Sim_obj& obj);

    void attach(View& v);

};


#endif
