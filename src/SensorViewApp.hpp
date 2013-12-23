#ifndef SENSORVIEWAPP_HPP
#define SENSORVIEWAPP_HPP

#include <QObject>

class QGuiApplication;
class QQuickView;

class SensorViewApp: public QObject {
  Q_OBJECT
public:
  SensorViewApp(QObject* a_parent, int a_argc, char** a_argv);

  int exec();

  ~SensorViewApp();

private:
  QScopedPointer<QGuiApplication> m_app;
  QScopedPointer<QQuickView> m_view;
};

#endif // SENSORVIEWAPP_HPP