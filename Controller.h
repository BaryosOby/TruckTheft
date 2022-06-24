#ifndef CPPAD03_CONTROLLER_H
#define CPPAD03_CONTROLLER_H
#define MAX_NAME 12

#include <fstream>
#include <exception>
#include <sstream>
#include "Model.h"

using namespace std;

class Controller {
private:
    map<string, int> choices = {{"default",     0},
                                {"size",        1},
                                {"zoom",        2},
                                {"pan",         3},
                                {"show",        4},
                                {"status",      5},
                                {"go",          6},
                                {"create",      7},
                                {"exit",        8},
                                {"course",      9},
                                {"position",    10},
                                {"destination", 11},
                                {"attack",      12},
                                {"stop",        13}};

    void erase_r(string &str, int size = 5);

    VehicleFactory vf;
    shared_ptr<View> view;

    vector<string> split(string &text, const string &delimiter = ",");

    void validFile(const string &fileName, fstream &file);

    void validName(const string &name, int maxSize = MAX_NAME);

    void validTruckLineSyntax(vector<string> data, bool isFirst = false);

    void parseTruck(string &file_name, fstream &file);

    void validWareLineSyntax(vector<string> &data);

    void parseWarehouse(string &file_name, fstream &file);

    double convertStringToFloat(string &number, bool is_time = false);

    void replaceChar(string &str, const string &c = ".");

    void validStateTrooper(vector<string> &data);

    void removeBrackets(string &str);

    void validChopper(vector<string> &data);

    void createTroop(vector<string> &data);

    void createChopper(vector<string> &data);

    void vehicleCommand(vector<string> &data);

    Point getPointFromString(string &x_st, string &y_st);

    class notANumberException : public exception {
    private:
        string msg;
    public:
        explicit notANumberException(const string &name) {
            msg = name + " is not a valid number\n";
        }

        const char *what() const noexcept override {
            return msg.c_str();
        }
    };

    class invalidVehicleTypeException : public exception {

    private:
        string msg;
    public:
        explicit invalidVehicleTypeException(const string &name) {
            msg = name + " does not support this operation\n";
        }

        const char *what() const noexcept override {
            return msg.c_str();
        }
    };


public:
    Controller(int argc, char **argv);

    void run();
};


#endif
