/*
  Test Simple Logger for Qt

  Mario Ban, 06.2015

*/

#include "eventLog.h"
#include "simpleQtLogger.h"

#include <QMetaObject>
#include <QMetaEnum>

EventLog::EventLog(QObject *parent)
  : QObject(parent)
{
  L_FUNC("");
  qDebug("EventLog::EventLog"); // TODO comment this
}

EventLog::~EventLog()
{
  L_FUNC("");
  qDebug("EventLog::~EventLog"); // TODO comment this
}

bool EventLog::eventFilter(QObject *obj, QEvent *event)
{
  // L_FUNC("");

  if(obj && event) {
    const QMetaObject* metaObject = obj->metaObject();
    QEvent::Type eventType = event->type();

    if(eventType != QEvent::UpdateRequest) {
      int eventTypeEnumIndex = QEvent::staticMetaObject.indexOfEnumerator("Type");
      QString eventTypeName = QEvent::staticMetaObject.enumerator(eventTypeEnumIndex).valueToKey(eventType);

      QString text = QString("%1: QEvent type=%2 '%3'").arg(metaObject->className()).arg(eventType).arg(eventTypeName);
      emit eventInfo(text);
    }
  }
  // standard event processing
  return QObject::eventFilter(obj, event);
}
