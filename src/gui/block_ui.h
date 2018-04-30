#ifndef BLOCK_UI_H
#define BLOCK_UI_H

#include <QPaintEvent>
#include <QWidget>
#include <list>

#include "../core/blockbase.h"
#include "port_ui.h"

class BlockUI : public QWidget, public BlockBase
{
private:
	QLabel label;
	bool drag = false;
	bool highlight = false;
	QPoint drag_p;
	int height;
	int width;
public:
	explicit BlockUI(const BlockBase &b, QWidget *parent = nullptr);
	void Move(int x, int y);
	void Highlight(bool enable);

protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // BLOCK_UI_H
