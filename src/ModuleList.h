// -*- C++ -*-
/**
 * \file ModuleList.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Richard Heck
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef MODULELIST_H
#define MODULELIST_H

#include <string>
#include <vector>

namespace lyx {

/**
 *  This class represents a particular LyX "module", which is a like a layout
 *  file, except that it does not stand alone. In that sense, it is more like
 *  a LaTeX package, where a layout file corresponds to a LaTeX class. Or, in
 *  LyX's own terms, a module is more like an included file that can be used
 *  with various document classes. The difference is that using a module only
 *  means selecting it in the Document>Settings dialog, whereas including a
 *  layout file means layout file editing.
 *
 *  In general, a given module can be used with any document class. That said,
 *  one module may `require' another, or it may `exclude' some other module.
 *  The requires and excludes are given in comments within the module file,
 *  which must begin roughly so:
 *   #\DeclareLyXModule{Theorems (By Section)}
 *   #DescriptionBegin
 *   #Numbers theorems and the like by section.
 *   #DescriptionEnd
 *   #Requires: theorems-std | theorems-ams
 *   #Excludes: theorems-chap
 *   #Category: theorems
 *  The description is used in the gui to give information to the user. The
 *  Requires, Excludes, and Category lines are read by the configuration script
 *  and written to a file lyxmodules.lst in the user configuration directory.
 *  That file is then read on startup to populate the ModuleList, below.
 *
 *  Modules can also be "provided" or "excluded" by document classes, using
 *  the ProvidesModule and ExcludesModule tags.
 */

class LyXModule {
public:
	///
	LyXModule(std::string const & name, std::string const & id,
	          std::string const & description,
	          std::vector<std::string> const & packagelist,
	          std::vector<std::string> const & requires,
	          std::vector<std::string> const & excludes,
	          std::string const & catgy);
	/// whether the required packages are available
	bool isAvailable() const;
	/// the missing prerequisites, if any
	std::vector<std::string> prerequisites() const;
	///
	std::string const & getName() const { return name_; }
	///
	std::string const & getID() const { return id_; }
	///
	std::string const & getFilename() const { return filename_; }
	///
	std::string const & getDescription() const { return description_; }
	///
	std::vector<std::string> const & getPackageList() const
		{ return package_list_; }
	///
	std::vector<std::string> const & getRequiredModules() const
		{ return required_modules_; }
	/// Modules this one excludes: the list should be treated disjunctively
	std::vector<std::string> const & getExcludedModules() const
		{ return excluded_modules_; }
	///
	std::string category() const { return category_; }
	/// \return true if the module is compatible with this one, i.e.,
	/// it does not exclude us and we do not exclude it.
	/// this will also return true if modname is unknown and we do not
	/// exclude it, since in that case we cannot check its exclusions.
	bool isCompatible(std::string const & modname) const;
	///
	static bool areCompatible(std::string const & mod1, std::string const & mod2);
private:
	/// what appears in the ui
	std::string name_;
	/// the module's unique identifier
	/// at present, this is the filename, without the extension
	std::string id_;
	/// the filename
	std::string filename_;
	/// a short description for use in the ui
	std::string description_;
	/// the LaTeX packages on which this depends, if any
	std::vector<std::string> package_list_;
	/// Modules this one requires: at least one
	std::vector<std::string> required_modules_;
	/// Modules this one excludes: none of these
	std::vector<std::string> excluded_modules_;
	/// Category, also used in the UI
	std::string category_;
	// these are mutable because they are used to cache the results
	// or an otherwise const operation.
	///
	mutable bool checked_;
	///
	mutable bool available_;
	///
	mutable std::vector<std::string> prerequisites_;
};

typedef std::vector<LyXModule> LyXModuleList;

/**
 *  The ModuleList represents the various LyXModule's that are available at
 *  present.
 */
class ModuleList {
public:
	///
	ModuleList() {}
	/// reads the modules from a file generated by configure.py
	bool read();
	///
	LyXModuleList::const_iterator begin() const;
	///
	LyXModuleList::iterator begin();
	///
	LyXModuleList::const_iterator end() const;
	///
	LyXModuleList::iterator end();
	///
	bool empty() const { return modlist_.empty(); }
	/// Returns a pointer to the LyXModule with filename str.
	/// Returns a null pointer if no such module is found.
	LyXModule const * operator[](std::string const & str) const;
	///
	LyXModule * operator[](std::string const & str);
	private:
	/// noncopyable
	ModuleList(ModuleList const &);
	///
	void operator=(ModuleList const &);
	/// add a module to the list
	void addLayoutModule(std::string const &, std::string const &,
		std::string const &, std::vector<std::string> const &,
		std::vector<std::string> const &, std::vector<std::string> const &,
		std::string const &);
	///
	std::vector<LyXModule> modlist_;
};

extern ModuleList theModuleList;
} // namespace lyx
#endif
