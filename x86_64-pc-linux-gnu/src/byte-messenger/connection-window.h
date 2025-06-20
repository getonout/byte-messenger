#ifndef CONNECTION_WINDOW_H
#define CONNECTION_WINDOW_H

#include <QDialog>

#include <cstdint>

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionWindow(QWidget *parent = nullptr);
    ~ConnectionWindow();

    enum class connectionStatus_t {NOT_CONNECTED,
                                   WAITING,
                                   CONNECTED};

    void setConnectionStatus(connectionStatus_t value);
    void setRoleButtonsEnabled(bool enabled = true);
    uint16_t getPortValue();
    void setStartButtonText(const char *pText);
    void updateConnectionInfo(bool connected);
    static void acceptCallback(int sock);

signals:
    void updateConnectionInfoSignal(bool connected);

public slots:
    void handleClientButton();
    void handleServerButton();
    void handleStartButton(bool depressed);
    void handleUpdateConnectionInfoSignal(bool connected);

private:
    Ui::ConnectionWindow *ui;

    enum class role_t {CLIENT, SERVER};

    role_t role;
};

#endif // CONNECTION_WINDOW_H
