/** ICP Project 2017/2018: BlockEditor
 * @file block_ui.h
 * @brief Block appearance
 * @author Tomáš Pazdiora (xpazdi02)
 * @author Michal Pospíšil (xpospi95)
 */

#ifndef BLOCK_UI_H
#define BLOCK_UI_H

#include <QApplication>
#include <QPaintEvent>
#include <QWidget>
#include <list>

#include <QLineEdit>
#include <QPainter>
#include <QPainterPath>

#include <utility>
#include <algorithm>

#include "block_ui.h"
#include "style.h"
#include "port_ui.h"
#include "graph_ui.h"

#include "../core/blockbase.h"

/**
 * @brief Block GUI representation
 */
template <typename BlockBaseT>
class BlockUI : public QWidget, public BlockBaseT
{
private:
	//! Vector of GUI input ports
	std::vector<InPortUI> inputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	//! Vector of GUI output ports
	std::vector<OutPortUI> outputs; // Should be const vector of non const elements, but this requires custom implementation of vector!
	QLabel label;
	//! Block's dragging status
	bool drag = false;
	//! Block's highlight status
	bool highlight = false;
	//! Block's position
	QPoint drag_p, offset;
protected:
	//! Block's height and width
	int width_, height_;
public:
	/**
	 * @brief BlockUI constructor
	 * @param b Block derived from BlockBase
	 * @param parent Widget where the block is rendered
	 */
	explicit BlockUI(const BlockBaseT &b, QWidget *parent = nullptr)
		: QWidget(parent), BlockBaseT(b), label(b.name.c_str(), this)
	{
		setMouseTracking(true);
		for(size_t i = 0; i < BlockBaseT::InputCount(); i++) {
			inputs.push_back(InPortUI(InPort(BlockBaseT::Input(i), *this), parent));
		}
		for(size_t i = 0; i < BlockBaseT::OutputCount(); i++) {
			outputs.push_back(OutPortUI(OutPort(BlockBaseT::Output(i), *this), parent));
		}

		int input_w = 0;
		int output_w = 0;
		if (inputs.size()>0) {
			input_w = (*std::max_element(inputs.begin(), inputs.end(),
				[] (const InPortUI &a, const InPortUI &b) { return a.getWidth() < b.getWidth(); }
			)).getWidth();
		}
		if (outputs.size()>0) {
			output_w = (*std::max_element(outputs.begin(), outputs.end(),
				[] (const OutPortUI &a, const OutPortUI &b) { return a.getWidth() < b.getWidth(); }
			)).getWidth();
		}

		height_ = (static_cast<int>(std::max(inputs.size(), outputs.size()))) * Style::PortMarginV +
				 std::max(Style::PortMarginV, Style::NodeNameHeight);
		width_ = std::max(input_w + output_w, Style::NodeMinWidth);
		width_ = std::max(width_, Style::NodeNamePadding * 2 + QApplication::fontMetrics().width(label.text()));

		resize(width_ + 1, height_ + 1);

		Move(0, 0);

		show();
		this->label.show();
	}

	/**
	 * @brief Position where block is placed
	 * @return Top left adjusted block's position
	 */
	QPoint Pos() const {
		return (pos() - offset);
	}

	/**
	 * @brief Generate ID for a port
	 * @param port Input port
	 * @return ID on success, -1 otherwise
	 */
	int getPortID(const InPort &port) const override
	{
		int idx = 0;
		for (const InPortUI &p : inputs) {
			if (&p == &port){
				return idx;
			}
			idx++;
		}
		return -1;
	}

	/**
	 * @brief Generate ID for a port
	 * @param port Output port
	 * @return ID on success, -1 otherwise
	 */
	int getPortID(const OutPort &port) const override
	{
		int idx = 0;
		for (const OutPortUI &p : outputs) {
			if (&p == &port){
				return idx;
			}
			idx++;
		}
		return -1;
	}

	/**
	 * @brief Returns reference to an input port specified by ID
	 * @param id Port's ID
	 * @return Address of a port
	 */
	InPort & Input(std::size_t id) override
	{
		return inputs[id];
	}

	//! Returns number of block's inputs
	std::size_t InputCount() override
	{
		return inputs.size();
	}

