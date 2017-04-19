#include "MessageSender.h"

FlockSimulator::MessageSender::MessageSender()
{
}

void FlockSimulator::MessageSender::sendMessage(QString msg)
{
    emit message(msg);
}

void FlockSimulator::MessageSender::sendError(QString msg)
{
    emit error(msg);
}

