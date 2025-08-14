/**
 * \file GuiCommandEdit.cpp
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author John Levon
 *
 * Full author contact details are available in file CREDITS.
 */

#include <config.h>

#include "GuiCommandEdit.h"

#include <QKeyEvent>
#include <QEvent>

#undef KeyPress

namespace lyx {
namespace frontend {

GuiCommandEdit::GuiCommandEdit(QWidget * parent)
	: QLineEdit(parent)
{
	setFocusPolicy(Qt::ClickFocus);
}


void GuiCommandEdit::keyPressEvent(QKeyEvent * e)
{
	if (e->modifiers() == Qt::NoModifier || e->modifiers() == Qt::KeypadModifier) {
		switch (e->key()) {
		case Qt::Key_Escape:
			// emit signal
			escapePressed();
			return;

		case Qt::Key_Up:
			// emit signal
			upPressed();
			return;

		case Qt::Key_Down:
			// emit signal
			downPressed();
			return;

		default:
			// do nothing
			break;
		}
	}
	QLineEdit::keyPressEvent(e);
}


bool GuiCommandEdit::event(QEvent * e)
{
	if (e->type() != QEvent::KeyPress)
		return QLineEdit::event(e);

	QKeyEvent * ev = (QKeyEvent *)e;

	if (ev->key() != Qt::Key_Tab)
		return QLineEdit::event(e);

	// emit signal
	tabPressed();
	return true;
}

} // namespace frontend
} // namespace lyx

#include "moc_GuiCommandEdit.cpp"
