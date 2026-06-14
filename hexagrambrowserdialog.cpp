#include "hexagrambrowserdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include<QCloseEvent>

HexagramBrowserDialog::HexagramBrowserDialog(IChing *iching, QWidget *parent)
    : QDialog(parent), iching(iching)
{
    setWindowTitle("I Ching Hexagram Browser");
    setMinimumSize(600, 650);
    setModal(false);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title
    QLabel *titleLabel = new QLabel("Select a Hexagram", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(12);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // Grid container
    setupGrid();

    // Info label
    QLabel *infoLabel = new QLabel("Click any hexagram to view its meaning", this);
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("color: #888; font-style: italic; margin: 10px;");
    mainLayout->addWidget(infoLabel);

    // Close button
    QPushButton *closeButton = new QPushButton("Close", this);
    closeButton->setFixedWidth(100);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);

    connect(closeButton, &QPushButton::clicked, this, [this]{
        emit hexDialogHidden();
        hide();;
    });
}

void HexagramBrowserDialog::setupGrid()
{
    QList<HexagramInfo> hexagrams = iching->getAllHexagrams();

    QWidget *gridWidget = new QWidget(this);
    QGridLayout *gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(8);

    int row = 0;
    int col = 0;

    for (const HexagramInfo &hex : hexagrams) {
        int hexNumber = hex.number.toInt();
        hexagramData[hexNumber] = hex;

        // Create button with symbol + number
        QString buttonText = QString("%1 %2").arg(hex.symbol, hex.number);
        QPushButton *button = new QPushButton(buttonText, this);

        // Override global button height for hexagram grid
        button->setFixedSize(65, 65);
        button->setProperty("hexNumber", hexNumber);

        applyButtonStyle(button, false);
        // Set tooltip with full info
        button->setToolTip(QString("%1 - %2 (%3)")
            .arg(hex.name)
            .arg(hex.description)
            .arg(hex.pinyin));

        connect(button, &QPushButton::clicked, this, &HexagramBrowserDialog::onHexagramButtonClicked);

        gridLayout->addWidget(button, row, col);
        hexagramButtons[hexNumber] = button;

        col++;
        if (col >= 8) {
            col = 0;
            row++;
        }
    }

    // Add the grid widget to the main layout
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(layout());
    if (mainLayout) {
        mainLayout->insertWidget(1, gridWidget);
    }
}

void HexagramBrowserDialog::onHexagramButtonClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int hexNumber = clickedButton->property("hexNumber").toInt();

    // Reset last selected button style
    if (lastSelectedButton) {
        applyButtonStyle(lastSelectedButton, false);
    }

    // Style the newly selected button
    applyButtonStyle(clickedButton, true);
    lastSelectedButton = clickedButton;

    // Emit signal with hexagram number
    emit hexagramSelected(hexNumber);
}

void HexagramBrowserDialog::applyButtonStyle(QPushButton* button, bool selected)
{
    if (!button) return;

    QString baseStyle =
        "QPushButton {"
        "    font-size: 13px;"
        "    min-height: 55px;"
        "    max-height: 55px;"
        "    min-width: 55px;"
        "    max-width: 55px;"
        "    padding: 2px;"
        "    background-color: #2a2a2a;"  // Default dark gray background
        "    border: 1px solid #555;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3a6ea5;"
        "    font-size: 26px;"
        "    font-weight: bold;"
        "    border: 1px solid #6ea8dc;"
        "}";

    if (selected) {
        button->setStyleSheet(baseStyle +
            "QPushButton {"
            "    border: 2px solid #ffd700;"
            "    background-color: #2a2a2a;"  // Keep same dark gray background
            "}");
    } else {
        button->setStyleSheet(baseStyle);
    }
}

void HexagramBrowserDialog::closeEvent(QCloseEvent *event)
{
    emit hexDialogHidden();
    hide();  // Hide instead of closing
    event->ignore();  // Ignore the close event
}

void HexagramBrowserDialog::hideEvent(QHideEvent *event)
{
    emit hexDialogHidden();
    QDialog::hideEvent(event);
}
