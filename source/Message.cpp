#include "Message.h"

Message::Message(
	const QString& nickname,
	const QDateTime& date,
	const QString& text
) :
	nickname(nickname),
	date(date),
	text(text)
{}
