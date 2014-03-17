# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/Sprite.h \
	source/Entity.h \
	source/VariableEntity.h \
	source/Level.h \
	source/Connection.h \
	source/ConnectionOptions.h \
	source/SpriteFactory.h
SOURCES += \
	source/Sprite.cpp \
	source/Entity.cpp \
	source/VariableEntity.cpp \
	source/Level.cpp \
	source/main.cpp \
	source/Connection.cpp \
	source/ConnectionOptions.cpp \
	source/SpriteFactory.cpp

# внешние библиотеки
LIBS += \
	-lsfml-system \
	-lsfml-window \
	-lsfml-graphics \
	-lboost_regex \
	-lboost_system \
	-lboost_program_options \
	-lboost_thread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
