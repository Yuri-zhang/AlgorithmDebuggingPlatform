/****************************************************************************
** Meta object code from reading C++ file 'GeoRect.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Geometry/GeoRect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeoRect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GeoRect_t {
    uint offsetsAndSizes[2];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GeoRect_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_GeoRect_t qt_meta_stringdata_GeoRect = {
    {
        QT_MOC_LITERAL(0, 7)   // "GeoRect"
    },
    "GeoRect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeoRect[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void GeoRect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject GeoRect::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseGeo::staticMetaObject>(),
    qt_meta_stringdata_GeoRect.offsetsAndSizes,
    qt_meta_data_GeoRect,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GeoRect_t
, QtPrivate::TypeAndForceComplete<GeoRect, std::true_type>



>,
    nullptr
} };


const QMetaObject *GeoRect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeoRect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeoRect.stringdata0))
        return static_cast<void*>(this);
    return BaseGeo::qt_metacast(_clname);
}

int GeoRect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseGeo::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
