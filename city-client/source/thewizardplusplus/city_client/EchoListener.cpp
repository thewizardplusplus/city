#include "EchoListener.h"
#include <iostream>

using namespace thewizardplusplus::city_client;

void EchoListener::onReceiveMessage(const std::string& message) {
	std::cout << "Server reply: \"" << message << "\".\n";
}
