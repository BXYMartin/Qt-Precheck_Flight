/****************************************************************************
** Meta object code from reading C++ file 'PrecheckFlight.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PrecheckFlight.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrecheckFlight.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrecheckFlight_t {
    QByteArrayData data[20];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrecheckFlight_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrecheckFlight_t qt_meta_stringdata_PrecheckFlight = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PrecheckFlight"
QT_MOC_LITERAL(1, 15, 12), // "sendToWorker"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "uint8_t*"
QT_MOC_LITERAL(4, 38, 7), // "content"
QT_MOC_LITERAL(5, 46, 6), // "size_t"
QT_MOC_LITERAL(6, 53, 4), // "size"
QT_MOC_LITERAL(7, 58, 8), // "testComm"
QT_MOC_LITERAL(8, 67, 11), // "sendMessage"
QT_MOC_LITERAL(9, 79, 9), // "beginTest"
QT_MOC_LITERAL(10, 89, 7), // "endTest"
QT_MOC_LITERAL(11, 97, 17), // "receiveFromWorker"
QT_MOC_LITERAL(12, 115, 5), // "trail"
QT_MOC_LITERAL(13, 121, 27), // "PrecheckStateMachine::State"
QT_MOC_LITERAL(14, 149, 5), // "state"
QT_MOC_LITERAL(15, 155, 28), // "PrecheckStateMachine::Status"
QT_MOC_LITERAL(16, 184, 6), // "status"
QT_MOC_LITERAL(17, 191, 7), // "message"
QT_MOC_LITERAL(18, 199, 14), // "printToConsole"
QT_MOC_LITERAL(19, 214, 13) // "printToOutput"

    },
    "PrecheckFlight\0sendToWorker\0\0uint8_t*\0"
    "content\0size_t\0size\0testComm\0sendMessage\0"
    "beginTest\0endTest\0receiveFromWorker\0"
    "trail\0PrecheckStateMachine::State\0"
    "state\0PrecheckStateMachine::Status\0"
    "status\0message\0printToConsole\0"
    "printToOutput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrecheckFlight[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    4,   63,    2, 0x0a /* Public */,
      18,    1,   72,    2, 0x0a /* Public */,
      19,    2,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 13, 0x80000000 | 15, QMetaType::QString,   12,   14,   16,   17,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void PrecheckFlight::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PrecheckFlight *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToWorker((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        case 1: _t->testComm(); break;
        case 2: _t->sendMessage(); break;
        case 3: _t->beginTest(); break;
        case 4: _t->endTest(); break;
        case 5: _t->receiveFromWorker((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< PrecheckStateMachine::State(*)>(_a[2])),(*reinterpret_cast< PrecheckStateMachine::Status(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 6: _t->printToConsole((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->printToOutput((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrecheckFlight::*)(uint8_t * , size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrecheckFlight::sendToWorker)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PrecheckFlight::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_PrecheckFlight.data,
    qt_meta_data_PrecheckFlight,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrecheckFlight::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrecheckFlight::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrecheckFlight.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PrecheckFlight::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PrecheckFlight::sendToWorker(uint8_t * _t1, size_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_PortHandler_t {
    QByteArrayData data[7];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PortHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PortHandler_t qt_meta_stringdata_PortHandler = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PortHandler"
QT_MOC_LITERAL(1, 12, 14), // "printToConsole"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "uint8_t*"
QT_MOC_LITERAL(4, 37, 7), // "content"
QT_MOC_LITERAL(5, 45, 6), // "size_t"
QT_MOC_LITERAL(6, 52, 4) // "size"

    },
    "PortHandler\0printToConsole\0\0uint8_t*\0"
    "content\0size_t\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PortHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,

       0        // eod
};

void PortHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PortHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->printToConsole((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PortHandler::*)(uint8_t * , size_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PortHandler::printToConsole)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PortHandler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PortHandler.data,
    qt_meta_data_PortHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PortHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PortHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PortHandler.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CSerialPortHandle"))
        return static_cast< CSerialPortHandle*>(this);
    return QObject::qt_metacast(_clname);
}

int PortHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PortHandler::printToConsole(uint8_t * _t1, size_t _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
