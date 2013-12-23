# The name of your app.
# NOTICE: name defined in TARGET has a corresponding QML filename.
#         If name defined in TARGET is changed, following needs to be
#         done to match new name:
#         - corresponding QML filename must be changed
#         - desktop icon filename must be changed
#         - desktop filename must be changed
#         - icon definition filename in desktop file must be changed
TARGET = SensorView

QT += concurrent

CONFIG += sailfishapp

QMAKE_CXXFLAGS += -std=c++0x

HEADERS += src/BLE.hpp src/Utils.hpp src/ListModel.hpp src/BLECharacteristic.hpp

SOURCES += src/SensorView.cpp src/BLE.cpp src/Utils.cpp src/ListModel.cpp src/BLECharacteristic.cpp

OTHER_FILES += qml/SensorView.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/SensorView.spec \
    rpm/SensorView.yaml \
    SensorView.desktop

