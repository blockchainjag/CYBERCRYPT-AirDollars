
Debian
====================
This directory contains files used to package airdollarsd/airdollars-qt
for Debian-based Linux systems. If you compile airdollarsd/airdollars-qt yourself, there are some useful files here.

## airdollars: URI support ##


airdollars-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install airdollars-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your airdollars-qt binary to `/usr/bin`
and the `../../share/pixmaps/airdollars128.png` to `/usr/share/pixmaps`

airdollars-qt.protocol (KDE)

