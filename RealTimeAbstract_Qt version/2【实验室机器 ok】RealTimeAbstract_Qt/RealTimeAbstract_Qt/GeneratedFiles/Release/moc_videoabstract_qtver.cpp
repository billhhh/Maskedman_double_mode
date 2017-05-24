/****************************************************************************
** Meta object code from reading C++ file 'videoabstract_qtver.h'
**
** Created: Sat Oct 4 11:02:03 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../videoabstract_qtver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoabstract_qtver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoAbstract_QTver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   20,   20,   20, 0x08,
      78,   20,   20,   20, 0x08,
     107,   20,   20,   20, 0x08,
     135,   20,   20,   20, 0x08,
     166,   20,   20,   20, 0x08,
     193,   20,   20,   20, 0x08,
     225,   20,   20,   20, 0x08,
     261,  259,   20,   20, 0x08,
     283,   20,   20,   20, 0x08,
     300,   20,   20,   20, 0x08,
     326,  322,   20,   20, 0x08,
     368,   20,   20,   20, 0x08,
     395,   20,   20,   20, 0x08,
     424,   20,   20,   20, 0x08,
     454,   20,   20,   20, 0x08,
     470,   20,   20,   20, 0x08,
     485,   20,   20,   20, 0x08,
     507,   20,   20,   20, 0x08,
     525,   20,   20,   20, 0x08,
     546,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoAbstract_QTver[] = {
    "VideoAbstract_QTver\0\0sendSwitchToRealTimeForm()\0"
    "on_open_file_button_clicked()\0"
    "on_analysis_button_clicked()\0"
    "on_setting_button_clicked()\0"
    "on_pushButton_switch_clicked()\0"
    "on_search_button_clicked()\0"
    "on_pushButton_playAll_clicked()\0"
    "on_show_video_check_box_clicked()\0,\0"
    "showVideo(QImage,int)\0openFileFailed()\0"
    "updateProcessBar(int)\0,,,\0"
    "drawAbstracts(QImage,QString,QString,int)\0"
    "updateProcessInfo(QString)\0"
    "changeAnalyzeButton(QString)\0"
    "changeAnalyzeButtonState(int)\0"
    "updateRunTime()\0endTimeCount()\0"
    "updateEventCount(int)\0playAbstract(int)\0"
    "removeAllAbstracts()\0"
    "get_enter_checkbox_state(bool)\0"
};

void VideoAbstract_QTver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoAbstract_QTver *_t = static_cast<VideoAbstract_QTver *>(_o);
        switch (_id) {
        case 0: _t->sendSwitchToRealTimeForm(); break;
        case 1: _t->on_open_file_button_clicked(); break;
        case 2: _t->on_analysis_button_clicked(); break;
        case 3: _t->on_setting_button_clicked(); break;
        case 4: _t->on_pushButton_switch_clicked(); break;
        case 5: _t->on_search_button_clicked(); break;
        case 6: _t->on_pushButton_playAll_clicked(); break;
        case 7: _t->on_show_video_check_box_clicked(); break;
        case 8: _t->showVideo((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->openFileFailed(); break;
        case 10: _t->updateProcessBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->drawAbstracts((*reinterpret_cast< QImage(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 12: _t->updateProcessInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->changeAnalyzeButton((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->changeAnalyzeButtonState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->updateRunTime(); break;
        case 16: _t->endTimeCount(); break;
        case 17: _t->updateEventCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->playAbstract((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->removeAllAbstracts(); break;
        case 20: _t->get_enter_checkbox_state((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoAbstract_QTver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoAbstract_QTver::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoAbstract_QTver,
      qt_meta_data_VideoAbstract_QTver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoAbstract_QTver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoAbstract_QTver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoAbstract_QTver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoAbstract_QTver))
        return static_cast<void*>(const_cast< VideoAbstract_QTver*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoAbstract_QTver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void VideoAbstract_QTver::sendSwitchToRealTimeForm()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
