#include "EditorModeMachine.hpp"

EditorModeMachine::EditorModeMachine(QObject * parent)
{

}

void EditorModeMachine::setMode(EditorModeMachine::Mode mode)
{
    m_mode = mode;
}

EditorModeMachine::Mode EditorModeMachine::mode() const
{
    return m_mode;
}
