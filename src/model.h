#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "utils.h"
#include "knot.h"

#include "glRender.h"

using namespace glRender;

class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject *parent = 0);
    void addKnot(Vec3 pos);
    void removeKnot(uint knotIndex);
    void moveKnot(uint knotIndex, Vec3 pos);
    void setKnotParam(uint knotIndex, Knot::Param param, float value);
    void selectKnot(uint knotIndex);
    void deselectKnot();
    Knot * getKnot(uint knotIndex);
    uint getSelectedKnotIndex();

signals:
    void knotAdded(uint index);
    void knotRemoved(uint index);
    void knotPositionChange(uint index, Vec3 oldPos, Vec3 newPos);
    void knotParamChange(uint index, Knot::Param param, float oldVale, float newValue);
    void knotSelected(uint knotIndex);

public slots:

private:
    uint m_data = 0;
};

#endif // MODEL_H
