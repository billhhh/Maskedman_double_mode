/****************************************************************************
** Meta object code from reading C++ file 'visualcontrol.h'
**
** Created: Tue 1. Feb 21:16:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../gui/visualcontrol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'visualcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_gui__VisualControl[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      43,   19,   19,   19, 0x0a,
      61,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_gui__VisualControl[] = {
    "gui::VisualControl\0\0captureTrainingImage()\0"
    "trainRecognizer()\0recognizeFaces()\0"
};

const QMetaObject gui::VisualControl::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_gui__VisualControl,
      qt_meta_data_gui__VisualControl, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &gui::VisualControl::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *gui::VisualControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *gui::VisualControl::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_gui__VisualControl))
        return static_cast<void*>(const_cast< VisualControl*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int gui::VisualControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: captureTrainingImage(); break;
        case 1: trainRecognizer(); break;
        case 2: recognizeFaces(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
