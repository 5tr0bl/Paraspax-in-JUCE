/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== LICENSE ==================
static const unsigned char temp_binary_data_2[] =
"Copyright (c) 2016-2017, Symonics GmbH, Christian Hoene\n"
"All rights reserved.\n"
"\n"
"Redistribution and use in source and binary forms, with or without\n"
"modification, are permitted provided that the following conditions are\n"
"met:\n"
"\n"
"    (1) Redistributions of source code must retain the above copyright\n"
"    notice, this list of conditions and the following disclaimer. \n"
"\n"
"    (2) Redistributions in binary form must reproduce the above copyright\n"
"    notice, this list of conditions and the following disclaimer in\n"
"    the documentation and/or other materials provided with the\n"
"    distribution.  \n"
"    \n"
"    (3)The name of the author may not be used to\n"
"    endorse or promote products derived from this software without\n"
"    specific prior written permission.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR\n"
"IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
"WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n"
"DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,\n"
"INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n"
"(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR\n"
"SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)\n"
"HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,\n"
"STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING\n"
"IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE\n"
"POSSIBILITY OF SUCH DAMAGE.\n"
"\n";

const char* LICENSE = (const char*) temp_binary_data_2;

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_3[] =
"\n"
"# Source\n"
"target_sources(${PROJECT_NAME}\n"
"PRIVATE\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_sofa_reader.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/mysofa.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/internal/hdf_dataobject.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/internal/hdf_fractalhead.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/internal/hdf_reader.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/internal/kdtree.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/libmysofa/internal/mysofa_internal.c\n"
")\n";

const char* CMakeLists_txt = (const char*) temp_binary_data_3;

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_4[] =
"\n"
"# Source for core SAF modules\n"
"target_sources(${PROJECT_NAME}\n"
"PRIVATE\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_cdf4sap/saf_cdf4sap.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_hoa/saf_hoa_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_hoa/saf_hoa_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_hoa/saf_hoa.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_hrir/saf_default_hrirs.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_hrir/saf_hrir.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_reverb/saf_reverb_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_reverb/saf_reverb_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_reverb/saf_reverb.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_sh/saf_sh_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_sh/saf_sh_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_sh/saf_sh.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_bessel.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_complex.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_decor.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_fft.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_filters.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_geometry.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_latticeCoeffs.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_loudspeaker_presets.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_matrixConv.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_misc.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_pitch.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_qmf.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_sensorarray_presets.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_sort.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_veclib.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_utilities/saf_utility_dvf.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_vbap/saf_vbap_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_vbap/saf_vbap_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/saf_vbap/saf_vbap.c\n"
")\n"
"\n"
"# Source for optional SAF modules\n"
"if(SAF_ENABLE_SOFA_READER_MODULE)\n"
"    add_subdirectory(saf_sofa_reader)\n"
"endif()\n"
"if(SAF_ENABLE_TRACKER_MODULE)\n"
"    target_sources(${PROJECT_NAME}\n"
"    PRIVATE\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker_internal.c\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker_internal.h\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_tracker/saf_tracker.c\n"
"    )\n"
"endif()\n"
"if(SAF_ENABLE_HADES_MODULE)\n"
"    target_sources(${PROJECT_NAME}\n"
"    PRIVATE\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_hades/saf_hades_analysis.c\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_hades/saf_hades_internal.h\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_hades/saf_hades_internal.c\n"
"        ${CMAKE_CURRENT_SOURCE_DIR}/saf_hades/saf_hades_synthesis.c\n"
"    )\n"
"endif()\n";

const char* CMakeLists_txt2 = (const char*) temp_binary_data_4;

//================== LICENSE.txt ==================
static const unsigned char temp_binary_data_5[] =
"The MIT License (MIT)\n"
"\n"
"Copyright (c) 2015 Juha Vilkamo (juha.vilkamo@aalto.fi)\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n"
"\n";

const char* LICENSE_txt = (const char*) temp_binary_data_5;

//================== LICENSE ==================
static const unsigned char temp_binary_data_6[] =
"The MIT License (MIT)\n"
"\n"
"Copyright (c) 2017-18 Leo McCormack (leo.mccormack@aalto.fi)\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n"
"\n";

const char* LICENSE2 = (const char*) temp_binary_data_6;

//================== COPYING.txt ==================
static const unsigned char temp_binary_data_7[] =
"Copyright (c) 2003-2010 Mark Borgerding . All rights reserved.\n"
"\n"
"KISS FFT is provided under:\n"
"\n"
"  SPDX-License-Identifier: BSD-3-Clause\n"
"\n"
"Being under the terms of the BSD 3-clause \"New\" or \"Revised\" License,\n"
"according with:\n"
"\n"
"  LICENSES/BSD-3-Clause\n"
"\n";

