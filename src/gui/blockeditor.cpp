/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: blockeditor.cpp
*/

/**
 * @file blockeditor.cpp
 * @brief UI Class for main window
 * @details Class contains code generated by Qt Designer (actual code is generated during compilation)
 *          and some handwritten code for other actions
 * @author Tomáš Pazdiora
 * @author Michal Pospíšil
 */
#include <QtWidgets>
#include <QString>

#include "blockeditor.h"
#include "ui_blockeditor.h"
#include "graph_ui.h"

BLOCKEDITOR::BLOCKEDITOR(GraphUI &g, QWidget *parent) :
	QMainWindow(parent),  ui(new Ui::BLOCKEDITOR), graph(g)
{
	ui->setupUi(this);

	QApplication::setApplicationDisplayName("BLOCKEDITOR");

	createActions();
	createMenus();
	createToolBars();
	setCurrentFile("");
	setUnifiedTitleAndToolBarOnMac(true);

	setCentralWidget(&graph);
	show();

	connect(graphName, SIGNAL(textChanged(const QString &)), this,
		SLOT(graphNameChange(const QString &))
	);

	graph.onGraphChange([this](){this->setWindowModified(true);});
}

BLOCKEDITOR::~BLOCKEDITOR()
{
	//avoid destruction of graph, which is destructed externally
	centralWidget()->setParent(nullptr);

	deleteToolBars();
	deleteActions();
	delete ui;
}

void BLOCKEDITOR::deleteActions()
{
	delete openAct;
	delete mergeAct;
	delete saveAct;
	delete saveAsAct;
	delete computeAct;
	delete stepAct;
	delete resetAct;
	delete aboutAct;
	delete helpAct;
	delete exitAct;
}

void BLOCKEDITOR::createActions()
{
	openAct = new QAction(QIcon(":/icons/open.png"), "&Open...", this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip("Open an existing file");
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	mergeAct = new QAction("&Merge", this);
	mergeAct->setStatusTip("Merge file into currently opened scheme");
	connect(mergeAct, SIGNAL(triggered()), this, SLOT(merge()));


	saveAct = new QAction(QIcon(":/icons/save.png"), "&Save", this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip("Save the document to disk");
	connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAct = new QAction("Save &As...", this);
	saveAsAct->setShortcuts(QKeySequence::SaveAs);
	saveAsAct->setStatusTip("Save the document with a new name");
	connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

	computeAct = new QAction(QIcon(":/icons/compute.png"), "&Compute (F3)", this);
	computeAct->setShortcut(QKeySequence::fromString("F3", QKeySequence::NativeText));
	computeAct->setStatusTip("Computes the whole scheme");
	connect(computeAct, SIGNAL(triggered()), this, SLOT(compute()));

	stepAct = new QAction(QIcon(":/icons/step.png"), "&Step (F4)", this);
	stepAct->setShortcut(QKeySequence::fromString("F4", QKeySequence::NativeText));
	stepAct->setStatusTip("Steps through the computation");
	connect(stepAct, SIGNAL(triggered()), this, SLOT(step()));

	resetAct = new QAction(QIcon(":/icons/reset.png"), "&Reset (F5)", this);
	resetAct->setShortcut(QKeySequence::fromString("F5", QKeySequence::NativeText));
	resetAct->setStatusTip("Marks first block as next to compute");
	connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

	aboutAct = new QAction(QIcon(":/icons/about.png"), "&About", this);
	aboutAct->setStatusTip("Show the application's about box");
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));


	helpAct = new QAction(QIcon(":/icons/help.png"), "&Help", this);
	helpAct->setStatusTip("Show the application's help");
	helpAct->setShortcuts(QKeySequence::HelpContents);
	connect(helpAct, SIGNAL(triggered()), this, SLOT(help()));

	exitAct = new QAction(QIcon(":/icons/exit.png"), "E&xit", this);
	exitAct->setStatusTip("Close the application");
	exitAct->setShortcuts(QKeySequence::Quit);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
}

void BLOCKEDITOR::createMenus()
{
	fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(openAct);
	fileMenu->addAction(mergeAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	helpMenu = menuBar()->addMenu("&Help");
	helpMenu->addAction(aboutAct);
	helpMenu->addSeparator();
	helpMenu->addAction(helpAct);
}

void BLOCKEDITOR::deleteToolBars()
{
	delete graphName;
	delete graphNameHint;
	delete spacerWidget;
}

void BLOCKEDITOR::createToolBars()
{
	fileToolBar = addToolBar("File");
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);

	actionToolBar = addToolBar("Actions");
	actionToolBar->addAction(computeAct);
	actionToolBar->addAction(stepAct);
	actionToolBar->addAction(resetAct);

	helpToolBar = addToolBar("Help");
	helpToolBar->addAction(helpAct);


	spacerWidget = new QWidget();
	spacerWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

	graphNameHint = new QLabel("Scheme name: ");

	graphName = new QLineEdit();
	graphName->setMaximumWidth(200);

	nameToolBar = addToolBar("Graph Name");
	nameToolBar->addWidget(spacerWidget);
	nameToolBar->addWidget(graphNameHint);
	nameToolBar->addWidget(graphName);
}

