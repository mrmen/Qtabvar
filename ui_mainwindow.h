/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Apr 19 15:33:35 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuitter;
    QAction *actionAdapter_le_tableau;
    QAction *actionG_n_rer_le_tableau;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QTableView *tableau;
    QHBoxLayout *horizontalLayout_3;
    QLabel *hauteurLabel;
    QSpinBox *hauteurSpinbox;
    QLabel *longueurLabel;
    QSpinBox *longueurSpinbox;
    QCheckBox *variationBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *updateTabular;
    QPushButton *getCode;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *codeEdit;
    QPushButton *effacerButton;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menu_dition;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(528, 434);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        actionAdapter_le_tableau = new QAction(MainWindow);
        actionAdapter_le_tableau->setObjectName(QString::fromUtf8("actionAdapter_le_tableau"));
        actionG_n_rer_le_tableau = new QAction(MainWindow);
        actionG_n_rer_le_tableau->setObjectName(QString::fromUtf8("actionG_n_rer_le_tableau"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 478, 252));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tableau = new QTableView(scrollAreaWidgetContents);
        tableau->setObjectName(QString::fromUtf8("tableau"));

        verticalLayout_3->addWidget(tableau);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        hauteurLabel = new QLabel(tab);
        hauteurLabel->setObjectName(QString::fromUtf8("hauteurLabel"));

        horizontalLayout_3->addWidget(hauteurLabel);

        hauteurSpinbox = new QSpinBox(tab);
        hauteurSpinbox->setObjectName(QString::fromUtf8("hauteurSpinbox"));

        horizontalLayout_3->addWidget(hauteurSpinbox);

        longueurLabel = new QLabel(tab);
        longueurLabel->setObjectName(QString::fromUtf8("longueurLabel"));

        horizontalLayout_3->addWidget(longueurLabel);

        longueurSpinbox = new QSpinBox(tab);
        longueurSpinbox->setObjectName(QString::fromUtf8("longueurSpinbox"));

        horizontalLayout_3->addWidget(longueurSpinbox);

        variationBox = new QCheckBox(tab);
        variationBox->setObjectName(QString::fromUtf8("variationBox"));

        horizontalLayout_3->addWidget(variationBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        updateTabular = new QPushButton(tab);
        updateTabular->setObjectName(QString::fromUtf8("updateTabular"));

        horizontalLayout_2->addWidget(updateTabular);

        getCode = new QPushButton(tab);
        getCode->setObjectName(QString::fromUtf8("getCode"));

        horizontalLayout_2->addWidget(getCode);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        codeEdit = new QTextEdit(tab_2);
        codeEdit->setObjectName(QString::fromUtf8("codeEdit"));

        verticalLayout_4->addWidget(codeEdit);


        verticalLayout_5->addLayout(verticalLayout_4);

        effacerButton = new QPushButton(tab_2);
        effacerButton->setObjectName(QString::fromUtf8("effacerButton"));

        verticalLayout_5->addWidget(effacerButton);

        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 528, 29));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menu_dition = new QMenu(menuBar);
        menu_dition->setObjectName(QString::fromUtf8("menu_dition"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menu_dition->menuAction());
        menuFichier->addSeparator();
        menuFichier->addAction(actionQuitter);
        menu_dition->addAction(actionAdapter_le_tableau);
        menu_dition->addAction(actionG_n_rer_le_tableau);

        retranslateUi(MainWindow);
        QObject::connect(actionQuitter, SIGNAL(triggered()), MainWindow, SLOT(close()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0, QApplication::UnicodeUTF8));
        actionQuitter->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAdapter_le_tableau->setText(QApplication::translate("MainWindow", "Adapter le tableau", 0, QApplication::UnicodeUTF8));
        actionAdapter_le_tableau->setShortcut(QApplication::translate("MainWindow", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        actionG_n_rer_le_tableau->setText(QApplication::translate("MainWindow", "G\303\251n\303\251rer le code", 0, QApplication::UnicodeUTF8));
        actionG_n_rer_le_tableau->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        hauteurLabel->setText(QApplication::translate("MainWindow", "Hauteur", 0, QApplication::UnicodeUTF8));
        longueurLabel->setText(QApplication::translate("MainWindow", "Longueur", 0, QApplication::UnicodeUTF8));
        variationBox->setText(QApplication::translate("MainWindow", "Variations", 0, QApplication::UnicodeUTF8));
        updateTabular->setText(QApplication::translate("MainWindow", "Adapter le tableau", 0, QApplication::UnicodeUTF8));
        getCode->setText(QApplication::translate("MainWindow", "G\303\251n\303\251rer", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Editeur", 0, QApplication::UnicodeUTF8));
        effacerButton->setText(QApplication::translate("MainWindow", "Effacer", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Code", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fichier", 0, QApplication::UnicodeUTF8));
        menu_dition->setTitle(QApplication::translate("MainWindow", "\303\211dition", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
