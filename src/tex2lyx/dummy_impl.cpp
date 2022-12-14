/**
 * \file dummy_impl.cpp
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Jean-Marc Lasgouttes
 *
 * Full author contact details are available in file CREDITS.
 */

/**
 * This file contains dummy implementation of some methods that are
 * needed byclasses used by tex2lyx. This allows to reduce the number
 * of classes we have to link against.
*/

// {[(

#include <config.h>

#include "Format.h"
#include "LaTeXFeatures.h"
#include "output_xhtml.h"

#include "support/Messages.h"

#include <iostream>

using namespace std;

namespace lyx {

//
// Dummy Alert support (needed by TextClass)
//


namespace frontend {
namespace Alert {
	void warning(docstring const & title, docstring const & message,
				 bool const &)
	{
		cerr << to_utf8(title) << "\n" << to_utf8(message) << endl;
	}
} // namespace Alert
} // namespace frontend


//
// Dummy verbose support
//

bool verbose = false;


//
// Dummy LyXRC support
//


class LyXRC {} lyxrc;


//
// Dummy translation support (needed at many places)
//


Messages messages_;
Messages const & getMessages(string const &)
{
	return messages_;
}


Messages const & getGuiMessages()
{
	return messages_;
}


//
// Dummy formats support (needed by Lexer)
//


Formats & theFormats()
{
	static Formats dummy_formats;
	return dummy_formats;
}

bool Formats::isZippedFile(support::FileName const&) const
{
	return false;
}


//
// Dummy features support (needed by ModuleList)
//


bool LaTeXFeatures::isAvailable(string const &)
{
	return true;
}


string alignmentToCSS(LyXAlignment)
{
	return string();
}

//
// Dummy FontMetrics (needed by Length)
//

namespace frontend {
class FontMetrics {
	int em() const { return 0; };
};
} // namespace frontend

class FontInfo;

frontend::FontMetrics const & theFontMetrics(FontInfo const &) {
	static frontend::FontMetrics dummy;
	return dummy;
}

//
// Keep the linker happy on Windows
//

void lyx_exit(int)
{}

} // namespace lyx
