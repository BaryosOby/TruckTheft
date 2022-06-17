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
void Controller::validTruckLineSyntax(vector<string> &data, bool isFirst) {
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
double Controller::convertStringToFloat(string &number) {
    replaceChar(number);
    stringstream toNum;
    double n;
    toNum << number;
    toNum >> n;
    toNum.clear();
    return n;
}
//replace ":" with "." to be a valid float
void Controller::replaceChar(string &str, const string &c) {
    str.replace(2, 1, c);
}

void Controller::validStateTrooper(vector<string>& data) {
    validName(data[0]); // possible data[1] need to check
    //need to check if warehouse exist

}

void Controller::validChopper(vector<string> &data) {
    validName(data[0]); // possible data[1] need to check
}

void Controller::removeBrackets(string &str) {
    int size = str.size() - 1;
    str.replace(0,1,"");
    str.replace(size -1,size,"");
}


void Controller::parseTruck(string &file_name, fstream& file) {
    try {
        validFile(file_name, file);
        string name = split(file_name, ".")[0];
        validName(name);
        string line;
        getline(file, line);
        auto v = split(line);
        validTruckLineSyntax(v, true);
        VehicleFactory vf;
        auto initWare = Model::getInstance().getWareByName(split(line)[0]);
        shared_ptr<Truck> t = dynamic_pointer_cast<Truck>(
                vf.createVehicle(truck, name, initWare.lock()->getLocation().x, initWare.lock()->getLocation().y));
        int crate_num{};
        while (!file.eof()) {
            getline(file, line);
            v = split(line);
            validTruckLineSyntax(v);
            auto ware = Model::getInstance().getWareByName(v[0]);
            t->pushWarehouse(ware);
            double arrive = convertStringToFloat(v[1]);
            double depart = convertStringToFloat(v[3]);
            int crates = static_cast<int>(convertStringToFloat(v[2]));
            auto p = pair<double, double>(arrive, depart);
            t->pushArriveDepart(p);
            t->pushCrates(crates);
            crate_num += crates;
        }
        initWare.lock()->setInventory(-crate_num);
        t->setCratesNum(crate_num);
        t->setNextWarehouse();
        Model::getInstance().pushObj(t);
    }
    catch (exception e){
        cerr << e.what();
        throw runtime_error("invalid file content");
    }

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
            double x = convertStringToFloat(v[1]);
            double y = convertStringToFloat(v[2]);
            auto w = make_shared<Warehouse>(v[0], x, y, crates);
            Model::getInstance().pushObj(w);
        }

}
