#include "MainWindow.h"
#include <QtCore/QSettings>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	#include <QtWidgets/QDesktopWidget>
#else
	#include <QtGui/QDesktopWidget>
#endif
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
	first_time_show(true),
	client(NULL)
{
	ui.setupUi(this);
	ui.message_editor->installEventFilter(this);
	ui.message_editor->setFocus();
}

MainWindow::~MainWindow(void) {
	client_thread.exit();
	client_thread.wait(1000);
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
	setWindowTitle(QString("%1 - %2").arg(windowTitle()).arg(nickname));

	QSettings settings(
		QApplication::applicationDirPath() + "/settings.ini",
		QSettings::IniFormat
	);
	settings.beginGroup("City Chat");
	QString host = settings.value("host", "localhost").toString();
	uint port = settings.value("port", 8001).toUInt();
	settings.endGroup();

	client = new Client(host, port, nickname);
	client->moveToThread(&client_thread);
	#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
		connect(
			&client_thread,
			SIGNAL(finished()),
			client,
			SLOT(deleteLater())
		);
	#else
		connect(
			&client_thread,
			SIGNAL(terminated()),
			client,
			SLOT(deleteLater())
		);
	#endif
	connect(
		client,
		SIGNAL(interlocutors(QStringList)),
		this,
		SLOT(setInterlocutors(QStringList))
	);
	qRegisterMetaType<Message::Group>("Message::Group");
	connect(
		client,
		SIGNAL(messages(Message::Group)),
		this,
		SLOT(addMessages(Message::Group))
	);
	connect(this, SIGNAL(message(QString)), client, SLOT(sendMessage(QString)));
	connect(client, SIGNAL(error(QString)), this, SLOT(showError(QString)));
	client_thread.start();

	show();
}

void MainWindow::setInterlocutors(const QStringList& interlocutors) {
	while (ui.interlocutors_view->count()) {
		delete ui.interlocutors_view->takeItem(0);
	}

	ui.interlocutors_view->addItems(interlocutors);

	QSet<QString> current_interlocutors = interlocutors.toSet();
	QSet<QString> lost_interlocutors =
		this->interlocutors - current_interlocutors;
	foreach (const QString& interlocutor, lost_interlocutors) {
		addMessage(
			Message(
				"system",
				QDateTime::currentDateTime(),
				trUtf8("<span style = \"color: #888;\">чат покидает %1.</span>")
					.arg(interlocutor)
			)
		);
	}
	QSet<QString> new_interlocutors =
		current_interlocutors - this->interlocutors;
	foreach (const QString& interlocutor, new_interlocutors) {
		addMessage(
			Message(
				"system",
				QDateTime::currentDateTime(),
				trUtf8(
					"<span style = \"color: green;\">в чат входит %1.</span>"
				).arg(interlocutor)
			)
		);
	}
	this->interlocutors = current_interlocutors;
}

void MainWindow::addMessages(const Message::Group& messages) {
	foreach (const Message& message, messages) {
		addMessage(message);
	}
}

void MainWindow::showError(const QString& message) {
	addMessage(
		Message(
			"system",
			QDateTime::currentDateTime(),
			QString("<span style = \"color: red;\">%1.</span>").arg(message))
	);
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
			.arg(message.time.toString("dd.MM.yyyy hh:mm:ss"))
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

		emit message(text);
	}
}
