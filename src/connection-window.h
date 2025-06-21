#ifndef CONNECTION_WINDOW_H
#define CONNECTION_WINDOW_H

/**
 * \file connection-window.h
 * \brief Source header file for the ConnectionWindow class.
 */

#include <cstdint>
#include <QDialog>
#ifdef WIN_BUILD
#include <winsock2.h>
#endif

namespace Ui {
class ConnectionWindow;
}

/**
 * \class ConnectionWindow
 * \brief Implements a GUI window presenting information and controls for managing the
 *        connection with a peer.
 */
class ConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    explicit ConnectionWindow(QWidget *parent = nullptr);
    /**
     * Destructor.
     */
    ~ConnectionWindow();

    enum class connectionStatus_t {NOT_CONNECTED,
                                   WAITING,
                                   CONNECTED};

    /**
     * Updates the connection status widget based on the value parameter.
     * \param value The new connection status to display to the user.
     */
    void setConnectionStatus(connectionStatus_t value);
    /**
     * Enables or disables the role (client/server) buttons to be used to allow or deny the
     * user the ability to change role depending on the the current connection status.
     * \param enabled The new state of the role buttons.
     */
    void setRoleButtonsEnabled(bool enabled = true);
    /**
     * Obtains the port value of the connected peer if any.
     * \return The port value.
     */
    uint16_t getPortValue();
    /**
     * Updates the text of the "startButton" button.
     * /param pText The text to be displayed on "startButton".
     */
    void setStartButtonText(const char *pText);
    /**
     * Triggers signal that window widgets should be updated to reflect a change in the
     * connection status.  Affected widgets include: the peer address text, the connection
     * status, the role buttons, etc.
     * \param connected The new status of the peer connection.
     */
    void updateConnectionInfo(bool connected);
#ifdef WIN_BUILD
    /**
     * Callback function to be invoked when the listening socket has accepted a connection
     * while running in the server role.
     * \param sock The SOCKET representing the accepted connection.
     */
    static void acceptCallback(SOCKET sock);
#else
    /**
     * Callback function to be invoked when the listening socket has accepted a connection
     * while running in the server role.
     * \param sock The socket file descriptor representing the accepted connection.
     */
    static void acceptCallback(int sock);
#endif

signals:
    /**
     * Qt signal used to indicate that connection status has changed.
     * \param The new status of the peer connection.
     */
    void updateConnectionInfoSignal(bool connected);

public slots:
    /**
     * Qt handler for handling of "clientButton" clicking.
     */
    void handleClientButton();
    /**
     * Qt handler for handling of "serverButton" clicking.
     */
    void handleServerButton();
    /**
     * Qt handler for handling of "startButton" toggling.
     * \param depressed The new toggle state of the button.  true=checked,
     *        false=not checked.
     */
    void handleStartButton(bool depressed);
    /**
     * Qt handler for handling the updateConnectionInfoSignal signal.
     * \param connected The new status of the peer connection.
     */
    void handleUpdateConnectionInfoSignal(bool connected);

private:
    Ui::ConnectionWindow *ui;

    enum class role_t {CLIENT, SERVER};

    role_t role; ///< The current role (client/server) of the application.
};

#endif // CONNECTION_WINDOW_H
