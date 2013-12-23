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
  Q_PROPERTY(bool inquiringCharacteristics READ isInquiringCharacteristics WRITE setInquiringCharacteristics NOTIFY inquiringCharacteristicsChanged);
public:
  BLE(QObject* a_parent = 0);

  void connectDevice(QString a_address);

  // populate charactesristics information asynchronously
  Q_INVOKABLE void inquireCharacteristics();

  // Is an inquiry in progress?  
  bool isInquiringCharacteristics() const { return m_inquiringCharacteristics; }

  // once characteristicsReady is emitted, this is updated.
  BLECharacteristics* getCharacteristics();

  virtual ~BLE();

signals:
  void characteristicsReady();
  void inquiringCharacteristicsChanged();

private slots:
  void characteristicsReadyHandler();

private:
  void setInquiringCharacteristics(bool a_inquiringCharacteristics) {
    m_inquiringCharacteristics = a_inquiringCharacteristics;
    emit inquiringCharacteristicsChanged();
  }

  QString                             m_address;
  BLECharacteristics                  m_characteristics;
  QFutureWatcher<BLECharacteristics>* m_futureCharacteristicsWatcher;
  bool                                m_inquiringCharacteristics;
};

#endif // BLE_HPP
