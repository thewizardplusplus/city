# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/thewizardplusplus/city_client/exceptions/CityClientException.h \
	source/thewizardplusplus/city_client/exceptions/HostResolveException.h \
	source/thewizardplusplus/city_client/exceptions/SendException.h \
	source/thewizardplusplus/city_client/exceptions/ReceiveException.h \
	source/thewizardplusplus/city_client/exceptions/EmptyMessageException.h \
	source/thewizardplusplus/city_client/exceptions/UnknownCommandException.h \
	source/thewizardplusplus/city_client/ConnectionPrivate.h \
	source/thewizardplusplus/city_client/Connection.h \
	source/thewizardplusplus/city_client/CommandLineArguments.h \
	source/thewizardplusplus/city_client/OptionsParser.h \
	source/thewizardplusplus/city_client/GenericOptionsParser.h \
	source/thewizardplusplus/city_client/ConnectionOptionsParser.h \
	source/thewizardplusplus/city_client/ConnectionOptions.h \
	source/thewizardplusplus/city_client/OptionsProcessorPrivate.h \
	source/thewizardplusplus/city_client/OptionsProcessor.h
SOURCES += \
	source/thewizardplusplus/city_client/exceptions/CityClientException.cpp \
	source/thewizardplusplus/city_client/exceptions/HostResolveException.cpp \
	source/thewizardplusplus/city_client/exceptions/SendException.cpp \
	source/thewizardplusplus/city_client/exceptions/ReceiveException.cpp \
	source/thewizardplusplus/city_client/exceptions/EmptyMessageException.cpp \
	source/thewizardplusplus/city_client/exceptions/UnknownCommandException.cpp \
	source/thewizardplusplus/city_client/ConnectionPrivate.cpp \
	source/thewizardplusplus/city_client/Connection.cpp \
	source/thewizardplusplus/city_client/CommandLineArguments.cpp \
	source/thewizardplusplus/city_client/OptionsParser.cpp \
	source/thewizardplusplus/city_client/GenericOptionsParser.cpp \
	source/thewizardplusplus/city_client/ConnectionOptionsParser.cpp \
	source/thewizardplusplus/city_client/ConnectionOptions.cpp \
	source/thewizardplusplus/city_client/OptionsProcessorPrivate.cpp \
	source/thewizardplusplus/city_client/OptionsProcessor.cpp \
	source/thewizardplusplus/city_client/main.cpp

# внешние библиотеки
LIBS += -lboost_program_options -lboost_system -lpthread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
