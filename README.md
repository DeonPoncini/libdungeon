---
Title: libdungeon
Description: dungeon generator
Author: Deon Poncini

---

libdungeon
===============

Developed by Deon Poncini <dex1337@gmail.com>

Downloads
---------
[github](https://github.com/DeonPoncini/libdungeon)

Description
-----------
A library for generating dungeon maps. Currently supports three generation
modes:
+Classic: random rectangular rooms joined by corridors
+Conway: cellular automata generation based on the game of life
+RandomCaves: Random polygonal rooms that fill the space available

Building
--------
    git clone https://github.com/DeonPoncini/libdungeon.git
    cd libdungeon
    mkdir _build
    cd _build
    cmake ..
    make

Usage
-----
The test program included dungeon-test can be run to generate an example of
each dungeon generating algorithm.

The algorithms are either feature based (Classic, RandomCaves) or cell based
(Conway). To use the algorithms set the appropriate feature values and call the
generating function. A TileMap is returned, which is a 2D array of Cells. The
cells are either valid or invalid. A valid cell indicates the cell is part of a
room, an invalid cell indicates that it is not part of the room

License
-------
Copyright (c) 2014 Deon Poncini. See the LICENSE file for license rights and limitations (MIT)
