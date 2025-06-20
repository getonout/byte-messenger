#include "connection-window.h"
#include "ui_connection-window.h"

#ifdef WIN_BUILD
#include <winsock2.h>
#else
#include <arpa/inet.h>
#endif
#include <csignal>
#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <unistd.h>

#include "object-manager.h"
#include "socket-routines.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);

    role = role_t::CLIENT;

    QObject::connect(this, &ConnectionWindow::updateConnectionInfoSignal,
                     this, &ConnectionWindow::handleUpdateConnectionInfoSignal);
    setConnectionStatus(connectionStatus_t::NOT_CONNECTED);
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::handleClientButton()
{
    role = role_t::CLIENT;
    this->findChild<QLineEdit *>("peerAddressEdit")->setEnabled(true);
    this->findChild<QPushButton *>("startButton")->setText("Connect");
}

void ConnectionWindow::handleServerButton()
{
    role = role_t::SERVER;
    this->findChild<QLineEdit *>("peerAddressEdit")->setEnabled(false);
    this->findChild<QPushButton *>("startButton")->setText("Start");
}

void ConnectionWindow::handleStartButton(bool depressed)
{
    QPushButton *pStartButton = this->findChild<QPushButton *>("startButton");

    if (depressed) // Connect or Start Server
    {
        setRoleButtonsEnabled(false);

        if (role == role_t::CLIENT) // Client role
        {
#ifdef WIN_BUILD
            SOCKET sock;
            int result = tcp::connectClient(this->findChild<QLineEdit *>("peerAddressEdit")->text().toUtf8().constData(),
                                            this->findChild<QLineEdit *>("portEdit")->text().toUShort(), sock);
#else
            int result = tcp::connectClient(this->findChild<QLineEdit *>("peerAddressEdit")->text().toUtf8().constData(),
                                            this->findChild<QLineEdit *>("portEdit")->text().toUShort());
#endif

            if (result < 0) // Error
            {
                std::cerr << "ConnectionWindow::handleStartButton(): Error executing tcp::connectClient()" << std::endl;
                if (result == tcp::CONNECT_SOCKET_ERROR)
                {
                    std::cerr << "  result=CONNECT_SOCKET_ERROR" << std::endl;
                }
                else if (result == tcp::CONNECT_ADDRESS_ERROR)
                {
                    std::cerr << "  result=CONNECT_ADDRESS_ERROR" << std::endl;
                }
                else if (result == tcp::CONNECT_CONNECT_ERROR)
                {
                    std::cerr << "  result=CONNECT_CONNECT_ERROR" << std::endl;
                }

                updateConnectionInfo(false);
            }
            else // Connected
            {
#ifdef WIN_BUILD
                ObjectManager::setPeerSocket(sock);
#else
                ObjectManager::setPeerSocket(result);
#endif
                updateConnectionInfo(true);

                tcp::startReadLoop(BasicDisplayWindow::readCallback);
            }
        }
        else // Server role
        {
            setConnectionStatus(connectionStatus_t::WAITING);
            tcp::startAcceptThread(ConnectionWindow::acceptCallback);
            pStartButton->setText("Stop");
        }
    }
    else // Disconnect or Stop Server
    {
        if (role == role_t::CLIENT) // Client role
        {
            pthread_kill(ObjectManager::getReadThread(), SIGTERM);
#ifdef WIN_BUILD
            closesocket(ObjectManager::getPeerSocket());
#else
            ::close(ObjectManager::getPeerSocket());
#endif
        }
        else // Server role
        {
            pthread_kill(ObjectManager::getReadThread(), SIGTERM);
            pthread_kill(ObjectManager::getAcceptThread(), SIGTERM);
#ifdef WIN_BUILD
            closesocket(ObjectManager::getPeerSocket());
            closesocket(ObjectManager::getListenSocket());
#else
            ::close(ObjectManager::getPeerSocket());
            ::close(ObjectManager::getListenSocket());
#endif
        }
        updateConnectionInfo(false);
    }
}

void ConnectionWindow::handleUpdateConnectionInfoSignal(bool connected)
{
    QPushButton *pStartButton = this->findChild<QPushButton *>("startButton");

    if (connected)
    {
        ObjectManager::setConnectionStatus(true);
        sockaddr_in *pPeerAddress = ObjectManager::getPeerAddress();
        this->findChild<QLineEdit *>("peerAddressEdit")->setText(inet_ntoa(pPeerAddress->sin_addr));
        ObjectManager::getConnectionWindow()->setConnectionStatus(connectionStatus_t::CONNECTED);
        setRoleButtonsEnabled(false);
        ObjectManager::getMessageWindow()->enableSendButton(true);
        // Start button action is Disconnect for both client and server role
        pStartButton->setText("Disconnect");
    }
    else
    {
        ObjectManager::setConnectionStatus(false);
        ObjectManager::getConnectionWindow()->setConnectionStatus(connectionStatus_t::NOT_CONNECTED);
        setRoleButtonsEnabled(true);
        ObjectManager::getMessageWindow()->enableSendButton(false);
        if (role == role_t::CLIENT) // Client role
        {
            pStartButton->setText("Connect");
        }
        else // Server role
        {
            pStartButton->setText("Start");
        }

        // Set Start button to allow for depressing again
        pStartButton->blockSignals(true);
        pStartButton->setChecked(false);
        pStartButton->blockSignals(false);
    }
}

void ConnectionWindow::setConnectionStatus(connectionStatus_t value)
{
    QLineEdit *pWidget = this->findChild<QLineEdit *>("statusEdit");

    switch (value)
    {
    case connectionStatus_t::NOT_CONNECTED:
        pWidget->setText("NOT CONNECTED");
        break;
    case connectionStatus_t::WAITING:
        pWidget->setText("WAITING");
        break;
    case connectionStatus_t::CONNECTED:
        pWidget->setText("CONNECTED");
        break;
    }
}

void ConnectionWindow::setRoleButtonsEnabled(bool enabled)
{
    this->findChild<QRadioButton *>("clientButton")->setEnabled(enabled);
    this->findChild<QRadioButton *>("serverButton")->setEnabled(enabled);
}

uint16_t ConnectionWindow::getPortValue()
{
    return static_cast<uint16_t>(std::stoi(this->findChild<QLineEdit *>("portEdit")->text().toStdString()));
}

void ConnectionWindow::setStartButtonText(const char *pText)
{
    this->findChild<QPushButton *>("startButton")->setText(pText);
}

void ConnectionWindow::updateConnectionInfo(bool connected)
{
    emit updateConnectionInfoSignal(connected);
}

#ifdef WIN_BUILD
void ConnectionWindow::acceptCallback(SOCKET sock)
{
    if (sock == INVALID_SOCKET)
    {
        ObjectManager::getConnectionWindow()->updateConnectionInfo(false);
    }
    else
    {
        ObjectManager::getConnectionWindow()->updateConnectionInfo(true);

        // Only handling 1 connection.  Close listening socket.
        closesocket(ObjectManager::getListenSocket());

        // Start Read Loop
        tcp::startReadLoop(BasicDisplayWindow::readCallback);
    }
}
#else
void ConnectionWindow::acceptCallback(int sock)
{
    if (sock == -1)
    {
        ObjectManager::getConnectionWindow()->updateConnectionInfo(false);
    }
    else
    {
        ObjectManager::getConnectionWindow()->updateConnectionInfo(true);

        // Only handling 1 connection.  Close listening socket.
        ::close(ObjectManager::getListenSocket());

        // Start Read Loop
        tcp::startReadLoop(BasicDisplayWindow::readCallback);
    }
}
#endif
