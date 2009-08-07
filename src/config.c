/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

#include <stdlib.h>
#include <getopt.h>
#include "compiler.h"


/******************************************************************************
 * The compiler options/config
 ******************************************************************************/

/* global configuration values */
CONFIG cfg;          
char szfilename[4096];
char szoutdir[4096];
char szprogdir[4096];

/* help text */
const char szhelp[] =
	"Usage:\n"
	"  neshla <filename.as> [-options]\n"
	"\n"
	"General Options:\n"
	"  -o path\n    : Set the destination path for the output files\n"
	"  -h,-?\n    : Display options help\n"
	"\n"
	"Message options:\n"
	"\n"
	"  -emax n\n    : Maximum number of errors before stopping (default: 100)\n"
	"  \n"
	"  -wmax n\n    : Maximum number of warnings before stopping (default: 100)\n"
	"  -wlevel n\n    : Warning level 0-2 (default: 1)\n"
	"  \n"
	"  -todo\n    : enable todo preprocessor messages (default: off)\n"
	"  -todomax n\n    : Maximum number of todo messages before stopping (default: 100)\n"
	"  \n"
	"  -tell\n    : enable tell preprocessor messages (default: off)\n"
	"  -tellmax n\n    : Maximum number of tell messages before stopping (default: 100)\n"
	"\n"
	"\n"
	"Stats/Logs:\n"
	"\n"
	"  -listvars\n    : output file [game].vlst with stats on each variable and it's memory usage/properties (default: off)\n"
	"  -listfuncs\n    : output file [game].flst with stats on each function file and it's address/type (default: off)\n"
	"  -listbanks\n    : output file [game].blst with stats on each bank and it's memory usage (default: off)\n"
	"  -listsrc\n    : output file [game].slst with stats on each source file and it's memory usage (default: off)\n"
	"\n"
	"\n"
	"Output Options:\n"
	"\n"
	"  -outraw\n    : output raw .prg and .chr binaries (default: off)\n"
	"  -nopadding\n    \t: pad the output ROMs up to the nearest solid size (default: off)\n"
	"  -noheader\n    : output ROM file without 16 byte iNES header (default: off)"
;


/******************************************************************************/
static struct option long_options[] = {
    { "emax",       required_argument,      0,                      'e' },
    { "wmax",       required_argument,      0,                      'w' },
    { "wlevel",     required_argument,      0,                      'v' },
    { "todo",       no_argument,            &cfg.msg.todo.enabled,   1  },
    { "todomax",    required_argument,      0,                      't' },
    { "tell",       no_argument,            &cfg.msg.tell.enabled,   1  },
    { "tellmax",    required_argument,      0,                      'l' },
    { "listvars",   no_argument,            &cfg.list.vars,          1  },
    { "listfuncs",  no_argument,            &cfg.list.functions,     1  },
    { "listbanks",  no_argument,            &cfg.list.banklist,      1  },
    { "listsrc",    no_argument,            &cfg.list.sourcesize,    1  },
    { "outraw",     no_argument,            &cfg.output.rawPrgChr,   1  },
    { "nopadding",  no_argument,            &cfg.output.padUp,       0  },
    { "noheader",   no_argument,            &cfg.output.enableHeader,0  },
    { 0, 0, 0, 0 }
};


/******************************************************************************/
BOOL InitConfig()
{
	cfg.msg.warning.max			= 100;
	cfg.msg.warning.level		= 1;  
	cfg.msg.error.max			= 100;
	cfg.msg.todo.max			= 100;
	cfg.msg.todo.enabled		= FALSE;
	cfg.msg.tell.max			= 100;
	cfg.msg.tell.enabled		= FALSE;

    cfg.list.vars				= FALSE;
    cfg.list.functions			= FALSE;
    cfg.list.banklist			= FALSE;
    cfg.list.sourcesize			= FALSE;

    cfg.output.rawPrgChr		= FALSE;
    cfg.output.padUp			= TRUE;
    cfg.output.enableHeader		= TRUE;

 	return TRUE;
}         

/******************************************************************************/
void ParseCommandLine(int argc, char* argv[])
{
    int c;

    /* get the path from the command line */
    if(argc < 2) {
        //message(0, "Usage <filename.as> [-options]");
    	message(0, szhelp);
        bexit(1);
    }

    STRCPY(szfilename, argv[1]);
    STRCPY(szoutdir, "./");

    /* turn off error output from getopt */
    opterr = 0;

    /* loop throught he options */
    while(1)
    {
        int option_index = 0;

        /* get the next option */
        c = getopt_long_only(argc, argv, ":o:h?", long_options, &option_index);

        /* if we've processed all of the options, return */
        if(c == -1)
            break;
        
        switch(c)
        {
            case 'e':
                /* -emax n */
                cfg.msg.error.max = atoi(optarg);
                break;
            case 'w':
                /* -wmax n */
                cfg.msg.warning.max = atoi(optarg);
                break;
            case 'v':
                /* -wlevel n */
                cfg.msg.warning.level = atoi(optarg);
                break;
            case 't':
                /* -todomax n */
                cfg.msg.todo.max = atoi(optarg);
                break;
            case 'l':
                /* -tellmax n */
                cfg.msg.tell.max = atoi(optarg);
                break;
            case 'o':
                /* -o <output dir> */
                STRCPY(szoutdir, optarg);
                break;
            case 'h':
            case '?':
                /* print the help text */
                message(0, szhelp);
                bexit(1);
            case ':':
                /* unknown option */
                message(0, "Invalid command or option: \"%s\"!", argv[optind]);
                message(0, "");
                bexit(2);
        }
    }

    /* dump the configuration settings */
    message(0, "CONFIG:");
    message(0, "-wmax %d", cfg.msg.warning.max);
    message(0, "-wlevel %d", cfg.msg.warning.level);
    message(0, "-emax %d", cfg.msg.error.max);
    message(0, "-todo %s", (cfg.msg.todo.enabled ? "TRUE" : "FALSE"));
    message(0, "-todomax %d", cfg.msg.todo.max);
    message(0, "-tellmax %d", cfg.msg.tell.max);
    message(0, "-listvars %s", (cfg.list.vars ? "TRUE" : "FALSE"));
    message(0, "-listfuncs %s", (cfg.list.functions ? "TRUE" : "FALSE"));
    message(0, "-listbanks %s", (cfg.list.banklist ? "TRUE" : "FALSE"));
    message(0, "-listsrc %s", (cfg.list.sourcesize ? "TRUE" : "FALSE"));
    message(0, "-outraw %s", (cfg.output.rawPrgChr ? "TRUE" : "FALSE"));
    message(0, "-nopadding %s", (cfg.output.padUp ? "TRUE" : "FALSE"));
    message(0, "-noheader %s", (cfg.output.enableHeader ? "TRUE" : "FALSE"));
    message(0, "file: %s", szfilename);
    message(0, "output dir: %s", szoutdir);
    message(0, "program dir: %s", szprogdir);
    message(0, "");
}

