# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/RenderInterfaceSFML.h \
	source/SystemInterfaceSFML.h \
	source/ShellFileInterface.h \
	source/EventListener.h \
	source/EventListenerFactory.h \
	source/DemoContext.h
SOURCES += \
	source/RenderInterfaceSFML.cpp \
	source/SystemInterfaceSFML.cpp \
	source/ShellFileInterface.cpp \
	source/EventListener.cpp \
	source/EventListenerFactory.cpp \
	source/DemoContext.cpp \
	source/main.cpp

# внешние библиотеки
LIBS += -L/usr/local/lib
LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lRocketCore -lRocketDebugger

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
