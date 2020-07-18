#include "Client.h"
#include <iostream>
#include <regex>
#include <string>
#include "httplib.h"

Client::Client()
{
	m_client = new httplib::Client("https://icfpc2020-api.testkontur.ru");
	std::cout << m_client->is_valid() << std::endl;
	const std::shared_ptr<httplib::Response> serverResponse = 
		m_client->Post("https://icfpc2020-api.testkontur.ru/aliens/send?apiKey=b4c1d7d8042e46c7a5e59574839f41b9",
		"110110000111011111100001001110100100100000",
		"text/plain");
	
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
	m_client = new httplib::Client(serverName, serverPort);
	const std::shared_ptr<httplib::Response> serverResponse = 
		m_client->Post(serverUrl.c_str(), playerKey.c_str(), "text/plain");

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
