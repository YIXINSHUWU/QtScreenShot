

#include "texttool.h"
#include "textwidget.h"
#include "textconfig.h"

#define BASE_POINT_SIZE 8


TextTool::TextTool(QObject *parent) : CaptureTool(parent), m_size(1) {
}

bool TextTool::isValid() const {
    return !m_text.isEmpty();
}

bool TextTool::closeOnButtonPressed() const {
    return false;
}

bool TextTool::isSelectable() const {
    return true;
}

bool TextTool::showMousePreview() const {
    return false;
}

QIcon TextTool::icon(const QColor &background, bool inEditor) const {
    Q_UNUSED(inEditor);
    return QIcon(iconPath(background) + "text.svg");
}

QString TextTool::name() const {
    return QStringLiteral("文本");
}

QString TextTool::nameID() {
    return QLatin1String("");
}

QString TextTool::description() const {
    return QStringLiteral("向截图添加文本");
}

QWidget *TextTool::widget() {
    TextWidget *w = new TextWidget();
    w->setTextColor(m_color);
    m_font.setPointSize(m_size + BASE_POINT_SIZE);
    w->setFont(m_font);
    connect(w, &TextWidget::textUpdated,
            this, &TextTool::updateText);
    m_widget = w;
    return w;
}

QWidget *TextTool::configurationWidget() {
    m_confW = new TextConfig();
    connect(m_confW, &TextConfig::fontFamilyChanged,
            this, &TextTool::updateFamily);
    connect(m_confW, &TextConfig::fontItalicChanged,
            this, &TextTool::updateFontItalic);
    connect(m_confW, &TextConfig::fontStrikeOutChanged,
            this, &TextTool::updateFontStrikeOut);
    connect(m_confW, &TextConfig::fontUnderlineChanged,
            this, &TextTool::updateFontUnderline);
    connect(m_confW, &TextConfig::fontWeightChanged,
            this, &TextTool::updateFontWeight);
    m_confW->setItalic(m_font.italic());
    m_confW->setUnderline(m_font.underline());
    m_confW->setStrikeOut(m_font.strikeOut());
    m_confW->setWeight(m_font.weight());
    return m_confW;
}

CaptureTool *TextTool::copy(QObject *parent) {
    TextTool *tt = new TextTool(parent);
    connect(m_confW, &TextConfig::fontFamilyChanged,
            tt, &TextTool::updateFamily);
    connect(m_confW, &TextConfig::fontItalicChanged,
            tt, &TextTool::updateFontItalic);
    connect(m_confW, &TextConfig::fontStrikeOutChanged,
            tt, &TextTool::updateFontStrikeOut);
    connect(m_confW, &TextConfig::fontUnderlineChanged,
            tt, &TextTool::updateFontUnderline);
    connect(m_confW, &TextConfig::fontWeightChanged,
            tt, &TextTool::updateFontWeight);
    tt->m_font = m_font;
    return tt;
}

void TextTool::undo(QPixmap &pixmap) {
    QPainter p(&pixmap);
    p.drawPixmap(m_backupArea.topLeft(), m_pixmapBackup);
}

void TextTool::process(QPainter &painter, const QPixmap &pixmap, bool recordUndo) {
    if (m_text.isEmpty()) {
        return;
    }
    QFontMetrics fm(m_font);
    QSize size(fm.boundingRect(QRect(), 0, m_text).size());
    m_backupArea.setSize(size);
    if (recordUndo) {
        m_pixmapBackup = pixmap.copy(m_backupArea + QMargins(0, 0, 5, 5));
    }
    // draw text
    painter.setFont(m_font);
    painter.setPen(m_color);
    painter.drawText(m_backupArea + QMargins(-5, -5, 5, 5), m_text);
}

void TextTool::paintMousePreview(QPainter &painter, const CaptureContext &context) {
    Q_UNUSED(painter);
    Q_UNUSED(context);
}

void TextTool::drawEnd(const QPoint &p) {
    m_backupArea.moveTo(p);
}

void TextTool::drawMove(const QPoint &p) {
    m_widget->move(p);
}

void TextTool::drawStart(const CaptureContext &context) {
    m_color = context.color;
    m_size = context.thickness;
    emit requestAction(REQ_ADD_CHILD_WIDGET);
}

void TextTool::pressed(const CaptureContext &context) {
    Q_UNUSED(context);
}

void TextTool::colorChanged(const QColor &c) {
    m_color = c;
    if (m_widget) {
        m_widget->setTextColor(c);
    }
}

void TextTool::thicknessChanged(const int th) {
    m_size = th;
    m_font.setPointSize(m_size + BASE_POINT_SIZE);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}

void TextTool::updateText(const QString &s) {
    m_text = s;
}

void TextTool::setFont(const QFont &f) {
    m_font = f;
    if (m_widget) {
        m_widget->setFont(f);
    }
}

void TextTool::updateFamily(const QString &s) {
    m_font.setFamily(s);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}

void TextTool::updateFontUnderline(const bool underlined) {
    m_font.setUnderline(underlined);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}

void TextTool::updateFontStrikeOut(const bool s) {
    m_font.setStrikeOut(s);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}

void TextTool::updateFontWeight(const QFont::Weight w) {
    m_font.setWeight(w);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}

void TextTool::updateFontItalic(const bool italic) {
    m_font.setItalic(italic);
    if (m_widget) {
        m_widget->setFont(m_font);
    }
}
