#ifndef ICP_GUI_H
#define ICP_GUI_H

#include <QMainWindow>

namespace Ui {
class ICP_GUI;
}

class ICP_GUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ICP_GUI(QWidget *parent = 0);
    ~ICP_GUI();

private:
    Ui::ICP_GUI *ui;
};

#endif // ICP_GUI_H
