//------------------------------------------------------------------------------
/// \file config.h.in
//
// Author(s):
//    Frank Tackmann
//
// Copyright:
//    Copyright (C) 2012 MIT, Frank Tackmann
//
//    This file is part of the Geneva MC framework. Geneva is distributed under
//    the terms of the GNU General Public License version 3 (GPLv3), see the
//    COPYING file that comes with this distribution for details.
//    Please respect the academic usage guidelines in the GUIDELINES file.
//
// Description:
//    Options and settings configured by cmake
//------------------------------------------------------------------------------

// version
#define GENEVA_VERSION_MAJOR 0
#define GENEVA_VERSION_MINOR 1

// location
#define GENEVA_ROOT "/Users/Hannes/Documents/Geneva/trunk"
#define GENEVA_DATADIR "/Users/Hannes/Documents/Geneva/trunk/data"

// default precision and accuracy for comparing doubles
#define DEFAULT_PRECISION 1e-10
#define DEFAULT_ACCURACY 1e-10

// FIXME: Assume for now that we have a wrong gamma function, should check
// and set this eventually with cmake
#define FIX_WRONG_GAMMA
/* #undef C99_GAMMA_THROW */

// flag whether to generate floating point exceptions at OS level
/* #undef TRAP_FPE */

// flag to use gsl
#define USE_GSL

// flag to use madgraph
#define USE_MADGRAPH

// flag to use lhapdf
#define USE_LHAPDF

// flag to use pythia8
#define USE_PYTHIA8
// pythia data dir
#define PYTHIA8_DATA_DIR "pythia8_DATA_DIR-NOTFOUND"

// flag to use fastjet
/* #undef USE_FASTJET */

// flag to use NJET2
/* #undef USE_NJET2 */

#define EXTERNAL_BIN_PATH  "/Users/Hannes/Documents/Geneva/trunk/external/bin"
