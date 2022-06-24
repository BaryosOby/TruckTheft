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
        for (const auto &n : crates) {
            if (!isdigit(n)) throw runtime_error("Crates amount is not a number!\n");
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
    if (is_time) {
        replaceChar(number);
    }
    stringstream toNum;
    double n;
    toNum << number;
    if ((toNum >> n).fail()) {
        throw notANumberException(number);
    }
    toNum.clear();
    if (is_time) {
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

void Controller::validStateTrooper(vector<string> &data) {
    validName(data[1]);
    Model::getInstance().getWareByName(data[3]);
}

void Controller::validChopper(vector<string> &data) {
    validName(data[0]);

}

void Controller::removeBrackets(string &str) {
    int size = str.size() - 1;
    str.replace(0, 1, "");
    str.replace(size - 1, size, "");
}


void Controller::parseTruck(string &file_name, fstream &file) {
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
            vf.createVehicle(truck, name, initWare.lock()->getInitLocation().x, initWare.lock()->getInitLocation().y));
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
    if (crates < 0) {
        throw runtime_error("crates number must be non-negative");
    }
}

void Controller::parseWarehouse(string &file_name, fstream &file) {
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
    if (str.size() > size) {
        unsigned long diff = str.size() - size;
        str.erase(str.end() - diff, str.end());
    }
}

void Controller::createTroop(vector<string> &data) {
    validStateTrooper(data);
    auto ware = Model::getInstance().getWareByName(data[3]).lock();
    auto tr = vf.createVehicle(trooper, data[1], ware->getInitLocation().x, ware->getInitLocation().y);
    Model::getInstance().pushObj(tr);
}

void Controller::createChopper(vector<string> &data) {
    validChopper(data);
    Point p = getPointFromString(data[3], data[4]);
    auto c = vf.createVehicle(chopper, data[1], p.x, p.y);
    Model::getInstance().pushObj(c);

}

Controller::Controller(int argc, char **argv) : vf(), view(make_shared<View>(View())) {
//    view(make_shared<View>(View()));
    int idx = 1;
    string curr_arg = argv[idx];
    if (curr_arg != "-w") {
        throw runtime_error("missing flag: -w");
    }
    curr_arg = argv[++idx];
    fstream file;
    parseWarehouse(curr_arg, file);
    curr_arg = argv[++idx];
    if (curr_arg != "-t") {
        throw runtime_error("missing flag: -t");
    }
    while (++idx < argc) {
        curr_arg = argv[idx];
        parseTruck(curr_arg, file);
    }
    Model::getInstance().attach(view);
}

void Controller::run() {
    bool running = true;
    while (running) {
        cout << "Time " << Model::getInstance().getTime() << ": Enter command: ";
        string command;
        getline(cin, command);
        vector<string> data = split(command, " ");
        try {
            switch (choices[data[0]]) {
                case 0: {
                    if (data[0] == "default") {
                        view->def_values();
                    } else {
                        vehicleCommand(data);
                    }
                    break;
                }
                case 1: {
                    if (data.size() != 2) {
                        throw invalid_argument(command);
                    }
                    int sz = (int) convertStringToFloat(data[1]);
                    if (sz < MIN_SIZE || sz > MAX_SIZE) {
                        throw invalid_argument(data[1]);
                    }
                    view->setSize(sz);
                    break;
                }
                case 2: {
                    if (data.size() != 2) {
                        throw invalid_argument(command);
                    }
                    double zm = convertStringToFloat(data[1]);
                    if (zm < 1) {
                        throw invalid_argument(data[1]);
                    }
                    view->setZoom(zm);
                    break;
                }
                case 3: {
                    if (data.size() != 3) {
                        throw invalid_argument(command);
                    }
                    double x = convertStringToFloat(data[1]);
                    double y = convertStringToFloat(data[2]);
                    view->setPan(Point(x, y));
                    break;
                }
                case 4: {
                    if (data.size() != 1) {
                        throw invalid_argument(command);
                    }
                    view->show();
                    break;
                }
                case 5: {
                    if (data.size() != 1) {
                        throw invalid_argument(command);
                    }
                    Model::getInstance().broadcast_status();
                    break;
                }
                case 6: {
                    if (data.size() != 1) {
                        throw invalid_argument(command);
                    }
                    Model::getInstance().update();
                    break;
                }
                case 7: {
                    if (data[2] == "Chopper") {
                        createChopper(data);
                    } else if (data[2] == "State_trooper") {
                        createTroop(data);
                    } else {
                        throw invalidVehicleTypeException(data[2]);
                    }
                    break;
                }
                case 8: {
                    running = false;
                    break;
                }
//                default: {
//                    vehicleCommand(data);
//                    break;
//                }
            }
        }
        catch (invalid_argument &ia) {
            cerr << ia.what() << endl;
        }
        catch (exception &e) {
            cerr << e.what() << endl;
        }
    }
}

Point Controller::getPointFromString(string &x_st, string &y_st) {
    x_st.erase(x_st.begin(), x_st.begin() + 1);
    x_st.erase(x_st.end() - 1, x_st.end());
    y_st.erase(y_st.end() - 1, y_st.end());
    double x = Controller::convertStringToFloat(x_st, false);
    double y = convertStringToFloat(y_st, false);
    return {x, y};
}

void Controller::vehicleCommand(vector<string> &data) {
    auto v = Model::getInstance().getVehicleByName(data[0]);
    ObjType tp;

    if (v == nullptr) {
        throw Model::invalidNameException(data[0]);
    }

    if (typeid(*v) == typeid(Truck)) {
        tp = truck;
    }

    if (typeid(*v) == typeid(Chopper)) {
        tp = chopper;
    }

    if (typeid(*v) == typeid(StateTrooper)) {
        tp = trooper;
    }

    switch (choices[data[1]]) {
        case 9: {
            if (tp == truck) {
                throw invalidVehicleTypeException("Truck");
            }
            if (tp == chopper) {
                weak_ptr<Chopper> c = dynamic_pointer_cast<Chopper>(v);
                if (data.size() != 4) {
                    throw invalid_argument(data[1]);
                }
                double speed = convertStringToFloat(data[3]) / 100;
                double course = convertStringToFloat(data[2]);
                if (speed > SPEED_LIM) {
                    throw invalid_argument(data[3]);

                }
                c.lock()->course(course, speed);

            }
            if (tp == trooper) {
                if (data.size() != 3) {
                    throw invalid_argument(data[1]);
                }
                double course = convertStringToFloat(data[2]);
                v->course(course);
            }
            break;
        }
        case 10: {
            if (tp == truck) {
                throw invalidVehicleTypeException("Truck");
            }
            if (tp == chopper) {
                weak_ptr<Chopper> c = dynamic_pointer_cast<Chopper>(v);
                if (data.size() != 5) {
                    throw invalid_argument(data[1]);
                }
                double speed = convertStringToFloat(data[5]) / 100;
                Point p = getPointFromString(data[3], data[4]);
                if (speed > SPEED_LIM) {
                    throw invalid_argument(data[3]);
                }
                c.lock()->position(p, speed);
            }
            if (tp == trooper) {
                if (data.size() != 4) {
                    throw invalid_argument(data[1]);

                }
                Point p = getPointFromString(data[3], data[4]);
                v->position(p);
            }
            break;
        }
        case 11: {
            if (tp == truck || tp == chopper) {
                throw invalid_argument(typeid(*v).name() + 6);

            }
            if (data.size() != 3) {
                throw invalid_argument(data[1]);
            }
            auto w = Model::getInstance().getWareByName(data[2]).lock();
            if (w == nullptr) {
                throw Model::invalidNameException(data[2]);
            }
            v->position(w->getInitLocation());
            break;
        }
        case 12: {
            if (data.size() != 3) {
                throw invalid_argument(data[1]);

            }
            Model::getInstance().attackByName(data[0], data[2]);
            break;
        }
        case 13: {
            if (data.size() != 2) {
                throw invalid_argument(data[1]);

            }
            v->setState(stopped);
            break;
        }
        default: {
            throw Model::invalidNameException(data[1]);
        }
    }
}
