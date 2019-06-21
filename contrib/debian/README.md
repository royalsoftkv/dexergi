
Debian
====================
This directory contains files used to package dexergid/dexergi-qt
for Debian-based Linux systems. If you compile dexergid/dexergi-qt yourself, there are some useful files here.

## dexergi: URI support ##


dexergi-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dexergi-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dexergi-qt binary to `/usr/bin`
and the `../../share/pixmaps/dexergi128.png` to `/usr/share/pixmaps`

dexergi-qt.protocol (KDE)

