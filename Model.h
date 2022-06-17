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

    bool findObj(Sim_obj& obj) const;

    shared_ptr<Vehicle> getVehicleByName(const string& name);

    bool findTroop(const Truck& t) const;

//    void attacks();



    double getTime() const;

public:

    class invalidNameException : public exception{
    private:
        string msg;
    public:
        explicit invalidNameException(const string& name){
            msg = name + "not found";
        }
        const char * what() const noexcept override{
            return msg.c_str();
        }
    };


    Model(Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(Model&) = delete;
    Model& operator=(Model&&) = delete;

    static Model& getInstance();

    void update();

    void pushObj(const shared_ptr<Sim_obj>& obj);

    void attach(View& v);

    void broadcast_status() const;

    void attackByName(const string &chop_name, const string &truck_name);

    void stop(const string& name);

    weak_ptr<Warehouse> getWareByName(const string& name);

    void setDestByName(const string &troop_name, const string &ware_name);

};


#endif
