#ifndef BLECHARACTERISTIC_HPP
#define BLECHARACTERISTIC_HPP

#include <QString>
#include <QUuid>
#include "ListModel.hpp"

class BLECharacteristic: public ListItem {
  Q_OBJECT

public:
  enum Roles {
    UuidRole = Qt::UserRole + 1,
    LabelRole,
    HandleRole,
    PropertiesRole,
    ValueHandleRole
  };

  BLECharacteristic(QObject* a_parent = 0);
  BLECharacteristic(QUuid uuid, QString label, int handle, int properties, int valueHandle);

  ~BLECharacteristic();

  QVariant data(int role) const;
  QHash<int, QByteArray> roleNames() const;

  inline QString id()          const { return m_uuid.toString(); }
  inline QUuid   uuid()        const { return m_uuid; }
  inline QString label()       const { return m_label; }
  inline int     handle()      const { return m_handle; }
  inline int     properties()  const { return m_properties; }
  inline int     valueHandle() const { return m_valueHandle; }

private:
  BLECharacteristic(const BLECharacteristic& a_other); /// not there
  void operator=(const BLECharacteristic& a_other); /// not there

  QUuid   m_uuid;
  QString m_label;
  int     m_handle;
  int     m_properties;
  int     m_valueHandle;
};

#endif // BLECHARACTERISTIC_HPP
