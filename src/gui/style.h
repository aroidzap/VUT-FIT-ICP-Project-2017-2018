/** ICP Project 2017/2018: BlockEditor
 * @file style.h
 * @brief All custom defined styles - header
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef STYLE_H
#define STYLE_H

#include <QColor>

/**
 * @brief Container for all custom defined styles
 */
class Style
{
public:
	//! Port connect diameter
	static const int PortSize;
	//! Port draw diameter
	static const int PortDrawSize;
	//! Port margin
	static const int PortMarginV;
	//! Port name padding
	static const int PortNamePadding;
	//! Port outline color
	static const QColor PortOutlineCol;
	//! Unoccupied port color
	static const QColor PortFreeCol;
	//! Port color when hovered over
	static const QColor PortHoverCol;

	//! Connection line width when hovered
	static const int ConnectionHoverSize;
	//! Connection line color
	static const QColor ConnectionCol;

	//! Padding around the graph widget
	static const int GraphLoadPadding;

	//! Offset for positioning text fields in IO blocks
	static const int NodeFieldOffset;
	//! Width of text fields in IO blocks
	static const int NodeFieldWidth;
	//! Block name padding
	static const int NodeNamePadding;
	//! Block name Height
	static const int NodeNameHeight;
	//! Block's minimum width
	static const int NodeMinWidth;
	//! Corner rounding size on block
	static const int NodeRoundSize;
	//! Block's outline color
	static const QColor NodeOutlineCol;
	//! Block's highlight outline color
	static const QColor NodeOutlineHighlightCol;
	//! Background block color
	static const QColor NodeBackgroundCol;

	//! Tooltip corner rounding size
	static const int TooltipRoundSize;
	//! Tooltip padding
	static const int TooltipPadding;
	//! Tooltip horizontal padding
	static const int TooltipHPadding;
	//! Tooltip outline color
	static const QColor TooltipOutlineCol;
	//! Tooltip background color
	static const QColor TooltipBackgroundCol;
	//! Tooltip text color
	static const QColor TooltipTextCol;
};

#endif // STYLE_H
