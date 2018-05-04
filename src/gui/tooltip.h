/*
*	ICP Project: BlockEditor
*	Authors: Tomáš Pazdiora (xpazdi02), Michal Pospíšil (xpospi95)
*	File: tooltip.h
*/

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <string>
#include <QWidget>

class Tooltip : public QWidget
{
private:
	std::string text;
public:
	static std::vector<std::string> TextLines(const std::string &text, int &width, int &height);
	explicit Tooltip(QWidget *parent = nullptr);
	void Text(std::string text);
	void Move(int x, int y);
protected:
	void paintEvent(QPaintEvent *event) override;
};

#endif // TOOLTIP_H
