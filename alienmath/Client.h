#ifndef CLIENT_H
#define CLIENT_H

#include "httplib.h"

class Client
{
public:
	Client();
	Client(const std::string serverUrl, const std::string playerKey);
	~Client() { delete m_client; }
private:
	httplib::Client *m_client;
};

#endif // CLIENT_H
