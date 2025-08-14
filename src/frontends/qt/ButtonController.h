// -*- C++ -*-
/**
 * \file ButtonController.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Allan Rae
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include "ButtonPolicy.h"

class QWidget;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QString;

namespace lyx {
namespace frontend {

/** General purpose button controller for up to four buttons.
    Controls the activation of the OK, Apply and Cancel buttons.
    Actually supports 4 buttons in all and it's up to the user to decide on
    the activation policy and which buttons correspond to which output of the
    state machine.
*/


/** \c ButtonController controls the activation of the OK, Apply and
 *  Cancel buttons.
 *
 * It actually supports 4 buttons in all and it's up to the user to decide on
 * the activation policy and which buttons correspond to which output of the
 * state machine.
 */

class ButtonController
{
public:
	ButtonController();
	~ButtonController();

	//@{
	/// Methods to set and get the ButtonPolicy.
	void setPolicy(ButtonPolicy::Policy policy);
	ButtonPolicy const & policy() const;
	ButtonPolicy & policy();
	//@}

	///
	void input(ButtonPolicy::SMInput);

	//@{
	/// Tell the BC that a particular button has been pressed.
	void ok();
	void apply();
	void cancel();
	void restore();
	void autoApply();
	//@}

	/// Tell the BC that the dialog is being hidden
	void hide();

	/**Refresh the activation state of the Ok, Apply, Close and
	 * Restore buttons.
	 */
	void refresh() const;

	/** Passthrough function -- returns its input value
	 *  Tell the BC about the read-only status of the underlying buffer.
	 */
	bool setReadOnly(bool);

	/**
	 *  Sets the activation state of the buttons immediately.
	 * \param validity Tell the BC that the data is, or is not, valid.
	 */
	void setValid(bool);

	//
	// View
	//

	//@{
	/// Store pointers to these widgets. \param default_button determines
	/// the default button of the dialog (bound to return). This is
	/// OK by default.
	void setOK(QPushButton * obj, bool const default_button = true);
	void setApply(QPushButton * obj, bool const default_button = false);
	void setCancel(QPushButton * obj, bool const default_button = false);
	void setRestore(QPushButton * obj, bool const default_button = false);
	void setAutoApply(QCheckBox * obj);
	//@}

	/** Add a pointer to the list of widgets whose activation
	 *  state is dependent upon the read-only status of the
	 *  underlying buffer.
	 */
	void addReadOnly(QWidget * obj);

	/** Add a widget to the list of all widgets whose validity should
	 *  be checked explicitly when the buttons are refreshed.
	 */
	void addCheckedLineEdit(QLineEdit * input, QWidget * target = 0, int tabindex = -1);

	/** Add a widget to the list of all widgets whose validity should
	 *  be checked explicitly when the buttons are refreshed.
	 */
	void addCheckedLineEditPanel(QLineEdit * input, QWidget * target, QString const panel);

private:
	/// noncopyable
	ButtonController(ButtonController const &);
	void operator=(ButtonController const &);

	/// pimpl
	class Private;
	Private * d;
};

} // namespace frontend
} // namespace lyx

#endif // BUTTONCONTROLLER_H
