// Copyright (c) 2011-2014 The AirDollars Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef AIRDOLLARS_QT_AIRDOLLARSADDRESSVALIDATOR_H
#define AIRDOLLARS_QT_AIRDOLLARSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AirDollarsAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AirDollarsAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** AirDollars address widget validator, checks for a valid airdollars address.
 */
class AirDollarsAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AirDollarsAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // AIRDOLLARS_QT_AIRDOLLARSADDRESSVALIDATOR_H
