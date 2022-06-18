#include "Controller.h"

vector<string> Controller::split(string &text, const string &delimiter) {
    vector<string> words{};
    size_t pos = 0;
    while ((pos = text.find(delimiter)) != string::npos) {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
    }
    words.push_back(text.substr(0, pos));
    return words;
}

void Controller::validFile(const string &fileName, fstream &file) {
    file.open(fileName, ios_base::in);
    if (!file.is_open()) {
        throw runtime_error(fileName + " is not open");
    }
}

void Controller::validName(const string &name, int maxSize) {
    if (name.size() > maxSize) throw runtime_error("Name is too long!\n");
    for (char c : name) {
        if (!isalpha(c)) throw runtime_error("Name contain non alpha chars!\n");
    }
}

//check  validation of a line in a truck file configuration.
void Controller::validTruckLineSyntax(vector<string> data, bool isFirst) {
    validName(data[0]);
    vector<string> time = split(data[1], ":");
    for (const auto &numbers : time) {
        for (char num : numbers) {
            if (isFirst) {
                if (num != '0') throw runtime_error("Illegal time to begin!\n");
                continue;
            }
            if (!isdigit(num)) throw runtime_error("Time is not a digit!\n");
        }
    }
    if (!isFirst) {
        string crates = data[2];
        for(const auto & n : crates){
            if(!isdigit(n)) throw runtime_error("Crates amount is not a number!\n");
        }
        time.clear();
        time = split(data[3], ":");
        for (const auto &numbers : time) {
            for (char num : numbers) {
                if (!isdigit(num)) throw runtime_error("Time is not a digit!\n");
            }
        }
    }
}

//convert given string to a float
double Controller::convertStringToFloat(string &number, bool is_time) {
    if(is_time){
        replaceChar(number);
    }
    stringstream toNum;
    double n;
    toNum << number;
    if((toNum >> n).fail()){
        //TODO throw;
    }
    toNum.clear();
    if(is_time){
        int int_n = (int) n;
        double after_point = n - int_n;
        after_point /= 0.6;
        n = int_n + after_point;
    }
    return n;
}
//replace ":" with "." to be a valid float
void Controller::replaceChar(string &str, const string &c) {
    str.replace(2, 1, c);
}

void Controller::validStateTrooper(vector<string>& data) {
    validName(data[1]);
    Model::getInstance().getWareByName(data[3]);
}

void Controller::validChopper(vector<string> &data) {
    validName(data[0]);

}

void Controller::removeBrackets(string &str) {
    int size = str.size() - 1;
    str.replace(0,1,"");
    str.replace(size -1,size,"");
}


void Controller::parseTruck(string &file_name, fstream& file) {
        validFile(file_name, file);
        string name = split(file_name, ".")[0];
        validName(name);
        string line;
        getline(file, line);
        auto v = split(line);
        erase_r(v[1]);
        validTruckLineSyntax(v, true);
        auto initWare = Model::getInstance().getWareByName(v[0]);
        shared_ptr<Truck> t = dynamic_pointer_cast<Truck>(
                vf.createVehicle(truck, name, initWare.lock()->getLocation().x, initWare.lock()->getLocation().y));
        int crate_num{};
        while (!file.eof()) {
            getline(file, line);
            v = split(line);
            erase_r(v[3]);
            validTruckLineSyntax(v);
            auto ware = Model::getInstance().getWareByName(v[0]);
            t->pushWarehouse(ware);
            double arrive = convertStringToFloat(v[1], true);
            double depart = convertStringToFloat(v[3], true);
            int crates = static_cast<int>(convertStringToFloat(v[2], false));
            auto p = pair<double, double>(arrive, depart);
            t->pushArriveDepart(p);
            t->pushCrates(crates);
            crate_num += crates;
        }
        initWare.lock()->setInventory(-crate_num);
        t->setCratesNum(crate_num);
        t->setNextWarehouse();
        Model::getInstance().pushObj(t);
        file.close();
}

