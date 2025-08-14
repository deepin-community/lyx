﻿Building the installer
======================

To build the installer do the following:

- install the latest version 3.x of NSIS (https://nsis.sourceforge.io/Download)
- install the NSIS Large Strings build (https://nsis.sourceforge.io/Special_Builds)
  (extract the extension ZIP file in your NSIS installation folder and this way overwrite some files)
- download the plugin Inetc (https://nsis.sourceforge.io/Inetc_plug-in)
  extract the content into the NSIS's installation folder
- download the plugin NSISList (https://nsis.sourceforge.io/NSISList_plug-in), download both .zip archives,
  extract Include\NSISList.nsh from the first archive to the folder Include of NSIS's installation folder and
  extract NSISList-Unicode\NSISList.dll from the second archive to the folder \Plugins\x86-unicode of NSIS's installation folder
- download the plugin ShellLink (https://nsis.sourceforge.io/ShellLink_plug-in)
  extract Unicode\Plugins\ShellLink.dll from the archive to the folder \Plugins\x86-unicode of NSIS's installation folder
- download the plugin ShellExecAsUser (https://nsis.sourceforge.io/ShellExecAsUser_plug-in), choose Unicode version
  extract unicode\ShellExecAsUser.dll from the archive to the folder \Plugins\x86-unicode of NSIS's installation folder
- Go to the Qt-kit directory, which you have specified as CMAKE_PREFIX_PATH before compiling in CMake Gui, enter the bin folder,
  copy these files:
   Qt5Concurrent.dll"
   Qt5Network.dll"
   Qt5OpenGL.dll"
   Qt5PrintSupport.dll"
  to %%lyxbuild%%\LYX_INSTALLED\bin
  The files will be named Qt6xxx.dll if compiled with Qt6
- open the file settings.nsh with a text editor and adapt the settings for your need. A good text editor
  for NSIS development is e.g. Visual Studio Code with the NSIS extension.
- right-click on the file lyx-standard.nsi and choose "Compile NSIS script"


Updating dependencies
=====================

- Imagemagick:
  download the portable version of imagemagick for windows from https://imagemagick.org/script/download.php (32 or 64 bit),
  current version is 7.0.10-0
  extract the zip archive,
  run imagemagickConvert.bat in %%repo%%\development\Win32\packaging\dependencies, browse to the extracted imagemagick archive,
  after the script finishes check for anything suspicious.
  if there is anything suspicious or it didn't work (in case imagemagic devs changed something), read the following description,
  it describes how it was done for 7.0.10-0, repair the bat file and update the description
  In the fresh extracted archive will be many executable files which are the exact same size as "magick.exe". magick.exe is
  the only executable LyX needs, delete the other redundant executables. Also delete ffmpeg.exe and IMDisplay.exe.
  The resulting folder size should be around 15-16 MB

- Ghostscript
  download ghostscript for windows from https://www.ghostscript.com/download/gsdnld.html (32 or 64 bit), current version is 9.50
  install to your computer or open the installer executable with 7zip, extract the folders "bin" and "lib" from the installdir/archive
  to %%dependencies%%\ghostscript.

- Python
  download the latest Python 3 release for windows from https://www.python.org/downloads/windows/ (embeddable package 64 bit),
  current version is 3.11.2
  Extract it and copy to %%dependencies%%\Python.
  open python3XX._pth file with a text editor, uncomment the "import site" line
  add following paths after the 2 already existing paths ('.' and python311.zip)
    ./Scripts
    ../Resources
    ../Resources/lyx2lyx
    ../Resources/scripts

- Visual Studio runtime
  Download the latest Visual C++ Redistributable (if you still haven't), the version should match with your VS C++ compiler
  (Buildtools) though. Find these files in Windows/System32 folder:
   concrt140.dll
   msvcp140.dll
   vcamp140.dll
   vccorlib140.dll
   vcomp140.dll
   vcruntime140.dll
  For 64 bit you will additionally need
   vcruntime140_1.dll
  See the Python description above for explanation of different store locations of 64 and 32 bit dlls. Copy these dlls to
  %%dependencies%%\bin.

- NetPbm
  download the latest binaries zip file from http://gnuwin32.sourceforge.net/packages/netpbm.htm,
  current version is 10.27, last updated on 12 May 2005
  extract the files
   libnetpbm10.dll
   pnmcrop.exe
  to %%dependencies%%\bin.

- DTL
  Using TeX Live Manager install package dtl.win32,
  From C:\texlive\2019\bin\win32 copy these files
   dt2dv.exe
   dv2dt.exe
  to %%dependencies%%\bin. You can uninstall the package afterwards.
  Info: Version 0.6.1 does not work with MikTex (math preview triggers error complaining about missing kpathsea631.dll),
  therefore this method is not usable.
  Update: as of report 11325 DTL tools are included in lyxgit and get compiled alongside lyx.

- rsvg-convert
  dowload the 7zip archve from https://opensourcepack.blogspot.com/2012/06/rsvg-convert-svg-image-conversion-tool.html,
  current version is 2.40.20
  Extract rsvg-convert.exe ti %%dependencies%%\bin.

- unoconv
  download the latest source code (zip) from https://github.com/unoconv/unoconv/releases
  current version is 0.8.2
  extract unoconv (no file extension) to %%dependencies%%\bin and add the extension ".py"

- pdfview.exe
  this is a NSIS script, which calls users standard pdf viewer to display pdf files you compile with
  LaTeX using LyX, its source is available in %%lyxgit%%\development\Win32\pdfview

Note: if you update any dependencies, please add a note to ChangeLog.txt