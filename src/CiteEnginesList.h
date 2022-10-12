// -*- C++ -*-
/**
 * \file CiteEnginesList.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Richard Heck
 * \author Jürgen Spitzmüller
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef CITEENGINESLIST_H
#define CITEENGINESLIST_H

#include "Citation.h"

#include <string>
#include <vector>

namespace lyx {

/**
 *  This class represents a particular LyX "cite engine", which defines the features
 * of a particular citation backend such as natbib or biblatex. In that sense, it is more like
 *  a LaTeX package, where a layout file corresponds to a LaTeX class.
 *
 *  In general, a given cite engine can be used with any document class. That said,
 *  one cite engine may `require' another, or it may `exclude' some other cite engine.
 *  The requires and excludes are given in comments within the cite engine file,
 *  which must begin roughly so:
 *  # \DeclareLyXCiteEngine[natbib.sty]{Natbib}
 *  # DescriptionBegin
 *  #   Natbib supports a range of both author-year and numerical styles mainly
 *  #   aimed at the Humanities. It features automatic sorting and merging of
 *  #   numerical citations, annotations, capitalization of the `van' part of
 *  #   author names, shortened and full author lists, and more.
 *  # DescriptionEnd
 *  # Excludes: basic | jurabib
 *  The description will be used in the gui to give information to the user. The
 *  Requires and Excludes lines are read by the configuration script
 *  and written to a file citeengines.lst in the user configuration directory.
 *  That file is then read on startup to populate the CiteEnginesList, below.
 *
 *  Engines can also be "provided" or "excluded" by document classes, using
 *  the ProvidesEngine and ExcludesEngine tags.
 */

class LyXCiteEngine {
public:
	///
	LyXCiteEngine(std::string const & name, std::string const & id,
		      std::vector<std::string> const & enginetypes,
		      std::string const & cfm,
		      std::vector<std::string> const & defaultbiblios,
		      std::string const & description,
		      std::vector<std::string> const & packagelist);
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
	std::string const & getCiteFramework() const { return cite_framework_; }
	///
	std::vector<std::string> const & getEngineType() const { return engine_types_; }
	///
	bool hasEngineType(CiteEngineType const &) const;
	///
	std::string getDefaultBiblio(CiteEngineType const &) const;
	///
	bool isDefaultBiblio(std::string const &) const;
	///
	std::string const & getDescription() const { return description_; }
	///
	std::vector<std::string> const & getPackageList() const
		{ return package_list_; }
	///
	bool requires(std::string const p) const;
private:
	/// what appears in the ui
	std::string name_;
	/// the engine's unique identifier
	/// at present, this is the filename, without the extension
	std::string id_;
	/// the filename
	std::string filename_;
	/// the engine type(s)
	std::vector<std::string> engine_types_;
	/// cite framework (bibtex, biblatex)
	std::string cite_framework_;
	/// default bibliography styles
	std::vector<std::string> default_biblios_;
	/// a short description for use in the ui
	std::string description_;
	/// the LaTeX packages on which this depends, if any
	std::vector<std::string> package_list_;
	// these are mutable because they are used to cache the results
	// or an otherwise const operation.
	///
	mutable bool checked_;
	///
	mutable bool available_;
	///
	mutable std::vector<std::string> prerequisites_;
};

typedef std::vector<LyXCiteEngine> LyXCiteEnginesList;

/**
 *  The CiteEnginesList represents the various LyXCiteEngine's that are available at
 *  present.
 */
class CiteEnginesList {
public:
	///
	CiteEnginesList() {}
	///
	std::string getTypeAsString(CiteEngineType const &) const;
	///
	CiteEngineType getType(std::string const &) const;
	/// reads the engines from a file generated by configure.py
	bool read();
	///
	LyXCiteEnginesList::const_iterator begin() const;
	///
	LyXCiteEnginesList::iterator begin();
	///
	LyXCiteEnginesList::const_iterator end() const;
	///
	LyXCiteEnginesList::iterator end();
	///
	bool empty() const { return englist_.empty(); }
	/// Returns a pointer to the LyXCiteEngine with filename str.
	/// Returns a null pointer if no such engine is found.
	LyXCiteEngine const * operator[](std::string const & str) const;
	///
	LyXCiteEngine * operator[](std::string const & str);
	private:
	/// noncopyable
	CiteEnginesList(CiteEnginesList const &);
	///
	void operator=(CiteEnginesList const &);
	/// add an engine to the list
	void addCiteEngine(std::string const &, std::string const &,
		std::vector<std::string> const &, std::string const &,
		std::vector<std::string> const &, std::string const &,
		std::vector<std::string> const &);
	///
	std::vector<LyXCiteEngine> englist_;
};

extern CiteEnginesList theCiteEnginesList;
} // namespace lyx
#endif
