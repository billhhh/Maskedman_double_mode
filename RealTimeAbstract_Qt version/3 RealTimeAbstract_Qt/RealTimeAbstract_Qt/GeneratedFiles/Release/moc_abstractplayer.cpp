/****************************************************************************
** Meta object code from reading C++ file 'abstractplayer.h'
**
** Created: Sat Oct 4 11:02:17 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../abstractplayer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AbstractPlayer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      41,   15,   15,   15, 0x08,
      72,   66,   15,   15, 0x08,
      90,   15,   15,   15, 0x08,
     116,  110,   15,   15, 0x08,
     144,  136,   15,   15, 0x08,
     168,   15,   15,   15, 0x08,
     183,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AbstractPlayer[] = {
    "AbstractPlayer\0\0on_play_button_clicked()\0"
    "on_exit_button_clicked()\0image\0"
    "showImage(QImage)\0getSliderMoved(int)\0"
    "value\0setSliderValue(int)\0min,max\0"
    "setSliderRange(int,int)\0getThreadEnd()\0"
    "getLoopCheckBoxStateChange(int)\0"
};

void AbstractPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AbstractPlayer *_t = static_cast<AbstractPlayer *>(_o);
        switch (_id) {
        case 0: _t->on_play_button_clicked(); break;
        case 1: _t->on_exit_button_clicked(); break;
        case 2: _t->showImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->getSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setSliderRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->getThreadEnd(); break;
        case 7: _t->getLoopCheckBoxStateChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AbstractPlayer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AbstractPlayer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AbstractPlayer,
      qt_meta_data_AbstractPlayer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AbstractPlayer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AbstractPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AbstractPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractPlayer))
        return static_cast<void*>(const_cast< AbstractPlayer*>(this));
    return QDialog::qt_metacast(_clname);
}

int AbstractPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
