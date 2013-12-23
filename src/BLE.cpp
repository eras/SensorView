#include <iostream>

#include <QtConcurrent>
#include <QDebug>
#include <QFuture>
#include <QFutureWatcher>
#include <QRegExp>

#include "Utils.hpp"
#include "BLE.hpp"
#include "BLECharacteristic.hpp"

BLE::BLE(QObject* a_parent) :
  QObject(a_parent), m_futureCharacteristicsWatcher(new QFutureWatcher<BLECharacteristics>(this)), m_inquiringCharacteristics(false)
{
  connect(m_futureCharacteristicsWatcher, SIGNAL(finished()), this, SLOT(characteristicsReadyHandler()));
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
BLE::characteristicsReadyHandler()
{
  m_characteristics = m_futureCharacteristicsWatcher->future().result();
  setInquiringCharacteristics(false);
  emit characteristicsReady();
}

void
BLE::inquireCharacteristics()
{
  if (m_inquiringCharacteristics) {
    return;
  }
  auto future = QtConcurrent::run([this]() -> BLECharacteristics {
      std::cerr << "Querying" << std::endl;
      // TODO: attacks lie here
      QList<QString> lines = readProcessLines("gatttool -b " + m_address + " --characteristics");
      BLECharacteristics results;
      // handle = 0x0002, char properties = 0x02, char value handle = 0x0003, uuid = 00002a00-0000-1000-8000-00805f9b34fb
      QRegExp re("^handle = 0x([^,]*), char properties = 0x([^,]*), char value handle = 0x([^,]*), uuid = (.*)$");
      int count = 0;
      int misses1 = 0;
      int misses2 = 0;
      // error: Transport endpoint is not connected (107)
      for (auto line : lines) {
        // int   handle;
        // int   properties;
        // int   valueHandle;
        // QUuid uuid;
        if (re.exactMatch(line)) {
          ++count;
          auto strs = re.capturedTexts();
          bool ok = true;
          int handle;
          int properties;
          int valueHandle;
          QUuid uuid;
          handle              = strs[1].toInt(&ok, 16);
          if (ok) properties  = strs[2].toInt(&ok, 16);
          if (ok) valueHandle = strs[3].toInt(&ok, 16);
          if (ok) uuid        = QUuid(strs[4]);
          if (!ok) {
            ++misses1;
            // uh oh?
          } else {
            results.push_back(new BLECharacteristic(uuid, "", handle, properties, valueHandle));
          }
        } else {
          ++misses2;
          // uh oh?
        }
      }
      std::cerr << "Querying complete, " << count << " lines, " << misses1 << "/" << misses2 << " misses" << " " << results.size() << " results" << std::endl;
      return results;
    });
  setInquiringCharacteristics(true);
  m_futureCharacteristicsWatcher->setFuture(future);
}

BLECharacteristics*
BLE::getCharacteristics()
{
  std::cerr << __FUNCTION__ << std::endl;
  return &m_characteristics;
}
