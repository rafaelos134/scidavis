/***************************************************************************
    File                 : Theme.h
    Project              : SciDAVis
    Description          : Application color themes (system, light, dark)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
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
#ifndef THEME_H
#define THEME_H

#include <QColor>
#include <QString>

//! Application color themes.
/**
 * A theme is a Fusion based style, a palette and a style sheet (":/styles/theme.qss", whose
 * @tokens@ are replaced by the colors below). Icons follow the palette on their own (see
 * IconLoader).
 */
namespace Theme {

enum class Mode { System, Light, Dark };

//! Colors of a theme, also used outside of the palette (workspace, MDI title bars, ...)
struct Colors
{
    QColor window, surface, base, alternateBase, text, mutedText, disabledText, border, button,
            buttonHover, hover, accent, accentText, accentSoft, workspace, titleBar,
            titleBarInactive, toolTip;
};

//! Settings value ("system", "light", "dark") to mode; anything else is System
Mode fromString(const QString &name);
QString toString(Mode mode);

//! Apply a theme to the application (style, palette and style sheet)
void apply(Mode mode);
//! The theme last passed to apply()
Mode current();
//! Whether the theme last applied is dark (for Mode::System, as reported by the platform)
bool isDark();
//! Colors of the theme last applied
const Colors &colors();

} // namespace Theme

#endif // THEME_H