	/**
	 * @brief Returns reference to an output port specified by ID
	 * @param id Port's ID
	 * @return Address of a port
	 */
	OutPort & Output(std::size_t id) override
	{
		return outputs[id];
	}

	//! Returns number of block's outputs
	std::size_t OutputCount() override
	{
		return outputs.size();
	}

	//! Move block to the specified offset in addition to it's position
	void updateOffset(QPoint offset){
		auto p = Pos();
		this->offset = offset;
		Move(p.x(), p.y());
	}

	/**
	 * @brief Moves block to a specified location
	 * @param x X-axis position
	 * @param y Y-axis position
	 */
	virtual void Move(int x, int y)
	{
		x += this->offset.x();
		y += this->offset.y();

		move(x, y);

		label.move(0, Style::NodeNamePadding);
		label.setFixedWidth(width_);
		label.setAlignment(Qt::AlignCenter);

		int offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
		for(auto &in : inputs) {
			in.Move(x, y + offset);
			offset += Style::PortMarginV;
		}
		offset = std::max(Style::PortMarginV, Style::NodeNameHeight);
		for(auto &out : outputs) {
			out.Move(x + width_, y + offset);
			offset += Style::PortMarginV;
		}
	}

	//! Change block's highlight status
	void Highlight(bool enable)
	{
		this->highlight = enable;
		update();
	}

protected:
	//! Rendering the block
	void paintEvent(QPaintEvent *) override
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		QPainterPath path;
		path.addRoundedRect(QRectF(.5, .5, width_, height_), Style::NodeRoundSize, Style::NodeRoundSize);

		painter.fillPath(path, QBrush(Style::NodeBackgroundCol));

		if (highlight) {
			QPainterPath h;
			h.addRoundedRect(QRectF(2.5, 2.5, width_ - 4, height_ - 4), Style::NodeRoundSize, Style::NodeRoundSize);

			QPen p(Style::NodeOutlineHighlightCol);
			p.setWidth(5);

			painter.strokePath(h, p);
		}

		painter.strokePath(path, QPen(Style::NodeOutlineCol));
	}

	//! Moving block by dragging
	void mouseMoveEvent(QMouseEvent *event) override
	{
		static_cast<GraphUI&>(this->graph).hideHoverConnectionUI();
		if(drag){
			QPoint tmp = Pos() + event->pos() - drag_p;
			Move(tmp.x(), tmp.y());
		}
	}
	//! Begin drag on left click, open context menu on right click
	void mousePressEvent(QMouseEvent *event) override
	{
		setFocus();
		if(event->button() != Qt::RightButton) {
			drag = true;
			drag_p = event->pos();
		}
		else {
			static_cast<GraphUI&>(this->graph).blockContextMenu(this);
		}
	}

	//! End drag
	void mouseReleaseEvent(QMouseEvent *) override
	{
		drag = false;
	}

	//! Hide connection tooltip when hovering over the block
	void enterEvent(QEvent *) override
	{
		static_cast<GraphUI&>(this->graph).hideHoverConnectionUI();
	}
};

/**
 * @brief Input block text edit box
 */
class TextEdit : public QLineEdit{
private:

	std::function<void(void)> callback;
	bool err = false;
	QString prev;
public:
	TextEdit(QWidget *parent, std::function<void(void)> callback)
		: QLineEdit(parent), callback(callback) { }
	void ErrorColor(bool err) {
		this->err = err;
	}
protected:
	void focusOutEvent(QFocusEvent *e) override {
		QLineEdit::focusOutEvent(e);
		if (text() != prev) { callback(); }
		prev = text();
	}
	void keyPressEvent(QKeyEvent *e) override {
		QLineEdit::keyPressEvent(e);
		if (text() != prev) { callback(); }
		prev = text();
	}
	void paintEvent(QPaintEvent *e) override {
		QLineEdit::paintEvent(e);
		if(err){
			QPainter painter(this);
			painter.setBrush(QColor(255, 0, 0, 64));
			painter.drawRect(0, 0, width() - 1, height() - 1);
		}
	}
};

/**
 *
 */
