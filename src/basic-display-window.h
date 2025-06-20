#ifndef BASIC_DISPLAYWINDOW_H
#define BASIC_DISPLAYWINDOW_H

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

class BasicDisplayWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BasicDisplayWindow(QWidget *parent = nullptr);
    ~BasicDisplayWindow();

    // Cannot pass the argument by reference between threads
    static void readCallback(std::vector<uint8_t> data);

    void addLine(const std::vector<uint8_t> &data, bool isRx = true, bool withTimestamp = true);
    void addNLine(const std::vector<uint8_t> &data, size_t length, bool isRx = true, bool withTimestamp = true);
    void addString(const std::string &value, bool withTimestamp = true);

signals:
    void readSignal(buffer_t data);

public slots:
    void handleReadSignal(std::vector<uint8_t> data);
    void handleCopyButton();

private:
    Ui::BasicDisplayWindow *ui;

    QListWidget *pList;
};

#endif // BASIC_DISPLAYWINDOW_H
