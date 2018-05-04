/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: alert.cpp
*/

#include "alert.h"

#include "QMessageBox"

void ErrorAlert(std::string message)
{
	QMessageBox alert;
	alert.setWindowTitle("ERROR");
	alert.setText(message.c_str());
	alert.show();
	alert.exec();
}
