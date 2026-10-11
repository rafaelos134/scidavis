/***************************************************************************
    File                 : iconloader.cpp
    Project              : SciDAVis
    --------------------------------------------------------------------
    Copyright            : (C) 2016 by Arun Narayanankutty
    Email                : n.arun.lifescience@gmail.com
    Description          : Load icons

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/

#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QIcon>
#include <QPixmap>

//! Loads the application icons.
/**
 * Icons are monochrome SVGs (resources ":/themed/<name>.svg") drawn in the colors of the
 * current application palette, so they adapt to light and dark themes automatically.
 */
class IconLoader
{
public:
    static QIcon load(const QString &name);
    static QPixmap pixmap(const QString &name, int size);

private:
    IconLoader() { }
};

#endif // ICONLOADER_H
