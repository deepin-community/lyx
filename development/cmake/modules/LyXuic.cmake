#
#  Copyright (c) 2006, Peter K?mmel, <syntheticpp@gmx.net>
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#  
#  1. Redistributions of source code must retain the copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote products 
#     derived from this software without specific prior written permission.
#  
#  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
#  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
#  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
#  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
#  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

execute_process(
	COMMAND ${KDE_UIC_EXECUTABLE}
	${KDE_UIC_FILE}
	OUTPUT_VARIABLE _uic_CONTENTS
	ERROR_QUIET)

set(KDE_UIC_CPP_FILE ${KDE_UIC_H_FILE})

if(WIN32)
    string(REGEX REPLACE "\r" "" _uic_CONTENTS "${_uic_CONTENTS}" )
endif()

file(WRITE ${KDE_UIC_CPP_FILE} "${_uic_CONTENTS}\n")

#message("" "")
#message("KDE_UIC_EXECUTABLE:" ${KDE_UIC_EXECUTABLE})
#message("KDE_UIC_FILE:" ${KDE_UIC_FILE})
#message("KDE_UIC_H_FILE:" ${KDE_UIC_H_FILE})
#message("KDE_UIC_CPP_FILE:" ${KDE_UIC_CPP_FILE})
#message("_uic_CONTENTS:" ${_uic_CONTENTS})
#message("" "")
