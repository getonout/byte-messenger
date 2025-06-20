#ifndef MESSAGE_LIST_WINDOW_H
#define MESSAGE_LIST_WINDOW_H

#include <QDialog>
#include <QListWidget>

#include "message.h"
#include "message-list.h"

namespace Ui {
class MessageListWindow;
}

class MessageListWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageListWindow(QWidget *parent = nullptr);
    ~MessageListWindow();
    void initialize();
    void addMessage(Message &message);

public slots:
    void handleLoadButton();
    void handleSaveButton();
    void handleOpenButton();

private:
    Ui::MessageListWindow *ui;

    MessageList messageList;
    QListWidget *pList;

    void addMessageToList(Message &message);
    void clearMessageList();
};

#endif // MESSAGE_LIST_WINDOW_H
