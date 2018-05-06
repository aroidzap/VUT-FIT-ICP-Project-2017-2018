/** ICP Project 2017/2018: BlockEditor
 * @file tooltip.h
 * @brief Tooltips for viewing values at connections
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
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
	void paintEvent(QPaintEvent *) override;
};

#endif // TOOLTIP_H
