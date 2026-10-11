/***************************************************************************
    File                 : Theme.cpp
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
#include "Theme.h"

#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QPalette>
#include <QProxyStyle>
#include <QStyleFactory>
#include <QStyleHints>
#include <QStyleOptionTitleBar>

namespace {

Theme::Colors lightColors()
{
    Theme::Colors c;
    c.window = QColor(0xf3f4f6);
    c.surface = QColor(0xffffff);
    c.base = QColor(0xffffff);
    c.alternateBase = QColor(0xf6f7f9);
    c.text = QColor(0x1f2328);
    c.mutedText = QColor(0x59636e);
    c.disabledText = QColor(0xa3a9b0);
    c.border = QColor(0xd5d9de);
    c.button = QColor(0xffffff);
    c.buttonHover = QColor(0xeef0f3);
    c.hover = QColor(0xe4e7eb);
    c.accent = QColor(0x2f6fed);
    c.accentText = QColor(0xffffff);
    c.accentSoft = QColor(0xdbe6fd);
    c.workspace = QColor(0xe2e5e9);
    c.titleBar = QColor(0xffffff);
    c.titleBarInactive = QColor(0xeceef1);
    c.toolTip = QColor(0xffffff);
    return c;
}

Theme::Colors darkColors()
{
    Theme::Colors c;
    c.window = QColor(0x1f2125);
    c.surface = QColor(0x26282d);
    c.base = QColor(0x17191c);
    c.alternateBase = QColor(0x1c1e22);
    c.text = QColor(0xe4e6e9);
    c.mutedText = QColor(0x9aa0a8);
    c.disabledText = QColor(0x5c626a);
    c.border = QColor(0x363a41);
    c.button = QColor(0x2b2e34);
    c.buttonHover = QColor(0x33373e);
    c.hover = QColor(0x2f3339);
    c.accent = QColor(0x4c8dff);
    c.accentText = QColor(0xffffff);
    c.accentSoft = QColor(0x24344f);
    c.workspace = QColor(0x141517);
    c.titleBar = QColor(0x2b2e34);
    c.titleBarInactive = QColor(0x222428);
    c.toolTip = QColor(0x2b2e34);
    return c;
}

Theme::Mode currentMode = Theme::Mode::System;
Theme::Colors currentColors = lightColors();
bool currentDark = false;

QPalette paletteFor(const Theme::Colors &c, bool dark)
{
    QPalette p;
    p.setColor(QPalette::Window, c.window);
    p.setColor(QPalette::WindowText, c.text);
    p.setColor(QPalette::Base, c.base);
    p.setColor(QPalette::AlternateBase, c.alternateBase);
    p.setColor(QPalette::Text, c.text);
    p.setColor(QPalette::Button, c.button);
    p.setColor(QPalette::ButtonText, c.text);
    p.setColor(QPalette::BrightText, QColor(0xff5c5c));
    p.setColor(QPalette::Highlight, c.accent);
    p.setColor(QPalette::HighlightedText, c.accentText);
    p.setColor(QPalette::ToolTipBase, c.toolTip);
    p.setColor(QPalette::ToolTipText, c.text);
    p.setColor(QPalette::PlaceholderText, c.mutedText);
    p.setColor(QPalette::Link, c.accent);
    p.setColor(QPalette::LinkVisited, c.accent.darker(120));
    // frame shades used by Fusion
    p.setColor(QPalette::Light, dark ? QColor(0x3a3e45) : QColor(0xffffff));
    p.setColor(QPalette::Midlight, dark ? QColor(0x30343a) : QColor(0xf5f6f8));
    p.setColor(QPalette::Mid, dark ? QColor(0x2a2d33) : QColor(0xc9ced5));
    p.setColor(QPalette::Dark, dark ? QColor(0x111214) : QColor(0xa9afb7));
    p.setColor(QPalette::Shadow, dark ? QColor(0x0b0c0e) : QColor(0x8a9099));
    for (auto role : { QPalette::WindowText, QPalette::Text, QPalette::ButtonText })
        p.setColor(QPalette::Disabled, role, c.disabledText);
    p.setColor(QPalette::Disabled, QPalette::Highlight, c.border);
    p.setColor(QPalette::Disabled, QPalette::HighlightedText, c.disabledText);
    p.setColor(QPalette::Inactive, QPalette::Highlight, dark ? c.accent.darker(140) : c.accentSoft);
    p.setColor(QPalette::Inactive, QPalette::HighlightedText, c.text);
    return p;
}

QString styleSheetFor(const Theme::Colors &c)
{
    QFile file(":/styles/theme.qss");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return QString();
    QString qss = QString::fromUtf8(file.readAll());
    const QList<QPair<QString, QColor>> tokens = {
        { "window", c.window },         { "surface", c.surface },
        { "base", c.base },             { "alternateBase", c.alternateBase },
        { "text", c.text },             { "mutedText", c.mutedText },
        { "disabledText", c.disabledText }, { "border", c.border },
        { "button", c.button },         { "buttonHover", c.buttonHover },
        { "hover", c.hover },           { "accent", c.accent },
        { "accentText", c.accentText }, { "accentSoft", c.accentSoft },
        { "toolTip", c.toolTip },
    };
    for (const auto &token : tokens)
        qss.replace("@" + token.first + "@", token.second.name());
    return qss;
}

/*!\brief Fusion with flat, theme colored title bars for the MDI sub-windows.
 *
 * Fusion paints title bars with a gradient of the highlight color and hard-coded white/black
 * text, which does not fit (and is unreadable in) the dark theme.
 */
class SciDAVisStyle : public QProxyStyle
{
public:
    SciDAVisStyle() : QProxyStyle(QStyleFactory::create("Fusion")) { }

