#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <QObject>
namespace  FlockSimulator {
class MessageSender : public QObject{
    Q_OBJECT
public:
    MessageSender();

signals:
    void error(QString);
    void message(QString);

public slots:
    virtual void sendMessage(QString msg);
    virtual void sendError(QString msg);
};
}
#endif // MESSAGESENDER_H
