/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: blockeditor.h
*/

#ifndef BLOCKEDITOR_H
#define BLOCKEDITOR_H

#include <QMainWindow>

namespace Ui {
class BLOCKEDITOR;
}

class BLOCKEDITOR : public QMainWindow
{
    Q_OBJECT

public:
	explicit BLOCKEDITOR(QWidget *parent = 0);
	~BLOCKEDITOR();

private:
	Ui::BLOCKEDITOR *ui;
};

#endif // BLOCKEDITOR_H
