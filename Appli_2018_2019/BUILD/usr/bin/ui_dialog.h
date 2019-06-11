/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpinBox *nombre1;
    QComboBox *operation;
    QSpinBox *nombre2;
    QPushButton *boutonEgal;
    QLabel *resultat;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(494, 300);
        horizontalLayout_2 = new QHBoxLayout(Dialog);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        nombre1 = new QSpinBox(Dialog);
        nombre1->setObjectName(QStringLiteral("nombre1"));

        horizontalLayout->addWidget(nombre1);

        operation = new QComboBox(Dialog);
        operation->setObjectName(QStringLiteral("operation"));

        horizontalLayout->addWidget(operation);

        nombre2 = new QSpinBox(Dialog);
        nombre2->setObjectName(QStringLiteral("nombre2"));

        horizontalLayout->addWidget(nombre2);

        boutonEgal = new QPushButton(Dialog);
        boutonEgal->setObjectName(QStringLiteral("boutonEgal"));

        horizontalLayout->addWidget(boutonEgal);

        resultat = new QLabel(Dialog);
        resultat->setObjectName(QStringLiteral("resultat"));

        horizontalLayout->addWidget(resultat);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
        operation->clear();
        operation->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "+", Q_NULLPTR)
         << QApplication::translate("Dialog", "-", Q_NULLPTR)
        );
        boutonEgal->setText(QApplication::translate("Dialog", "=", Q_NULLPTR));
        resultat->setText(QApplication::translate("Dialog", "hello", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
