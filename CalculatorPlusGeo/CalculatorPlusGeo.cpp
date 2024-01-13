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
        // Lock buttons accordingly
        lockBtns();

        // If the expression has noting in it ie event led to empty string, simply return
        if (m_internalExpr.length() < 1)
            return;

        // If the back of the expression is '(' or an operator, return as this expression is not yet valid
        else if (std::find(shuntYard::OPERATORS.begin(), shuntYard::OPERATORS.end(), m_internalExpr.back()) != std::end(shuntYard::OPERATORS) ||
            m_internalExpr.back() == '(')
            return;

        // If the expression has a length of 1, simply return that value
        else if (m_internalExpr.length() == 1)
            return ui.ansrBrowser->setText(QString::fromStdString(m_internalExpr));

        // Otherwise attempt to make a shuntyard with the expression and validate it
        auto yard = std::make_unique<shuntYard::Yard>(m_internalExpr);
        if (!yard->validateShunt())
        {// Throw exception to produce invalid message to user
            throw std::exception();
        }
        // Otherwise its a valid expression, solve it via RPN
        std::string ansr = shuntYard::RPNEval(yard->getOutQueue());
        // Format to add commas
        formatAnsr(ansr);
        // Convert to QString and display
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
    bool hasDec = true;
    if (decIndex == std::string::npos)
    {// If none is found start from the end of the string
        decIndex = ansr.size();
        hasDec = false;
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

    // Format the result to remove extra zeros after decimal ie, .00000 from 4.00000
    if(hasDec)
    {
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
}
void CalculatorPlusGeo::formatDisplayExpr()
{// Formats the user input expression to add commas to large numbers
    // Get internal expression (not shown to user)
    m_displayExpr = QString::fromStdString(m_internalExpr);
    // Initialize values for format logic
    int idx = 1; // skips beginning character to account for starting negative number
    int revIdx = 1;
    int digitCnt = 0;

    // If starting character is a decimal set boolean control to true
    if (m_displayExpr.startsWith('.'))
        m_displayAftrDec = true;
    else
        m_displayAftrDec = false;
  
    // While not the end of the expression
    while(!(idx > m_displayExpr.length() - 1))
    {
        // Grab an element
        QChar ele = m_displayExpr.at(idx);
        // If not after a decimal and the current element is an operator, right parenthesis, decimal or end of string
        if (!m_displayAftrDec && (ele == ')' ||  ele == '.' || idx == m_displayExpr.length() - 1 ||
            std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(), 
            [&ele](const char &op) { return ele == op; })))
        {
            // Reverse direction adding commas until another operator or right parenthesis
            // If index is an operator and the prior index is a right parenthesis skip over the parenthesis
            if (idx - 2 > 0 && m_displayExpr.at(idx - 1) == ')')
                revIdx = idx - 2;
            // Set revIdx based on element at current index or if index is end of string 
            else if (idx == m_displayExpr.length() - 1 && !(ele == ')' || ele == '.' || 
                std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
                [&ele](const char& op) { return ele == op; })))
                revIdx = idx; // begins from end of string
            else
                revIdx = idx - 1; // Skips back 1 to go to number before operator/dec/parenthesis

            digitCnt = 0; // Reset the digit counter
            // While not at the beginning of the string
            while (revIdx > 0)
            {
                digitCnt++;
                // If current value is left parenthesis or an operator break out of inner loop
                if (QChar revEle = m_displayExpr.at(revIdx); revEle == '(' ||
                    std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
                    [&revEle](const char& op) { return revEle == op; })) 
                {
                    break;
                }
                // Else if a comma should be placed and next value is a number
                else if (QChar nextEle = m_displayExpr.at(revIdx - 1); digitCnt == 3 && 
                    std::any_of(shuntYard::NUMBERS.cbegin(), shuntYard::NUMBERS.cend(),
                    [&nextEle] (const char &num) { return nextEle == num;}))
                {
                    m_displayExpr.insert(revIdx, ",");
                    idx++; // Increment index to account for new character
                    digitCnt = 0;
                    revIdx--;
                }
                // Otherwise continue iteration
                else
                {
                    revIdx--;
                }
            }
        }
        // If element was a decimal set bool to skip numbers after
        if (ele == '.')
            m_displayAftrDec = true;
        // Else if its an operator or left parenthesis then we are no longer after a decimal
        else if (ele == '(' ||
            std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
            [&ele](const char& op) { return ele == op; }))
            m_displayAftrDec = false;
        idx++;
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
    if (m_internalExpr.empty()) {
        btnsReset();
        return;
    }
    // Otherwise get the last character in the expression
    char lastEntry = m_internalExpr.back();
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
        ui.decBtn->setDisabled(true);
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
        if (isConverted) {
            if (!(a + b > c) || !(a + c > b) || !(b + c > a))
            {
                ui.geoAnsrBrowser->setText("Invalid Input: One triangle side must not double the length of the others!");
                return;
            }
            result = operations::triangleArea(a, b, c);
        }
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
characters to the expressions when clicked, the display string is formatted */
void CalculatorPlusGeo::zeroClicked()
{
    m_internalExpr += '0';
    m_displayExpr += '0';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::oneClicked() 
{
    m_internalExpr += '1';
    m_displayExpr += '1';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::twoClicked()
{
    m_internalExpr += '2';
    m_displayExpr += '2';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::threeClicked()
{
    m_internalExpr += '3';
    m_displayExpr += '3';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::fourClicked()
{
    m_internalExpr += '4';
    m_displayExpr += '4';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::fiveClicked()
{
    m_internalExpr += '5';
    m_displayExpr += '5';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::sixClicked()
{
    m_internalExpr += '6';
    m_displayExpr += '6';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::sevenClicked()
{
    m_internalExpr += '7';
    m_displayExpr += '7';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::eightClicked()
{
    m_internalExpr += '8';
    m_displayExpr += '8';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::nineClicked()
{
    m_internalExpr += '9';
    m_displayExpr += '9';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::leftParenClicked()
{
    m_internalExpr += '(';
    m_displayExpr += '(';
    formatDisplayExpr();
    m_pDepth++;// Increase parenthesis depth to allow and equal amount of ')' characters
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::rightParenClicked()
{
    m_internalExpr += ')';
    m_displayExpr += ')';
    formatDisplayExpr();
    m_pDepth--;// Decrease parenthesis depth to prevent too many ')' characters
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::powClicked()
{
    m_internalExpr += '^';
    m_displayExpr += '^';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::divClicked()
{
    m_internalExpr += '/';
    m_displayExpr += '/';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::multiClicked()
{
    m_internalExpr += '*';
    m_displayExpr += '*';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::minusClicked()
{
    m_internalExpr += '-';
    m_displayExpr += '-';
    formatDisplayExpr();
    m_minusCnt++;// Increase minusCnt to prevent too many '-' characters
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::plusClicked()
{
    m_internalExpr += '+';
    m_displayExpr += '+';
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::decClicked()
{
        m_internalExpr += '.';
        m_displayExpr += '.';
        formatDisplayExpr();
        ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::delClicked()
{/* Deletes the last character in the expression string and resets 
 buttons to an appropriate state based on what character was deleted
 and what the new last character and new next last character are */

    // If internal expression is 0 or 1 in length, expression will be empty so reset logic and clear
    if (m_internalExpr.length() <= 1)
    {
        m_pDepth = 0;
        m_minusCnt = 1;
        m_afterDec = false;
        m_displayAftrDec = false;
        btnsReset();
        m_internalExpr.clear();
        m_displayExpr.clear();
        ui.ansrBrowser->clear();
        ui.exprBrowser->clear();
        return;
    }
    char last = m_internalExpr.back();
    // If the character being deleted is one of the following
    if (last == ')')
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
    {
        m_afterDec = false;// Set decimal logic to before status
        m_displayAftrDec = false;
        ui.decBtn->setEnabled(true);
    }

    // If the last value is an operator or last is minus and minus count = 1
    if (std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
        [&last](const char& op) { return last == op; }) || (last == '-' && m_minusCnt == 1))
    {   // Look for the next occurrence of a '.' or an operator
        for (auto itr = m_internalExpr.end() - 2; itr > m_internalExpr.begin(); itr--)
        {
            // If there is a decimal point then we are after a decimal
            if (*itr == '.')
            {// Set logic appropriately
                m_afterDec = true;
                m_displayAftrDec = true;
                ui.decBtn->setDisabled(true);
                break;
            }
            // Else if we reach another parenthesis or operator then we are not after a decimal
            else if (*itr == '(' || *itr == ')' || std::any_of(shuntYard::OPERATORS.cbegin(), shuntYard::OPERATORS.cend(),
                [itr](const char& op) { return *itr == op; }))
            {// Set logic appropriately
                m_afterDec = false;// Set decimal logic to before status
                m_displayAftrDec = false;
                ui.decBtn->setEnabled(true);
                break;
            }
        }
    }

    // Remove the last character from the expression
    m_internalExpr.pop_back();

    // Get the new last character and set next last to null
    char newLast = m_internalExpr.back();
    char nextLast = '\0';
    // If size > 1 then a next last character exists
    if (m_internalExpr.size() > 1)
    {
        nextLast = m_internalExpr.at(m_internalExpr.size() - 2); // Set it as next last
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
    formatDisplayExpr();
    ui.exprBrowser->setText(m_displayExpr);
}

void CalculatorPlusGeo::clearClicked()
{// User clicked the clear button --> clear all text, reset buttons and logic
    m_pDepth = 0;
    m_minusCnt = 1;
    m_afterDec = false;
    m_displayAftrDec = false;
    m_displayExpr.clear();
    m_internalExpr.clear();
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