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
	source/ParameterizedEntity.h
SOURCES += \
	source/TextureFactory.cpp \
	source/Sprite.cpp \
	source/FontFactory.cpp \
	source/Label.cpp \
	source/LabelStyle.cpp \
	source/Entity.cpp \
	source/ParameterizedEntity.cpp \
	source/main.cpp

# внешние библиотеки
LIBS += -lsfml-system -lsfml-window -lsfml-graphics

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
