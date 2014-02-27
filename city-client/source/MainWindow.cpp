#include "MainWindow.h"
#include <QtGui/QDesktopWidget>
#include <QtCore/QDateTime>

const QString MainWindow::MESSAGE_TEMPLATE =
	"<p>"
		"<strong>%1</strong> "
		"<span style = \"font-style: italic; color: #808080;\">(%2)</span>"
		"<strong>:</strong> "
		"%3"
	"</p>";

MainWindow::MainWindow(void) :
	QMainWindow(NULL),
	first_time_show(true)
{
	ui.setupUi(this);
	ui.message_editor->installEventFilter(this);
	ui.message_editor->setFocus();

	//TODO: remove this line
	ui.interlocutors_view->addItems(QStringList() << "test1" << "test2");
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
	if (object == ui.message_editor && event->type() == QEvent::KeyPress) {
		QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
		if (key_event->key() == Qt::Key_Return) {
			if (!(key_event->modifiers() & Qt::ShiftModifier)) {
				on_send_button_clicked();
			} else {
				ui.message_editor->textCursor().insertText("\n");
			}

			return true;
		}
	}

	return QMainWindow::eventFilter(object, event);
}

void MainWindow::start(const QString& nickname) {
	this->nickname = nickname;
	setWindowTitle(QString("%1 - %2").arg(windowTitle()).arg(nickname));
	show();
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

	if (first_time_show) {
		QRect desktop_rectangle = QApplication::desktop()->availableGeometry();
		resize(desktop_rectangle.size() / 2);
		move(desktop_rectangle.center() - rect().center());

		int size = ui.global_splitter->height() / 3;
		ui.global_splitter->setSizes(QList<int>() << 2 * size << size);

		size = ui.views_splitter->width() / 3;
		ui.views_splitter->setSizes(QList<int>() << 2 * size << size);

		first_time_show = false;
	}
}

void MainWindow::addMessage(const Message& message) {
	QString text = message.text;
	text.replace(QRegExp("%(\\w+)%"), "<strong>\\1</strong>");
	text.replace(QRegExp("\r?\n\r?"), "<br />");

	ui.chat_view->append(
		MESSAGE_TEMPLATE
			.arg(message.nickname)
			.arg(message.date.toString("dd.mm.yyyy hh:mm:ss"))
			.arg(text)
	);
}

void MainWindow::on_interlocutors_view_itemClicked(QListWidgetItem* item) {
	ui.message_editor->textCursor().insertText(
		QString("%%1%").arg(item->text())
	);
}

void MainWindow::on_message_editor_textChanged(void) {
	ui.send_button->setEnabled(!ui.message_editor->toPlainText().isEmpty());
}

void MainWindow::on_send_button_clicked(void) {
	QString text = ui.message_editor->toPlainText();
	if (!text.isEmpty()) {
		ui.message_editor->clear();
		ui.message_editor->setFocus();

		emit message(Message(nickname, QDateTime::currentDateTime(), text));
		//TODO: remove this line
		addMessage(Message(nickname, QDateTime::currentDateTime(), text));
	}
}
