/** ICP Project 2017/2018: BlockEditor
 * @file tooltip.h
 * @brief Tooltips for viewing values when hovering over connections
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <string>
#include <QWidget>

//! Tooltips shown when hovering over connections
class Tooltip : public QWidget
{
private:
	//! Label used in the tooltip
	std::string text;
public:
	//! Function that renders labels in a tooltip
	static std::vector<std::string> TextLines(const std::string &text, int &width, int &height);
	/**
	 * @brief Tooltip constructor
	 * @param parent Parent connection widget
	 */
	explicit Tooltip(QWidget *parent = nullptr);
	/**
	 * @brief Value caption
	 * @param text Caption
	 */
	void Text(std::string text);
	/**
	 * @brief Places the tooltip at the specified coordinates
	 * @param x X-axis coordinate
	 * @param y Y-axis coordinate
	 */
	void Move(int x, int y);
protected:
	//! Rendering the block
	void paintEvent(QPaintEvent *) override;
};

#endif // TOOLTIP_H
