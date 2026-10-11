/***************************************************************************
    File                 : BracketHighlighter.cpp
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
#include "BracketHighlighter.h"
#include "Theme.h"

#include <QComboBox>
#include <QCoreApplication>
#include <QInputMethodEvent>
#include <QLineEdit>
#include <QSet>
#include <QTextEdit>

namespace {

bool isOpening(QChar c)
{
    return c == '(' || c == '[' || c == '{';
}

bool isClosing(QChar c)
{
    return c == ')' || c == ']' || c == '}';
}

QChar partnerOf(QChar c)
{
    switch (c.unicode()) {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    default:
        return QChar();
    }
}

/*!\brief Walks a text, calling visit(position, character) for brackets outside of strings.
 *
 * Quoted strings ("..." and '...', with backslash escapes) and "#" comments end at a line
 * break.
 */
template<typename Visitor>
void forEachBracket(const QString &text, Visitor visit)
{
    QChar quote;
    bool comment = false;
    for (int i = 0; i < text.size(); i++) {
        const QChar c = text.at(i);
        if (c == '\n' || c == QChar::ParagraphSeparator) {
            quote = QChar();
            comment = false;
        } else if (comment) {
            continue;
        } else if (!quote.isNull()) {
            if (c == '\\')
                i++;
            else if (c == quote)
                quote = QChar();
        } else if (c == '"' || c == '\'') {
            quote = c;
        } else if (c == '#') {
            comment = true;
        } else if (isOpening(c) || isClosing(c)) {
            visit(i, c);
        }
    }
}

QSet<BracketHighlighter *> &highlighters()
{
    static QSet<BracketHighlighter *> set;
    return set;
}

void highlightMatchingPair(QTextEdit *edit)
{
    QList<QTextEdit::ExtraSelection> selections;
    const QString text = edit->toPlainText();
    const int cursor = edit->textCursor().position();
    // the bracket right after the cursor, or else right before it
    for (int pos : { cursor, cursor - 1 }) {
        if (pos < 0 || pos >= text.size()
            || !(isOpening(text.at(pos)) || isClosing(text.at(pos))))
            continue;
        const int partner = BracketHighlighter::matchingBracket(text, pos);
        if (partner < 0)
            break;
        for (int p : { pos, partner }) {
            QTextEdit::ExtraSelection selection;
            selection.cursor = QTextCursor(edit->document());
            selection.cursor.setPosition(p);
            selection.cursor.setPosition(p + 1, QTextCursor::KeepAnchor);
            selection.format = BracketHighlighter::matchFormat();
            selections << selection;
        }
        break;
    }
    edit->setExtraSelections(selections);
}

//! Colors the brackets of a QLineEdit through input method text formats.
class LineEditBrackets : public QObject
{
public:
    explicit LineEditBrackets(QLineEdit *edit) : QObject(edit), d_edit(edit)
    {
        instances().insert(this);
        connect(edit, &QLineEdit::textChanged, this, &LineEditBrackets::update);
        connect(edit, &QLineEdit::cursorPositionChanged, this, &LineEditBrackets::update);
        update();
    }
    ~LineEditBrackets() override { instances().remove(this); }

    static QSet<LineEditBrackets *> &instances()
    {
        static QSet<LineEditBrackets *> set;
        return set;
    }

    void update()
    {
        const QString text = d_edit->text();
        int depth = 0;
        const auto brackets = BracketHighlighter::scan(text, depth);
        const int cursor = d_edit->cursorPosition();

        // pair next to the cursor
        int pairA = -1, pairB = -1;
        for (int pos : { cursor, cursor - 1 }) {
            if (pos >= 0 && pos < text.size()
                && (isOpening(text.at(pos)) || isClosing(text.at(pos)))) {
                const int partner = BracketHighlighter::matchingBracket(text, pos);
                if (partner >= 0) {
                    pairA = pos;
                    pairB = partner;
                }
                break;
            }
        }

        // input method attributes are relative to the cursor position
        QList<QInputMethodEvent::Attribute> attributes;
        for (const auto &b : brackets) {
            QTextCharFormat format = BracketHighlighter::bracketFormat(b.depth, b.error);
            if (b.position == pairA || b.position == pairB)
                format.merge(BracketHighlighter::matchFormat());
            attributes << QInputMethodEvent::Attribute(QInputMethodEvent::TextFormat,
                                                       b.position - cursor, 1, format);
        }
        QInputMethodEvent event(QString(), attributes);
        QCoreApplication::sendEvent(d_edit, &event);
    }

private:
    QLineEdit *d_edit;
};

} // namespace

