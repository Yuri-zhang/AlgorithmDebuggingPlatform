/****************************************************************************
** Meta object code from reading C++ file 'LibImageView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../LibImageView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LibImageView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LibImageView_t {
    QByteArrayData data[21];
    char stringdata0[323];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LibImageView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LibImageView_t qt_meta_stringdata_LibImageView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LibImageView"
QT_MOC_LITERAL(1, 13, 21), // "signal_GeoViewChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 19), // "signal_mousePressed"
QT_MOC_LITERAL(4, 56, 1), // "x"
QT_MOC_LITERAL(5, 58, 1), // "y"
QT_MOC_LITERAL(6, 60, 20), // "signal_mouseReleased"
QT_MOC_LITERAL(7, 81, 17), // "signal_viewScaled"
QT_MOC_LITERAL(8, 99, 5), // "ratio"
QT_MOC_LITERAL(9, 105, 21), // "signal_rButtonPressed"
QT_MOC_LITERAL(10, 127, 16), // "signal_rButtonUp"
QT_MOC_LITERAL(11, 144, 17), // "signal_mouseMoved"
QT_MOC_LITERAL(12, 162, 23), // "signal_ContextMenuEvent"
QT_MOC_LITERAL(13, 186, 18), // "QContextMenuEvent*"
QT_MOC_LITERAL(14, 205, 5), // "event"
QT_MOC_LITERAL(15, 211, 24), // "signal_MapMouseMoveEvent"
QT_MOC_LITERAL(16, 236, 12), // "QMouseEvent*"
QT_MOC_LITERAL(17, 249, 12), // "slot_timeout"
QT_MOC_LITERAL(18, 262, 19), // "slot_GeoViewChanged"
QT_MOC_LITERAL(19, 282, 18), // "slot_RegionLimited"
QT_MOC_LITERAL(20, 301, 21) // "SlotMapMouseMoveEvent"

    },
    "LibImageView\0signal_GeoViewChanged\0\0"
    "signal_mousePressed\0x\0y\0signal_mouseReleased\0"
    "signal_viewScaled\0ratio\0signal_rButtonPressed\0"
    "signal_rButtonUp\0signal_mouseMoved\0"
    "signal_ContextMenuEvent\0QContextMenuEvent*\0"
    "event\0signal_MapMouseMoveEvent\0"
    "QMouseEvent*\0slot_timeout\0slot_GeoViewChanged\0"
    "slot_RegionLimited\0SlotMapMouseMoveEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LibImageView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    2,   80,    2, 0x06 /* Public */,
       6,    2,   85,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
       9,    2,   93,    2, 0x06 /* Public */,
      10,    2,   98,    2, 0x06 /* Public */,
      11,    2,  103,    2, 0x06 /* Public */,
      12,    1,  108,    2, 0x06 /* Public */,
      15,    1,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    0,  116,    2, 0x08 /* Private */,
      20,    1,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   14,

       0        // eod
};

void LibImageView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LibImageView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_GeoViewChanged(); break;
        case 1: _t->signal_mousePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signal_mouseReleased((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->signal_viewScaled((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->signal_rButtonPressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->signal_rButtonUp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->signal_mouseMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->signal_ContextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        case 8: _t->signal_MapMouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 9: _t->slot_timeout(); break;
        case 10: _t->slot_GeoViewChanged(); break;
        case 11: _t->slot_RegionLimited(); break;
        case 12: _t->SlotMapMouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LibImageView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_GeoViewChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_mousePressed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_mouseReleased)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_viewScaled)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_rButtonPressed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_rButtonUp)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_mouseMoved)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(QContextMenuEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_ContextMenuEvent)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(QMouseEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LibImageView::signal_MapMouseMoveEvent)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LibImageView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LibImageView.data,
    qt_meta_data_LibImageView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LibImageView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LibImageView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LibImageView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LibImageView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void LibImageView::signal_GeoViewChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LibImageView::signal_mousePressed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LibImageView::signal_mouseReleased(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LibImageView::signal_viewScaled(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void LibImageView::signal_rButtonPressed(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void LibImageView::signal_rButtonUp(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void LibImageView::signal_mouseMoved(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void LibImageView::signal_ContextMenuEvent(QContextMenuEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void LibImageView::signal_MapMouseMoveEvent(QMouseEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
