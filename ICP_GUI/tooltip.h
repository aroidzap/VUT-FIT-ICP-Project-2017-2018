#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <string>
#include <QWidget>

class Tooltip : public QWidget
{
	Q_OBJECT
private:
	std::string text;
public:
	explicit Tooltip(QWidget *parent = nullptr);
	void Text(std::string text);
	void Move(int x, int y);
protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // TOOLTIP_H
