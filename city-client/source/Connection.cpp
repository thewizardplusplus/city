#include "Connection.h"
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

Connection::Connection(const QString& host, const uint port) :
	socket(io_service, udp::endpoint(udp::v4(), LOCAL_PORT))
{
	receiver_endpoint = resolve(host, port);
}

void Connection::send(const QString& message) {
	QByteArray data = message.toUtf8();
	socket.send_to(buffer(data.constData(), data.size()), receiver_endpoint);
}

QString Connection::receive(void) {
	char reply_buffer[MAXIMAL_REPLY_LENGTH];
	udp::endpoint sender_endpoint;
	size_t reply_length = socket.receive_from(
		buffer(reply_buffer),
		sender_endpoint
	);

	return QString::fromUtf8(reply_buffer, reply_length);
}

udp::endpoint Connection::resolve(
	const QString& host,
	const uint port
) {
	udp::resolver resolver(io_service);
	udp::resolver::query query(
		udp::v4(),
		host.toStdString(),
		lexical_cast<std::string>(port)
	);

	return *resolver.resolve(query);
}
