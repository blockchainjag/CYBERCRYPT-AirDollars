#!/bin/bash
# Copyright (c) 2013-2014 The AirDollars Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

BUILDDIR="/home/airdollars"
EXEEXT=".exe"

# These will turn into comments if they were disabled when configuring.
ENABLE_WALLET=1
ENABLE_UTILS=1
ENABLE_AIRDOLLARSD=1

REAL_AIRDOLLARSD="$BUILDDIR/src/airdollarsd${EXEEXT}"
REAL_AIRDOLLARSCLI="$BUILDDIR/src/airdollars-cli${EXEEXT}"

