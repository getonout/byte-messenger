#ifndef MESSAGE_WINDOW_H
#define MESSAGE_WINDOW_H

#include <cstdint>
#include <cstring>
#include <QDialog>
#include <vector>

#include "message.h"

namespace Ui {
class MessageWindow;
}

class MessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MessageWindow(QWidget *parent = nullptr);
    ~MessageWindow();

    void setMessageId(uint32_t value);
    uint32_t getMessageId();
    void setName(std::string value);
    std::string getName();
    void setData(const std::vector<uint8_t> &data);
    std::vector<uint8_t> getData();
    void enableSendButton(bool enable = true);

public slots:
    void handleLoadButton();
    void handleSaveButton();
    void handleSendButton();
    void handleAddButton();

private:
    Ui::MessageWindow *ui;

    Message message;
};

#endif // MESSAGE_WINDOW_H
