// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The AirDollars Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Money parsing/formatting utilities.
 */
#ifndef AIRDOLLARS_UTILMONEYSTR_H
#define AIRDOLLARS_UTILMONEYSTR_H

#include <stdint.h>
#include <string>

#include "amount.h"

std::string FormatMoney(const CAmount& n, bool fPlus=false);
bool ParseMoney(const std::string& str, CAmount& nRet);
bool ParseMoney(const char* pszIn, CAmount& nRet);

#endif // AIRDOLLARS_UTILMONEYSTR_H
