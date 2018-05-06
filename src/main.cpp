/** ICP Project 2017/2018: BlockEditor
 * @file main.cpp
 * @brief Application execution point
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#include "gui/blockeditor.h"
#include <QApplication>

#include "gui/graph_ui.h"

int main(int argc, char *argv[]) {

	QApplication app(argc, argv);

	GraphUI schema;

	BLOCKEDITOR win(schema);

	return app.exec();
}
