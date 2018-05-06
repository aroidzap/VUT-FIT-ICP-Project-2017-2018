/** ICP Project 2017/2018: BlockEditor
 * @file alert.cpp
 * @brief Creating alert windows
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
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
