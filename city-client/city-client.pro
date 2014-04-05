# параметры сборки, специфичные для окружения
win32:SFML_INCLUDES_PATH = E:\\SFML-1.6\\include
win32:SFML_LIBS_PATH = E:\\SFML-1.6\\lib
win32:BOOST_INCLUDES_PATH = E:\\boost_1_54_0
win32:BOOST_LIBS_PATH = E:\\boost_1_54_0\\stage\\lib

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
win32 {
	INCLUDEPATH += $$BOOST_INCLUDES_PATH $$SFML_INCLUDES_PATH
	LIBS += -L$$BOOST_LIBS_PATH -L$$SFML_LIBS_PATH
	LIBS += \
		-lsfml-system \
		-lsfml-window \
		-lsfml-graphics \
		-lboost_regex-mgw48-mt-1_54 \
		-lboost_system-mgw48-mt-1_54 \
		-lboost_program_options-mgw48-mt-1_54 \
		-lboost_thread-mgw48-mt-1_54 \
		-lws2_32
}
unix:LIBS += \
	-lsfml-system \
	-lsfml-window \
	-lsfml-graphics \
	-lboost_regex \
	-lboost_system \
	-lboost_program_options \
	-lboost_thread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
# отключение предупреждений в Boost
win32:QMAKE_CXXFLAGS += \
	-Wno-long-long \
	-Wno-unused-local-typedefs \
	-fno-strict-aliasing
