#include "Connection.h"
#include "ConnectionPrivate.h"

using namespace thewizardplusplus::city_client;

Connection::Connection(const std::string& host, const unsigned short port) {
	connection.reset(new ConnectionPrivate(host, port));
}

std::string Connection::sendMessage(const std::string& message) {
	connection->send(message);
	return connection->receive();
}
