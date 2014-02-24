#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Message.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(void);
	virtual bool eventFilter(QObject* object, QEvent* event);

signals:
	void message(const Message& message);

public slots:
	void setInterlocutors(const QStringList& interlocutors);
	void addMessages(const Message::Group& messages);

protected:
	virtual void showEvent(QShowEvent* event);

private:
	static const QString MESSAGE_TEMPLATE;

	Ui::MainWindow ui;
	bool processed;

	void addMessage(const Message& message);

private slots:
	void selectInterlocutor(QListWidgetItem* item);
	void updateSendButton(void);
	void sendMessage(void);
};
#endif
