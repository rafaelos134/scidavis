/***************************************************************************
    File                 : iconloader.cpp
    Project              : SciDAVis
    --------------------------------------------------------------------
    Copyright            : (C) 2016 by Arun Narayanankutty
                           (C) 2026 themed SVG icons
    Email                : n.arun.lifescience@gmail.com
    Description          : Load icons that follow the application palette

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

#include "IconLoader.h"

#include <QApplication>
#include <QFile>
#include <QHash>
#include <QIconEngine>
#include <QPainter>
#include <QPalette>
#include <QPixmapCache>
#include <QSvgRenderer>
#include <QtDebug>

namespace {

const QString themedPath = QStringLiteral(":/themed/%1.svg");

//! SVG sources, loaded once
QByteArray svgSource(const QString &path)
{
    static QHash<QString, QByteArray> cache;
    auto it = cache.find(path);
    if (it == cache.end()) {
        QFile file(path);
        QByteArray data;
        if (file.open(QIODevice::ReadOnly))
            data = file.readAll();
        // slightly lighter strokes than the 2px of the icon sources look better at 16-24px
        data.replace("stroke-width=\"2\"", "stroke-width=\"1.75\"");
        it = cache.insert(path, data);
    }
    return it.value();
}

/*!\brief Icon engine rendering a monochrome SVG in the colors of the current palette.
 *
 * "currentColor" in the SVG becomes the window text color (or the disabled/highlighted text
 * color, depending on the icon mode) and "#ACCENT" the highlight color. Pixmaps are rendered
 * on demand and cached per color, so icons follow theme changes without being recreated.
 */
class ThemedIconEngine : public QIconEngine
{
public:
    explicit ThemedIconEngine(const QString &path) : d_path(path) { }

    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State) override
    {
        const qreal dpr = painter->device() ? painter->device()->devicePixelRatio() : 1.0;
        painter->drawPixmap(rect, render(rect.size(), dpr, mode));
    }

    QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State) override
    {
        return render(size, 1.0, mode);
    }

    QPixmap scaledPixmap(const QSize &size, QIcon::Mode mode, QIcon::State, qreal scale) override
    {
        return render(size, scale, mode);
    }

    QIconEngine *clone() const override { return new ThemedIconEngine(d_path); }
    QString key() const override { return QStringLiteral("SciDAVisThemedIcon"); }
    bool isNull() override { return svgSource(d_path).isEmpty(); }

private:
    QPixmap render(const QSize &size, qreal dpr, QIcon::Mode mode) const
    {
        if (size.isEmpty())
            return QPixmap();
        const QPalette palette = QApplication::palette();
        QColor color = palette.color(QPalette::Active, QPalette::WindowText);
        QColor accent = palette.color(QPalette::Active, QPalette::Highlight);
        if (mode == QIcon::Disabled) {
            color = palette.color(QPalette::Disabled, QPalette::WindowText);
            accent = color;
        } else if (mode == QIcon::Selected) {
            color = accent = palette.color(QPalette::Active, QPalette::HighlightedText);
        }

        const QString key = QStringLiteral("themed:%1:%2x%3@%4:%5:%6")
                                    .arg(d_path)
                                    .arg(size.width())
                                    .arg(size.height())
                                    .arg(dpr)
                                    .arg(color.name(QColor::HexArgb), accent.name(QColor::HexArgb));
        QPixmap pixmap;
        if (QPixmapCache::find(key, &pixmap))
            return pixmap;

        QByteArray svg = svgSource(d_path);
        svg.replace("currentColor", color.name(QColor::HexRgb).toLatin1());
        svg.replace("#ACCENT", accent.name(QColor::HexRgb).toLatin1());
        QSvgRenderer renderer(svg);

        pixmap = QPixmap(size * dpr);
        pixmap.fill(Qt::transparent);
        {
            QPainter painter(&pixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            if (color.alphaF() < 1.0)
                painter.setOpacity(color.alphaF());
            // keep the square icon centered in non-square requests
            const qreal side = qMin(size.width(), size.height()) * dpr;
            renderer.render(&painter,
                            QRectF((size.width() * dpr - side) / 2, (size.height() * dpr - side) / 2,
                                   side, side));
        }
        pixmap.setDevicePixelRatio(dpr);
        QPixmapCache::insert(key, pixmap);
        return pixmap;
    }

    QString d_path;
};

} // namespace

QIcon IconLoader::load(const QString &name)
{
    if (name.isEmpty()) {
        qDebug() << "Icon name is null";
        return QIcon();
    }
    const QString path = themedPath.arg(name);
    if (QFile::exists(path))
        return QIcon(new ThemedIconEngine(path));

    // legacy bitmap resources
    for (const QString &legacy : { QStringLiteral(":/%1.xpm"), QStringLiteral(":/%1.png") }) {
        if (QFile::exists(legacy.arg(name)))
            return QIcon(QPixmap(legacy.arg(name)));
    }
    qDebug() << "Couldn't load icon" << name;
    return QIcon();
}

QPixmap IconLoader::pixmap(const QString &name, int size)
{
    return load(name).pixmap(size, size);
}
