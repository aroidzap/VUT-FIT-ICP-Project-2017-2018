#include "icp_gui.h"

ICP_GUI::ICP_GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ICP_GUI)
{
	ui->setupUi(this);
}

ICP_GUI::~ICP_GUI()
{
    delete ui;
}
