#include "ConnectionOptions.h"

using namespace thewizardplusplus::city_client;

ConnectionOptions::ConnectionOptions(
	const std::string& host,
	const unsigned short port
) :
	host(host),
	port(port)
{}

std::string ConnectionOptions::getHost(void) const {
	return host;
}

unsigned short ConnectionOptions::getPort(void) const {
	return port;
}
