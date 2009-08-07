/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *  Copyright (C) 2009 David Huseby, <dave@linuxprogrammer.org>
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

#include <unistd.h>
#include <time.h>
#include "compiler.h"

#define CLK_TCK CLOCKS_PER_SEC

void PrintTime(void);


int main(int argc, char* argv[])
{
	int c,i,l;
    char *s,*p, *tmp;

	clock_t start, end;
	start = clock();

	message(0,"Nintendo NES High Level Assembler");
    message(0,"");
    message(0,"Version %s, %s",SZ_VERSION,SZ_BUILD_DATE);
    message(0,"By David Huseby :: http://www.linuxprogrammer.org");
    message(0,"");
    message(0,"Legacy Win32 Version %s, %s",SZ_LEGACY_VERSION,SZ_LEGACY_BUILD_DATE);
    message(0,"By Brian Provinciano :: http://www.bripro.com");
    message(0,"");

    if(argc < 1)
    	return 3;

    if(!getcwd(szprogdir, sizeof(szprogdir)-1))
        return 3;

    tmp = FixPathSet(szprogdir);
    STRCPY(szprogdir, tmp);
    
    /* set the default values on the config settings */
	if(!InitConfig()) 
        return 4;

    /* parse the command line arguments */
    ParseCommandLine(argc, argv);

	sysDirList		= NULL;
    includeDirList	= NULL;
    libDirList		= NULL;

    /* make sure there is a trailing slash on output dir */
    tmp = FixPathSet(szoutdir);
    STRCPY(szoutdir, tmp);
	strcpy(outDir, szoutdir);

    /* add folders to default include list */
    message(0, "prog dir: %s", szprogdir);
    sprintf(szTemp, "%s", szprogdir);
    AddDirList(&sysDirList, szTemp);
    sprintf(szTemp, "%sinclude/", szprogdir);
    message(0, "include dir: %s", szTemp);
    AddDirList(&includeDirList, szTemp);
    sprintf(szTemp, "%slib/", szprogdir);
    message(0, "lib dir: %s", szTemp);
    AddDirList(&libDirList, szTemp);

    /* initialize and run the compiler */
	if(InitializeCompiler()) 
    {
	    message(0, "System Dir List:");
        PrintStringList(sysDirList);
        message(0, "System Include List:");
        PrintStringList(includeDirList);
        message(0, "System Lib List:");
        PrintStringList(libDirList);
        
        message(0,"Compiling file: %s ...", szfilename);
    	DoCompile(szfilename);
    }

	{
		float fl = (clock() - start) / CLK_TCK;
		printf("The time was: %f\n", fl);
	}

    if(COMPILE_SUCCESS) 
    {
		ShutDownCompiler();   
    	PrintTime();
		message(MSG_COMPSUCCESS);
    } else // automatically shuts down
    	fatal(FTL_COMPFAIL);
    message(0,"");

	return 0;
}


BOOL DoCompile(char *szFilename)
{
	BOOL result;

	result = CompileScript(szFilename, NULL, NULL);

    if(cfg.list.sourcesize && fSrcList) {
    	CloseFile(fSrcList);
    }
    return result;
}


void PrintTime()
{
	time_t t;
    char *s;

	time(&t);
	s = ctime(&t);

    message(0,"");
	message(0,"%s", s);
}

