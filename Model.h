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
    weak_ptr<View> view;
    double time;

    Model();

    bool findObj(Sim_obj &obj) const;


    bool findTroop(const Truck &t) const;


public:

    class invalidNameException : public exception {
    private:
        string msg;
    public:
        explicit invalidNameException(const string &name) {
            msg = name + " not found\n";
        }

        const char *what() const noexcept override {
            return msg.c_str();
        }
    };

    double getTime() const;

    Model(Model &) = delete;

    Model(Model &&) = delete;

    Model &operator=(Model &) = delete;

    Model &operator=(Model &&) = delete;

    static Model &getInstance();

    void update();

    void pushObj(const shared_ptr<Sim_obj> &obj);

    void attach(shared_ptr<View> &v);

    void broadcast_status() const;

    void attackByName(const string &chop_name, const string &truck_name);

    weak_ptr<Warehouse> getWareByName(const string &name);

    shared_ptr<Vehicle> getVehicleByName(const string &name);

};


#endif
