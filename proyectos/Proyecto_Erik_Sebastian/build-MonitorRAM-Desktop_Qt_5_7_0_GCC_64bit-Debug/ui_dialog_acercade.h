/********************************************************************************
** Form generated from reading UI file 'dialog_acercade.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ACERCADE_H
#define UI_DIALOG_ACERCADE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog_AcercaDe
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Dialog_AcercaDe)
    {
        if (Dialog_AcercaDe->objectName().isEmpty())
            Dialog_AcercaDe->setObjectName(QStringLiteral("Dialog_AcercaDe"));
        Dialog_AcercaDe->resize(342, 229);
        verticalLayout_2 = new QVBoxLayout(Dialog_AcercaDe);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(Dialog_AcercaDe);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(Dialog_AcercaDe);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(Dialog_AcercaDe);
        QObject::connect(pushButton, SIGNAL(clicked()), Dialog_AcercaDe, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog_AcercaDe);
    } // setupUi

    void retranslateUi(QDialog *Dialog_AcercaDe)
    {
        Dialog_AcercaDe->setWindowTitle(QApplication::translate("Dialog_AcercaDe", "Acerca De", 0));
        textBrowser->setHtml(QApplication::translate("Dialog_AcercaDe", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Proyecto para la materia de Sistemas Operativos de la Facultad de Ingenier\303\255a de la UNAM Grupo 07.</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Integrantes:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Sebastian Aguilar</p>\n"
"<p s"
                        "tyle=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Erik Rodrigo Sanabria Betancourt</p></body></html>", 0));
        pushButton->setText(QApplication::translate("Dialog_AcercaDe", "&Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_AcercaDe: public Ui_Dialog_AcercaDe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ACERCADE_H
