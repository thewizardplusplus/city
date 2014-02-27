#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "ui_StartWindow.h"

class StartWindow : public QDialog {
Q_OBJECT

public:
	StartWindow(void);

signals:
	void login(const QString& nickname);

protected:
	virtual void showEvent(QShowEvent* event);

private:
	Ui::StartWindow ui;
	bool first_time_show;

private slots:
	void on_nickname_editor_textEdited(const QString& text);
	void on_login_button_clicked(void);
};
#endif
