#ifndef BLE_HPP
#define BLE_HPP

#include <QFutureWatcher>
#include <QObject>
#include <QUuid>
#include <QString>

class BLECharacteristic;
typedef QList<BLECharacteristic*> BLECharacteristics;

class BLE: public QObject {
  Q_OBJECT
public:
  BLE(QObject* a_parent = 0);

  void connectDevice(QString a_address);

  // populate charactesristics information asynchronously
  void inquireCharacteristics();

  // once characteristicsReady is emitted, this is updated.
  BLECharacteristics* getCharacteristics();

  virtual ~BLE();

signals:
  void characteristicsReady();

private slots:
  void characteristicsReadyHandler();

private:
  QString                             m_address;
  BLECharacteristics                  m_characteristics;
  QFutureWatcher<BLECharacteristics>* m_futureCharacteristicsWatcher;
};

#endif // BLE_HPP
