

#include "notifierbox.h"
#include "confighandler.h"
#include "globalvalues.h"
#include <QTimer>
#include <QPainter>
#include <QApplication>

NotifierBox::NotifierBox(QWidget *parent) : QWidget(parent) {
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    m_timer->setInterval(1200);
    connect(m_timer, &QTimer::timeout, this, &NotifierBox::hide);
    m_bgColor = ConfigHandler().uiMainColorValue();
    m_foregroundColor = (ColorUtils::colorIsDark(m_bgColor) ?
                             Qt::white : Qt::black);
    m_bgColor.setAlpha(180);
    const int size = (GlobalValues::buttonBaseSize() +
                      GlobalValues::buttonBaseSize()/2) *
            qApp->devicePixelRatio();
    setFixedSize(QSize(size, size));
}

void NotifierBox::enterEvent(QEvent *) {
    hide();
}

void NotifierBox::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    // draw Elipse
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(m_bgColor, Qt::SolidPattern));
    painter.setPen(QPen(Qt::transparent));
    painter.drawEllipse(rect());
    // Draw the text:
    painter.setPen(QPen(m_foregroundColor));
    painter.drawText(rect(), Qt::AlignCenter, m_message);
}

void NotifierBox::showMessage(const QString &msg) {
    m_message = msg;
    update();
    show();
    m_timer->start();
}

void NotifierBox::showColor(const QColor &color) {
    Q_UNUSED(color);
    m_message = QLatin1String("");
}