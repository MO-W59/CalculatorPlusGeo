/* Basic components of the calculator in addition to those created
by the ui file */
#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CalculatorPlusGeo.h"

class CalculatorPlusGeo : public QMainWindow
{
    Q_OBJECT
    int m_pDepth = 0;
    short m_minusCnt = 1;
    bool m_afterDec = false;
    bool m_displayAftrDec = false;
    QString m_displayExpr = "";
    std::string m_internalExpr = "";
    std::array<QPushButton*, 4> OP_BTNS;
    std::array<QPushButton*, 9> NUM_BTNS;


public:
    CalculatorPlusGeo(QWidget *parent = nullptr);
    ~CalculatorPlusGeo();

private slots:
    void switchModes();
    void zeroClicked();
    void oneClicked();
    void twoClicked();
    void threeClicked();
    void fourClicked();
    void fiveClicked();
    void sixClicked();
    void sevenClicked();
    void eightClicked();
    void nineClicked();
    void leftParenClicked();
    void rightParenClicked();
    void powClicked();
    void divClicked();
    void multiClicked();
    void minusClicked();
    void plusClicked();
    void decClicked();
    void delClicked();
    void clearClicked();
    void squareClicked();
    void rectClicked();
    void circleClicked();
    void triangleClicked();
    void cubeClicked();
    void cuboidClicked();
    void sphereClicked();
    void triPyClicked();
    void sqrPyClicked();

private:
    Ui::CalculatorPlusGeoClass ui;
    void setHandlers() const;
    void tryCal();
    void tryGeo();
    void lockBtns();
    void btnsReset();
    void enableNumBtns(bool) const;
    void enableOpsBtns(bool) const;
    void formatAnsr(std::string&) const;
    void formatDisplayExpr();
    void clearGeoLines();
    bool isNum(const char&) const;
    bool isOp(const char&) const;
};
