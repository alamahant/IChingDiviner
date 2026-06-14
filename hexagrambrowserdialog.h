#ifndef HEXAGRAMBROWSERDIALOG_H
#define HEXAGRAMBROWSERDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QMap>
#include <QPushButton>
#include "iching.h"

class HexagramBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HexagramBrowserDialog(IChing *iching, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;
    void hideEvent(QHideEvent *event) override;

signals:
    void hexagramSelected(int hexagramNumber);
    void hexDialogHidden();
private slots:
    void onHexagramButtonClicked();

private:
    IChing *iching;
    QMap<int, QPushButton*> hexagramButtons;
    QMap<int, HexagramInfo> hexagramData;
    QPushButton* lastSelectedButton = nullptr;

    void setupGrid();
    void applyButtonStyle(QPushButton* button, bool selected);
};

#endif
