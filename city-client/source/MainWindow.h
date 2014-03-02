#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Message.h"
#include "Client.h"
#include "ui_MainWindow.h"
#include <QtCore/QThread>

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);
	virtual ~MainWindow(void);
	virtual bool eventFilter(QObject* object, QEvent* event);

signals:
	void message(const QString& message);

public slots:
	void start(const QString& nickname);
	void setInterlocutors(const QStringList& interlocutors);
	void addMessages(const Message::Group& messages);
	void showError(const QString& message);

protected:
	virtual void showEvent(QShowEvent* event);

private:
	static const QString MESSAGE_TEMPLATE;

	Ui::MainWindow ui;
	bool first_time_show;
	Client* client;
	QThread client_thread;
	QSet<QString> interlocutors;

	void addMessage(const Message& message);

private slots:
	void on_interlocutors_view_itemClicked(QListWidgetItem* item);
	void on_message_editor_textChanged(void);
	void on_send_button_clicked(void);
};
#endif
