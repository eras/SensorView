#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QScopedPointer>
#include <sailfishapp.h>

#include "BLE.hpp"
#include "BLECharacteristic.hpp"
#include "ListModel.hpp"

#include "SensorViewApp.hpp"

SensorViewApp::SensorViewApp(QObject* a_parent, int a_argc, char** a_argv) :
  QObject(a_parent)
{
  m_app.reset(SailfishApp::application(a_argc, a_argv));
  m_view.reset(SailfishApp::createView());

  m_view->engine()->addImportPath(SailfishApp::pathTo("qml/components").toString());
  m_view->setSource(SailfishApp::pathTo("qml/SensorView.qml"));

  //BLE* ble = new BLE();
  //ble->inquireCharacteristics();

  ListModel* model = new ListModel(new BLECharacteristic);
  model->appendRow(new BLECharacteristic(QUuid(), "hello", 1, 2, 3));
  model->appendRow(new BLECharacteristic(QUuid(), "hello", 2, 3, 1));
  m_view->rootContext()->setContextProperty("characteristicsModel", model);

  m_view->show();
}

int
SensorViewApp::exec()
{
  return QGuiApplication::exec();
}

SensorViewApp::~SensorViewApp()
{
}
