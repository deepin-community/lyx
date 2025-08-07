/**
 * \file debug.cpp
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Lars Gullik Bjønnes
 * \author Jean-Marc Lasgouttes
 * \author Pavel Sanda
 *
 * Full author contact details are available in file CREDITS.
 */

#include <config.h>

#include "support/debug.h"

#include "support/convert.h"
#include "support/FileName.h"
#include "support/gettext.h"
#include "support/lstrings.h"
#include "support/ProgressInterface.h"

#include <iostream>
#include <iomanip>


using namespace std;
using namespace lyx::support;

namespace lyx {

namespace {

struct DebugErrorItem {
	Debug::Type level;
	char const * name;
	char const * desc;
};


DebugErrorItem errorTags[] = {
	{ Debug::NONE,      "none",      N_("No debugging messages")},
	{ Debug::INFO,      "info",      N_("General information")},
	{ Debug::INIT,      "init",      N_("Program initialisation")},
	{ Debug::KEY,       "key",       N_("Keyboard events handling")},
	{ Debug::GUI,       "gui",       N_("GUI handling")},
	{ Debug::PARSER,    "parser",    N_("Lyxlex grammar parser")},
	{ Debug::LYXRC,     "lyxrc",     N_("Configuration files reading")},
	{ Debug::KBMAP,     "kbmap",     N_("Custom keyboard definition")},
	{ Debug::OUTFILE,   "outfile",   N_("Output source file generation/processing")},
	{ Debug::OUTFILE,   "latex",     N_("Output source file generation/processing (alias to 'outfile')")},
	{ Debug::MATHED,    "mathed",    N_("Math editor")},
	{ Debug::FONT,      "font",      N_("Font handling")},
	{ Debug::TCLASS,    "tclass",    N_("Textclass files reading")},
	{ Debug::LYXVC,     "lyxvc",     N_("Version control")},
	{ Debug::LYXSERVER, "lyxserver", N_("External control interface")},
	{ Debug::UNDO,      "undo",      N_("Undo/Redo mechanism")},
	{ Debug::ACTION,    "action",    N_("User commands")},
	{ Debug::LYXLEX,    "lyxlex",    N_("The LyX Lexer")},
	{ Debug::DEPEND,    "depend",    N_("Dependency information")},
	{ Debug::INSETS,    "insets",    N_("LyX Insets")},
	{ Debug::FILES,     "files",     N_("Files used by LyX")},
	{ Debug::WORKAREA,  "workarea",  N_("Workarea events")},
	{ Debug::CLIPBOARD, "clipboard", N_("Clipboard handling")},
	{ Debug::GRAPHICS,  "graphics",  N_("Graphics conversion and loading")},
	{ Debug::CHANGES,   "changes",   N_("Change tracking")},
	{ Debug::EXTERNAL,  "external",  N_("External template/inset messages")},
	{ Debug::PAINTING,  "painting",  N_("RowPainter profiling")},
	{ Debug::SCROLLING, "scrolling", N_("Scrolling debugging")},
	{ Debug::MACROS,    "macros",    N_("Math macros")},
	{ Debug::RTL,       "rtl",       N_("RTL/Bidi")},
	{ Debug::LOCALE,    "locale",    N_("Locale/Internationalisation")},
	{ Debug::SELECTION, "selection", N_("Selection copy/paste mechanism")},
	{ Debug::FIND,      "find",      N_("Find and replace mechanism, terse version")},
	{ Debug::FINDVERBOSE,"findverbose", N_("Find and replace mechanism, verbose version")},
	{ Debug::DEBUG,     "debug",     N_("Developers' general debug messages")},
	{ Debug::ANY,       "any",       N_("All debugging messages")},
	{ Debug::ANY,       "all",       N_("All debugging messages (alias to 'all')")}
};


int const numErrorTags = sizeof(errorTags)/sizeof(errorTags[0]);

} // namespace


int Debug::levelCount()
{
	return numErrorTags;
}


Debug::Type Debug::value(int idx)
{
	if (idx > 0 && idx < numErrorTags)
		return errorTags[idx].level;
	return Debug::NONE;
}


string const Debug::description(Debug::Type val)
{
	for (const auto & errorTag : errorTags) {
		if (errorTag.level == val)
			return errorTag.desc;
	}
	return "unknown level";
}


string const Debug::name(Debug::Type val)
{
	for (const auto & errorTag : errorTags) {
		if (errorTag.level == val)
			return errorTag.name;
	}
	return "unknown level";
}


string const Debug::realName(int idx)
{
	if (idx < numErrorTags)
		return errorTags[idx].name;
	return "unknown index";
}


Debug::Type Debug::value(string const & val)
{
	Type l = Debug::NONE;
	string v = val;
	while (!v.empty()) {
		size_t const st = v.find(',');
		string const tmp = ascii_lowercase(v.substr(0, st));
		if (tmp.empty())
			break;
		// Is it a number?
		if (isStrInt(tmp))
			l |= static_cast<Type>(convert<unsigned long long>(tmp));
		else
			// Search for an explicit name
			for (DebugErrorItem const & item : errorTags)
				if (tmp == item.name) {
					l |= item.level;
					break;
				}
		if (st == string::npos)
			break;
		v.erase(0, st + 1);
	}
	return l;
}


string Debug::badValue(string const & val)
{
	string v = val;
	while (!v.empty()) {
		size_t const st = v.find(',');
		string const tmp = ascii_lowercase(v.substr(0, st));
		if (tmp.empty())
			break;
		// Is it a number?
		if (!tmp.empty() && !isStrInt(tmp)) {
			// Search for an explicit name
			bool found = false;
			for (DebugErrorItem const & item : errorTags)
				if (tmp == item.name) {
					found = true;
					break;
				}
			if (!found)
				return tmp;
		}
		if (st == string::npos)
			break;
		v.erase(0, st + 1);
	}
	return empty_string();
}


void Debug::showLevel(ostream & os, Debug::Type level)
{
	// Show what features are traced
	for (DebugErrorItem const & item : errorTags) {
		if (item.level != Debug::ANY
		      && item.level != Debug::NONE
		      && item.level & level) {
			// avoid to_utf8(_(...)) re-entrance problem
			docstring const s = _(item.desc);
			os << to_utf8(bformat(_("Debugging `%1$s' (%2$s)"),
					from_utf8(item.name), s))
			   << '\n';
		}
	}
	os.flush();
}


void Debug::showTags(ostream & os)
{
	for (DebugErrorItem const & item : errorTags)
		os << setw(12) << static_cast<Debug::base_type>(item.level)
		   << setw(13) << item.name
		   << "  " << to_utf8(_(item.desc)) << '\n';
	os.flush();
}


void LyXErr::disable()
{
	enabled_ = false;
}


void LyXErr::enable()
{
	enabled_ = true;
}


bool LyXErr::debugging(Debug::base_type t) const
{
	return (dt_ & t);
}


void LyXErr::endl()
{
	if (enabled_) {
		stream() << std::endl;
		if (second_enabled_)
			secondStream() << std::endl;
	}
}


char const * LyXErr::stripName(char const * n)
{
	string const name = n;
	// find the last occurrence of /src/ in name
	size_t pos = name.rfind("/src/");
	if (pos == string::npos)
		pos = name.rfind("\\src\\");
	if (pos == string::npos)
		return n;
	else
		return n + pos + 5;
}


// It seems not possible to instantiate operator template out of class body
template<class T>
LyXErr & toStream(LyXErr & l, T t)
{
	if (l.enabled()){
		l.stream() << t;
		if (l.secondEnabled()) {
			l.secondStream() << t;
			ProgressInterface::instance()->lyxerrFlush();
		}
	}
	return l;
}


LyXErr & operator<<(LyXErr & l, void const * t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, char const * t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, char t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, int t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, unsigned int t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, long t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, unsigned long t)
{ return toStream(l, t); }
#ifdef HAVE_LONG_LONG_INT
LyXErr & operator<<(LyXErr & l, long long t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, unsigned long long t)
{ return toStream(l, t); }
#endif
LyXErr & operator<<(LyXErr & l, double t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, string const & t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, docstring const & t)
{ return toStream(l, to_utf8(t)); }
LyXErr & operator<<(LyXErr & l, FileName const & t)
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, ostream &(*t)(ostream &))
{ return toStream(l, t); }
LyXErr & operator<<(LyXErr & l, ios_base &(*t)(ios_base &))
{ return toStream(l, t); }


// The global instance
LyXErr lyxerr;



} // namespace lyx
