/****************************************************************************
** Meta object code from reading C++ file 'LibImageView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../LibImageView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LibImageView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LibImageView_t {
    uint offsetsAndSizes[42];
    char stringdata0[13];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[20];
    char stringdata4[2];
    char stringdata5[2];
    char stringdata6[21];
    char stringdata7[18];
    char stringdata8[6];
    char stringdata9[22];
    char stringdata10[17];
    char stringdata11[18];
    char stringdata12[24];
    char stringdata13[19];
    char stringdata14[6];
    char stringdata15[25];
    char stringdata16[13];
    char stringdata17[13];
    char stringdata18[20];
    char stringdata19[19];
    char stringdata20[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_LibImageView_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_LibImageView_t qt_meta_stringdata_LibImageView = {
    {
        QT_MOC_LITERAL(0, 12),  // "LibImageView"
        QT_MOC_LITERAL(13, 21),  // "signal_GeoViewChanged"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 19),  // "signal_mousePressed"
        QT_MOC_LITERAL(56, 1),  // "x"
        QT_MOC_LITERAL(58, 1),  // "y"
        QT_MOC_LITERAL(60, 20),  // "signal_mouseReleased"
        QT_MOC_LITERAL(81, 17),  // "signal_viewScaled"
        QT_MOC_LITERAL(99, 5),  // "ratio"
        QT_MOC_LITERAL(105, 21),  // "signal_rButtonPressed"
        QT_MOC_LITERAL(127, 16),  // "signal_rButtonUp"
        QT_MOC_LITERAL(144, 17),  // "signal_mouseMoved"
        QT_MOC_LITERAL(162, 23),  // "signal_ContextMenuEvent"
        QT_MOC_LITERAL(186, 18),  // "QContextMenuEvent*"
        QT_MOC_LITERAL(205, 5),  // "event"
        QT_MOC_LITERAL(211, 24),  // "signal_MapMouseMoveEvent"
        QT_MOC_LITERAL(236, 12),  // "QMouseEvent*"
        QT_MOC_LITERAL(249, 12),  // "slot_timeout"
        QT_MOC_LITERAL(262, 19),  // "slot_GeoViewChanged"
        QT_MOC_LITERAL(282, 18),  // "slot_RegionLimited"
        QT_MOC_LITERAL(301, 21)   // "SlotMapMouseMoveEvent"
    },
    "LibImageView",
    "signal_GeoViewChanged",
    "",
    "signal_mousePressed",
    "x",
    "y",
    "signal_mouseReleased",
    "signal_viewScaled",
    "ratio",
    "signal_rButtonPressed",
    "signal_rButtonUp",
    "signal_mouseMoved",
    "signal_ContextMenuEvent",
    "QContextMenuEvent*",
    "event",
    "signal_MapMouseMoveEvent",
    "QMouseEvent*",
    "slot_timeout",
    "slot_GeoViewChanged",
    "slot_RegionLimited",
    "SlotMapMouseMoveEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LibImageView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x06,    1 /* Public */,
       3,    2,   93,    2, 0x06,    2 /* Public */,
       6,    2,   98,    2, 0x06,    5 /* Public */,
       7,    1,  103,    2, 0x06,    8 /* Public */,
       9,    2,  106,    2, 0x06,   10 /* Public */,
      10,    2,  111,    2, 0x06,   13 /* Public */,
      11,    2,  116,    2, 0x06,   16 /* Public */,
      12,    1,  121,    2, 0x06,   19 /* Public */,
      15,    1,  124,    2, 0x06,   21 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      17,    0,  127,    2, 0x08,   23 /* Private */,
      18,    0,  128,    2, 0x08,   24 /* Private */,
      19,    0,  129,    2, 0x08,   25 /* Private */,
      20,    1,  130,    2, 0x08,   26 /* Private */,

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
        (void)_t;
        switch (_id) {
        case 0: _t->signal_GeoViewChanged(); break;
        case 1: _t->signal_mousePressed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 2: _t->signal_mouseReleased((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->signal_viewScaled((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 4: _t->signal_rButtonPressed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->signal_rButtonUp((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->signal_mouseMoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 7: _t->signal_ContextMenuEvent((*reinterpret_cast< std::add_pointer_t<QContextMenuEvent*>>(_a[1]))); break;
        case 8: _t->signal_MapMouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 9: _t->slot_timeout(); break;
        case 10: _t->slot_GeoViewChanged(); break;
        case 11: _t->slot_RegionLimited(); break;
        case 12: _t->SlotMapMouseMoveEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LibImageView::*)();
            if (_t _q_method = &LibImageView::signal_GeoViewChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (_t _q_method = &LibImageView::signal_mousePressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (_t _q_method = &LibImageView::signal_mouseReleased; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(double );
            if (_t _q_method = &LibImageView::signal_viewScaled; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (_t _q_method = &LibImageView::signal_rButtonPressed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (_t _q_method = &LibImageView::signal_rButtonUp; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(int , int );
            if (_t _q_method = &LibImageView::signal_mouseMoved; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(QContextMenuEvent * );
            if (_t _q_method = &LibImageView::signal_ContextMenuEvent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (LibImageView::*)(QMouseEvent * );
            if (_t _q_method = &LibImageView::signal_MapMouseMoveEvent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
    }
}

const QMetaObject LibImageView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_LibImageView.offsetsAndSizes,
    qt_meta_data_LibImageView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LibImageView_t
, QtPrivate::TypeAndForceComplete<LibImageView, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QContextMenuEvent *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>


>,
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
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