const char* COPYING_txt = (const char*) temp_binary_data_7;

//================== LICENSE ==================
static const unsigned char temp_binary_data_8[] =
"MIT License\n"
"\n"
"Copyright (c) 2019 Leo McCormack\n"
"\n"
"Permission is hereby granted, free of charge, to any person obtaining a copy\n"
"of this software and associated documentation files (the \"Software\"), to deal\n"
"in the Software without restriction, including without limitation the rights\n"
"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
"copies of the Software, and to permit persons to whom the Software is\n"
"furnished to do so, subject to the following conditions:\n"
"\n"
"The above copyright notice and this permission notice shall be included in all\n"
"copies or substantial portions of the Software.\n"
"\n"
"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
"SOFTWARE.\n";

const char* LICENSE3 = (const char*) temp_binary_data_8;

//================== COPYING ==================
static const unsigned char temp_binary_data_9[] =
"Copyright 2002-2008 \tXiph.org Foundation\n"
"Copyright 2002-2008 \tJean-Marc Valin\n"
"Copyright 2005-2007\tAnalog Devices Inc.\n"
"Copyright 2005-2008\tCommonwealth Scientific and Industrial Research \n"
"                        Organisation (CSIRO)\n"
"Copyright 1993, 2002, 2006 David Rowe\n"
"Copyright 2003 \t\tEpicGames\n"
"Copyright 1992-1994\tJutta Degener, Carsten Bormann\n"
"\n"
"Redistribution and use in source and binary forms, with or without\n"
"modification, are permitted provided that the following conditions\n"
"are met:\n"
"\n"
"- Redistributions of source code must retain the above copyright\n"
"notice, this list of conditions and the following disclaimer.\n"
"\n"
"- Redistributions in binary form must reproduce the above copyright\n"
"notice, this list of conditions and the following disclaimer in the\n"
"documentation and/or other materials provided with the distribution.\n"
"\n"
"- Neither the name of the Xiph.org Foundation nor the names of its\n"
"contributors may be used to endorse or promote products derived from\n"
"this software without specific prior written permission.\n"
"\n"
"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n"
"``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n"
"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR\n"
"A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR\n"
"CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,\n"
"EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,\n"
"PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR\n"
"PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF\n"
"LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING\n"
"NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS\n"
"SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n";

const char* COPYING = (const char*) temp_binary_data_9;

