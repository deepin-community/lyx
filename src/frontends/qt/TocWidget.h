// -*- C++ -*-
/**
 * \file TocWidget.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author John Levon
 * \author Abdelrazak Younes
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef TOC_WIDGET_H
#define TOC_WIDGET_H

#include "ui_TocUi.h"

#include "FuncCode.h"

#include <QString>
#include <QWidget>

class QModelIndex;
class QPoint;
class QTimer;

namespace lyx {

class Cursor;
class DispatchResult;
class FuncRequest;
class FuncStatus;
class Inset;

namespace frontend {

class FancyLineEdit;
class GuiView;

class TocWidget : public QWidget, public Ui::TocUi
{
	Q_OBJECT
public:
	///
	TocWidget(GuiView & gui_view, QWidget * parent = 0);

	/// Initialise GUI.
	void init(QString const & str);
	///
	void doDispatch(Cursor & cur, FuncRequest const & fr, DispatchResult & dr);
	///send request to lyx::dispatch with proper guiview handle
	///(if ToC is detached current_view can be different window)
	void sendDispatch(FuncRequest fr);
	///
	bool getStatus(Cursor & cur, FuncRequest const & fr, FuncStatus & status)
		const;

public Q_SLOTS:
	/// Schedule an update of the dialog, delaying expensive operations
	void updateView();
	/// Update completely without delay
	void updateViewNow();

protected Q_SLOTS:
	///
	void select(QModelIndex const & index);
	///
	void goTo(QModelIndex const &);

	void on_tocTV_activated(QModelIndex const &);
	void on_tocTV_pressed(QModelIndex const &);
	void on_tocTV_doubleClicked(QModelIndex const &);
	void on_updateTB_clicked();
	void on_sortCB_stateChanged(int state);
	void on_persistentCB_stateChanged(int state);
	void on_depthSL_valueChanged(int depth);
	void on_typeCO_activated(int value);
	void on_moveUpTB_clicked();
	void on_moveDownTB_clicked();
	void on_moveInTB_clicked();
	void on_moveOutTB_clicked();
	void filterContents();

	void showContextMenu(const QPoint & pos);

private Q_SLOTS:
	/// Perform the expensive update operations
	void finishUpdateView();

private:
	///
	void enableControls(bool enable = true);
	///
	bool canOutline()
		{ return current_type_ == "tableofcontents"; }
	/// It is not possible to have synchronous navigation in a correct
	/// and efficient way with the label and change type because Toc::item()
	/// does a linear search. Even when fixed, it might even not be desirable
	/// to do so if we want to support drag&drop of labels and references.
	bool canNavigate()
		{ return current_type_ != "label" && current_type_ != "change"; }
	///
	bool isSortable()
		{ return current_type_ != "tableofcontents"; }
	///
	QModelIndexList getIndices();
	/// \returns the top-most ancestor of \p descendant
	QModelIndex getAncestor(QModelIndex const & descendant) const;
	/// \returns \c true if \p ancestor is an ancestor (parent, grandparent, etc.) of \p descendant
	bool isAncestor(QModelIndex const & ancestor, QModelIndex const & descendant) const;
	/// \returns depth of the current item
	int getItemDepth(QModelIndex const & index);
	/// collapse all nodes to \c depth except for the branch of the currently active item
	void collapseAllOthers(int const depth);
	///
	void setTreeDepth(int depth, bool const maintain_current = false);
	///
	void outline(FuncCode func_code);
	/// finds the inset that is connected to the current item,
	/// if any, otherwise return null
	Inset * itemInset() const;
	///
	QString current_type_;

	/// depth of list shown
	int depth_;
	/// persistence of uncollapsed nodes in toc view
	bool persistent_;
	/// keep uncollapsed nodes in this event
	bool keep_expanded_;
	///
	GuiView & gui_view_;
	// Timer for scheduling expensive update operations
	QTimer * timer_;
	/// Filter bar
	FancyLineEdit * filter_ = nullptr;
};

} // namespace frontend
} // namespace lyx

#endif // TOC_WIDGET_H
