#include "blockeditor.h"
#include "ui_blockeditor.h"

BLOCKEDITOR::BLOCKEDITOR(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::BLOCKEDITOR)
{
	ui->setupUi(this);
}

BLOCKEDITOR::~BLOCKEDITOR()
{
    delete ui;
}
