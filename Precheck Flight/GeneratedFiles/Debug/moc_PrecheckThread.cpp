/****************************************************************************
** Meta object code from reading C++ file 'PrecheckThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PrecheckThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrecheckThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PrecheckThread_t {
    QByteArrayData data[16];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PrecheckThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PrecheckThread_t qt_meta_stringdata_PrecheckThread = {
    {
QT_MOC_LITERAL(0, 0, 14), // "PrecheckThread"
QT_MOC_LITERAL(1, 15, 12), // "sendToWindow"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "count"
QT_MOC_LITERAL(4, 35, 27), // "PrecheckStateMachine::State"
QT_MOC_LITERAL(5, 63, 5), // "state"
QT_MOC_LITERAL(6, 69, 28), // "PrecheckStateMachine::Status"
QT_MOC_LITERAL(7, 98, 6), // "status"
QT_MOC_LITERAL(8, 105, 7), // "message"
QT_MOC_LITERAL(9, 113, 19), // "sendDetailsToWindow"
QT_MOC_LITERAL(10, 133, 8), // "function"
QT_MOC_LITERAL(11, 142, 15), // "receiveFromPort"
QT_MOC_LITERAL(12, 158, 8), // "uint8_t*"
QT_MOC_LITERAL(13, 167, 7), // "content"
QT_MOC_LITERAL(14, 175, 6), // "size_t"
QT_MOC_LITERAL(15, 182, 4) // "size"

    },
    "PrecheckThread\0sendToWindow\0\0count\0"
    "PrecheckStateMachine::State\0state\0"
    "PrecheckStateMachine::Status\0status\0"
    "message\0sendDetailsToWindow\0function\0"
    "receiveFromPort\0uint8_t*\0content\0"
    "size_t\0size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrecheckThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   29,    2, 0x06 /* Public */,
       9,    4,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    2,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6, QMetaType::QString,    3,    5,    7,    8,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 6, QMetaType::QString, QMetaType::QString,    5,    7,   10,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,

       0        // eod
};

void PrecheckThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PrecheckThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToWindow((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< PrecheckStateMachine::State(*)>(_a[2])),(*reinterpret_cast< PrecheckStateMachine::Status(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->sendDetailsToWindow((*reinterpret_cast< PrecheckStateMachine::State(*)>(_a[1])),(*reinterpret_cast< PrecheckStateMachine::Status(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->receiveFromPort((*reinterpret_cast< uint8_t*(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PrecheckThread::*)(QString , PrecheckStateMachine::State , PrecheckStateMachine::Status , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrecheckThread::sendToWindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PrecheckThread::*)(PrecheckStateMachine::State , PrecheckStateMachine::Status , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PrecheckThread::sendDetailsToWindow)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PrecheckThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_PrecheckThread.data,
    qt_meta_data_PrecheckThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PrecheckThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrecheckThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PrecheckThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PrecheckThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PrecheckThread::sendToWindow(QString _t1, PrecheckStateMachine::State _t2, PrecheckStateMachine::Status _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PrecheckThread::sendDetailsToWindow(PrecheckStateMachine::State _t1, PrecheckStateMachine::Status _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
