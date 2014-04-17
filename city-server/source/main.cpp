#include "Connection.h"
#include "Level.h"
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>

using namespace boost;
using namespace boost::algorithm;
using namespace boost::program_options;

static const char MESSAGE_PARTS_SEPARATOR = ':';
static const size_t MAXIMAL_MESSAGE_LENGTH = 1024;
static const regex MESSAGE_PATTERN(
	"^(r|(w:(0|[1-9]\\d*)|m:(0|[1-9]\\d*):[0-3]))$"
);

std::string ConvertCharToString(char symbol) {
	return std::string(1, symbol);
}

void ProcessError(const std::string& message) {
	std::cerr
		<< format("City server error: %s.\n")
			% to_lower_copy(message)
		<< std::flush;
}

unsigned short ParseCommandLineArguments(
	int arguments_number,
	char* arguments[]
) {
	options_description options;
	options.add_options()
		("port", value<unsigned short>()->required());

	variables_map parameters;
	store(
		command_line_parser(arguments_number, arguments)
			.options(options)
			.run(),
		parameters
	);
	notify(parameters);

	return parameters["port"].as<unsigned short>();
}

void ProcessMessage(
	const ConnectionSmartPointer& connection,
	const std::string& message,
	const LevelSmartPointer& level
) {
	if (!regex_match(message, MESSAGE_PATTERN)) {
		throw std::runtime_error("invalid command");
	}

	if (message == "r") {
		size_t player_id = level->addPlayer();
		connection->send(lexical_cast<std::string>(player_id));

		return;
	}

	std::vector<std::string> message_parts;
	split(
		message_parts,
		message,
		is_any_of(ConvertCharToString(MESSAGE_PARTS_SEPARATOR))
	);

	size_t player_id = lexical_cast<size_t>(message_parts[1]);
	level->updatePlayerTimestamp(player_id);

	if (starts_with(message, "w")) {
		connection->send(level->toString(player_id));
	} else if (starts_with(message, "m")) {
		bool moved = level->movePlayer(
			player_id,
			static_cast<Direction>(lexical_cast<int>(message_parts[2]))
		);
		connection->send(moved ? "true" : "false");
	}
}

void StartServer(
	const ConnectionSmartPointer& connection,
	const LevelSmartPointer& level
) {
	while (true) try {
		std::string message = connection->receive();
		ProcessMessage(connection, message, level);
	} catch(const std::exception& exception) {
		ProcessError(exception.what());
		connection->send(
			(format("error%c%s")
				% MESSAGE_PARTS_SEPARATOR
				% exception.what()).str()
		);
	}
}

void CleanerThreadFunction(const LevelSmartPointer& level) {
	while (true) {
		level->removeLostPlayers();
		level->updateCastles();
		level->addSkeleton();
	}
}

void StartCleanerThread(const LevelSmartPointer& level) {
	new thread(CleanerThreadFunction, level);
}

int main(int arguments_number, char* arguments[]) try {
	unsigned short port = ParseCommandLineArguments(
		arguments_number,
		arguments
	);
	ConnectionSmartPointer connection(new Connection(port));
	LevelSmartPointer level(new Level("level.lvl"));
	StartCleanerThread(level);
	StartServer(connection, level);
} catch(const std::exception& exception) {
	ProcessError(exception.what());
}
