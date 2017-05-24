/****************************************************************************
** Meta object code from reading C++ file 'playthread.h'
**
** Created: Sat Oct 4 11:02:16 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../playthread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlayThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      36,   34,   11,   11, 0x05,
      61,   11,   11,   11, 0x05,
      82,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_PlayThread[] = {
    "PlayThread\0\0sendPlayImage(QImage)\0,\0"
    "sendSliderRange(int,int)\0sendSliderValue(int)\0"
    "threadEnd()\0"
};

void PlayThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlayThread *_t = static_cast<PlayThread *>(_o);
        switch (_id) {
        case 0: _t->sendPlayImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->sendSliderRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->threadEnd(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlayThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlayThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_PlayThread,
      qt_meta_data_PlayThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlayThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlayThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlayThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayThread))
        return static_cast<void*>(const_cast< PlayThread*>(this));
    return QThread::qt_metacast(_clname);
}

int PlayThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PlayThread::sendPlayImage(QImage _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayThread::sendSliderRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayThread::sendSliderValue(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayThread::threadEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
