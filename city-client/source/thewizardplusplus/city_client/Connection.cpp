#include "Connection.h"
#include "ConnectionPrivate.h"

using namespace thewizardplusplus::city_client;

typedef Connection::Listener Listener;

Connection::Connection(const std::string& host, const unsigned short port) {
	connection.reset(new ConnectionPrivate(host, port));
}

void Connection::addReceiveMessageListener(const Listener& listener) {
	listeners.add(listener);
}

void Connection::removeReceiveMessageListener(const Listener& listener) {
	listeners.remove(listener);
}

void Connection::sendMessage(const std::string& message) {
	connection->send(message);

	std::string reply = connection->receive();
	listeners.process(message);
}
