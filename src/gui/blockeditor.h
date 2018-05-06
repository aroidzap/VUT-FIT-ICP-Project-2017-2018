/** ICP Project 2017/2018: BlockEditor
 * @file blockeditor.h
 * @brief Block appearance
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef BLOCKEDITOR_H
#define BLOCKEDITOR_H

#include <QMainWindow>
#include "graph_ui.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLineEdit;
class QLabel;
QT_END_NAMESPACE

namespace Ui {
class BLOCKEDITOR;
}

/**
 * @brief Main window class
 * This class is a QWidget that is parent to all graphic elements within the window.
 * All other control widgets (except the dropdown menus for adding/removing blocks) are declared here.
 */
class BLOCKEDITOR : public QMainWindow
{
    Q_OBJECT
public:
	//! Constructor
	explicit BLOCKEDITOR(GraphUI &g, QWidget *parent = 0);
	//! Destructor
	~BLOCKEDITOR();

protected:
	//! Event called when closing the opened scheme
	void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
	//! Button slot to call when creating a new scheme
	void newFile();
	//! Button slot to call when opening a file
	void open();
	//! Button slot to call when merging a file into existing scheme
	void merge();
	//! Button slot to call when opening a file
	bool save();
	//! Button slot to call when saving file a new one
	bool saveAs();
	//! Button slot called when computing the whole scheme
	void compute();
	//! Button slot called when computing one block from compute queue
	void step();
	//! Button slot called to set first block as next in compute queue
	void reset();
	//! Button slot called when opening help
	void help();
	//! Button slot called when opening about box
	void about();

	//! Function called on scheme name text edit field change
	void graphNameChange(const QString & name);

private:
	Ui::BLOCKEDITOR *ui;
	GraphUI &graph;

	//! Function that destroys QActions for buttons
	void deleteActions();
	//! Function that creates QActions for buttons
    void createActions();
	//! Sets up menu bar with all buttons
    void createMenus();
	//! Destroys toolbars
	void deleteToolBars();
	//! Place buttons on toolbars
    void createToolBars();
	//! Asks user to save changes before quitting
    bool maybeSave();
	//! Creates dialogs for opening a scheme file
	void loadFile(const QString &fileName, bool merge);
	//! Creates dialogs for saving a scheme to disk
    bool saveFile(const QString &fileName);
	//! Sets current file name in window title
    void setCurrentFile(const QString &fileName);

	//! Currently edited file's name
    QString curFile;

	//! Dialog used for opening and closing files
    QMenu *fileMenu;
	//! Dialog used for help and about boxes
    QMenu *helpMenu;

	//! Toolbar with file buttons
	QToolBar *fileToolBar;
	//! Toolbar with buttons related to computing blocks
    QToolBar *actionToolBar;
	//! Toolbar with a help button
    QToolBar *helpToolBar;
	//! Toolbar with a name of currently edited scheme
	QToolBar *nameToolBar;

	//! Widget that right-aligns the scheme name
	QWidget *spacerWidget;

	//! Widget that captions scheme name text edit with scheme name (graphName)
	QLabel *graphNameHint;

	//! Text edit where user can see and change name of the scheme
	QLineEdit *graphName;

	//! Action for creating a new file
	QAction *newAct;
	//! Action for opening a file
	QAction *openAct;
	//! Action for merging a file into the currently edited scheme
	QAction *mergeAct;
	//! Action for saving a file
    QAction *saveAct;
	//! Action for saving file as a new one
    QAction *saveAsAct;
	//! Action for closing the BlockEditor
    QAction *exitAct;
	//! Action for computing the whole scheme
    QAction *computeAct;
	//! Action for computing next block in the compute queue
    QAction *stepAct;
	//! Action that sets the first block as next in compute queue
    QAction *resetAct;
	//! Action for deleting a block
	QAction *deleteAct;
	//! Action for showing the help box
    QAction *helpAct;
	//! Action for calling the about box
    QAction *aboutAct;

};

#endif // BLOCKEDITOR_H
