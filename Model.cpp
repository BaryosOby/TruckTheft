#include "Model.h"

Model::Model(){
    string name = "Frankfurt";
    auto frank = make_shared<Warehouse>(name, 40, 10, 100000);
    objs.push_back(frank);
    warehouses.push_back(frank);
}

bool Model::findObj(Sim_obj &obj) {
    return false;
}

Model &Model::getInstance() {
    static Model mod;
    return mod;
}

void Model::update() {
    for(const auto& ob : objs){
        ob->update(time);
    }

}

void Model::pushObj(Sim_obj& obj) {

    if(typeid(obj) == typeid(Truck)){
        auto o = make_shared<Truck>(dynamic_cast<Truck&>(obj));
        objs.push_back(o);
        trucks.push_back(o);
        if(view){
            view->pushObj(o);
        }
    }

    if(typeid(obj) == typeid(Chopper)){
        auto o = make_shared<Chopper>(dynamic_cast<Chopper&>(obj));
        objs.push_back(o);
        choppers.push_back(o);
        if(view){
            view->pushObj(o);
        }
    }

    if(typeid(obj) == typeid(StateTrooper)){
        auto o = make_shared<StateTrooper>(dynamic_cast<StateTrooper&>(obj));
        objs.push_back(o);
        troops.push_back(o);
        if(view){
            view->pushObj(o);
        }
    }

    if(typeid(obj) == typeid(Warehouse)){
        auto o = make_shared<Warehouse>(dynamic_cast<Warehouse&>(obj));
        objs.push_back(o);
        warehouses.push_back(o);
        if(view){
            view->pushObj(o);
        }
    }
}

void Model::attach(View &v) {
    view = make_shared<View>(v);
    for(const auto& ob : objs){
        view->pushObj(ob);
    }
}

void Model::attacks(){

    for(const auto& chop : choppers){

    }

}
