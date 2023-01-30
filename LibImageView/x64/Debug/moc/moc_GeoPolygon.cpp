/****************************************************************************
** Meta object code from reading C++ file 'GeoPolygon.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Geometry/GeoPolygon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeoPolygon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GeoPolygon_t {
    uint offsetsAndSizes[8];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GeoPolygon_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_GeoPolygon_t qt_meta_stringdata_GeoPolygon = {
    {
        QT_MOC_LITERAL(0, 10),  // "GeoPolygon"
        QT_MOC_LITERAL(11, 11),  // "DeletePoint"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 8)   // "AddPoint"
    },
    "GeoPolygon",
    "DeletePoint",
    "",
    "AddPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeoPolygon[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x0a,    1 /* Public */,
       3,    0,   27,    2, 0x0a,    2 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GeoPolygon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GeoPolygon *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->DeletePoint(); break;
        case 1: _t->AddPoint(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject GeoPolygon::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseGeo::staticMetaObject>(),
    qt_meta_stringdata_GeoPolygon.offsetsAndSizes,
    qt_meta_data_GeoPolygon,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GeoPolygon_t
, QtPrivate::TypeAndForceComplete<GeoPolygon, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *GeoPolygon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeoPolygon::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeoPolygon.stringdata0))
        return static_cast<void*>(this);
    return BaseGeo::qt_metacast(_clname);
}

int GeoPolygon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseGeo::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
