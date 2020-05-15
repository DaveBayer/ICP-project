/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[30];
    char stringdata0[418];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "timeChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "stopAnimation"
QT_MOC_LITERAL(4, 38, 15), // "resumeAnimation"
QT_MOC_LITERAL(5, 54, 15), // "editNextRoute_s"
QT_MOC_LITERAL(6, 70, 20), // "showConnectionInfo_s"
QT_MOC_LITERAL(7, 91, 42), // "std::vector<std::pair<std::st..."
QT_MOC_LITERAL(8, 134, 13), // "closeEditMode"
QT_MOC_LITERAL(9, 148, 11), // "updateClock"
QT_MOC_LITERAL(10, 160, 6), // "zoomIn"
QT_MOC_LITERAL(11, 167, 7), // "zoomOut"
QT_MOC_LITERAL(12, 175, 11), // "defaultZoom"
QT_MOC_LITERAL(13, 187, 7), // "setTime"
QT_MOC_LITERAL(14, 195, 11), // "toggleClock"
QT_MOC_LITERAL(15, 207, 11), // "fasterClock"
QT_MOC_LITERAL(16, 219, 11), // "slowerClock"
QT_MOC_LITERAL(17, 231, 9), // "actStreet"
QT_MOC_LITERAL(18, 241, 8), // "uint32_t"
QT_MOC_LITERAL(19, 250, 10), // "addTraffic"
QT_MOC_LITERAL(20, 261, 12), // "clearTraffic"
QT_MOC_LITERAL(21, 274, 15), // "changeLineRoute"
QT_MOC_LITERAL(22, 290, 17), // "getCollidingLines"
QT_MOC_LITERAL(23, 308, 15), // "updateLineRoute"
QT_MOC_LITERAL(24, 324, 18), // "std::vector<Point>"
QT_MOC_LITERAL(25, 343, 11), // "openStreets"
QT_MOC_LITERAL(26, 355, 17), // "getConnectionInfo"
QT_MOC_LITERAL(27, 373, 17), // "TransportVehicle*"
QT_MOC_LITERAL(28, 391, 14), // "setStatusLabel"
QT_MOC_LITERAL(29, 406, 11) // "std::string"

    },
    "MainWindow\0timeChanged\0\0stopAnimation\0"
    "resumeAnimation\0editNextRoute_s\0"
    "showConnectionInfo_s\0"
    "std::vector<std::pair<std::string,float> >\0"
    "closeEditMode\0updateClock\0zoomIn\0"
    "zoomOut\0defaultZoom\0setTime\0toggleClock\0"
    "fasterClock\0slowerClock\0actStreet\0"
    "uint32_t\0addTraffic\0clearTraffic\0"
    "changeLineRoute\0getCollidingLines\0"
    "updateLineRoute\0std::vector<Point>\0"
    "openStreets\0getConnectionInfo\0"
    "TransportVehicle*\0setStatusLabel\0"
    "std::string"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       3,    0,  132,    2, 0x06 /* Public */,
       4,    0,  133,    2, 0x06 /* Public */,
       5,    0,  134,    2, 0x06 /* Public */,
       6,    1,  135,    2, 0x06 /* Public */,
       8,    0,  138,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  139,    2, 0x08 /* Private */,
      10,    0,  140,    2, 0x08 /* Private */,
      11,    0,  141,    2, 0x08 /* Private */,
      12,    0,  142,    2, 0x08 /* Private */,
      13,    0,  143,    2, 0x08 /* Private */,
      14,    0,  144,    2, 0x08 /* Private */,
      15,    0,  145,    2, 0x08 /* Private */,
      16,    0,  146,    2, 0x08 /* Private */,
      17,    1,  147,    2, 0x08 /* Private */,
      19,    0,  150,    2, 0x08 /* Private */,
      20,    0,  151,    2, 0x08 /* Private */,
      21,    0,  152,    2, 0x08 /* Private */,
      22,    0,  153,    2, 0x08 /* Private */,
      23,    2,  154,    2, 0x08 /* Private */,
      25,    0,  159,    2, 0x08 /* Private */,
      26,    2,  160,    2, 0x08 /* Private */,
      28,    1,  165,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 24,    2,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18, 0x80000000 | 27,    2,    2,
    QMetaType::Void, 0x80000000 | 29,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->stopAnimation(); break;
        case 2: _t->resumeAnimation(); break;
        case 3: _t->editNextRoute_s(); break;
        case 4: _t->showConnectionInfo_s((*reinterpret_cast< std::vector<std::pair<std::string,float> >(*)>(_a[1]))); break;
        case 5: _t->closeEditMode(); break;
        case 6: _t->updateClock(); break;
        case 7: _t->zoomIn(); break;
        case 8: _t->zoomOut(); break;
        case 9: _t->defaultZoom(); break;
        case 10: _t->setTime(); break;
        case 11: _t->toggleClock(); break;
        case 12: _t->fasterClock(); break;
        case 13: _t->slowerClock(); break;
        case 14: _t->actStreet((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 15: _t->addTraffic(); break;
        case 16: _t->clearTraffic(); break;
        case 17: _t->changeLineRoute(); break;
        case 18: _t->getCollidingLines(); break;
        case 19: _t->updateLineRoute((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< std::vector<Point>(*)>(_a[2]))); break;
        case 20: _t->openStreets(); break;
        case 21: _t->getConnectionInfo((*reinterpret_cast< uint32_t(*)>(_a[1])),(*reinterpret_cast< TransportVehicle*(*)>(_a[2]))); break;
        case 22: _t->setStatusLabel((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 21:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TransportVehicle* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::timeChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopAnimation)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resumeAnimation)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::editNextRoute_s)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)(std::vector<std::pair<std::string,float>> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::showConnectionInfo_s)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeEditMode)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::timeChanged(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stopAnimation()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::resumeAnimation()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::editNextRoute_s()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::showConnectionInfo_s(std::vector<std::pair<std::string,float>> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::closeEditMode()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
