/********************************************************************************
** Form generated from reading UI file 'testimagencomputador.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTIMAGENCOMPUTADOR_H
#define UI_TESTIMAGENCOMPUTADOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestImagenComputador
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *lblPic;
    QPushButton *btnCapturar;
    QPushButton *btnCerrar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TestImagenComputador)
    {
        if (TestImagenComputador->objectName().isEmpty())
            TestImagenComputador->setObjectName(QString::fromUtf8("TestImagenComputador"));
        TestImagenComputador->resize(878, 597);
        centralWidget = new QWidget(TestImagenComputador);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblPic = new QLabel(centralWidget);
        lblPic->setObjectName(QString::fromUtf8("lblPic"));

        verticalLayout->addWidget(lblPic);

        btnCapturar = new QPushButton(centralWidget);
        btnCapturar->setObjectName(QString::fromUtf8("btnCapturar"));

        verticalLayout->addWidget(btnCapturar);

        btnCerrar = new QPushButton(centralWidget);
        btnCerrar->setObjectName(QString::fromUtf8("btnCerrar"));

        verticalLayout->addWidget(btnCerrar);

        TestImagenComputador->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TestImagenComputador);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TestImagenComputador->setStatusBar(statusBar);

        retranslateUi(TestImagenComputador);

        QMetaObject::connectSlotsByName(TestImagenComputador);
    } // setupUi

    void retranslateUi(QMainWindow *TestImagenComputador)
    {
        TestImagenComputador->setWindowTitle(QApplication::translate("TestImagenComputador", "TestImagenComputador", nullptr));
        lblPic->setText(QString());
        btnCapturar->setText(QApplication::translate("TestImagenComputador", "Capturar", nullptr));
        btnCerrar->setText(QApplication::translate("TestImagenComputador", "Cerrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestImagenComputador: public Ui_TestImagenComputador {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTIMAGENCOMPUTADOR_H
