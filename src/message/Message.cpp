#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "Message.h"

using namespace std;

Message::Message(string s) : _payload(s){
    parse();
}

void Message::setPayload(string payload) {
        _payload = payload;
        parse();
}

void Message::parse() 
{
    _data = {};
    string parsed;
    stringstream ss(_payload);
    getline(ss, parsed, ':');
    if(parsed == "data") 
    {
        ss.seekp(-1, std::ios_base::end);
        _type = Message::Type::data;
        while(getline(ss, parsed, ',')) 
        {
            auto line = parsed;
            parsed.erase(remove(parsed.begin(), parsed.end(), ','), parsed.end());
            stringstream parsedss(parsed);
            string point1;
            parsedss >> point1;
            string point2;
            parsedss >> point2;
            try {
                _data.push_back({stod(point1), stod(point2)});
            } catch (...) {
                cout << "ERROR: point1 " << point1 << " point2" << point2 << endl;
                cout << "Data: " << line << endl;
                cout << "Message: " << _payload << line << endl;
            }
        }
    } else {
        _type = Message::Type::control;
    }

}