template <typename BlockBaseT>
class InputBlockUI : public BlockUI<BlockBaseT> {
private:
	int orig_w, orig_h;
	int text_in_off;
	std::map<std::string, TextEdit*> text_in;
	void update_output() {
		this->graph.computeReset();
		Type &val = this->Output(0).Value();
		for(auto l : text_in){
			bool ok;
			val[l.first] = l.second->text().toDouble(&ok);
			if(!ok){
				val[l.first] = 0.0;
				l.second->ErrorColor(true);
			} else {
				l.second->ErrorColor(false);
			}
		}
	}
public:
	explicit InputBlockUI(const BlockUI<BlockBaseT> &b, QWidget *parent = nullptr)
		: BlockUI<BlockBaseT>(b, parent), orig_w(this->width_), orig_h(this->height_){
		auto data = this->Output(0).Value().Data();
		text_in_off = 0;
		for(auto &el : data){
			text_in_off = std::max(text_in_off, QApplication::fontMetrics().width((el.first + " : ").c_str()));
		}
		int off = Style::NodeNameHeight - 3;

		for(auto &el : data){
			auto l = new TextEdit(this, [this](){this->update_output();});
			l->show();
			l->setText("0");
			l->resize(Style::NodeFieldWidth, l->height());
			l->move(Style::PortNamePadding + text_in_off, off);
			text_in.insert(std::pair<std::string, TextEdit*>(el.first.c_str(), l));
			off += Style::NodeFieldOffset;
		}
		update_output();
	}
	bool Computable() override {
		return false;
	}
	~InputBlockUI(){
		for(auto l : text_in){
			delete l.second;
		}
	}
	void Move(int x, int y) override
	{
		this->width_ = this->orig_w - static_cast<OutPortUI&>(this->Output(0)).getWidth() + text_in_off + Style::NodeFieldWidth;
		int cnt = static_cast<int>(text_in.size()) - 1;
		this->height_ = this->orig_h + Style::NodeFieldOffset * (cnt < 0 ? 0 : cnt);
		this->resize(this->width_ + 1, this->height_ + 1);
		BlockUI<BlockBaseT>::Move(x, y);
	}
protected:
	void paintEvent(QPaintEvent *event) override {
		BlockUI<BlockBaseT>::paintEvent(event);

		int h = QApplication::fontMetrics().height();

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		int offset = Style::NodeNameHeight + h - 2;
		for(const auto &el : text_in){
			painter.drawText(Style::PortNamePadding, offset, (el.first + " : ").c_str());
			offset += Style::NodeFieldOffset;
		}
	}
};

template <typename BlockBaseT>
class OutputBlockUI : public BlockUI<BlockBaseT> {
private:
	int orig_w, orig_h;
public:
	explicit OutputBlockUI(const BlockUI<BlockBaseT> &b, QWidget *parent = nullptr)
		: BlockUI<BlockBaseT>(b, parent), orig_w(this->width_), orig_h(this->height_) {
		this->Input(0).onConnectionChange([this](Port &){this->update();});
		this->Input(0).onValueChange([this](Port &){this->update();});
	}
	bool Computable() override {
		return false;
	}
	void updateBlockSize()
	{
		int w, h;
		auto lines = Tooltip::TextLines(static_cast<std::string>(this->Input(0).Value()), w, h);
		int cnt = static_cast<int>(lines.size()) - 1;
		this->height_ = this->orig_h + h * (cnt < 0 ? 0 : cnt) - h;
		this->width_ = this->orig_w - static_cast<InPortUI&>(this->Input(0)).getWidth() + w;
		this->width_ = std::max(this->width_, Style::NodeNamePadding * 2 + QApplication::fontMetrics().width(this->name.c_str()));
		this->width_ = std::max(this->width_, Style::NodeMinWidth);
		this->resize(this->width_ + 1, this->height_ + 1);
	}
	void Move(int x, int y) override {
		updateBlockSize();
		BlockUI<BlockBaseT>::Move(x, y);
	}
protected:
	void paintEvent(QPaintEvent *event) override
	{
		updateBlockSize();
		BlockUI<BlockBaseT>::paintEvent(event);

		int w, h;
		auto lines = Tooltip::TextLines(static_cast<std::string>(this->Input(0).Value()), w, h);

		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing);

		int offset = Style::PortMarginV + h - 3;
		for(const std::string &line : lines){
			painter.drawText(Style::PortNamePadding, offset, line.c_str());
			offset += h;
		}
	}
};

#endif // BLOCK_UI_H
