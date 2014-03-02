#include "Message.h"

Message::Message(
	const QString& nickname,
	const QDateTime& time,
	const QString& text
) :
	nickname(nickname),
	time(time),
	text(text)
{}
