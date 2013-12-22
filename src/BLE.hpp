#ifndef BLE_HPP
#define BLE_HPP

#include <QObject>
#include <QUuid>
#include <QString>

struct BLECharacteristic {
  int   handle;
  int   properties;
  int   valueHandle;
  QUuid uuid;
};

typedef QList<BLECharacteristic> BLECharacteristics;

class BLE: public QObject {
  Q_OBJECT
public:
  BLE(QObject* a_parent = 0);

  void connectDevice(QString a_address);

  // populate charactesristics information asynchronously
  void inquireCharacteristics();

  // once characteristicsReady is emitted, use this to get them
  QList<BLECharacteristic> getCharacteristics() const;

  virtual ~BLE();

signals:
  void characteristicsReady();

private slots:

private:
  QString            m_address;
  BLECharacteristics m_characteristisc;
};

#endif // BLE_HPP
