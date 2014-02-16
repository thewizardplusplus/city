#ifndef CONNECTION_H
#define CONNECTION_H

#include "ReceiveMessageListenerGroup.h"
#include <boost/shared_ptr.hpp>

namespace thewizardplusplus {
namespace city_client {

class ConnectionPrivate;

class Connection {
public:
	typedef ReceiveMessageListenerGroup::Listener Listener;

	explicit Connection(const std::string& host, const unsigned short port);
	void addReceiveMessageListener(const Listener& listener);
	void removeReceiveMessageListener(const Listener& listener);
	void sendMessage(const std::string& message);

private:
	boost::shared_ptr<ConnectionPrivate> connection;
	ReceiveMessageListenerGroup listeners;
};

}
}
#endif
