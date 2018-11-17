#ifndef VIEWEDITORMODE_H
#define VIEWEDITORMODE_H

#include <QWidget>

namespace Ui
{
class ViewEditorMode;
}

class ViewEditorMode : public QWidget
{
    Q_OBJECT

public:
    explicit ViewEditorMode(QWidget * parent = 0);
    ~ViewEditorMode();

private:
    Ui::ViewEditorMode * ui;
};

#endif // VIEWEDITORMODE_H
