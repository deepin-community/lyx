// -*- C++ -*-
/**
 * \file InsetFootlike.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Lars Gullik Bjønnes
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef INSETFOOTLIKE_H
#define INSETFOOTLIKE_H

#include "InsetCollapsible.h"


namespace lyx {

// To have this class is probably a bit overkill... (Lgb)

// The footnote inset
class InsetFootlike : public InsetCollapsible {
public:
	///
	explicit InsetFootlike(Buffer *);
	///
	bool hasSettings() const override { return false; }
private:
	///
	void write(std::ostream & os) const override;
	///
	bool insetAllowed(InsetCode) const override;
};


} // namespace lyx

#endif
