#include "CalculatorPlusGeo.hpp"
#include "shuntYard.hpp"

CalculatorPlusGeo::CalculatorPlusGeo(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    OP_BTNS =
    {// '-' button not included due to negative number support
        ui.powBtn,
        ui.divBtn,
        ui.multiBtn,
        ui.plusBtn
    };

    NUM_BTNS =
    {
        ui.oneBtn,
        ui.twoBtn,
        ui.threeBtn,
        ui.fourBtn,
        ui.fiveBtn,
        ui.sixBtn,
        ui.sevenBtn,
        ui.eightBtn,
        ui.nineBtn
    };

    setHandlers();
    btnsReset();
}

void CalculatorPlusGeo::setHandlers() const
{
    // Connects all events to handlers
    connect(ui.modeSwtchBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::switchModes);
    connect(ui.zeroBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::zeroClicked);
    connect(ui.oneBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::oneClicked);
    connect(ui.twoBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::twoClicked);
    connect(ui.threeBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::threeClicked);
    connect(ui.fourBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::fourClicked);
    connect(ui.fiveBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::fiveClicked);
    connect(ui.sixBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::sixClicked);
    connect(ui.sevenBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::sevenClicked);
    connect(ui.eightBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::eightClicked);
    connect(ui.nineBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::nineClicked);
    connect(ui.leftParenBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::leftParenClicked);
    connect(ui.rightParenBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::rightParenClicked);
    connect(ui.powBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::powClicked);
    connect(ui.divBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::divClicked);
    connect(ui.multiBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::multiClicked);
    connect(ui.minusBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::minusClicked);
    connect(ui.plusBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::plusClicked);
    connect(ui.decBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::decClicked);
    connect(ui.delBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::delClicked);
    connect(ui.clearBtn, &QPushButton::clicked, this, &CalculatorPlusGeo::clearClicked);
    connect(ui.exprBrowser, &QTextBrowser::textChanged, this, &CalculatorPlusGeo::tryCal);
    connect(ui.geoVal1Line, &QLineEdit::textChanged, this, &CalculatorPlusGeo::tryGeo);
    connect(ui.geoVal2Line, &QLineEdit::textChanged, this, &CalculatorPlusGeo::tryGeo);
    connect(ui.geoVal3Line, &QLineEdit::textChanged, this, &CalculatorPlusGeo::tryGeo);
    connect(ui.sqrRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::squareClicked);
    connect(ui.rectRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::rectClicked);
    connect(ui.circleRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::circleClicked);
    connect(ui.triRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::triangleClicked);
    connect(ui.cubeRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::cubeClicked);
    connect(ui.cuboidRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::cuboidClicked);
    connect(ui.sphRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::sphereClicked);
    connect(ui.triPyRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::triPyClicked);
    connect(ui.sqrPyRadio, &QRadioButton::clicked, this, &CalculatorPlusGeo::sqrPyClicked);
}

CalculatorPlusGeo::~CalculatorPlusGeo() = default;

void CalculatorPlusGeo::switchModes()
{// Switches the stack index page when top button is clicked
    int index = ui.calStack->currentIndex();

    if (index == 1)
        ui.calStack->setCurrentIndex(0);
    else
        ui.calStack->setCurrentIndex(1);
}

void CalculatorPlusGeo::tryCal()
{// Attempts to calculate the expression as user clicks buttons
    try
    {
        // Get expression from gui, lock buttons accordingly
        QString qexpr = ui.exprBrowser->toPlainText();
        lockBtns();

        // If the expression has noting in it ie event led to empty string, simply return
        if (qexpr.length() < 1)
            return;

        // If the back of the expression is '(' or an operator, return as this expression is not yet valid
        else if (std::find(shuntYard::OPERATORS.begin(), shuntYard::OPERATORS.end(), qexpr.back()) != std::end(shuntYard::OPERATORS) ||
            qexpr.back() == '(')
            return;

        // If the expression has a lenght of 1, simply return that value
        else if (qexpr.length() == 1)
            return ui.ansrBrowser->setText(qexpr);

        // Otherwise take the expression
        std::string expr = qexpr.toStdString();
    
        // Attempt to make a shuntyard with the expression and validate it
        auto yard = std::make_unique<shuntYard::Yard>(expr);
        if (!yard->validateShunt())
        {// Throw expception to produce invalid message to user
            throw std::exception();
        }
        // Otherwise its a valid expression, solve it via RPN
        std::string ansr = shuntYard::RPNEval(yard->getOutQueue());
        // Format to add commas
        formatAnsr(ansr);
        // Convert back to QString and display
        QString qansr = QString::fromStdString(ansr);
        ui.ansrBrowser->setText(qansr);
    }
    catch (const std::exception &except)
    {
        ui.ansrBrowser->setText("Waiting for a valid expression. . .");
    }
}

