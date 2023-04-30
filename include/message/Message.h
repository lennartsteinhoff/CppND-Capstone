#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Message {
    public:
    Message(string);
    Message() {};
    Message(Message const &source) {
        _type = source._type;
        _payload = stringstream(source._payload.str());
        _data = source._data;
        _size = source._size;
    }
    Message(Message &&source) {}
    Message& operator=(Message const &source) {}
    Message& operator=(Message &&source) {}
    
    string getPayload() {return _payload.str();}
    void setPayload(string);


    typedef vector<vector<double>> Data;
    enum class Type { command, data, control};

    Data data() {
        return _data;
    }

    Message::Type type() {
        return _type;
    }

    private:
    Type _type;
    stringstream _payload;
    Data _data;
    uint _size;
    void parse();
};

#endif