//================== README ==================
static const unsigned char temp_binary_data_10[] =
"ZLIB DATA COMPRESSION LIBRARY\r\n"
"\r\n"
"zlib 1.2.11 is a general purpose data compression library.  All the code is\r\n"
"thread safe.  The data format used by the zlib library is described by RFCs\r\n"
"(Request for Comments) 1950 to 1952 in the files\r\n"
"http://tools.ietf.org/html/rfc1950 (zlib format), rfc1951 (deflate format) and\r\n"
"rfc1952 (gzip format).\r\n"
"\r\n"
"All functions of the compression library are documented in the file zlib.h\r\n"
"(volunteer to write man pages welcome, contact zlib@gzip.org).  A usage example\r\n"
"of the library is given in the file test/example.c which also tests that\r\n"
"the library is working correctly.  Another example is given in the file\r\n"
"test/minigzip.c.  The compression library itself is composed of all source\r\n"
"files in the root directory.\r\n"
"\r\n"
"To compile all files and run the test program, follow the instructions given at\r\n"
"the top of Makefile.in.  In short \"./configure; make test\", and if that goes\r\n"
"well, \"make install\" should work for most flavors of Unix.  For Windows, use\r\n"
"one of the special makefiles in win32/ or contrib/vstudio/ .  For VMS, use\r\n"
"make_vms.com.\r\n"
"\r\n"
"Questions about zlib should be sent to <zlib@gzip.org>, or to Gilles Vollant\r\n"
"<info@winimage.com> for the Windows DLL version.  The zlib home page is\r\n"
"http://zlib.net/ .  Before reporting a problem, please check this site to\r\n"
"verify that you have the latest version of zlib; otherwise get the latest\r\n"
"version and check whether the problem still exists or not.\r\n"
"\r\n"
"PLEASE read the zlib FAQ http://zlib.net/zlib_faq.html before asking for help.\r\n"
"\r\n"
"Mark Nelson <markn@ieee.org> wrote an article about zlib for the Jan.  1997\r\n"
"issue of Dr.  Dobb's Journal; a copy of the article is available at\r\n"
"http://marknelson.us/1997/01/01/zlib-engine/ .\r\n"
"\r\n"
"The changes made in version 1.2.11 are documented in the file ChangeLog.\r\n"
"\r\n"
"Unsupported third party contributions are provided in directory contrib/ .\r\n"
"\r\n"
"zlib is available in Java using the java.util.zip package, documented at\r\n"
"http://java.sun.com/developer/technicalArticles/Programming/compression/ .\r\n"
"\r\n"
"A Perl interface to zlib written by Paul Marquess <pmqs@cpan.org> is available\r\n"
"at CPAN (Comprehensive Perl Archive Network) sites, including\r\n"
"http://search.cpan.org/~pmqs/IO-Compress-Zlib/ .\r\n"
"\r\n"
"A Python interface to zlib written by A.M. Kuchling <amk@amk.ca> is\r\n"
"available in Python 1.5 and later versions, see\r\n"
"http://docs.python.org/library/zlib.html .\r\n"
"\r\n"
"zlib is built into tcl: http://wiki.tcl.tk/4610 .\r\n"
"\r\n"
"An experimental package to read and write files in .zip format, written on top\r\n"
"of zlib by Gilles Vollant <info@winimage.com>, is available in the\r\n"
"contrib/minizip directory of zlib.\r\n"
"\r\n"
"\r\n"
"Notes for some targets:\r\n"
"\r\n"
"- For Windows DLL versions, please see win32/DLL_FAQ.txt\r\n"
"\r\n"
"- For 64-bit Irix, deflate.c must be compiled without any optimization. With\r\n"
"  -O, one libpng test fails. The test works in 32 bit mode (with the -n32\r\n"
"  compiler flag). The compiler bug has been reported to SGI.\r\n"
"\r\n"
"- zlib doesn't work with gcc 2.6.3 on a DEC 3000/300LX under OSF/1 2.1 it works\r\n"
"  when compiled with cc.\r\n"
"\r\n"
"- On Digital Unix 4.0D (formely OSF/1) on AlphaServer, the cc option -std1 is\r\n"
"  necessary to get gzprintf working correctly. This is done by configure.\r\n"
"\r\n"
"- zlib doesn't work on HP-UX 9.05 with some versions of /bin/cc. It works with\r\n"
"  other compilers. Use \"make test\" to check your compiler.\r\n"
"\r\n"
"- gzdopen is not supported on RISCOS or BEOS.\r\n"
"\r\n"
"- For PalmOs, see http://palmzlib.sourceforge.net/\r\n"
"\r\n"
"\r\n"
"Acknowledgments:\r\n"
"\r\n"
"  The deflate format used by zlib was defined by Phil Katz.  The deflate and\r\n"
"  zlib specifications were written by L.  Peter Deutsch.  Thanks to all the\r\n"
"  people who reported problems and suggested various improvements in zlib; they\r\n"
"  are too numerous to cite here.\r\n"
"\r\n"
"Copyright notice:\r\n"
"\r\n"
" (C) 1995-2017 Jean-loup Gailly and Mark Adler\r\n"
"\r\n"
"  This software is provided 'as-is', without any express or implied\r\n"
"  warranty.  In no event will the authors be held liable for any damages\r\n"
"  arising from the use of this software.\r\n"
"\r\n"
"  Permission is granted to anyone to use this software for any purpose,\r\n"
"  including commercial applications, and to alter it and redistribute it\r\n"
"  freely, subject to the following restrictions:\r\n"
"\r\n"
"  1. The origin of this software must not be misrepresented; you must not\r\n"
"     claim that you wrote the original software. If you use this software\r\n"
"     in a product, an acknowledgment in the product documentation would be\r\n"
"     appreciated but is not required.\r\n"
"  2. Altered source versions must be plainly marked as such, and must not be\r\n"
"     misrepresented as being the original software.\r\n"
"  3. This notice may not be removed or altered from any source distribution.\r\n"
"\r\n"
"  Jean-loup Gailly        Mark Adler\r\n"
"  jloup@gzip.org          madler@alumni.caltech.edu\r\n"
"\r\n"
"If you use the zlib library in a product, we would appreciate *not* receiving\r\n"
"lengthy legal documents to sign.  The sources are provided for free but without\r\n"
"warranty of any kind.  The library has been entirely written by Jean-loup\r\n"
"Gailly and Mark Adler; it does not include third-party code.\r\n"
"\r\n"
"If you redistribute modified sources, we would appreciate that you include in\r\n"
"the file ChangeLog history information documenting your changes.  Please read\r\n"
"the FAQ for more information on the distribution of modified source versions.\r\n";

