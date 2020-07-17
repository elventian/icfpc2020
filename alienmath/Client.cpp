#include "Client.h"
#include <iostream>
#include <regex>
#include <string>
#include "httplib.h"

Client::Client(const std::string serverUrl, const std::string playerKey)
{
	const std::regex urlRegexp("http://(.+):(\\d+)");
	std::smatch urlMatches;
	if (!std::regex_search(serverUrl, urlMatches, urlRegexp) || urlMatches.size() != 3) {
		std::cout << "Unexpected server response:\nBad server URL" << std::endl;
		return;
	}
	const std::string serverName = urlMatches[1];
	const int serverPort = std::stoi(urlMatches[2]);
	httplib::Client client(serverName, serverPort);
	const std::shared_ptr<httplib::Response> serverResponse = 
		client.Post(serverUrl.c_str(), playerKey.c_str(), "text/plain");

	if (!serverResponse) {
		std::cout << "Unexpected server response:\nNo response from server" << std::endl;
		return;
	}
	
	if (serverResponse->status != 200) {
		std::cout << "Unexpected server response:\nHTTP code: " << serverResponse->status
		          << "\nResponse body: " << serverResponse->body << std::endl;
		return;
	}

	std::cout << "Server response: " << serverResponse->body << std::endl;
}
