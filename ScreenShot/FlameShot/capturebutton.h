
#pragma once

#include <QPushButton>
#include <QMap>
#include <QVector>

class QWidget;
class QPropertyAnimation;
class CaptureTool;

class CaptureButton : public QPushButton {
    Q_OBJECT

public:
    // Don't forget to add the new types to CaptureButton::iterableButtonTypes
    // in the .cpp and the order value in the private array buttonTypeOrder
    enum ButtonType {
        TYPE_PENCIL = 0,
        TYPE_DRAWER = 1,
        TYPE_ARROW = 2,
        TYPE_SELECTION = 3,
        TYPE_RECTANGLE = 4,
        TYPE_CIRCLE = 5,
        TYPE_MARKER = 6,
        TYPE_SELECTIONINDICATOR = 7,
        TYPE_MOVESELECTION = 8,
        TYPE_UNDO = 9,
        TYPE_COPY = 10,
        TYPE_SAVE = 11,
        TYPE_EXIT = 12,
        TYPE_BLUR = 15,
        TYPE_REDO = 16,
        TYPE_PIN = 17,
        TYPE_TEXT = 18,
    };

#if QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
    Q_ENUMS(ButtonType)
#else
    Q_ENUM(ButtonType)
#endif

    CaptureButton() = delete;
    explicit CaptureButton(const ButtonType, QWidget *parent = nullptr);

    static QString globalStyleSheet();
    static QVector<CaptureButton::ButtonType> getIterableButtonTypes();
    static int getPriorityByButton(CaptureButton::ButtonType);

    QString name() const;
    QString description() const;
    QIcon icon() const;
    QString styleSheet() const;
    CaptureTool* tool() const;

    void setColor(const QColor &c);
    void animatedShow();
    ButtonType buttonType() const;

protected:
    virtual void mousePressEvent(QMouseEvent *);
    static QVector<ButtonType> iterableButtonTypes;

    CaptureTool *m_tool;

signals:
    void pressedButton(CaptureButton *);

private:
    CaptureButton(QWidget *parent = nullptr);
    ButtonType m_buttonType;

    QPropertyAnimation *m_emergeAnimation;

    static QColor m_mainColor;

    void initButton();
    void updateIcon();
};