const char* README = (const char*) temp_binary_data_10;

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_11[] =
"# Source\n"
"target_sources(${PROJECT_NAME}\n"
"PRIVATE\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/afSTFT/afSTFT_protoFilter.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/afSTFT/afSTFTlib.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/afSTFT/afSTFT_internal.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/afSTFT/afSTFT_internal.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/convhull_3d/convhull_3d.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/kissFFT/_kiss_fft_guts.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/kissFFT/kiss_fft.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/kissFFT/kiss_fftr.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/md_malloc/md_malloc.c\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/arch.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/os_support.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/resample_neon.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/resample_sse.h\r   "
" ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/resample.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/speex_resampler.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/speex_resampler/speexdsp_types.h\n"
"    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/adler32.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/compress.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/crc32.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/crc32.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/deflate.c\r    ${CMAKE_C"
"URRENT_SOURCE_DIR}/zlib/deflate.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/infback.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inffast.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inffast.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inffixed.h\r    ${CMAKE_CURRENT_SO"
"URCE_DIR}/zlib/inflate.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inflate.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inftrees.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/inftrees.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/trees.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/"
"zlib/trees.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/uncompr.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zconf.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zlib.h\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zutil.c\r    ${CMAKE_CURRENT_SOURCE_DIR}/zlib/zutil.h\n"
")\n";

