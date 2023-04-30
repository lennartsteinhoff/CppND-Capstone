#ifndef NETWORKERROR_H
#define NETWORKERROR_H

// code found here: https://tldp.org/LDP/LG/issue74/tougher.html

#include <string>

class NetworkError
{
public:
  NetworkError(std::string s) : m_s(s){};
  NetworkError(){};

  std::string description() { return m_s; }

private:
  std::string m_s;
};

#endif