#ifndef SENSORVIEWAPP_HPP
#define SENSORVIEWAPP_HPP

#include <QObject>

class QGuiApplication;
class QQuickView;

class BLE;
class ListModel;

class SensorViewApp: public QObject {
  Q_OBJECT
public:
  SensorViewApp(QObject* a_parent, int a_argc, char** a_argv);

  int exec();

  ~SensorViewApp();

private slots:
  void updateCharacteristics();

private:
  QGuiApplication* m_app;
  QQuickView*      m_view;
  BLE*             m_ble;
  ListModel*       m_characteristicsModel;
};

#endif // SENSORVIEWAPP_HPP
