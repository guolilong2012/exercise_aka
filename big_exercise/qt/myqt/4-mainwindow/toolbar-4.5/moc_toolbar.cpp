/****************************************************************************
** Meta object code from reading C++ file 'toolbar.h'
**
** Created: Fri Sep 9 08:30:38 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "toolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ToolBar[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      31,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ToolBar[] = {
    "ToolBar\0\0slotComboBox(QString)\0"
    "slotSpinBox(QString)\0"
};

const QMetaObject ToolBar::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ToolBar,
      qt_meta_data_ToolBar, 0 }
};

const QMetaObject *ToolBar::metaObject() const
{
    return &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar))
        return static_cast<void*>(const_cast< ToolBar*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotComboBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: slotSpinBox((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
