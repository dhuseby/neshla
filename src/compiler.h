/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software.
 * You may use this code for anything you wish.
 * It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/
#ifndef compilerH
#define compilerH
/******************************************************************************/
#define SZ_LEGACY_VERSION      "1.0.0"
#define SZ_LEGACY_BUILD_DATE   "April 12th, 2005" //"December 19th, 2003"
#define SZ_VERSION  "1.0.1"
#define SZ_BUILD_DATE "August 3rd 2009"

/******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

#include "typedefs.h"

#include "message.h"
#include "memalloc.h"
#include "fileio.h"
#include "config.h"

#include "init.h"
#include "list.h"
#include "strhand.h"
#include "scrbase.h"

#include "opcodes.h"
#include "opcodetable.h"

#include "getcode.h"

#include "prepbase.h"

#include "vars.h"
#include "functions.h"
#include "labels.h"

#include "outbuf.h"
#include "fixoffs.h"
#include "writecode.h"
#include "scrbin.h"
#include "banks.h"

#include "data.h"

/******************************************************************************/
#define STRCMP ssStrCmp
/******************************************************************************/
BOOL DoCompile(char *szFilename);
/******************************************************************************/
#endif
/******************************************************************************/