void BLOCKEDITOR::closeEvent(QCloseEvent *event)
{
	if (maybeSave()) {
		event->accept();
	} else {
		event->ignore();
	}
}

void BLOCKEDITOR::open()
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this,
			QString(), QString(), QString("BLOCKEDITOR Files (*.gph)"));
		if (!fileName.isEmpty())
			loadFile(fileName, false);
	}
}

void BLOCKEDITOR::merge()
{

	QString fileName = QFileDialog::getOpenFileName(this,
		QString("Merge"), QString(), QString("BLOCKEDITOR Files (*.gph)"));
	if (!fileName.isEmpty())
		loadFile(fileName, true);

}

bool BLOCKEDITOR::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	} else {
		return saveFile(curFile);
	}
}

bool BLOCKEDITOR::saveAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setNameFilter("BLOCKEDITOR Files (*.gph)");
	std::string saveName;
	if (curFile.isEmpty()) {
		if (graph.GetName().empty()){
			saveName = "untitled.gph";
		} else {
			saveName = graph.GetName() + ".gph";
		}
	} else {
		saveName = curFile.toStdString();
	}
	dialog.selectFile(saveName.c_str());
	QStringList files;
	if (dialog.exec())
		files = dialog.selectedFiles();
	else
		return false;

	return saveFile(files.at(0));
}

void BLOCKEDITOR::compute() {
	graph.computeAll();
}

void BLOCKEDITOR::step() {
	graph.computeStep();
}

void BLOCKEDITOR::reset() {
	graph.computeReset();
}

void BLOCKEDITOR::about()
{
	QMessageBox::about(this, "About Block Editor",
							 "<h1>Block Editor</h1>"
							 "<h2>ICP Project 2017/2018</h2>"
							 "<p><b>Authors:</b> Tomáš Pazdiora, Michal Pospíšil</p>");
}

void BLOCKEDITOR::graphNameChange(const QString &name)
{
	graph.SetName(name.toStdString());
}

void BLOCKEDITOR::help()
{
	QMessageBox::about(this, "Help",
							 "<h1>Block Editor Help</h1>"
							 "<h2>Blocks</h2>"
							 "<p><b>Creating blocks: </b>Right-click and select the desired type.</p>"
							 "<p><b>Deleting blocks: </b>Right-click on block and select 'Delete'.</p>"
							 "<h2>Connections</h2>"
							 "<p><b>Creating connections: </b>Click on one port, then on other to make connection. Click elsewhere to discard connection.</p>"
							 "<p><b>Detaching connection: </b>Click on input port to detach connection. Click elsewhere to discard connection or click on any input port to reconnect.</p>"
					   );

}

bool BLOCKEDITOR::maybeSave()
{
	if(this->isWindowModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, "BLOCKEDITOR",
										 "The document has been modified.\n"
										 "Do you want to save your changes?",
					 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return save();
		}
		else {
			if (ret == QMessageBox::Cancel) {
			return false;
			}
		}
	}
	return true;

}

void BLOCKEDITOR::loadFile(const QString &fileName, bool merge)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, "BLOCKEDITOR",
								   QString::fromStdString("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return;
	}

	QTextStream in(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	// FILE LOADING
	std::stringstream funcIn;
	while(!in.atEnd()){
		funcIn << in.read(1024).toStdString() << '\n';
	}

	if(!graph.loadGraph(funcIn, merge)) {
		QMessageBox::warning(this, "BLOCKEDITOR",
								   QString::fromStdString("Error while reading the file."));
	}
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	graphName->setText(QString::fromStdString(graph.GetName()));
	statusBar()->showMessage("File loaded", 2000);

	if(!merge){
		setCurrentFile(fileName);
		setWindowModified(false);
	}
}


bool BLOCKEDITOR::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, "Application",
							 QString::fromStdString("Cannot write file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	// FILE SAVING
	std::stringstream funcOut;
	funcOut = graph.saveGraph();

	while(funcOut.good()) {
		std::string str;
		std::getline(funcOut, str);
		out << QString::fromStdString(str) << '\n';
	}
	if(funcOut.fail()) {
		QMessageBox::warning(this, "BLOCKEDITOR",
								   QString::fromStdString("Error while writing the file."));
	}
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage("File saved", 2000);
	return true;
}

void BLOCKEDITOR::setCurrentFile(const QString &fileName)
{
	curFile = fileName;

	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty()) {
		shownName = "untitled.gph";
	}

	setWindowFilePath(shownName);
}
