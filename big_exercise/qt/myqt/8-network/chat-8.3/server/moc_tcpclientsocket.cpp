/****************************************************************************
** Meta object code from reading C++ file 'tcpclientsocket.h'
**
** Created: Sun Sep 11 09:50:13 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tcpclientsocket.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpclientsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TcpClientSocket[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      19,   17,   16,   16, 0x05,
      46,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   16,   16,   16, 0x09,
      79,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TcpClientSocket[] = {
    "TcpClientSocket\0\0,\0updateClients(QString,int)\0"
    "disconnected(int)\0dataReceived()\0"
    "slotDisconnected()\0"
};

const QMetaObject TcpClientSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_TcpClientSocket,
      qt_meta_data_TcpClientSocket, 0 }
};

const QMetaObject *TcpClientSocket::metaObject() const
{
    return &staticMetaObject;
}

void *TcpClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClientSocket))
        return static_cast<void*>(const_cast< TcpClientSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int TcpClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateClients((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: disconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: dataReceived(); break;
        case 3: slotDisconnected(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TcpClientSocket::updateClients(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpClientSocket::disconnected(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE