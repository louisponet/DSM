/****************************************************************************
** Meta object code from reading C++ file 'createstructurewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../src/windows/createstructurewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createstructurewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateStructureWindow_t {
    QByteArrayData data[24];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateStructureWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateStructureWindow_t qt_meta_stringdata_CreateStructureWindow = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CreateStructureWindow"
QT_MOC_LITERAL(1, 22, 16), // "structureCreated"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 10), // "Structure*"
QT_MOC_LITERAL(4, 51, 9), // "structure"
QT_MOC_LITERAL(5, 61, 16), // "destroyStructure"
QT_MOC_LITERAL(6, 78, 7), // "addAtom"
QT_MOC_LITERAL(7, 86, 8), // "Particle"
QT_MOC_LITERAL(8, 95, 4), // "atom"
QT_MOC_LITERAL(9, 100, 10), // "updateCell"
QT_MOC_LITERAL(10, 111, 1), // "i"
QT_MOC_LITERAL(11, 113, 1), // "j"
QT_MOC_LITERAL(12, 115, 17), // "plusButtonClicked"
QT_MOC_LITERAL(13, 133, 16), // "minButtonClicked"
QT_MOC_LITERAL(14, 150, 19), // "createButtonClicked"
QT_MOC_LITERAL(15, 170, 8), // "editAtom"
QT_MOC_LITERAL(16, 179, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(17, 197, 4), // "item"
QT_MOC_LITERAL(18, 202, 9), // "editCoord"
QT_MOC_LITERAL(19, 212, 8), // "editName"
QT_MOC_LITERAL(20, 221, 4), // "name"
QT_MOC_LITERAL(21, 226, 19), // "cancelButtonClicked"
QT_MOC_LITERAL(22, 246, 17), // "comboBoxSelection"
QT_MOC_LITERAL(23, 264, 10) // "cellLayout"

    },
    "CreateStructureWindow\0structureCreated\0"
    "\0Structure*\0structure\0destroyStructure\0"
    "addAtom\0Particle\0atom\0updateCell\0i\0j\0"
    "plusButtonClicked\0minButtonClicked\0"
    "createButtonClicked\0editAtom\0"
    "QTableWidgetItem*\0item\0editCoord\0"
    "editName\0name\0cancelButtonClicked\0"
    "comboBoxSelection\0cellLayout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateStructureWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   78,    2, 0x0a /* Public */,
       9,    2,   81,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    1,   89,    2, 0x08 /* Private */,
      18,    1,   92,    2, 0x08 /* Private */,
      19,    1,   95,    2, 0x08 /* Private */,
      21,    0,   98,    2, 0x08 /* Private */,
      22,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void CreateStructureWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateStructureWindow *_t = static_cast<CreateStructureWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->structureCreated((*reinterpret_cast< Structure*(*)>(_a[1]))); break;
        case 1: _t->destroyStructure(); break;
        case 2: _t->addAtom((*reinterpret_cast< Particle(*)>(_a[1]))); break;
        case 3: _t->updateCell((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->plusButtonClicked(); break;
        case 5: _t->minButtonClicked(); break;
        case 6: _t->createButtonClicked(); break;
        case 7: _t->editAtom((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->editCoord((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->editName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->cancelButtonClicked(); break;
        case 11: _t->comboBoxSelection((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CreateStructureWindow::*_t)(Structure * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateStructureWindow::structureCreated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CreateStructureWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CreateStructureWindow::destroyStructure)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CreateStructureWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreateStructureWindow.data,
      qt_meta_data_CreateStructureWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateStructureWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateStructureWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateStructureWindow.stringdata0))
        return static_cast<void*>(const_cast< CreateStructureWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreateStructureWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CreateStructureWindow::structureCreated(Structure * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CreateStructureWindow::destroyStructure()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
