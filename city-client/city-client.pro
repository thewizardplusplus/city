# параметры сборки, специфичные для окружения
win32:BOOST_INCLUDES_PATH = E:\\boost_1_54_0
win32:BOOST_LIBS_PATH = E:\\boost_1_54_0\\stage\\lib

# общие настройки
CONFIG += warn_on
QT += svg

# файлы проекта
HEADERS += \
	source/MainWindow.h \
	source/GraphicsScene.h \
    source/DynamicSprite.h \
    source/MoveDirection.h
SOURCES += \
	source/main.cpp \
	source/MainWindow.cpp \
	source/GraphicsScene.cpp \
    source/DynamicSprite.cpp

# внешние библиотеки
win32 {
	INCLUDEPATH += $$BOOST_INCLUDES_PATH
	LIBS += -L$$BOOST_LIBS_PATH
	LIBS += \
		-lboost_regex-mgw48-mt-1_54 \
		-lboost_system-mgw48-mt-1_54 \
		-lboost_program_options-mgw48-mt-1_54 \
		-lboost_thread-mgw48-mt-1_54 \
		-lws2_32
}
unix:LIBS += \
	-lboost_regex \
	-lboost_system \
	-lboost_program_options \
	-lboost_thread

# флаги компилятора
QMAKE_CXXFLAGS += -std=c++03 -pedantic -Wall -W -O2
# отключение предупреждений в Qt и Boost
QMAKE_CXXFLAGS += -Wno-long-long
# отключение предупреждений в Boost
win32:QMAKE_CXXFLAGS += \
	-Wno-unused-local-typedefs \
	-fno-strict-aliasing

RESOURCES += \
	resources/resources.qrc
