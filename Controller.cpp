//
// Created by Itamar on 01/06/2022.
//

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
//check truck validation
void Controller::validTruck(vector<string> &data, bool isFirst) {
    validName(data[0], MAX_NAME);
    vector<string> time = split(data[1], ":");
    string crates = data[2]; //TODO move under !isFirst
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
float Controller::convertStringToFloat(string &number) {
    replaceChar(number);
    stringstream toNum;
    float n;
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