void CalculatorPlusGeo::formatAnsr(std::string& ansr)
{// Formats an answer to add commas to a number --> 1000 --> 1,000
    // Look for a decimal
    auto decIndex = ansr.find('.');
    int negativeOffset = 3; // 3 for no negative numbers
    if (decIndex == std::string::npos)
    {// If none is found start from the end of the string
        decIndex = ansr.size();
    }

    // Check if it is a negative number
    if (ansr.front() == '-')
        negativeOffset = 4; // 4 for negative numbers -> extra '-'

    // While there are still 3 numbers ahead of the current location
    while (decIndex > negativeOffset)
    {
        // decrement the location by 3 and add a comma
        decIndex -= 3;
        ansr.insert(decIndex, ",");
    }

    // Format the result to remove .00000 from 4.00000
    while (ansr.size() > 1 && ansr.back() == '0' || ansr.back() == '.')
    {
        if (ansr.back() == '.' && ansr.front() == '0')
        {
            ansr = "<= 0.000000";
            break;
        }
        else if (ansr.back() == '.')
        {
            ansr.pop_back();
            break;
        }
        ansr.pop_back();
    }
}

void CalculatorPlusGeo::lockBtns() 
{/*
 Locks calculator buttons depending on last character entered into expression,
 prevents user from entering an invalid sequence of tokens such as ")9+/4..--(.4.^^".
 Also uses member variables m_minusCnt, m_afterDec, and m_pDepth to logically
 active or deactivate the decimal, minus, and parenthesis.
 */
    // If there is no expression, reset all buttons and return
    if (ui.exprBrowser->toPlainText().isEmpty()) {
        btnsReset();
        return;
    }
    // Otherwise get the last character in the expression
    QString qLastEntry = ui.exprBrowser->toPlainText().last(1);
    char lastEntry = qLastEntry.toStdString()[0];
    // If its a number set lastEntry to 'n'
    if (std::any_of(shuntYard::NUMBERS.cbegin(), shuntYard::NUMBERS.cend(), 
        [lastEntry](char const &num) { return num == lastEntry; }))
    {
        lastEntry = 'n';
    }
    // else if its a '-' do nothing
    else if (lastEntry == '-') 
    {
        /* No need to change '-' to '-' for switch operation.
        Protects the minus button for negative numbers and avoids
        the 'o' assignment below. This check is required because
        the '-' character is included in shuntYard::OPERATORS.*/
    }
    else if (std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
        [lastEntry](char const &op) { return op == lastEntry; })) 
    // If its an operator other than '-' set last as 'o'
    {
        lastEntry = 'o';
    }
    // Other cases handle themselves as their char values will be used in the switch as is
   
    // Disable buttons based on lastEntry
    switch (lastEntry)
    {
    case 'n':
        m_minusCnt = 0;
        // Enable these btns
        enableOpsBtns(true);
        ui.zeroBtn->setEnabled(true);
        ui.minusBtn->setEnabled(true);
        ui.decBtn->setEnabled(true);
        if (m_pDepth > 0)
            ui.rightParenBtn->setEnabled(true);
        // Disable these btns
        else
            ui.rightParenBtn->setDisabled(true);
        ui.leftParenBtn->setDisabled(true);
        break;

    case 'o':
        m_minusCnt = 1;
        m_afterDec = false;
        // Enable these btns
        ui.leftParenBtn->setEnabled(true);
        ui.minusBtn->setEnabled(true);
        ui.decBtn->setEnabled(true);
        ui.zeroBtn->setEnabled(true);
        enableNumBtns(true);
        // Disable these btns
        enableOpsBtns(false);
        ui.rightParenBtn->setDisabled(true);
        break;

    case '-':
        m_afterDec = false;
        // Enable these btns
        enableNumBtns(true);
        ui.decBtn->setEnabled(true);
        ui.zeroBtn->setEnabled(true);
        if (m_minusCnt <= 1) 
        {
            ui.leftParenBtn->setEnabled(true);
        }
        // Disable these btns
        else
        {
            ui.leftParenBtn->setDisabled(true);
        }
        if (m_minusCnt >= 2) // Allows two consecutive '-'s ie 4 - -4 = 0
        {
            ui.minusBtn->setDisabled(true);
        }
        ui.rightParenBtn->setDisabled(true);
        enableOpsBtns(false);
        break;

    case '.':
        m_minusCnt = 0;
        m_afterDec = true;
        // Enable these btns
        enableNumBtns(true);
        ui.zeroBtn->setEnabled(true);
        // Disable these btns
        enableOpsBtns(false);
        ui.minusBtn->setDisabled(true);
        ui.leftParenBtn->setDisabled(true);
        ui.rightParenBtn->setDisabled(true);
        break;

    case '(':
        m_minusCnt = 1;
        // Enable these btns
        enableNumBtns(true);
        ui.minusBtn->setEnabled(true);
        ui.decBtn->setEnabled(true);
        ui.zeroBtn->setEnabled(true);
        ui.leftParenBtn->setEnabled(true);
        // Disable these btns
        enableOpsBtns(false);
        ui.rightParenBtn->setDisabled(true);
        break;

    case ')':
        m_minusCnt = 0;
        m_afterDec = false;
        // Enable these btns
        enableOpsBtns(true);
        ui.minusBtn->setEnabled(true);
        if (m_pDepth > 0)
            ui.rightParenBtn->setEnabled(true);
        // Disable these btns
        else
            ui.rightParenBtn->setDisabled(true);
        enableNumBtns(false);
        ui.leftParenBtn->setDisabled(true);
        ui.zeroBtn->setDisabled(true);
        ui.decBtn->setDisabled(true);
        break;

    case '0':
        m_minusCnt = 0;
        // Enable these btns
        enableOpsBtns(true);
        ui.rightParenBtn->setEnabled(true);
        ui.minusBtn->setEnabled(true);
        ui.decBtn->setEnabled(true);
        if (m_afterDec)
        {
            enableNumBtns(true);
            ui.zeroBtn->setEnabled(true);
        }
        // Disable these btns
        else
        {
            enableNumBtns(false);
            ui.zeroBtn->setDisabled(true);
        }
        ui.leftParenBtn->setDisabled(true);
        break;

    default:
        break;
    }
    
}

