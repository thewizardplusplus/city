#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/shared_ptr.hpp>

namespace thewizardplusplus {
namespace city_client {

class ConnectionPrivate;

class Connection {
public:
	explicit Connection(const std::string& host, const unsigned short port);
	std::string sendMessage(const std::string& message);

private:
	boost::shared_ptr<ConnectionPrivate> connection;
};

}
}
#endif
