/****************************************************************************
** Meta object code from reading C++ file 'maskedmaninqt.h'
**
** Created: Tue Sep 16 10:04:18 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../maskedmaninqt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maskedmaninqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MaskedManInQt[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      40,   14,   14,   14, 0x08,
      71,   65,   14,   14, 0x08,
      89,   14,   14,   14, 0x08,
     115,  109,   14,   14, 0x08,
     143,  135,   14,   14, 0x08,
     167,   14,   14,   14, 0x08,
     191,  182,   14,   14, 0x08,
     208,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MaskedManInQt[] = {
    "MaskedManInQt\0\0on_play_button_clicked()\0"
    "on_exit_button_clicked()\0image\0"
    "showImage(QImage)\0getSliderMoved(int)\0"
    "value\0setSliderValue(int)\0min,max\0"
    "setSliderRange(int,int)\0getThreadEnd()\0"
    "isDetect\0showMmrInfo(int)\0"
    "on_pBtn_openVideo_clicked()\0"
};

void MaskedManInQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MaskedManInQt *_t = static_cast<MaskedManInQt *>(_o);
        switch (_id) {
        case 0: _t->on_play_button_clicked(); break;
        case 1: _t->on_exit_button_clicked(); break;
        case 2: _t->showImage((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 3: _t->getSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setSliderValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setSliderRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->getThreadEnd(); break;
        case 7: _t->showMmrInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pBtn_openVideo_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MaskedManInQt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MaskedManInQt::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MaskedManInQt,
      qt_meta_data_MaskedManInQt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MaskedManInQt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MaskedManInQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MaskedManInQt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MaskedManInQt))
        return static_cast<void*>(const_cast< MaskedManInQt*>(this));
    return QDialog::qt_metacast(_clname);
}

int MaskedManInQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
