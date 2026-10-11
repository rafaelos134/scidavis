/***************************************************************************
    File                 : BracketHighlighter.h
    Project              : SciDAVis
    Description          : Rainbow coloring and matching of (), [] and {} in formulas
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
#ifndef BRACKETHIGHLIGHTER_H
#define BRACKETHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>

class QComboBox;
class QLineEdit;
class QTextEdit;

//! Colors (), [] and {} by nesting depth and highlights the pair around the cursor.
/**
 * Every nesting level gets its own color (as "rainbow brackets" in code editors), closing
 * brackets without an opening one are marked as errors, and the bracket next to the text
 * cursor is highlighted together with its partner, which shows where an expression begins
 * and ends. Brackets inside quoted strings are ignored. Colors follow the light/dark theme.
 *
 * Use attach() on any formula input; the highlighter is owned by the widget.
 */
class BracketHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    //! Color the brackets of a multi-line editor (and highlight matching pairs)
    static void attach(QTextEdit *edit);
    //! Color the brackets of a single line editor (and highlight matching pairs)
    static void attach(QLineEdit *edit);
    //! Same for the line editor of an editable combo box
    static void attach(QComboBox *box);

    //! Recolor every attached editor, e.g. after a theme change
    static void updateAll();

    //! A bracket found by scan()
    struct Bracket
    {
        int position; //!< in the scanned text
        int depth; //!< nesting depth (0 for the outermost pair)
        bool error; //!< closing without opening, or not matching the opening type
    };
    /*!\brief Find the brackets of a text.
     * \param depth nesting depth at the start of the text, updated to the depth at its end
     */
    static QVector<Bracket> scan(const QString &text, int &depth);
    //! Position of the bracket matching the one at position (or -1)
    static int matchingBracket(const QString &text, int position);
    //! Format used for a bracket
    static QTextCharFormat bracketFormat(int depth, bool error);
    //! Format added to the bracket pair next to the cursor
    static QTextCharFormat matchFormat();

    explicit BracketHighlighter(QTextDocument *document);
    ~BracketHighlighter() override;

protected:
    void highlightBlock(const QString &text) override;
};

#endif // BRACKETHIGHLIGHTER_H
