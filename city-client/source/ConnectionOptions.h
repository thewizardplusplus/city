#ifndef CONNECTIONOPTIONS_H
#define CONNECTIONOPTIONS_H

#include <string>

class ConnectionOptions {
public:
	std::string host;
	unsigned int port;

	ConnectionOptions(const std::string& host, const unsigned int port);
};
#endif