void CalculatorPlusGeo::btnsReset() 
{ // Sets buttons to the proper starting state
    // These buttons must be available if the expression is empty
    ui.decBtn->setEnabled(true);
    ui.leftParenBtn->setEnabled(true);
    ui.minusBtn->setEnabled(true); // Supports beginning negative number
    ui.zeroBtn->setEnabled(true);
    enableNumBtns(true);

    // These buttons must be unavailable if the expression is empty
    ui.rightParenBtn->setDisabled(true);
    enableOpsBtns(false);
}

void CalculatorPlusGeo::enableNumBtns(bool b) 
{// Function to loop through all number buttons and disable or enable them
    for (QPushButton *btn : NUM_BTNS) 
    {
        btn->setEnabled(b);
    }
}

void CalculatorPlusGeo::enableOpsBtns(bool b)
{// Function to loop through all operator buttons excluding '-' and disable or enable them

    for (QPushButton *btn : OP_BTNS)
    {
        btn->setEnabled(b);
    }
}

void CalculatorPlusGeo::tryGeo()
{// Attempts to calculate the inputs on the geometry page
    
    std::string targetShape = "null";
    QString qA = ui.geoVal1Line->text();
    QString qB = ui.geoVal2Line->text();
    QString qC = ui.geoVal3Line->text();
    double result = 0;
    // Get active shape in the geometry page
    for (int row = 0; row < ui.geoGrid->rowCount(); row++)
    {
        for (int col = 0; col < ui.geoGrid->columnCount(); col++)
        {
            QRadioButton* radBtn = static_cast<QRadioButton*>(ui.geoGrid->itemAtPosition(row, col)->widget());
            if (radBtn != nullptr && radBtn->isChecked())
            {
                QString qtargetShape = radBtn->objectName();
                targetShape = qtargetShape.toStdString();
            }
        }
    }
    /* Obtain the needed values from the ui
    Calculate the area or volume of the requested shape with the given values
    If any conversion fails abort, display error and return */ 
    bool isConverted = false;
    if (targetShape == "null")
    {
        ui.geoAnsrBrowser->setText("Error: You need to select a shape!");
        return;
    }
    else if (targetShape == "sqrRadio")
    {
        double a = qA.toDouble(&isConverted);
        if (isConverted)
            result = a * a;
    }
    else if (targetShape == "rectRadio")
    {
        double a = qA.toDouble(&isConverted);
        double b = qB.toDouble(&isConverted);
        if (isConverted)
            result = a * b;
    }
    else if (targetShape == "triRadio")
    {
        double a = qA.toDouble(&isConverted);
        double b = qB.toDouble(&isConverted);
        double c = qC.toDouble(&isConverted);

        /* Triangle sides can not be >= the other two sides together ie (a = 3) + (b = 3) = (c = 6)
        enters this if statement and displays the invalid input message */
        if (!(a + b > c) || !(a + c > b) || !(b + c > a)) 
        {
            ui.geoAnsrBrowser->setText("Invalid Input: One triangle side must not double the length of the others!");
            return;
        }
        if (isConverted)
            result = operations::triangleArea(a, b, c);
    }
    else if (targetShape == "circleRadio")
    {

        double a = qA.toDouble(&isConverted);
        if (isConverted)
            result = operations::circleArea(a);
    }
    else if (targetShape == "cubeRadio")
    {
        double a = qA.toDouble(&isConverted);
        if (isConverted)
            result = a * a * a;
    }
    else if (targetShape == "cuboidRadio")
    {
        double a = qA.toDouble(&isConverted);
        double b = qB.toDouble(&isConverted);
        double c = qC.toDouble(&isConverted);
        if (isConverted)
            result = a * b * c;
    }
    else if (targetShape == "sphRadio")
    {
        double a = qA.toDouble(&isConverted);
        if (isConverted)
            result = operations::sphereVol(a);
    }
    else if (targetShape == "triPyRadio")
    {
        double a = qA.toDouble(&isConverted);
        double b = qB.toDouble(&isConverted);
        if (isConverted)
            result = operations::triPyVol(a, b);
    }
    else if (targetShape == "sqrPyRadio")
    {
        double a = qA.toDouble(&isConverted);
        double b = qB.toDouble(&isConverted);
        if (isConverted)
            result = operations::quadPyVol(a, b);
    }
    else
    {// Catches a case if the target shape is not found but will most likely never be seen
        ui.geoAnsrBrowser->setText("Error: Did not hit a proper radio button branch!");
    }

    if (!isConverted)
    {
        ui.geoAnsrBrowser->setText("Awaiting valid input . . .");
        return;
    }

    // Change result to a string, format it to have commas and convert it to a QString
    std::string ansr = std::to_string(result);
    formatAnsr(ansr);
    QString qansr = QString::fromStdString(ansr);
    // Display the answer to user
    ui.geoAnsrBrowser->setText(qansr); 
}

