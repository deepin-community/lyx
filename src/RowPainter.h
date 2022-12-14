// -*- C++ -*-
/**
 * \file RowPainter.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author various
 * \author John Levon
 * \author André Pönitz
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef ROWPAINTER_H
#define ROWPAINTER_H

#include "Changes.h"
#include "Row.h"

#include "support/types.h"

namespace lyx {

class BufferView;
class Font;
class FontInfo;
class Inset;
class Language;
class PainterInfo;
class Paragraph;
class ParagraphList;
class Text;
class TextMetrics;

namespace frontend { class Painter; }

/**
 * A class used for painting an individual row of text.
 * FIXME: get rid of that class.
 */
class RowPainter {
public:
	/// initialise and run painter
	RowPainter(PainterInfo & pi, Text const & text,
	           Row const & row, int x, int y);

	/// paint various parts
	/// FIXME: transfer to TextMetrics
	void paintAppendix() const;
	void paintDepthBar() const;
	void paintChangeBar() const;
	void paintTooLargeMarks(bool const left, bool const right) const;
	void paintFirst() const;
	void paintLast() const;
	void paintText();
	void paintOnlyInsets();
	void paintSelection() const;

private:
	void paintForeignMark(Row::Element const & e) const;
	void paintStringAndSel(Row::Element const & e) const;
	void paintTextDecoration(Row::Element const & e) const;
	void paintMisspelledMark(Row::Element const & e) const;
	void paintChange(Row::Element const & e) const;
	void paintAppendixStart(int y) const;
	void paintInset(Row::Element const & e) const;

	/// return the label font for this row
	FontInfo labelFont() const;

	///
	void paintLabel() const;
	///
	void paintTopLevelLabel() const;


	/// contains painting related information.
	PainterInfo & pi_;

	/// Text for the row
	Text const & text_;
	TextMetrics const & tm_;
	ParagraphList const & pars_;

	/// The row to paint
	Row const & row_;

	/// Row's paragraph
	Paragraph const & par_;

	/// row changed? (change tracking)
	Change const change_;

	// Looks ugly - is
	double const xo_;
	int const yo_;    // current baseline
	double x_;
};

} // namespace lyx

#endif // ROWPAINTER_H
