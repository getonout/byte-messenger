#ifndef BASIC_DISPLAYWINDOW_H
#define BASIC_DISPLAYWINDOW_H

/**
 * \file basic-display-window.h
 * \brief Source header file for the BasicDisplayWindow class.
 */

#include <cstdint>
#include <QDialog>
#include <QListWidget>
#include <sys/types.h>
#include <vector>

namespace Ui {
class BasicDisplayWindow;
}

typedef std::vector<uint8_t> buffer_t;

Q_DECLARE_METATYPE(buffer_t)

/**
 * \class BasicDisplayWindow
 * \brief Implements a GUI window for displaying transmitted or received message data.
 */
class BasicDisplayWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    explicit BasicDisplayWindow(QWidget *parent = nullptr);
    /**
     * Destructor.
     */
    ~BasicDisplayWindow();

    /**
     * Callback function to be used by a reading thread to signal that data was read from
     * the peer.
     * \param data Vector of binary data that was read from the peer.
     */
    static void readCallback(std::vector<uint8_t> data);

    /**
     * Adds a line of text to the display window representing the data parameter.
     * \param data Vector of the binary data to display in the window.
     * \param isRx Indicates in which direction the data travelled.  true=peer-to-app
     *        (receiving), false=app-to-peer (transmitting).
     * \param withTimestamp Indicates whether a timestamp should be included with the
     *        displayed message text.
     */
    void addLine(const std::vector<uint8_t> &data, bool isRx = true, bool withTimestamp = true);
    
    /**
     * Adds a line of text to the display window representing the data parameter.
     * \param data Vector of the binary data to display in the window.
     * \param length The number of bytes of data in the data parameter.
     * \param isRx Indicates in which direction the data travelled.  true=peer-to-app
     *        (receiving), false=app-to-peer (transmitting).
     * \param withTimestamp Indicates whether a timestamp should be included with the
     *        displayed message text.
     */
    void addNLine(const std::vector<uint8_t> &data, size_t length, bool isRx = true, bool withTimestamp = true);
    
    /**
     * Adds a string of text to the display window.
     * \param value The string of text to display.
     * \param withTimestamp Indicates whether a timestamp should be included with the
     *        displayed text.
     */
    void addString(const std::string &value, bool withTimestamp = true);

signals:
    /**
     * Qt signal definition for passing data read from the peer.
     * \param data The binary data that was read from the peer.
     */
    void readSignal(buffer_t data);

public slots:
    /**
     * Qt signal handler for the readSignal signal.
     * \param data The binary data that was read from the peer.
     */
    void handleReadSignal(std::vector<uint8_t> data);
    /**
     * Qt signal handler for handling of "copyButton" clicking.
     */
    void handleCopyButton();

private:
    Ui::BasicDisplayWindow *ui;

    QListWidget *pList; ///< Holds the list of text lines to be displayed in the window.
};

#endif // BASIC_DISPLAYWINDOW_H
