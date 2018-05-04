/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: main.cpp
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
