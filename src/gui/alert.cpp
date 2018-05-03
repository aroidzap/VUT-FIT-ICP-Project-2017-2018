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
