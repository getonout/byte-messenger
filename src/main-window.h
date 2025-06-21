#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * \file main-window.h
 * \brief Source header file for the MainWindow class.
 */

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * \class MainWindow
 * \brief Implements a GUI window which provides the user with controls to access all of the
 *        application windows.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * Destructor.
     */
    ~MainWindow();

public slots:
    /**
     * Qt handler for handling of "basicDisplayButton" clicking.
     */
    void handleBasicDisplayButton();
    /**
     * Qt handler for handling of "connectionButton" clicking.
     */
    void handleConnectionButton();
    /**
     * Qt handler for handling of "messageButton" clicking.
     */
    void handleMessageButton();
    /**
     * Qt handler for handling of "messageListButton" clicking.
     */
    void handleMessageListButton();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
