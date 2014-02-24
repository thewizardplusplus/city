#include "MainWindow.h"
#include <QtGui/QDesktopWidget>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>

const QString MainWindow::MESSAGE_TEMPLATE =
	"<p>"
		"<strong>%1</strong> "
		"<span style = \"font-style: italic; color: #808080;\">(%2)</span>"
		"<strong>:</strong> "
		"%3"
	"</p>";

MainWindow::MainWindow(void) :
	QMainWindow(NULL),
	processed(false)
{
	ui.setupUi(this);
	ui.message_editor->installEventFilter(this);
	ui.message_editor->setFocus();

	connect(
		ui.interlocutors_view,
		SIGNAL(itemClicked(QListWidgetItem*)),
		this,
		SLOT(selectInterlocutor(QListWidgetItem*))
	);
	connect(
		ui.message_editor,
		SIGNAL(textChanged()),
		this,
		SLOT(updateSendButton())
	);
	connect(ui.send_button, SIGNAL(clicked()), this, SLOT(sendMessage()));
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
	if (object == ui.message_editor && event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->key() == Qt::Key_Return) {
			if (!(key_event->modifiers() & Qt::ShiftModifier)) {
				sendMessage();
			} else {
				ui.message_editor->textCursor().insertText("\n");
			}

			return true;
		}
	}

	return QMainWindow::eventFilter(object, event);
}

void MainWindow::setInterlocutors(const QStringList& interlocutors) {
	while (ui.interlocutors_view->count()) {
		delete ui.interlocutors_view->takeItem(0);
	}

	ui.interlocutors_view->addItems(interlocutors);
}

void MainWindow::addMessages(const Message::Group& messages) {
	foreach (const Message& message, messages) {
		addMessage(message);
	}
}

void MainWindow::showEvent(QShowEvent* event) {
	(void)event;

	if (!processed) {
		QRect desktop_rectangle = QApplication::desktop()->availableGeometry();
		resize(desktop_rectangle.size() / 2);
		move(desktop_rectangle.center() - rect().center());

		int size = ui.global_splitter->height() / 3;
		ui.global_splitter->setSizes(QList<int>() << 2 * size << size);

		size = ui.views_splitter->width() / 3;
		ui.views_splitter->setSizes(QList<int>() << 2 * size << size);

		processed = true;
	}
}

void MainWindow::addMessage(const Message& message) {
	QString text = message.text;
	text.replace(QRegExp("@(\\w+)\\b"), "<strong>\\1</strong>");
	text.replace("\n", "<br />");

	ui.chat_view->append(
		MESSAGE_TEMPLATE
			.arg(message.nickname)
			.arg(message.date.toString("dd.mm.yyyy hh:mm:ss"))
			.arg(text)
	);
}

void MainWindow::selectInterlocutor(QListWidgetItem* item) {
	ui.message_editor->textCursor().insertText("@" + item->text());
}

void MainWindow::updateSendButton(void) {
	ui.send_button->setEnabled(!ui.message_editor->toPlainText().isEmpty());
}

void MainWindow::sendMessage(void) {
	QString text = ui.message_editor->toPlainText();
	if (!text.isEmpty()) {
		ui.message_editor->clear();
		emit message(Message(trUtf8("Я"), QDateTime::currentDateTime(), text));

		addMessage(Message(trUtf8("Я"), QDateTime::currentDateTime(), text));
	}

	ui.message_editor->setFocus();
}
