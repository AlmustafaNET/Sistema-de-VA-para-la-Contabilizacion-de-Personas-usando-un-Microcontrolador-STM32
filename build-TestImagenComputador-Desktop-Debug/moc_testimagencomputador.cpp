/****************************************************************************
** Meta object code from reading C++ file 'testimagencomputador.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TestImagenComputador/testimagencomputador.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'testimagencomputador.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TestImagenComputador_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TestImagenComputador_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TestImagenComputador_t qt_meta_stringdata_TestImagenComputador = {
    {
QT_MOC_LITERAL(0, 0, 20), // "TestImagenComputador"
QT_MOC_LITERAL(1, 21, 7), // "onError"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "msg"
QT_MOC_LITERAL(4, 34, 11), // "onConectado"
QT_MOC_LITERAL(5, 46, 10), // "onRecibido"
QT_MOC_LITERAL(6, 57, 4), // "buff"
QT_MOC_LITERAL(7, 62, 22), // "on_btnCapturar_clicked"
QT_MOC_LITERAL(8, 85, 20) // "on_btnCerrar_clicked"

    },
    "TestImagenComputador\0onError\0\0msg\0"
    "onConectado\0onRecibido\0buff\0"
    "on_btnCapturar_clicked\0on_btnCerrar_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TestImagenComputador[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       5,    1,   45,    2, 0x08 /* Private */,
       7,    0,   48,    2, 0x08 /* Private */,
       8,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TestImagenComputador::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TestImagenComputador *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onConectado((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onRecibido((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->on_btnCapturar_clicked(); break;
        case 4: _t->on_btnCerrar_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TestImagenComputador::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_TestImagenComputador.data,
    qt_meta_data_TestImagenComputador,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TestImagenComputador::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TestImagenComputador::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TestImagenComputador.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TestImagenComputador::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
