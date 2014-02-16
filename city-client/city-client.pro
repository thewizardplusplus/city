# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/thewizardplusplus/city_client/Connection.h \
	source/thewizardplusplus/city_client/ReceiveMessageListener.h
SOURCES += \
	source/thewizardplusplus/city_client/Connection.cpp \
	source/thewizardplusplus/city_client/ReceiveMessageListener.cpp \
	source/thewizardplusplus/city_client/main.cpp

# внешние библиотеки
LIBS += -lboost_system -lpthread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