/* For each of the following button handlers they add their respective
characters to the expression when clicked */
void CalculatorPlusGeo::zeroClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "0");
}

void CalculatorPlusGeo::oneClicked() 
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "1");
}

void CalculatorPlusGeo::twoClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "2");
}

void CalculatorPlusGeo::threeClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "3");
}

void CalculatorPlusGeo::fourClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "4");
}

void CalculatorPlusGeo::fiveClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "5");
}

void CalculatorPlusGeo::sixClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "6");
}

void CalculatorPlusGeo::sevenClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "7");
}

void CalculatorPlusGeo::eightClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "8");
}

void CalculatorPlusGeo::nineClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "9");
}

void CalculatorPlusGeo::leftParenClicked()
{
    m_pDepth++;// Increase parenthesis depth to allow and equal amount of ')' characters
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "(");
}

void CalculatorPlusGeo::rightParenClicked()
{
    m_pDepth--;// Decrease parenthesis depth to prevent too many ')' characters
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + ")");
}

void CalculatorPlusGeo::powClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "^");
}

void CalculatorPlusGeo::divClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "/");
}

void CalculatorPlusGeo::multiClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "*");
}

void CalculatorPlusGeo::minusClicked()
{
    m_minusCnt++;// Increase minusCnt to prevent too many '-' characters
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "-");
}

