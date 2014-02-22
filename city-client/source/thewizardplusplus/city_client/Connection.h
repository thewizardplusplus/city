#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <memory>

namespace thewizardplusplus {
namespace city_client {

class ConnectionPrivate;

class Connection {
public:
	Connection(const std::string& host, const unsigned short port);
	std::string sendMessage(const std::string& message);

private:
	std::auto_ptr<ConnectionPrivate> connection;

	void send(const std::string& message);
	std::string receive(void);
};

}
}
#endif
