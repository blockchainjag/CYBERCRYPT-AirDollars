// Copyright (c) 2011-2013 The AirDollars Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIRDOLLARS_QT_COINCONTROLTREEWIDGET_H
#define AIRDOLLARS_QT_COINCONTROLTREEWIDGET_H

#include <QKeyEvent>
#include <QTreeWidget>

class CoinControlTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit CoinControlTreeWidget(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // AIRDOLLARS_QT_COINCONTROLTREEWIDGET_H
