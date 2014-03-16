# общие настройки
CONFIG += console
CONFIG += warn_on
CONFIG -= qt

# файлы проекта
HEADERS += \
	source/TextureFactory.h \
	source/Sprite.h \
	source/FontFactory.h \
	source/Label.h \
	source/LabelStyle.h \
	source/Entity.h \
	source/VariableEntity.h \
	source/Level.h \
	source/Connection.h \
	source/ConnectionOptions.h
SOURCES += \
	source/TextureFactory.cpp \
	source/Sprite.cpp \
	source/FontFactory.cpp \
	source/Label.cpp \
	source/LabelStyle.cpp \
	source/Entity.cpp \
	source/VariableEntity.cpp \
	source/Level.cpp \
	source/main.cpp \
	source/Connection.cpp \
	source/ConnectionOptions.cpp

# внешние библиотеки
LIBS += \
	-lsfml-system \
	-lsfml-window \
	-lsfml-graphics \
	-lboost_regex \
	-lboost_system \
	-lboost_program_options

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
