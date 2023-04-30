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
        _payload = source._payload;
        _data = source._data;
        _size = source._size;
    }
    Message(Message &&source) {
        _type = source._type;
        _payload = move(source._payload);
        _data = move(source._data);
        _size = source._size;
    }
    Message& operator=(Message const &source) {
        _type = source._type;
        _payload = source._payload;
        _data = source._data;
        _size = source._size;
        return *this;
    }
    Message& operator=(Message &&source) {
        _type = source._type;
        _payload = move(source._payload);
        _data = move(source._data);
        _size = source._size;
        return *this;
    }
    
    string getPayload() {return _payload;}
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
    string _payload;
    Data _data;
    uint _size;
    void parse();
};

#endif