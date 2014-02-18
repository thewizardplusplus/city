#include "Connection.h"
#include "ConnectionPrivate.h"
#include "exceptions/HostResolveException.h"
#include "exceptions/SendException.h"
#include "exceptions/ReceiveException.h"

using namespace thewizardplusplus::city_client;
using namespace thewizardplusplus::city_client::exceptions;
using namespace boost::system;

Connection::Connection(const std::string& host, const unsigned short port) try {
	connection.reset(new ConnectionPrivate(host, port));
} catch(const system_error& exception) {
	throw HostResolveException(host, port, exception.what());
}

std::string Connection::sendMessage(const std::string& message) {
	send(message);
	return receive();
}

void Connection::send(const std::string& message) try {
	connection->send(message);
} catch(const system_error& exception) {
	throw SendException(exception.what());
}

std::string Connection::receive(void) try {
	return connection->receive();
} catch(const system_error& exception) {
	throw ReceiveException(exception.what());
}