void BracketHighlighter::attach(QTextEdit *edit)
{
    if (!edit)
        return;
    new BracketHighlighter(edit->document());
    connect(edit, &QTextEdit::cursorPositionChanged, edit, [edit] { highlightMatchingPair(edit); });
    connect(edit, &QTextEdit::textChanged, edit, [edit] { highlightMatchingPair(edit); });
}

void BracketHighlighter::attach(QLineEdit *edit)
{
    if (edit)
        new LineEditBrackets(edit);
}

void BracketHighlighter::attach(QComboBox *box)
{
    if (box && box->isEditable())
        attach(box->lineEdit());
}

void BracketHighlighter::updateAll()
{
    for (BracketHighlighter *highlighter : std::as_const(highlighters()))
        highlighter->rehighlight();
    for (LineEditBrackets *edit : std::as_const(LineEditBrackets::instances()))
        edit->update();
}

QVector<BracketHighlighter::Bracket> BracketHighlighter::scan(const QString &text, int &depth)
{
    QVector<Bracket> result;
    QString open; // brackets opened in this text, to detect mismatched types
    forEachBracket(text, [&](int i, QChar c) {
        if (isOpening(c)) {
            result.append({ i, depth, false });
            open.append(c);
            depth++;
        } else if (depth == 0) {
            result.append({ i, 0, true }); // nothing to close
        } else {
            const bool mismatch = !open.isEmpty() && open.back() != partnerOf(c);
            if (!open.isEmpty())
                open.chop(1);
            depth--;
            result.append({ i, depth, mismatch });
        }
    });
    return result;
}

int BracketHighlighter::matchingBracket(const QString &text, int position)
{
    const QChar c = text.at(position);
    if (!isOpening(c) && !isClosing(c))
        return -1;
    QVector<int> stack;
    int partner = -1;
    forEachBracket(text, [&](int i, QChar b) {
        if (partner >= 0)
            return;
        if (isOpening(b)) {
            stack.append(i);
        } else if (!stack.isEmpty() && text.at(stack.back()) == partnerOf(b)) {
            const int opening = stack.takeLast();
            if (opening == position)
                partner = i;
            else if (i == position)
                partner = opening;
        } else if (!stack.isEmpty()) {
            stack.removeLast(); // mismatched pair, keep going
        }
    });
    return partner;
}

QTextCharFormat BracketHighlighter::bracketFormat(int depth, bool error)
{
    // the bracket pair colors of common code editors, readable on light and dark backgrounds
    static const QColor light[] = { QColor(0x0431fa), QColor(0x319331), QColor(0xa0522d) };
    static const QColor dark[] = { QColor(0xffd700), QColor(0xda70d6), QColor(0x179fff) };
    QTextCharFormat format;
    if (error) {
        format.setForeground(Theme::isDark() ? QColor(0xff6b6b) : QColor(0xd70015));
        format.setFontUnderline(true);
        format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
    } else {
        format.setForeground(Theme::isDark() ? dark[depth % 3] : light[depth % 3]);
    }
    return format;
}

QTextCharFormat BracketHighlighter::matchFormat()
{
    QTextCharFormat format;
    format.setBackground(Theme::colors().accentSoft);
    format.setFontWeight(QFont::Bold);
    return format;
}

BracketHighlighter::BracketHighlighter(QTextDocument *document) : QSyntaxHighlighter(document)
{
    highlighters().insert(this);
}

BracketHighlighter::~BracketHighlighter()
{
    highlighters().remove(this);
}

void BracketHighlighter::highlightBlock(const QString &text)
{
    // nesting depth carried over from the previous line (block state -1 means unset)
    int depth = qMax(0, previousBlockState());
    for (const auto &b : scan(text, depth))
        setFormat(b.position, 1, bracketFormat(b.depth, b.error));
    setCurrentBlockState(depth);
}
