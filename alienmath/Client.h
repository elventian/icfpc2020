#ifndef CLIENT_H
#define CLIENT_H

#include "httplib.h"

class Client
{
public:
	Client(const std::string serverUrl, const std::string playerKey);
};

#endif // CLIENT_H
