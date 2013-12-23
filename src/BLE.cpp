#include <iostream>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QRegExp>

#include "Utils.hpp"
#include "BLE.hpp"
#include "BLECharacteristic.hpp"

BLE::BLE(QObject* a_parent) :
  QObject(a_parent)
{
}

BLE::~BLE()
{
  // nothing
}

void
BLE::connectDevice(QString a_address)
{
  m_address = a_address;
}


void
BLE::inquireCharacteristics()
{
  auto future = QtConcurrent::run([]() -> BLECharacteristics {
      QList<QString> lines = readProcessLines("echo moi");
      BLECharacteristics results;
      // handle = 0x0002, char properties = 0x02, char value handle = 0x0003, uuid = 00002a00-0000-1000-8000-00805f9b34fb
      QRegExp re("^handle = ([^,]*), char properties = ([^,]*), char value handle = ([^,]*), uuid = (.*)$");
      for (auto line : lines) {
        // int   handle;
        // int   properties;
        // int   valueHandle;
        // QUuid uuid;
        if (re.exactMatch(line)) {
          auto strs = re.capturedTexts();
          bool ok = true;
          int handle;
          int properties;
          int valueHandle;
          QUuid uuid;
          handle              = strs[0].toInt(&ok, 0);
          if (ok) properties  = strs[1].toInt(&ok, 0);
          if (ok) valueHandle = strs[2].toInt(&ok, 0);
          if (ok) uuid        = QUuid(strs[3]);
          if (!ok) {
            // uh oh?
          } else {
            results.push_back(new BLECharacteristic(uuid, "", handle, properties, valueHandle));
          }
        } else {
          // uh oh?
        }
      }
      return results;
    });
  auto watcher = new QFutureWatcher<BLECharacteristics>();
  connect(watcher, SIGNAL(finished()), this, SLOT(characteristicsReady));
  watcher->setFuture(future);
}

BLECharacteristics*
BLE::getCharacteristics()
{
  return &m_characteristics;
}
