#ifndef PORT_H
#define PORT_H

#include <QPaintEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QLabel>
#include <string>

class Port : public QWidget
{
	Q_OBJECT
private:
	bool input;
	bool hover = false;
	QLabel label;
public:
	void Move(int x, int y);
	explicit Port(std::string name, bool input, QWidget *parent = nullptr);

	int getWidth() const;
protected:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void leaveEvent(QEvent *event) override;
};

#endif // PORT_H
