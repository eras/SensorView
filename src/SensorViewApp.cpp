#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QScopedPointer>
#include <sailfishapp.h>

#include <iostream>

#include "BLE.hpp"
#include "BLECharacteristic.hpp"
#include "ListModel.hpp"

#include "SensorViewApp.hpp"

SensorViewApp::SensorViewApp(QObject* a_parent, int a_argc, char** a_argv) :
  QObject(a_parent), m_ble(new BLE(this)), m_characteristicsModel(new ListModel(new BLECharacteristic, this))
{
  m_app = SailfishApp::application(a_argc, a_argv);
  m_view = SailfishApp::createView();

  m_view->engine()->addImportPath(SailfishApp::pathTo("qml/components").toString());
  m_view->setSource(SailfishApp::pathTo("qml/SensorView.qml"));

  m_view->rootContext()->setContextProperty("ble", m_ble);
  m_view->rootContext()->setContextProperty("characteristicsModel", m_characteristicsModel);

  m_view->show();

  connect(m_ble, SIGNAL(characteristicsReady()), this, SLOT(updateCharacteristics()));
  m_ble->connectDevice("34:B1:F7:D5:59:A2");
  m_ble->inquireCharacteristics();
}

void
SensorViewApp::updateCharacteristics()
{
  std::cerr << "Updating characteristics" << std::endl;
  m_characteristicsModel->clear();
  BLECharacteristics* characteristics = m_ble->getCharacteristics();
  for (auto c : *characteristics) {
    std::cerr << __LINE__ << std::endl;
    m_characteristicsModel->appendRow(c);
  }
}

int
SensorViewApp::exec()
{
  return QGuiApplication::exec();
}

SensorViewApp::~SensorViewApp()
{
}