    int pixelMetric(PixelMetric metric, const QStyleOption *option,
                    const QWidget *widget) const override
    {
        if (metric == PM_TitleBarHeight)
            return qMax(26, QProxyStyle::pixelMetric(metric, option, widget));
        return QProxyStyle::pixelMetric(metric, option, widget);
    }

    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option,
                            QPainter *painter, const QWidget *widget) const override
    {
        const auto *titleBar = qstyleoption_cast<const QStyleOptionTitleBar *>(option);
        if (control != CC_TitleBar || !titleBar) {
            QProxyStyle::drawComplexControl(control, option, painter, widget);
            return;
        }

        const Theme::Colors &c = Theme::colors();
        const bool active = titleBar->titleBarState & State_Active;
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->fillRect(titleBar->rect, active ? c.titleBar : c.titleBarInactive);
        if (active)
            painter->fillRect(QRect(titleBar->rect.topLeft(), QSize(titleBar->rect.width(), 2)),
                              c.accent);
        painter->setPen(c.border);
        painter->drawLine(titleBar->rect.bottomLeft(), titleBar->rect.bottomRight());

        // window icon
        if (titleBar->subControls & SC_TitleBarSysMenu && !titleBar->icon.isNull()) {
            QRect r = subControlRect(control, titleBar, SC_TitleBarSysMenu, widget);
            const int side = qMin(16, qMin(r.width(), r.height()));
            titleBar->icon.paint(painter, QRect(r.center() - QPoint(side / 2 - 1, side / 2 - 1),
                                                QSize(side, side)));
        }

        // title
        if (titleBar->subControls & SC_TitleBarLabel) {
            QRect r = subControlRect(control, titleBar, SC_TitleBarLabel, widget).adjusted(4, 0, -4, 0);
            QFont font = painter->font();
            font.setBold(active);
            painter->setFont(font);
            painter->setPen(active ? c.text : c.mutedText);
            painter->drawText(r, Qt::AlignVCenter | Qt::AlignLeft,
                              painter->fontMetrics().elidedText(titleBar->text, Qt::ElideRight,
                                                                r.width()));
        }

        // buttons
        const SubControl buttons[] = { SC_TitleBarMinButton, SC_TitleBarNormalButton,
                                       SC_TitleBarMaxButton, SC_TitleBarCloseButton };
        for (SubControl button : buttons) {
            if (!(titleBar->subControls & button))
                continue;
            QRect r = subControlRect(control, titleBar, button, widget);
            if (!r.isValid() || r.isEmpty())
                continue;
            r = r.adjusted(1, 1, -1, -1);
            const bool hovered = (titleBar->activeSubControls & button)
                    && (titleBar->state & (State_MouseOver | State_Sunken));
            if (hovered) {
                painter->setPen(Qt::NoPen);
                painter->setBrush(button == SC_TitleBarCloseButton ? QColor(0xe5484d) : c.hover);
                painter->drawRoundedRect(r, 4, 4);
            }
            QPen pen(hovered && button == SC_TitleBarCloseButton ? QColor(Qt::white)
                                                                   : (active ? c.text : c.mutedText),
                     1.3);
            pen.setCapStyle(Qt::RoundCap);
            painter->setPen(pen);
            painter->setBrush(Qt::NoBrush);
            const QRectF g = QRectF(r).adjusted(r.width() * .32, r.height() * .32,
                                                -r.width() * .32, -r.height() * .32);
            switch (button) {
            case SC_TitleBarCloseButton:
                painter->drawLine(g.topLeft(), g.bottomRight());
                painter->drawLine(g.topRight(), g.bottomLeft());
                break;
            case SC_TitleBarMinButton:
                painter->drawLine(QPointF(g.left(), g.bottom()), g.bottomRight());
                break;
            case SC_TitleBarMaxButton:
                painter->drawRect(g);
                break;
            case SC_TitleBarNormalButton: {
                const qreal d = g.width() * .3;
                painter->drawRect(g.adjusted(0, d, -d, 0));
                painter->drawPolyline(QPolygonF({ QPointF(g.left() + d, g.top() + d),
                                                  QPointF(g.left() + d, g.top()), g.topRight(),
                                                  QPointF(g.right(), g.bottom() - d),
                                                  QPointF(g.right() - d, g.bottom() - d) }));
                break;
            }
            default:
                break;
            }
        }
        painter->restore();
    }
};

bool platformIsDark()
{
    return QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;
}

} // namespace

namespace Theme {

Mode fromString(const QString &name)
{
    if (name == "light")
        return Mode::Light;
    if (name == "dark")
        return Mode::Dark;
    return Mode::System; // also the former "default"
}

QString toString(Mode mode)
{
    switch (mode) {
    case Mode::Light:
        return "light";
    case Mode::Dark:
        return "dark";
    default:
        return "system";
    }
}

void apply(Mode mode)
{
    static bool initialized = false;
    if (!initialized) {
        initialized = true;
        QApplication::setStyle(new SciDAVisStyle);
        // follow the platform when it switches between light and dark
        QObject::connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, qApp,
                         [] {
                             if (currentMode == Mode::System)
                                 apply(Mode::System);
                         });
    }

    currentMode = mode;
    currentDark = mode == Mode::Dark || (mode == Mode::System && platformIsDark());
    currentColors = currentDark ? darkColors() : lightColors();
    QApplication::setPalette(paletteFor(currentColors, currentDark));
    qApp->setStyleSheet(styleSheetFor(currentColors));
}

Mode current()
{
    return currentMode;
}

bool isDark()
{
    return currentDark;
}

const Colors &colors()
{
    return currentColors;
}

} // namespace Theme
