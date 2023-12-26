/********************************************************************************
** Form generated from reading UI file 'CalculatorPlusGeo.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATORPLUSGEO_H
#define UI_CALCULATORPLUSGEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalculatorPlusGeoClass
{
public:
    QWidget *centralWidget;
    QStackedWidget *calStack;
    QWidget *calPage;
    QTextBrowser *exprBrowser;
    QTextBrowser *ansrBrowser;
    QLabel *eqlsLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *calGrid;
    QPushButton *fourBtn;
    QPushButton *leftParenBtn;
    QPushButton *sevenBtn;
    QPushButton *powBtn;
    QPushButton *oneBtn;
    QPushButton *divBtn;
    QPushButton *rightParenBtn;
    QPushButton *decBtn;
    QPushButton *eightBtn;
    QPushButton *nineBtn;
    QPushButton *multiBtn;
    QPushButton *fiveBtn;
    QPushButton *sixBtn;
    QPushButton *minusBtn;
    QPushButton *twoBtn;
    QPushButton *threeBtn;
    QPushButton *plusBtn;
    QPushButton *zeroBtn;
    QPushButton *delBtn;
    QPushButton *clearBtn;
    QWidget *geoPage;
    QWidget *gridLayoutWidget_2;
    QGridLayout *geoGrid;
    QRadioButton *cuboidRadio;
    QRadioButton *cubeRadio;
    QRadioButton *triRadio;
    QRadioButton *circleRadio;
    QRadioButton *rectRadio;
    QRadioButton *sqrRadio;
    QRadioButton *sqrPyRadio;
    QRadioButton *triPyRadio;
    QRadioButton *sphRadio;
    QLineEdit *geoVal1Line;
    QLineEdit *geoVal3Line;
    QLineEdit *geoVal2Line;
    QLabel *formulaHeadLabel;
    QLabel *formulaContentLabel;
    QLabel *geoEqlsLabel;
    QTextBrowser *geoAnsrBrowser;
    QPushButton *modeSwtchBtn;

    void setupUi(QMainWindow *CalculatorPlusGeoClass)
    {
        if (CalculatorPlusGeoClass->objectName().isEmpty())
            CalculatorPlusGeoClass->setObjectName("CalculatorPlusGeoClass");
        CalculatorPlusGeoClass->resize(400, 530);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CalculatorPlusGeoClass->sizePolicy().hasHeightForWidth());
        CalculatorPlusGeoClass->setSizePolicy(sizePolicy);
        CalculatorPlusGeoClass->setStyleSheet(QString::fromUtf8("background: rgb(50, 50, 50);"));
        centralWidget = new QWidget(CalculatorPlusGeoClass);
        centralWidget->setObjectName("centralWidget");
        calStack = new QStackedWidget(centralWidget);
        calStack->setObjectName("calStack");
        calStack->setGeometry(QRect(10, 40, 381, 481));
        calPage = new QWidget();
        calPage->setObjectName("calPage");
        exprBrowser = new QTextBrowser(calPage);
        exprBrowser->setObjectName("exprBrowser");
        exprBrowser->setGeometry(QRect(0, 10, 381, 61));
        exprBrowser->setFocusPolicy(Qt::NoFocus);
        exprBrowser->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195)"));
        ansrBrowser = new QTextBrowser(calPage);
        ansrBrowser->setObjectName("ansrBrowser");
        ansrBrowser->setGeometry(QRect(55, 80, 321, 61));
        ansrBrowser->setFocusPolicy(Qt::NoFocus);
        ansrBrowser->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195);"));
        eqlsLabel = new QLabel(calPage);
        eqlsLabel->setObjectName("eqlsLabel");
        eqlsLabel->setGeometry(QRect(0, 80, 49, 61));
        QFont font;
        font.setPointSize(36);
        eqlsLabel->setFont(font);
        eqlsLabel->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));
        eqlsLabel->setAlignment(Qt::AlignCenter);
        gridLayoutWidget = new QWidget(calPage);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(0, 150, 381, 331));
        calGrid = new QGridLayout(gridLayoutWidget);
        calGrid->setSpacing(6);
        calGrid->setContentsMargins(11, 11, 11, 11);
        calGrid->setObjectName("calGrid");
        calGrid->setContentsMargins(0, 0, 0, 0);
        fourBtn = new QPushButton(gridLayoutWidget);
        fourBtn->setObjectName("fourBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(fourBtn->sizePolicy().hasHeightForWidth());
        fourBtn->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(26);
        fourBtn->setFont(font1);
        fourBtn->setFocusPolicy(Qt::NoFocus);
        fourBtn->setStyleSheet(QString::fromUtf8("QPushButton#fourBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#fourBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#fourBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(fourBtn, 2, 0, 1, 1);

        leftParenBtn = new QPushButton(gridLayoutWidget);
        leftParenBtn->setObjectName("leftParenBtn");
        sizePolicy1.setHeightForWidth(leftParenBtn->sizePolicy().hasHeightForWidth());
        leftParenBtn->setSizePolicy(sizePolicy1);
        leftParenBtn->setFont(font1);
        leftParenBtn->setFocusPolicy(Qt::NoFocus);
        leftParenBtn->setStyleSheet(QString::fromUtf8("QPushButton#leftParenBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#leftParenBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#leftParenBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}\n"
""));

        calGrid->addWidget(leftParenBtn, 0, 0, 1, 1);

        sevenBtn = new QPushButton(gridLayoutWidget);
        sevenBtn->setObjectName("sevenBtn");
        sizePolicy1.setHeightForWidth(sevenBtn->sizePolicy().hasHeightForWidth());
        sevenBtn->setSizePolicy(sizePolicy1);
        sevenBtn->setFont(font1);
        sevenBtn->setFocusPolicy(Qt::NoFocus);
        sevenBtn->setStyleSheet(QString::fromUtf8("QPushButton#sevenBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#sevenBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#sevenBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(sevenBtn, 1, 0, 1, 1);

        powBtn = new QPushButton(gridLayoutWidget);
        powBtn->setObjectName("powBtn");
        sizePolicy1.setHeightForWidth(powBtn->sizePolicy().hasHeightForWidth());
        powBtn->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(22);
        powBtn->setFont(font2);
        powBtn->setFocusPolicy(Qt::NoFocus);
        powBtn->setStyleSheet(QString::fromUtf8("QPushButton#powBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#powBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#powBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(powBtn, 0, 2, 1, 1);

        oneBtn = new QPushButton(gridLayoutWidget);
        oneBtn->setObjectName("oneBtn");
        sizePolicy1.setHeightForWidth(oneBtn->sizePolicy().hasHeightForWidth());
        oneBtn->setSizePolicy(sizePolicy1);
        oneBtn->setFont(font1);
        oneBtn->setFocusPolicy(Qt::NoFocus);
        oneBtn->setStyleSheet(QString::fromUtf8("QPushButton#oneBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#oneBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#oneBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(oneBtn, 3, 0, 1, 1);

        divBtn = new QPushButton(gridLayoutWidget);
        divBtn->setObjectName("divBtn");
        sizePolicy1.setHeightForWidth(divBtn->sizePolicy().hasHeightForWidth());
        divBtn->setSizePolicy(sizePolicy1);
        divBtn->setFont(font1);
        divBtn->setFocusPolicy(Qt::NoFocus);
        divBtn->setStyleSheet(QString::fromUtf8("QPushButton#divBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#divBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#divBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(divBtn, 0, 3, 1, 1);

        rightParenBtn = new QPushButton(gridLayoutWidget);
        rightParenBtn->setObjectName("rightParenBtn");
        sizePolicy1.setHeightForWidth(rightParenBtn->sizePolicy().hasHeightForWidth());
        rightParenBtn->setSizePolicy(sizePolicy1);
        rightParenBtn->setFont(font1);
        rightParenBtn->setFocusPolicy(Qt::NoFocus);
        rightParenBtn->setStyleSheet(QString::fromUtf8("QPushButton#rightParenBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#rightParenBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#rightParenBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(rightParenBtn, 0, 1, 1, 1);

        decBtn = new QPushButton(gridLayoutWidget);
        decBtn->setObjectName("decBtn");
        sizePolicy1.setHeightForWidth(decBtn->sizePolicy().hasHeightForWidth());
        decBtn->setSizePolicy(sizePolicy1);
        decBtn->setFont(font1);
        decBtn->setFocusPolicy(Qt::NoFocus);
        decBtn->setStyleSheet(QString::fromUtf8("QPushButton#decBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#decBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#decBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(decBtn, 4, 0, 1, 1);

        eightBtn = new QPushButton(gridLayoutWidget);
        eightBtn->setObjectName("eightBtn");
        sizePolicy1.setHeightForWidth(eightBtn->sizePolicy().hasHeightForWidth());
        eightBtn->setSizePolicy(sizePolicy1);
        eightBtn->setFont(font1);
        eightBtn->setFocusPolicy(Qt::NoFocus);
        eightBtn->setStyleSheet(QString::fromUtf8("QPushButton#eightBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#eightBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#eightBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(eightBtn, 1, 1, 1, 1);

        nineBtn = new QPushButton(gridLayoutWidget);
        nineBtn->setObjectName("nineBtn");
        sizePolicy1.setHeightForWidth(nineBtn->sizePolicy().hasHeightForWidth());
        nineBtn->setSizePolicy(sizePolicy1);
        nineBtn->setFont(font1);
        nineBtn->setFocusPolicy(Qt::NoFocus);
        nineBtn->setStyleSheet(QString::fromUtf8("QPushButton#nineBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#nineBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#nineBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(nineBtn, 1, 2, 1, 1);

        multiBtn = new QPushButton(gridLayoutWidget);
        multiBtn->setObjectName("multiBtn");
        sizePolicy1.setHeightForWidth(multiBtn->sizePolicy().hasHeightForWidth());
        multiBtn->setSizePolicy(sizePolicy1);
        multiBtn->setFont(font1);
        multiBtn->setFocusPolicy(Qt::NoFocus);
        multiBtn->setStyleSheet(QString::fromUtf8("QPushButton#multiBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#multiBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#multiBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(multiBtn, 1, 3, 1, 1);

        fiveBtn = new QPushButton(gridLayoutWidget);
        fiveBtn->setObjectName("fiveBtn");
        sizePolicy1.setHeightForWidth(fiveBtn->sizePolicy().hasHeightForWidth());
        fiveBtn->setSizePolicy(sizePolicy1);
        fiveBtn->setFont(font1);
        fiveBtn->setFocusPolicy(Qt::NoFocus);
        fiveBtn->setStyleSheet(QString::fromUtf8("QPushButton#fiveBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#fiveBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#fiveBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(fiveBtn, 2, 1, 1, 1);

        sixBtn = new QPushButton(gridLayoutWidget);
        sixBtn->setObjectName("sixBtn");
        sizePolicy1.setHeightForWidth(sixBtn->sizePolicy().hasHeightForWidth());
        sixBtn->setSizePolicy(sizePolicy1);
        sixBtn->setFont(font1);
        sixBtn->setFocusPolicy(Qt::NoFocus);
        sixBtn->setStyleSheet(QString::fromUtf8("QPushButton#sixBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#sixBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#sixBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(sixBtn, 2, 2, 1, 1);

        minusBtn = new QPushButton(gridLayoutWidget);
        minusBtn->setObjectName("minusBtn");
        sizePolicy1.setHeightForWidth(minusBtn->sizePolicy().hasHeightForWidth());
        minusBtn->setSizePolicy(sizePolicy1);
        minusBtn->setFont(font1);
        minusBtn->setFocusPolicy(Qt::NoFocus);
        minusBtn->setStyleSheet(QString::fromUtf8("QPushButton#minusBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#minusBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#minusBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(minusBtn, 2, 3, 1, 1);

        twoBtn = new QPushButton(gridLayoutWidget);
        twoBtn->setObjectName("twoBtn");
        sizePolicy1.setHeightForWidth(twoBtn->sizePolicy().hasHeightForWidth());
        twoBtn->setSizePolicy(sizePolicy1);
        twoBtn->setFont(font1);
        twoBtn->setFocusPolicy(Qt::NoFocus);
        twoBtn->setStyleSheet(QString::fromUtf8("QPushButton#twoBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#twoBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#twoBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(twoBtn, 3, 1, 1, 1);

        threeBtn = new QPushButton(gridLayoutWidget);
        threeBtn->setObjectName("threeBtn");
        sizePolicy1.setHeightForWidth(threeBtn->sizePolicy().hasHeightForWidth());
        threeBtn->setSizePolicy(sizePolicy1);
        threeBtn->setFont(font1);
        threeBtn->setFocusPolicy(Qt::NoFocus);
        threeBtn->setStyleSheet(QString::fromUtf8("QPushButton#threeBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#threeBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#threeBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(threeBtn, 3, 2, 1, 1);

        plusBtn = new QPushButton(gridLayoutWidget);
        plusBtn->setObjectName("plusBtn");
        sizePolicy1.setHeightForWidth(plusBtn->sizePolicy().hasHeightForWidth());
        plusBtn->setSizePolicy(sizePolicy1);
        plusBtn->setFont(font1);
        plusBtn->setFocusPolicy(Qt::NoFocus);
        plusBtn->setStyleSheet(QString::fromUtf8("QPushButton#plusBtn {\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"background: rgb(0, 86, 63);\n"
"}\n"
"\n"
"QPushButton#plusBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#plusBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(plusBtn, 3, 3, 1, 1);

        zeroBtn = new QPushButton(gridLayoutWidget);
        zeroBtn->setObjectName("zeroBtn");
        sizePolicy1.setHeightForWidth(zeroBtn->sizePolicy().hasHeightForWidth());
        zeroBtn->setSizePolicy(sizePolicy1);
        zeroBtn->setFont(font1);
        zeroBtn->setFocusPolicy(Qt::NoFocus);
        zeroBtn->setStyleSheet(QString::fromUtf8("QPushButton#zeroBtn{\n"
"background: rgb(80, 80, 80);\n"
"color: rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#zeroBtn:hover{\n"
"background: rgb(100, 100, 100);\n"
"}\n"
"\n"
"QPushButton#zeroBtn:pressed{\n"
"background: rgb(80, 80, 80);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(zeroBtn, 4, 1, 1, 1);

        delBtn = new QPushButton(gridLayoutWidget);
        delBtn->setObjectName("delBtn");
        sizePolicy1.setHeightForWidth(delBtn->sizePolicy().hasHeightForWidth());
        delBtn->setSizePolicy(sizePolicy1);
        delBtn->setFont(font2);
        delBtn->setFocusPolicy(Qt::NoFocus);
        delBtn->setStyleSheet(QString::fromUtf8("QPushButton#delBtn{\n"
"color:rgb(35, 35, 35);\n"
"background: rgb(154, 46, 46);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#delBtn:hover{\n"
"background: rgb(181, 54, 54);\n"
"}\n"
"\n"
"QPushButton#delBtn:pressed{\n"
"background: rgb(130, 39, 39);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(delBtn, 4, 2, 1, 1);

        clearBtn = new QPushButton(gridLayoutWidget);
        clearBtn->setObjectName("clearBtn");
        sizePolicy1.setHeightForWidth(clearBtn->sizePolicy().hasHeightForWidth());
        clearBtn->setSizePolicy(sizePolicy1);
        clearBtn->setFont(font2);
        clearBtn->setFocusPolicy(Qt::NoFocus);
        clearBtn->setStyleSheet(QString::fromUtf8("QPushButton#clearBtn{\n"
"color:rgb(35, 35, 35);\n"
"background: rgb(154, 46, 46);\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QPushButton#clearBtn:hover{\n"
"background: rgb(181, 54, 54);\n"
"}\n"
"\n"
"QPushButton#clearBtn:pressed{\n"
"background: rgb(130, 39, 39);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));

        calGrid->addWidget(clearBtn, 4, 3, 1, 1);

        calStack->addWidget(calPage);
        geoPage = new QWidget();
        geoPage->setObjectName("geoPage");
        gridLayoutWidget_2 = new QWidget(geoPage);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(40, 10, 331, 151));
        geoGrid = new QGridLayout(gridLayoutWidget_2);
        geoGrid->setSpacing(6);
        geoGrid->setContentsMargins(11, 11, 11, 11);
        geoGrid->setObjectName("geoGrid");
        geoGrid->setContentsMargins(0, 0, 0, 0);
        cuboidRadio = new QRadioButton(gridLayoutWidget_2);
        cuboidRadio->setObjectName("cuboidRadio");
        cuboidRadio->setFocusPolicy(Qt::NoFocus);
        cuboidRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(cuboidRadio, 1, 2, 1, 1);

        cubeRadio = new QRadioButton(gridLayoutWidget_2);
        cubeRadio->setObjectName("cubeRadio");
        cubeRadio->setFocusPolicy(Qt::NoFocus);
        cubeRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(cubeRadio, 1, 1, 1, 1);

        triRadio = new QRadioButton(gridLayoutWidget_2);
        triRadio->setObjectName("triRadio");
        triRadio->setFocusPolicy(Qt::NoFocus);
        triRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(triRadio, 1, 0, 1, 1);

        circleRadio = new QRadioButton(gridLayoutWidget_2);
        circleRadio->setObjectName("circleRadio");
        circleRadio->setFocusPolicy(Qt::NoFocus);
        circleRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(circleRadio, 0, 2, 1, 1);

        rectRadio = new QRadioButton(gridLayoutWidget_2);
        rectRadio->setObjectName("rectRadio");
        rectRadio->setFocusPolicy(Qt::NoFocus);
        rectRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(rectRadio, 0, 1, 1, 1);

        sqrRadio = new QRadioButton(gridLayoutWidget_2);
        sqrRadio->setObjectName("sqrRadio");
        sqrRadio->setFocusPolicy(Qt::NoFocus);
        sqrRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(sqrRadio, 0, 0, 1, 1);

        sqrPyRadio = new QRadioButton(gridLayoutWidget_2);
        sqrPyRadio->setObjectName("sqrPyRadio");
        sqrPyRadio->setFocusPolicy(Qt::NoFocus);
        sqrPyRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(sqrPyRadio, 2, 2, 1, 1);

        triPyRadio = new QRadioButton(gridLayoutWidget_2);
        triPyRadio->setObjectName("triPyRadio");
        triPyRadio->setFocusPolicy(Qt::NoFocus);
        triPyRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(triPyRadio, 2, 1, 1, 1);

        sphRadio = new QRadioButton(gridLayoutWidget_2);
        sphRadio->setObjectName("sphRadio");
        sphRadio->setFocusPolicy(Qt::NoFocus);
        sphRadio->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));

        geoGrid->addWidget(sphRadio, 2, 0, 1, 1);

        geoVal1Line = new QLineEdit(geoPage);
        geoVal1Line->setObjectName("geoVal1Line");
        geoVal1Line->setGeometry(QRect(262, 180, 111, 41));
        geoVal1Line->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 15px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195);"));
        geoVal3Line = new QLineEdit(geoPage);
        geoVal3Line->setObjectName("geoVal3Line");
        geoVal3Line->setGeometry(QRect(260, 300, 111, 41));
        geoVal3Line->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 15px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195);"));
        geoVal2Line = new QLineEdit(geoPage);
        geoVal2Line->setObjectName("geoVal2Line");
        geoVal2Line->setGeometry(QRect(260, 240, 111, 41));
        geoVal2Line->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 15px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195);"));
        formulaHeadLabel = new QLabel(geoPage);
        formulaHeadLabel->setObjectName("formulaHeadLabel");
        formulaHeadLabel->setGeometry(QRect(10, 170, 111, 41));
        QFont font3;
        font3.setPointSize(16);
        formulaHeadLabel->setFont(font3);
        formulaHeadLabel->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));
        formulaContentLabel = new QLabel(geoPage);
        formulaContentLabel->setObjectName("formulaContentLabel");
        formulaContentLabel->setGeometry(QRect(10, 230, 231, 121));
        formulaContentLabel->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));
        formulaContentLabel->setAlignment(Qt::AlignCenter);
        formulaContentLabel->setWordWrap(true);
        geoEqlsLabel = new QLabel(geoPage);
        geoEqlsLabel->setObjectName("geoEqlsLabel");
        geoEqlsLabel->setGeometry(QRect(90, 370, 181, 31));
        geoEqlsLabel->setFont(font3);
        geoEqlsLabel->setStyleSheet(QString::fromUtf8("color: rgb(195, 195, 195);"));
        geoEqlsLabel->setAlignment(Qt::AlignCenter);
        geoAnsrBrowser = new QTextBrowser(geoPage);
        geoAnsrBrowser->setObjectName("geoAnsrBrowser");
        geoAnsrBrowser->setGeometry(QRect(0, 420, 381, 61));
        geoAnsrBrowser->setFocusPolicy(Qt::NoFocus);
        geoAnsrBrowser->setStyleSheet(QString::fromUtf8("background: rgb(39, 39, 39);\n"
"border: 3px solid rgb(195, 195, 195);\n"
"border-radius: 20px;\n"
"padding: 3px;\n"
"color: rgb(195, 195, 195);"));
        calStack->addWidget(geoPage);
        modeSwtchBtn = new QPushButton(centralWidget);
        modeSwtchBtn->setObjectName("modeSwtchBtn");
        modeSwtchBtn->setGeometry(QRect(90, 10, 221, 24));
        QFont font4;
        font4.setPointSize(11);
        modeSwtchBtn->setFont(font4);
        modeSwtchBtn->setFocusPolicy(Qt::NoFocus);
        modeSwtchBtn->setStyleSheet(QString::fromUtf8("QPushButton#modeSwtchBtn{\n"
"color: rgb(195, 195, 195);\n"
"background: rgb(0, 86, 63);\n"
"border-radius: 9px;\n"
"}\n"
"\n"
"QPushButton#modeSwtchBtn:hover{\n"
"background: rgb(0, 102, 73);\n"
"}\n"
"\n"
"QPushButton#modeSwtchBtn:pressed{\n"
"background: rgb(0, 68, 49);\n"
"border: 2px solid rgb(45, 45, 45);\n"
"}"));
        modeSwtchBtn->setFlat(false);
        CalculatorPlusGeoClass->setCentralWidget(centralWidget);
        QWidget::setTabOrder(geoVal1Line, geoVal2Line);
        QWidget::setTabOrder(geoVal2Line, geoVal3Line);

        retranslateUi(CalculatorPlusGeoClass);
        QObject::connect(sqrPyRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setEnabled);
        QObject::connect(sqrPyRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(triPyRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setEnabled);
        QObject::connect(triPyRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(sphRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setDisabled);
        QObject::connect(sphRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(cuboidRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setEnabled);
        QObject::connect(cuboidRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setEnabled);
        QObject::connect(cubeRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setDisabled);
        QObject::connect(cubeRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(triRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setEnabled);
        QObject::connect(triRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setEnabled);
        QObject::connect(sqrRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setDisabled);
        QObject::connect(sqrRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(rectRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setEnabled);
        QObject::connect(rectRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);
        QObject::connect(circleRadio, &QRadioButton::clicked, geoVal2Line, &QLineEdit::setDisabled);
        QObject::connect(circleRadio, &QRadioButton::clicked, geoVal3Line, &QLineEdit::setDisabled);

        calStack->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CalculatorPlusGeoClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalculatorPlusGeoClass)
    {
        CalculatorPlusGeoClass->setWindowTitle(QCoreApplication::translate("CalculatorPlusGeoClass", "CalculatorPlusGeo", nullptr));
        exprBrowser->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Input . . .", nullptr));
        ansrBrowser->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Input . . .", nullptr));
        eqlsLabel->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "=", nullptr));
        fourBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "4", nullptr));
        leftParenBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "(", nullptr));
        sevenBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "7", nullptr));
        powBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "^ pow", nullptr));
        oneBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "1", nullptr));
        divBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "/", nullptr));
        rightParenBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", ")", nullptr));
        decBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", ".", nullptr));
        eightBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "8", nullptr));
        nineBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "9", nullptr));
        multiBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "*", nullptr));
        fiveBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "5", nullptr));
        sixBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "6", nullptr));
        minusBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "-", nullptr));
        twoBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "2", nullptr));
        threeBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "3", nullptr));
        plusBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "+", nullptr));
        zeroBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "0", nullptr));
        delBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "<Del", nullptr));
        clearBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Clear", nullptr));
        cuboidRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Cuboid", nullptr));
        cubeRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Cube", nullptr));
        triRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Triangle", nullptr));
        circleRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Circle", nullptr));
        rectRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Rectangle", nullptr));
        sqrRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Square", nullptr));
        sqrPyRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Right\n"
"Square\n"
"Pyramid", nullptr));
        triPyRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Right\n"
"Triangle\n"
"Pyramid", nullptr));
        sphRadio->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Sphere", nullptr));
        geoVal1Line->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Shape...", nullptr));
        geoVal3Line->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Shape...", nullptr));
        geoVal2Line->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Shape...", nullptr));
        formulaHeadLabel->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Formula:", nullptr));
        formulaContentLabel->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Formulas will appear here. . .", nullptr));
        geoEqlsLabel->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Area/Volume =", nullptr));
        geoAnsrBrowser->setPlaceholderText(QCoreApplication::translate("CalculatorPlusGeoClass", "Awaiting Input . . .", nullptr));
        modeSwtchBtn->setText(QCoreApplication::translate("CalculatorPlusGeoClass", "Calculator / Geometry", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalculatorPlusGeoClass: public Ui_CalculatorPlusGeoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATORPLUSGEO_H
