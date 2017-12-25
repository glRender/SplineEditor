#include "model.h"

DataModel::DataModel(QObject *parent) : QObject(parent)
{

}

void DataModel::addKnot(Vec3 pos)
{

}

void DataModel::removeKnot(uint knotIndex)
{

}

void DataModel::moveKnot(uint knotIndex, Vec3 pos)
{

}

void DataModel::setKnotParam(uint knotIndex, Knot::Param param, float value)
{

}

void DataModel::selectKnot(uint knotIndex)
{

}

void DataModel::deselectKnot()
{

}

Knot * DataModel::getKnot(uint knotIndex)
{
    return nullptr;

}

uint DataModel::getSelectedKnotIndex()
{
    return -1;
}

