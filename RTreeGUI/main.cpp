/*
 * QDiagram - A Qt package for creating routed diagrams.
 *
 * Class Name: %{Cpp:License:ClassName}
 *
 * File: %{Cpp:License:FileName}
 *
 * Copyright (C) 2020  Mark E. Wilson
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * See the file LICENSE.LGPL distributed with the library
 *
 * Licensees holding a valid commercial license may use this file in
 * accordance with the commercial license agreement provided with the
 * library.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Author(s):  Mark E. Wilson
 *
 * QDiagram depends on the libavoid library:
 *
 *      libavoid - Fast, Incremental, Object-avoiding Line Router
 *
 *      Copyright (C) 2010-2014  Monash University
*/
#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
