#ifndef BLOCK_UI_H
#define BLOCK_UI_H

#include <QPaintEvent>
#include <QWidget>
#include <list>

#include "port_ui.h"

class BlockUI : public QWidget
{
	Q_OBJECT
private:
	QLabel name;
	std::list<Port*> inputs;
	std::list<Port*> outputs;
	bool drag = false;
	QPoint drag_p;
	int height;
	int width;
public:
	explicit BlockUI(std::string name, QPoint position = QPoint(0, 0), QWidget *parent = nullptr);
	~BlockUI();
	void Move(int x, int y);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BLOCK_UI_H
