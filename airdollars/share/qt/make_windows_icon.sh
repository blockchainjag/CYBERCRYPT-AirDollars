#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/airdollars.png
ICON_DST=../../src/qt/res/icons/airdollars.ico
convert ${ICON_SRC} -resize 16x16 airdollars-16.png
convert ${ICON_SRC} -resize 32x32 airdollars-32.png
convert ${ICON_SRC} -resize 48x48 airdollars-48.png
convert airdollars-16.png airdollars-32.png airdollars-48.png ${ICON_DST}

