#pragma once

#include <QObject>

class EditorModeMachine : public QObject
{
    Q_OBJECT
public:
    enum class Mode {
        No,
        Selection,
        Deletion,
        Addition,
        Moving
    };

    EditorModeMachine(QObject * parent = nullptr);

    void setMode(Mode mode);
    Mode mode() const;

signals:
    void changed();

private:
    Mode m_mode = Mode::No;
};
