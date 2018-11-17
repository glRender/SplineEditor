#include "ViewEditorMode.h"
#include "ui_ViewEditorMode.h"

ViewEditorMode::ViewEditorMode(QWidget * parent)
    : QWidget(parent)
    , ui(new Ui::ViewEditorMode)
{
    ui->setupUi(this);
}

ViewEditorMode::~ViewEditorMode()
{
    delete ui;
}
