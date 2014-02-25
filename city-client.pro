# общие настройки
CONFIG += warn_on

# файлы проекта
HEADERS += \
	source/StartWindow.h \
	source/Message.h \
	source/MainWindow.h
SOURCES += \
	source/StartWindow.cpp \
	source/Message.cpp \
	source/MainWindow.cpp \
	source/main.cpp
FORMS += \
	source/StartWindow.ui \
	source/MainWindow.ui
RESOURCES += \
	source/resources.qrc

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
# для игнорирования варнингов в хедерах Qt
QMAKE_CXXFLAGS += -Wno-long-long
