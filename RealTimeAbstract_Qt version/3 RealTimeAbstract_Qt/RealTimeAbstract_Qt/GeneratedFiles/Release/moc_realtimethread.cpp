/****************************************************************************
** Meta object code from reading C++ file 'realtimethread.h'
**
** Created: Sat Oct 4 11:02:19 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../realtimethread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'realtimethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RealTimeThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   16,   15,   15, 0x05,
      46,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      73,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RealTimeThread[] = {
    "RealTimeThread\0\0,\0sendCameraImage(int,QImage)\0"
    "sendAbstractCount(int,int)\0timerTimeOut()\0"
};

void RealTimeThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RealTimeThread *_t = static_cast<RealTimeThread *>(_o);
        switch (_id) {
        case 0: _t->sendCameraImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 1: _t->sendAbstractCount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->timerTimeOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RealTimeThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RealTimeThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RealTimeThread,
      qt_meta_data_RealTimeThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RealTimeThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RealTimeThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RealTimeThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RealTimeThread))
        return static_cast<void*>(const_cast< RealTimeThread*>(this));
    return QThread::qt_metacast(_clname);
}

int RealTimeThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RealTimeThread::sendCameraImage(int _t1, QImage _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RealTimeThread::sendAbstractCount(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
