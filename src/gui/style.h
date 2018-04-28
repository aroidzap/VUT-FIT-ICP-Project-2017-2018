#ifndef STYLE_H
#define STYLE_H

#include <QColor>

class Style
{
public:
	static const int PortSize;
	static const int PortDrawSize;
	static const int PortMarginV;
	static const int PortNamePadding;
	static const QColor PortOutlineCol;
	static const QColor PortFreeCol;
	static const QColor PortHoverCol;

	static const int ConnectionHoverSize;
	static const QColor ConnectionCol;

	static const int NodeNamePadding;
	static const int NodeNameHeight;
	static const int NodeMinWidth;
	static const int NodeRoundSize;
	static const QColor NodeOutlineCol;
	static const QColor NodeOutlineHighlightCol;
	static const QColor NodeBackgroundCol;

	static const int TooltipRoundSize;
	static const QColor TooltipOutlineCol;
	static const QColor TooltipBackgroundCol;
	static const QColor TooltipTextCol;
};

#endif // STYLE_H
