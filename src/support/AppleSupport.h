// -*- C++ -*-
/**
 * \file AppleSupport.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * \author Stephan Witt
 *
 * Full author contact details are available in file CREDITS.
 */

#ifndef LYX_SUPPORT_APPLESUPPORT_H
#define LYX_SUPPORT_APPLESUPPORT_H

#ifdef __cplusplus
extern "C" {
#endif
	void appleCleanupEditMenu();
	void appleCleanupViewMenu();

	// query the system preferences for users tabbing preference
	bool appleUserTabbingPreferenceAlways();

	// Query the Standard User Defaults for float values of
	// NSTextInsertionPointBlinkPeriodOn resp. NSTextInsertionPointBlinkPeriodOff
	// and return the integer part of it - return -1 in case of unset value
	int NSTextInsertionPointBlinkPeriodOn();
	int NSTextInsertionPointBlinkPeriodOff();
#ifdef __cplusplus
}
#endif

#endif
