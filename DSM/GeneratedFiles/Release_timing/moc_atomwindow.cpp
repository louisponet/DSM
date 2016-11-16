/****************************************************************************
** Meta object code from reading C++ file 'atomwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/windows/atomwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'atomwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AtomWindow_t {
    QByteArrayData data[10];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AtomWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AtomWindow_t qt_meta_stringdata_AtomWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "AtomWindow"
QT_MOC_LITERAL(1, 11, 12), // "atomSelected"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "Particle"
QT_MOC_LITERAL(4, 34, 8), // "particle"
QT_MOC_LITERAL(5, 43, 14), // "updateListView"
QT_MOC_LITERAL(6, 58, 4), // "text"
QT_MOC_LITERAL(7, 63, 17), // "atomDoubleClicked"
QT_MOC_LITERAL(8, 81, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 98, 4) // "item"

    },
    "AtomWindow\0atomSelected\0\0Particle\0"
    "particle\0updateListView\0text\0"
    "atomDoubleClicked\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AtomWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x08 /* Private */,
       7,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void AtomWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AtomWindow *_t = static_cast<AtomWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->atomSelected((*reinterpret_cast< Particle(*)>(_a[1]))); break;
        case 1: _t->updateListView((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->atomDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AtomWindow::*_t)(Particle );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AtomWindow::atomSelected)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AtomWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AtomWindow.data,
      qt_meta_data_AtomWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AtomWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AtomWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AtomWindow.stringdata0))
        return static_cast<void*>(const_cast< AtomWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int AtomWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void AtomWindow::atomSelected(Particle _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
