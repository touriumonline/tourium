
Debian
====================
This directory contains files used to package touriumd/tourium-qt
for Debian-based Linux systems. If you compile touriumd/tourium-qt yourself, there are some useful files here.

## tourium: URI support ##


tourium-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install tourium-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your touriumqt binary to `/usr/bin`
and the `../../share/pixmaps/tourium128.png` to `/usr/share/pixmaps`

tourium-qt.protocol (KDE)

