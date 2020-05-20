

#pragma once

#include <QWidget>

class QTimer;

class NotifierBox : public QWidget {
    Q_OBJECT
public:
    explicit NotifierBox(QWidget *parent = nullptr);

protected:
    virtual void enterEvent(QEvent *);
    virtual void paintEvent(QPaintEvent *);

public slots:
    void showMessage(const QString &msg);
    void showColor(const QColor &color);

private:
    QTimer *m_timer;
    QString m_message;
    QColor m_bgColor;
    QColor m_foregroundColor;
};
