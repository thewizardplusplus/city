# общие настройки
equals(QT_MAJOR_VERSION, 5) {
	QT += widgets
}
CONFIG += warn_on

# файлы проекта
HEADERS += \
	source/StartWindow.h \
	source/Message.h \
	source/MainWindow.h \
	source/Connection.h \
	source/Client.h
SOURCES += \
	source/StartWindow.cpp \
	source/Message.cpp \
	source/MainWindow.cpp \
	source/Connection.cpp \
	source/Client.cpp \
	source/main.cpp
FORMS += \
	source/StartWindow.ui \
	source/MainWindow.ui
RESOURCES += \
	source/resources.qrc

# внешние библиотеки
unix {
	LIBS += -lboost_program_options -lboost_system -lpthread
}
win32 {
	INCLUDEPATH += E:\\boost_1_54_0
	LIBS += -LE:\\boost_1_54_0\\stage\\lib -lboost_program_options-mgw48-mt-1_54 -lboost_system-mgw48-mt-1_54 -lpthread -lws2_32
}

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
# для игнорирования варнингов в хедерах Qt
QMAKE_CXXFLAGS += -Wno-long-long -Wno-unused-local-typedefs -fno-strict-aliasing