void CalculatorPlusGeo::plusClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + "+");
}

void CalculatorPlusGeo::decClicked()
{
    ui.exprBrowser->setText(ui.exprBrowser->toPlainText() + ".");
}

void CalculatorPlusGeo::delClicked()
{/* Deletes the last character in the expression string and resets 
 buttons to an appropriate state based on what character was deleted
 and what the new last character and new next last character are */
    // Get the expression
    QString current = ui.exprBrowser->toPlainText();

    // if it is 0 or 1 in length, expression will be empty so reset logic and clear
    if (current.length() <= 1)
    {
        m_pDepth = 0;
        m_minusCnt = 1;
        m_afterDec = false;
        btnsReset();
        ui.ansrBrowser->clear();
        ui.exprBrowser->clear();
        return;
    }

    // If the character being deleted is one of the following
    if (QChar last = current.back(); last == ')')
    {
        ui.rightParenBtn->setEnabled(true); // Enable the button
        m_pDepth++; // and increase the parenthesis depth
    }
    else if (last == '(')
        m_pDepth--; // Decrease the parenthesis depth
    else if (last == '-')
    {
        if (m_minusCnt > 0)
            m_minusCnt--; // Decrement minus count but only if count is > 0 to prevent "---"
        if (m_minusCnt < 2)
            ui.minusBtn->setEnabled(true); // If minus count is < 2 then enable the button
    }
    else if (last == '.')
        m_afterDec = false; // Set decimal logic to before status

    // Remove the last character from the expression
    current.removeLast();

    // Get the new last character and set next last to null
    QChar newLast = current.back();
    QChar nextLast = '\0';
    // If size > 1 then a next last character exists
    if (current.size() > 1)
    {
        nextLast = current.at(current.size() - 2); // Set it as next last
    }

    // If both these characters are '-'
    if (newLast == '-' && nextLast == '-')
    {
        m_minusCnt = 2; // Set minus count to 2
    }
    // If only the newLast
    else if (newLast == '-')
    {
        m_minusCnt = 1; // Set minus count to 1
    }

    // Display the new expression
    ui.exprBrowser->setText(current);
}

void CalculatorPlusGeo::clearClicked()
{// User clicked the clear button --> clear all text, reset buttons and logic
    m_pDepth = 0;
    m_minusCnt = 1;
    m_afterDec = false;
    btnsReset();
    ui.exprBrowser->clear();
    ui.ansrBrowser->clear();
}

/* This marks the beginning of the handlers for the geometry radio buttons
when they are clicked. NOTE: Deactivation of these lineEdits is handled in
ui_CalculatorPlusGeo.h, this section handles text only */

void CalculatorPlusGeo::clearGeoLines()
{
    ui.geoVal1Line->clear();
    ui.geoVal2Line->clear();
    ui.geoVal3Line->clear();
}

void CalculatorPlusGeo::squareClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("side = ");
    ui.geoVal2Line->setPlaceholderText("N/A");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::rectClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("height = ");
    ui.geoVal2Line->setPlaceholderText("width = ");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::circleClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("radius = ");
    ui.geoVal2Line->setPlaceholderText("N/A");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::triangleClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("a = ");
    ui.geoVal2Line->setPlaceholderText("b = ");
    ui.geoVal3Line->setPlaceholderText("c = ");
}

void CalculatorPlusGeo::cubeClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("edge = ");
    ui.geoVal2Line->setPlaceholderText("N/A");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::cuboidClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("height = ");
    ui.geoVal2Line->setPlaceholderText("width = ");
    ui.geoVal3Line->setPlaceholderText("depth = ");
}

void CalculatorPlusGeo::sphereClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("radius = ");
    ui.geoVal2Line->setPlaceholderText("N/A");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::triPyClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("height = ");
    ui.geoVal2Line->setPlaceholderText("base = ");
    ui.geoVal3Line->setPlaceholderText("N/A");
}

void CalculatorPlusGeo::sqrPyClicked()
{
    clearGeoLines();
    ui.geoVal1Line->setPlaceholderText("height = ");
    ui.geoVal2Line->setPlaceholderText("base = ");
    ui.geoVal3Line->setPlaceholderText("N/A");
}