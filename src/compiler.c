/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/
#pragma hdrstop
#include <unistd.h>
#include <time.h>
#include "compiler.h"
/******************************************************************************/
#pragma package(smart_init)
#define CLK_TCK CLOCKS_PER_SEC
/******************************************************************************/

void PrintTime(void);
/******************************************************************************/
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
/******************************************************************************/
BOOL DoCompile(char *szFilename)
{
	BOOL result;

	result = CompileScript(szFilename, NULL, NULL);

    if(cfg.list.sourcesize && fSrcList) {
    	CloseFile(fSrcList);
    }
    return result;
}
/******************************************************************************/
void PrintTime()
{
	time_t t;
    char *s;

	time(&t);
	s = ctime(&t);

    message(0,"");
	message(0,"%s", s);

    //free(s);
}
/******************************************************************************/

                /*
    FILE *f = fopen("e:\\neshla\\_design\\mappershtml.txt","w");

    STRINT *si = siMappers, **sip, *sp;
    int cnt=0;
    STRINT **sints;
    while(si->string[0]) {
        si++;
        cnt++;
    }
    sints = (STRINT**)malloc(sizeof(STRINT*)*cnt);
    sip = sints;
    si = siMappers;;
    while(si->string[0]) {
        *sip++ = si;
        si++;
    }

    moo:
    i = 1;
    while(i<cnt) {
        if(strcmp(sints[i-1]->string,sints[i]->string)>0) {
         	sp = sints[i-1];
            sints[i-1] = sints[i];
            sints[i] = sp;
            goto moo;
        }
        i++;
    }

    i = 0;
    while(i<cnt) {
    	si = sints[i++];
    	fprintf(f,"<tr bgcolor=\"#FFFFF0\" class=\"NormalText\">");
    	fprintf(f,"<td><div align=\"left\">%s</div></td>", si->string);
    	fprintf(f,"<td><div align=\"left\">%d</div></td>", si->index);
    	fprintf(f,"</tr>\n");
        si++;
    }
    fclose(f);

    free(sints);  */

/*

    FILE *f = fopen("e:\\neshla\\_design\\condhtml.txt","w");

    i = 0;
    while(siConditions[i].string[0]) {
    	fprintf(f,"<tr bgcolor=\"#FFFFF0\">");
    	fprintf(f,"<td><div align=\"left\" class=\"NormalText\">%s</div></td>", siConditions[i].string);
    	fprintf(f,"<td><div align=\"left\" class=\"txcode\">%s</div></td>", GetOpcodeName(siConditions[i].index));
    	fprintf(f,"</tr>\n");
        i++;
    }
    fclose(f);*/
