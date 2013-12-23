#include "BLECharacteristic.hpp"

BLECharacteristic::BLECharacteristic(QObject* a_parent) :
  ListItem(a_parent)
{
}

BLECharacteristic::BLECharacteristic(QUuid a_uuid, QString a_label, int a_handle, int a_properties, int a_valueHandle) :
  m_uuid(a_uuid), m_label(a_label), m_handle(a_handle), m_properties(a_properties), m_valueHandle(a_valueHandle)
{
  // nothing
}

QVariant
BLECharacteristic::data(int a_role) const
{
  switch (a_role) {
  case UuidRole: return uuid();
  case LabelRole: return label();
  case HandleRole: return handle();
  case PropertiesRole: return properties();
  case ValueHandleRole: return valueHandle();
  }
  return QVariant();
}

QHash<int, QByteArray>
BLECharacteristic::roleNames() const
{
  QHash<int, QByteArray> names;
  names[UuidRole] = "uuid";
  names[LabelRole] = "label";
  names[HandleRole] = "handle";
  names[PropertiesRole] = "properties";
  names[ValueHandleRole] = "valueHandle";
  return names;
}

BLECharacteristic::~BLECharacteristic()
{
  // nothing
}
