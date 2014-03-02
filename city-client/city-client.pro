# общие настройки
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
LIBS += -lboost_program_options -lboost_system -lpthread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
# для игнорирования варнингов в хедерах Qt
QMAKE_CXXFLAGS += -Wno-long-long