const char* CMakeLists_txt3 = (const char*) temp_binary_data_11;

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_12[] =
"cmake_minimum_required(VERSION 3.15)\n"
"#include(CheckIncludeFiles) # For some reason this causes an error on windows...\n"
"\n"
"# Check required variables are defined\n"
"if(NOT DEFINED SAF_PERFORMANCE_LIB AND NOT APPLE)\n"
"    message(FATAL_ERROR \"You must define the SAF_PERFORMANCE_LIB environment variable\")\n"
"endif()\n"
"if(NOT DEFINED SAF_PERFORMANCE_LIB AND APPLE)\n"
"    set(SAF_PERFORMANCE_LIB \"SAF_USE_APPLE_ACCELERATE\")\n"
"endif()\n"
"\n"
"# Pull version number from the framework's main header file:\n"
"file(READ \"include/saf.h\" ver)\n"
"string(REGEX MATCH \"SAF_VERSION_MAJOR ([0-9]*)\" _ ${ver})\n"
"set(ver_major ${CMAKE_MATCH_1})\n"
"string(REGEX MATCH \"SAF_VERSION_MINOR ([0-9]*)\" _ ${ver})\n"
"set(ver_minor ${CMAKE_MATCH_1})\n"
"string(REGEX MATCH \"SAF_VERSION_PATCH ([0-9]*)\" _ ${ver})\n"
"set(ver_patch ${CMAKE_MATCH_1})\n"
"set(SAF_VERSION \"${ver_major}.${ver_minor}.${ver_patch}\")\n"
"\n"
"# Display License\n"
"if(SAF_ENABLE_TRACKER_MODULE)\n"
"    set(SAF_LICENSE \"GNU GPLv2\")\n"
"else()\n"
"    set(SAF_LICENSE \"ISC\")\n"
"endif()\n"
"\n"
"# SAF Banner:\n"
"message(\"\n"
"     _____     _____     _____\n"
"   (  ____ ) (  ___  ) (  ____ )\n"
"   | ( __ |/ | ( _ ) | | ( _  |/\n"
"   (_____  ) |  ___  | |  __)\n"
"   /|____) | | |   | | | |\n"
"   (_______) |_|   |_| |_|   (Version: ${SAF_VERSION}, License: ${SAF_LICENSE})\n"
"\")\n"
"\n"
"# Configure SAF\n"
"message(STATUS \"Configuring the Spatial_Audio_Framework (SAF):\")\n"
"\n"
"if(SAF_ENABLE_SIMD) # before declaring project, set compilation flags for SIMD support\n"
"    set(CMAKE_CXX_FLAGS \"${CMAKE_C_FLAGS}   -march=native\" CACHE STRING \"Default C options\"   FORCE)\n"
"    set(CMAKE_C_FLAGS   \"${CMAKE_CXX_FLAGS} -march=native\" CACHE STRING \"Default CXX options\" FORCE)\n"
"endif()\n"
"\n"
"project(saf VERSION ${SAF_VERSION} LANGUAGES C)\n"
"add_library(${PROJECT_NAME}) #STATIC\n"
"set_target_properties(${PROJECT_NAME}\n"
"PROPERTIES\n"
"    VERSION ${PROJECT_VERSION}\n"
"    SOVERSION ${PROJECT_VERSION} \n"
")\n"
"\n"
"# Display system and configuration info\n"
"message(STATUS \"${CMAKE_SYSTEM_INFO_FILE}, name: ${CMAKE_SYSTEM_NAME}, arch: ${CMAKE_SYSTEM_PROCESSOR}, sys: ${CMAKE_SYSTEM}\")\n"
"if(BUILD_SHARED_LIBS)\n"
"    message(STATUS \"Configuring ${PROJECT_NAME} as a SHARED library...\")\n"
"else()\n"
"    message(STATUS \"Configuring ${PROJECT_NAME} as a STATIC library...\")\n"
"endif()\n"
"\n"
"# Framework include paths\n"
"target_include_directories(${PROJECT_NAME} \n"
"PUBLIC\n"
"    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>\n"
"    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>\n"
")\n"
"include(GNUInstallDirs)\n"
"\n"
"# Framework source files\n"
"add_subdirectory(modules)\n"
"add_subdirectory(resources)\n"
"\n"
"# set(SAF_PERFORMANCE_LIB \"SAF_USE_OPEN_BLAS_AND_LAPACKE\" CACHE STRING \"Performance library for SAF to use.\")\n"
"\n"
"############################################################################\n"
"# Performance library dependencies\n"
"if( ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_INTEL_MKL_LP64\" OR ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_INTEL_MKL_ILP64\")\n"
"   \n"
"    # Default header path and libs, (which are platform dependent):\n"
"    if(NOT DEFINED INTEL_MKL_HEADER_PATH)\n"
"        if(MSVC)\n"
"            set(INTEL_MKL_HEADER_PATH \"C:/Program Files (x86)/Intel/oneAPI/mkl/latest/include\") \n"
"        elseif(MSYS OR MINGW) \n"
"            set(INTEL_MKL_HEADER_PATH \"/c/Program Files (x86)/Intel/oneAPI/mkl/latest/include\") \n"
"        elseif(APPLE)\n"
"            set(INTEL_MKL_HEADER_PATH \"/opt/intel/oneapi/mkl/latest/include\")\n"
"        elseif(UNIX AND NOT APPLE)\n"
"            if(EXISTS \"/opt/intel/oneapi/mkl/latest/include\")\n"
"                set(INTEL_MKL_HEADER_PATH \"/opt/intel/oneapi/mkl/latest/include\")\n"
"            else()\n"
"                message(SEND_ERROR \"Intel mkl.h default path not found, please specify!\")\n"
"            endif()\n"
"        endif()\n"
"    endif()\n"
"    if ( ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_INTEL_MKL_LP64\" )\n"
"        target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_INTEL_MKL_LP64=1)\n"
"\n"
"        if (NOT DEFINED INTEL_MKL_LIB)\n"
"            if(MSVC)\n"
"                set(INTEL_MKL_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_mkl_custom_lp64.lib\")\n"
"            elseif(MSYS OR MINGW)\n"
"                set(INTEL_MKL_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_mkl_custom_lp64.lib\")\n"
"            elseif(APPLE)\n"
"                set(INTEL_MKL_LIB \"/usr/local/lib/libsaf_mkl_custom_lp64.dylib\")\n"
"            elseif(UNIX AND NOT APPLE)\n"
"                set(INTEL_MKL_LIB \"/usr/local/lib/libsaf_mkl_custom_lp64.so\")\n"
"            endif()\n"
"        endif()\n"
"\n"
"    else()\n"
"        target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_INTEL_MKL_ILP64=1)\n"
"\n"
"        if (NOT DEFINED INTEL_MKL_LIB)\n"
"            if(MSVC)\n"
"                set(INTEL_MKL_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_mkl_custom_ilp64.lib\")\n"
"            elseif(MSYS OR MINGW)\n"
"                set(INTEL_MKL_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_mkl_custom_ilp64.lib\")\n"
"            elseif(APPLE)\n"
"                set(INTEL_MKL_LIB \"/usr/local/lib/libsaf_mkl_custom_ilp64.dylib\")\n"
"            elseif(UNIX AND NOT APPLE)\n"
"                set(INTEL_MKL_LIB \"/usr/local/lib/libsaf_mkl_custom_ilp64.so\")\n"
"            endif()\n"
"        endif()\n"
"    endif()\n"
"\n"
"    message(STATUS \"SAF_PERFORMANCE_LIB: ${SAF_PERFORMANCE_LIB}\")\n"
"    if (NOT EXISTS \"${INTEL_MKL_HEADER_PATH}/mkl.h\")\n"
"        message(SEND_ERROR \"Intel mkl.h not found\")\n"
"    endif()\n"
"    message(STATUS \"Using Intel MKL. Linking against: ${INTEL_MKL_LIB}\")\n"
"\n"
"    # Add target header paths and libs\n"
"    target_include_directories(${PROJECT_NAME} PUBLIC ${INTEL_MKL_HEADER_PATH} )\n"
"    target_link_libraries(${PROJECT_NAME} PUBLIC ${INTEL_MKL_LIB} )\n"
"\n"
"elseif( ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_OPEN_BLAS_AND_LAPACKE\")\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_OPEN_BLAS_AND_LAPACKE=1)\n"
"\n"
"    set(OPENBLAS_LIBRARY \"C:/Users/Micha/source/repos/OpenBLAS-0.3.24-x64/lib/libopenblas.lib\")\n"
"    message(STATUS \"OPENBLAS_LIBRARY: ${OPENBLAS_LIBRARY}\")\n"
"    # find and link libraries\n"
"    if (NOT DEFINED OPENBLAS_LIBRARY)\n"
"        find_library(OPENBLAS_LIBRARY openblas HINTS \"C:/Users/Micha/source/repos/OpenBLAS-0.3.24-x64/lib/libopenblas.lib\")\n"
"        \n"
"    endif()\n"
"\n"
"    set(LAPACKE_LIBRARY \"C:/Users/Micha/source/repos/OpenBLAS-0.3.24-x64/lib/libopenblas.lib\")\n"
"    if (NOT DEFINED LAPACKE_LIBRARY)\n"
"        find_library(LAPACKE_LIBRARY lapacke HINTS \"C:/Users/Micha/source/repos/OpenBLAS-0.3.24-x64/lib/libopenblas.lib\")\n"
"    endif()\n"
"    target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENBLAS_LIBRARY} ${LAPACKE_LIBRARY})\n"
"\n"
"    # Add header search paths if they are defined\n"
"    if(DEFINED OPENBLAS_HEADER_PATH)\n"
"        target_include_directories(${PROJECT_NAME} PUBLIC ${OPENBLAS_HEADER_PATH})\n"
"    endif()\n"
"    if(DEFINED LAPACKE_HEADER_PATH)\n"
"        target_include_directories(${PROJECT_NAME} PUBLIC ${LAPACKE_HEADER_PATH})\n"
"    endif()\n"
"\n"
"    # Disable this particular warning... We know, but it's OK.\n"
"    if(UNIX)\n"
"        target_compile_options(${PROJECT_NAME} PRIVATE -Wno-incompatible-pointer-types)\n"
"    endif()\n"
"    \n"
"    message(STATUS \"Using OpenBLAS. Linking against: ${OPENBLAS_LIBRARY}; ${LAPACKE_LIBRARY}\")\n"
"\n"
"elseif( ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_ATLAS\")\n"
"    message(STATUS \"Using ATLAS...\")\n"
"    message(SEND_ERROR \"Not yet supported! Please contribute if you use this library.\")\n"
"\n"
"elseif(APPLE AND ${SAF_PERFORMANCE_LIB} MATCHES \"SAF_USE_APPLE_ACCELERATE\")\n"
"    message(STATUS \"Using Apple Accelerate. Linking against the Accelerate framework...\")\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_APPLE_ACCELERATE=1) \n"
"    target_link_libraries(${PROJECT_NAME} PUBLIC \"-framework Accelerate\") \n"
"\n"
"else()\n"
"    message(SEND_ERROR \"The specified SAF_PERFORMANCE_LIB is not supported\")\n"
"\n"
"endif()\n"
"\n"
"############################################################################\n"
"# Enable/Disable Intel IPP\n"
"if(SAF_USE_INTEL_IPP)\n"
"\n"
"    # Default header path and libs, (which are platform dependent):\n"
"    if(NOT DEFINED INTEL_IPP_HEADER_PATH)\n"
"        if(MSVC)\n"
"            set(INTEL_IPP_HEADER_PATH \"C:/Program Files (x86)/Intel/oneAPI/ipp/latest/include\") \n"
"        elseif(MSYS OR MINGW) \n"
"            set(INTEL_IPP_HEADER_PATH \"/c/Program Files (x86)/Intel/oneAPI/ipp/latest/include\") \n"
"        elseif(APPLE)\n"
"            set(INTEL_IPP_HEADER_PATH \"/opt/intel/oneapi/ipp/latest/include\")\n"
"        elseif(UNIX AND NOT APPLE)\n"
"            if(EXISTS \"/opt/intel/oneapi/ipp/latest/include\")\n"
"                set(INTEL_IPP_HEADER_PATH \"/opt/intel/oneapi/ipp/latest/include\")\n"
"            else()\n"
"                message(SEND_ERROR \"Intel ipp.h default path not found, please specify!\")\n"
"            endif()\n"
"        endif()\n"
"    endif()\n"
"\n"
"    if (NOT DEFINED INTEL_IPP_LIB)\n"
"        if(MSVC)\n"
"            set(INTEL_IPP_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_ipp_custom.lib\")\n"
"        elseif(MSYS OR MINGW)\n"
"            set(INTEL_IPP_LIB \"${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/saf_ipp_custom.lib\")\n"
"        elseif(APPLE)\n"
"            set(INTEL_IPP_LIB \"/usr/local/lib/libsaf_ipp_custom.dylib\")\n"
"        elseif(UNIX AND NOT APPLE)\n"
"            set(INTEL_IPP_LIB \"/usr/local/lib/libsaf_ipp_custom.so\")\n"
"        endif()\n"
"    endif()\n"
"\n"
"\n"
"    if (NOT EXISTS \"${INTEL_IPP_HEADER_PATH}/ipp.h\")\n"
"        message(SEND_ERROR \"Intel ipp.h not found\")\n"
"    endif()\n"
"    message(STATUS \"Using Intel IPP. Linking against: ${INTEL_IPP_LIB}\")\n"
"\n"
"    # Add target header paths and libs\n"
"    target_include_directories(${PROJECT_NAME} PUBLIC ${INTEL_IPP_HEADER_PATH} )\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_INTEL_IPP=1)\n"
"    target_link_libraries(${PROJECT_NAME} PUBLIC ${INTEL_IPP_LIB} )\n"
"endif()\n"
"\n"
"############################################################################\n"
"# Enable/Disable FFTW\n"
"if(SAF_USE_FFTW)\n"
"    # Indicate to saf that the saf_sofa_reader module should be enabled\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_USE_FFTW=${SAF_USE_FFTW})\n"
"        \n"
"    # Header path and libs are platform dependent\n"
"    if(MSVC)\n"
"        message(FATAL_ERROR \"Incomplete list\")\n"
"    elseif(MSYS OR MINGW)\n"
"        message(FATAL_ERROR \"Incomplete list\")\n"
"    elseif(APPLE) \n"
"        message(FATAL_ERROR \"Incomplete list\")\n"
"    elseif(UNIX AND NOT APPLE) \n"
"        find_library(FFTW_LIBRARY fftw3f HINTS /usr/local/lib)\n"
"        if (NOT FFTW_LIBRARY)\n"
"            message(FATAL_ERROR \"FFTW_LIBRARY not found\")\n"
"        endif()\n"
"        target_link_libraries(${PROJECT_NAME} PUBLIC ${FFTW_LIBRARY})\n"
"        message(STATUS \"Linking FFTW: ${FFTW_LIBRARY}\")\n"
"    endif() \n"
"endif()\n"
"\n"
"############################################################################\n"
"# Enable SIMD intrinsics\n"
"if(SAF_ENABLE_SIMD)\n"
"    # Note: appropriate compiler flags were previously added before declaration of project \n"
"    message(STATUS \"SIMD intrinsics support is enabled.\")\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_ENABLE_SIMD=1)\n"
"endif()\n"
"\n"
"############################################################################\n"
"# Sofa reader module dependencies\n"
"if(SAF_ENABLE_SOFA_READER_MODULE)\n"
"    message(STATUS \"saf_sofa_reader module enabled.\")\n"
"\n"
"    # Indicate to saf that the saf_sofa_reader module should be enabled\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_ENABLE_SOFA_READER_MODULE=${SAF_ENABLE_SOFA_READER_MODULE})\n"
"\n"
"    if(SAF_ENABLE_NETCDF)\n"
"        message(STATUS \"netcdf enabled for saf_sofa_reader module. Linking against netcdf...\")\n"
"        target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_ENABLE_NETCDF=${SAF_ENABLE_NETCDF})\n"
"        \n"
"        # Header path and libs are platform dependent\n"
"        if(MSVC)\n"
"            # Link NetCDF dependencies (HDF5 and its dependencies: zlib,szip):\n"
"            if(SAF_HDF5_INCLUDE_DIR AND SAF_HDF5_LIB_DIR)\n"
"                target_include_directories(${PROJECT_NAME} PUBLIC ${SAF_HDF5_INCLUDE_DIR})\n"
"                set(SAF_HDF5_LIBS\n"
"                    ${SAF_HDF5_LIB_DIR}/libhdf5.lib\n"
"                    ${SAF_HDF5_LIB_DIR}/libzlib.lib\n"
"                    ${SAF_HDF5_LIB_DIR}/libszip.lib\n"
"                    ${SAF_HDF5_LIB_DIR}/libhdf5_hl.lib\n"
"                )\n"
"            else()\n"
"                target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/include)\n"
"                set(SAF_HDF5_LIBS\n"
"                    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/libzlib.lib\n"
"                ) \n"
"                set(SAF_HDF5_LIBS ${SAF_HDF5_LIBS}\n"
"                    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/libhdf5.lib\n"
"                    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/libszip.lib\n"
"                    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/libhdf5_hl.lib\n"
"                )\n"
"            endif()\n"
"            target_link_libraries(${PROJECT_NAME} PRIVATE ${SAF_HDF5_LIBS})\n"
"            message(STATUS \"Linking HDF5: ${SAF_HDF5_LIBS}\")\n"
"\n"
"            # Link NetCDF\n"
"            if(SAF_NETCDF_INCLUDE_DIR AND SAF_NETCDF_LIB_DIR)\n"
"                target_include_directories(${PROJECT_NAME} PUBLIC ${SAF_NETCDF_INCLUDE_DIR})\n"
"                set(SAF_NETCDF_LIBS ${SAF_NETCDF_LIB_DIR}/netcdf.lib)\n"
"            else()\n"
"                target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/include)\n"
"                set(SAF_NETCDF_LIBS ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/Win64/lib/netcdf.lib)\n"
"            endif()\n"
"            target_link_libraries(${PROJECT_NAME} PRIVATE ${SAF_NETCDF_LIBS})\n"
"            message(STATUS \"Linking NETCDF: ${SAF_NETCDF_LIBS}\")\n"
"            \n"
"        elseif(MSYS OR MINGW)\n"
"            message(SEND_ERROR \"Currently unsupported on MSYS\")\n"
"\n"
"        elseif(APPLE) \n"
"            if (SAF_NETCDF_INCLUDE_DIR AND SAF_NETCDF_LIBRARIES)\n"
"                 message(STATUS \"Using NetCDF include dir ${SAF_NETCDF_INCLUDE_DIR} and libraries ${SAF_NETCDF_LIBRARIES}\")\n"
"                 target_include_directories(${PROJECT_NAME} PUBLIC ${SAF_NETCDF_INCLUDE_DIR})\n"
"                 target_link_libraries(${PROJECT_NAME} PRIVATE ${SAF_NETCDF_LIBRARIES})\n"
"             else()\n"
"                 target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/MacOSX/include)\n"
"                 target_link_libraries(${PROJECT_NAME}\n"
"                 PRIVATE\n"
"                     ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/MacOSX/lib/libz.a\n"
"                 )\n"
"                 target_link_libraries(${PROJECT_NAME}\n"
"                 PRIVATE\n"
"                     ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/MacOSX/lib/libnetcdf.a\n"
"                     ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/MacOSX/lib/libhdf5.a\n"
"                     ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/MacOSX/lib/libhdf5_hl.a\n"
"                 )\n"
"             endif()\n"
"\n"
"        elseif(UNIX AND NOT APPLE)\n"
"            find_library(NETCDF_LIBRARY netcdf HINTS HINTS /usr/lib/x86_64-linux-gnu /usr/lib/arm-linux-gnueabihf)\n"
"            if (NOT NETCDF_LIBRARY)\n"
"                message(FATAL_ERROR \"NETCDF_LIBRARY not found\")\n"
"            endif()\n"
"            target_link_libraries(${PROJECT_NAME} PUBLIC ${NETCDF_LIBRARY})\n"
"            message(STATUS \"Linking NETCDF: ${NETCDF_LIBRARY}\")\n"
"\n"
"        endif() \n"
"    endif() \n"
"else()\n"
"    message(STATUS \"saf_sofa_reader module disabled.\")\n"
"endif()\n"
"\n"
"\n"
"############################################################################\n"
"# Enable/Disable tracker module\n"
"if(SAF_ENABLE_TRACKER_MODULE)\n"
"    message(STATUS \"saf_tracker module enabled. \")\n"
"\n"
"    # Indicate to saf that the saf_tracker module should be enabled\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_ENABLE_TRACKER_MODULE=${SAF_ENABLE_TRACKER_MODULE})\n"
"\n"
"else()\n"
"    message(STATUS \"saf_tracker module disabled.\")\n"
"endif()\n"
"\n"
"############################################################################\n"
"# Enable/Disable HADES module\n"
"if(SAF_ENABLE_HADES_MODULE)\n"
"    message(STATUS \"saf_hades module enabled. \")\n"
"\n"
"    # Indicate to saf that the saf_hades module should be enabled\n"
"    target_compile_definitions(${PROJECT_NAME} PUBLIC SAF_ENABLE_HADES_MODULE=${SAF_ENABLE_HADES_MODULE})\n"
"\n"
"else()\n"
"    message(STATUS \"saf_hades module disabled.\")\n"
"endif()\n"
"\n"
"\n"
"############################################################################\n"
"# Extra compiler flags\n"
"if(UNIX)\n"
"    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)\n"
"endif()\n"
"if(SAF_ENABLE_FAST_MATH_FLAG)\n"
"    if((CMAKE_CXX_COMPILER_ID MATCHES \"Clang\") OR (CMAKE_CXX_COMPILER_ID MATCHES \"GNU\"))\n"
"        add_compile_options(-ffast-math)\n"
"    endif()\n"
"endif()\n"
"\n"
"\n"
"############################################################################\n"
"# set RPATHs\n"
"set(CMAKE_INSTALL_RPATH $ORIGIN)\n";

const char* CMakeLists_txt4 = (const char*) temp_binary_data_12;
}