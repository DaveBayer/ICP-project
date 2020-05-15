/****************************************************************************
** Meta object code from reading C++ file 'lineobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/lineobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lineobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LineObject_t {
    QByteArrayData data[14];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LineObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LineObject_t qt_meta_stringdata_LineObject = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LineObject"
QT_MOC_LITERAL(1, 11, 20), // "showConnectionInfo_s"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 19), // "getConnectionInfo_s"
QT_MOC_LITERAL(4, 53, 8), // "uint32_t"
QT_MOC_LITERAL(5, 62, 17), // "TransportVehicle*"
QT_MOC_LITERAL(6, 80, 12), // "startVehicle"
QT_MOC_LITERAL(7, 93, 11), // "timeChanged"
QT_MOC_LITERAL(8, 105, 13), // "stopAnimation"
QT_MOC_LITERAL(9, 119, 15), // "resumeAnimation"
QT_MOC_LITERAL(10, 135, 18), // "showConnectionInfo"
QT_MOC_LITERAL(11, 154, 42), // "std::vector<std::pair<std::st..."
QT_MOC_LITERAL(12, 197, 17), // "getConnectionInfo"
QT_MOC_LITERAL(13, 215, 1) // "v"

    },
    "LineObject\0showConnectionInfo_s\0\0"
    "getConnectionInfo_s\0uint32_t\0"
    "TransportVehicle*\0startVehicle\0"
    "timeChanged\0stopAnimation\0resumeAnimation\0"
    "showConnectionInfo\0"
    "std::vector<std::pair<std::string,float> >\0"
    "getConnectionInfo\0v"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LineObject[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   60,    2, 0x08 /* Private */,
       7,    1,   61,    2, 0x08 /* Private */,
       8,    0,   64,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    1,   66,    2, 0x08 /* Private */,
      12,    1,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,    2,
    QMetaType::Void, 0x80000000 | 5,   13,

       0        // eod
};

void LineObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LineObject *_t = static_cast<LineObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showConnectionInfo_s(); break;
        case 1: _t->getConnectionInfo_s((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< TransportVehicle*(*)>(_a[2]))); break;
        case 2: _t->startVehicle(); break;
        case 3: _t->timeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->stopAnimation(); break;
        case 5: _t->resumeAnimation(); break;
        case 6: _t->showConnectionInfo((*reinterpret_cast< std::vector<std::pair<std::string,float> >(*)>(_a[1]))); break;
        case 7: _t->getConnectionInfo((*reinterpret_cast< TransportVehicle*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TransportVehicle* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TransportVehicle* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (LineObject::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LineObject::showConnectionInfo_s)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (LineObject::*_t)(uint32_t , TransportVehicle * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LineObject::getConnectionInfo_s)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject LineObject::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LineObject.data,
      qt_meta_data_LineObject,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LineObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LineObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LineObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LineObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void LineObject::showConnectionInfo_s()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LineObject::getConnectionInfo_s(uint32_t _t1, TransportVehicle * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