void Controller::validWareLineSyntax(vector<string> &data) {
    validName(data[0]);
    int crates;
    stringstream ss(data[3]);
    ss >> crates;
    if(crates < 0){
        throw runtime_error("crates number must be non-negative");
    }
}

void Controller::parseWarehouse(string &file_name, fstream &file){
        validFile(file_name, file);
        string line;
        while (!file.eof()) {
            getline(file, line);
            auto v = split(line, ", ");
            validWareLineSyntax(v);
            int crates;
            stringstream ss(v[3]);
            ss >> crates;
            string x_str;
            string y_str;
            v[1].erase(v[1].begin(), v[1].begin() + 1);
            v[2].erase(v[2].end() - 1, v[2].end());
            double x = convertStringToFloat(v[1], false);
            double y = convertStringToFloat(v[2], false);
            auto w = make_shared<Warehouse>(v[0], x, y, crates);
            Model::getInstance().pushObj(w);
        }
        file.close();
}


void Controller::erase_r(string &str, int size) {
    if(str.size() > size){
        unsigned long diff = str.size() - size;
        str.erase(str.end() - diff,str.end());
    }
}

void Controller::createTroop(vector<string> &data) {
    validStateTrooper(data);
    auto ware = Model::getInstance().getWareByName(data[3]).lock();
    auto tr = vf.createVehicle(trooper, data[1], ware->getLocation().x, ware->getLocation().y);
    Model::getInstance().pushObj(tr);
}

void Controller::createChopper(vector<string> &data) {

    data[3].erase(data[3].begin(), data[3].begin() + 1);
    data[3].erase(data[3].end()-1, data[3].end());
    data[4].erase(data[4].end()-1, data[4].end());
    double x = convertStringToFloat(data[3], false);
    double y = convertStringToFloat(data[4], false);
    auto c = vf.createVehicle(chopper, data[1], x, y);
    Model::getInstance().pushObj(c);

}

Controller::Controller(int argc, char **argv) {

}

void Controller::run() {
    bool running = true;
    while(running){
        cout << "Time " << Model::getInstance().getTime() << ": Enter command: ";
        string command;
        getline(cin, command);
        vector<string> data = split(command, " ");
        switch(choices[data[0]]){
            case 0:{
                view->def_values();
                break;
            }
            case 1:{
                if(data.size() != 2){ //TODO ERRORS
                    //throw error
                }
                int sz = (int)convertStringToFloat(data[1]);
                if(sz < MIN_SIZE || sz > MAX_SIZE){
                    // throw error
                }
                view->setSize(sz);
                break;
            }
            case 2:{
                if(data.size() != 2){ //TODO ERRORS
                    //throw error
                }
                double zm = convertStringToFloat(data[1]);
                if(zm < 1){
                    // throw error
                }
                view->setZoom(zm);
                break;
            }
            case 3:{
                if(data.size() != 3){ //TODO ERRORS
                    //throw error
                }
                double x = convertStringToFloat(data[1]);
                double y = convertStringToFloat(data[2]);
                view->setPan(Point(x, y));
                break;
            }
            case 4:{
                if(data.size() != 1){
                    //throw
                }
                view->show();
                break;
            }
            case 5:{
                if(data.size() != 1){
                    //throw
                }
                Model::getInstance().broadcast_status();
                break;
            }
            case 6:{
                if(data.size() != 1){
                    //throw
                }
                Model::getInstance().update();
            }
            case 7:{
                if(data[2] == "Chopper"){
                    createChopper(data);
                }
                else if(data[2] == "State_trooper"){
                    createTroop(data);
                }
                else{
                    // throw error
                }
                break;
            }
            case 8:{
                running = false;
                break;
            }
            default:{

            }

        }

    }

}

void Controller::vehicleCommand(vector<string> &data) {

}
