

#pragma once

#include <QWidget>

class QVBoxLayout;
class QPushButton;

class TextConfig : public QWidget {
    Q_OBJECT
public:
    explicit TextConfig(QWidget *parent = nullptr);

    void setUnderline(const bool u);
    void setStrikeOut(const bool s);
    void setWeight(const int w);
    void setItalic(const bool i);

signals:
    void fontFamilyChanged(const QString &f);
    void fontUnderlineChanged(const bool underlined);
    void fontStrikeOutChanged(const bool dashed);
    void fontWeightChanged(const QFont::Weight w);
    void fontItalicChanged(const bool italic);

public slots:

private slots:
    void weightButtonPressed(const bool w);

private:
    QVBoxLayout *m_layout;
    QPushButton *m_strikeOutButton;
    QPushButton *m_underlineButton;
    QPushButton *m_weightButton;
    QPushButton *m_italicButton;
};
