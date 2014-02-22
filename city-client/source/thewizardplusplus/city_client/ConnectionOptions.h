#ifndef CONNECTIONOPTIONS_H
#define CONNECTIONOPTIONS_H

#include <string>

namespace thewizardplusplus {
namespace city_client {

class ConnectionOptions {
public:
	ConnectionOptions(const std::string& host, const unsigned short port);
	std::string getHost(void) const;
	unsigned short getPort(void) const;

private:
	std::string host;
	unsigned short port;
};

}
}
#endif
