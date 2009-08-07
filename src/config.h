/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *	You may use this code for anything you wish.
 *	It comes with no warranty.
 ***************************************************************************/

#ifndef configH
#define configH

typedef struct config_s 
{
	struct 
    {
		struct 
        {
        	int		max;
            int		level;
        } warning;

		struct 
        {
        	int		max;
        } error;

		struct 
        {
        	BOOL	enabled;
        	int		max;
        } todo;

		struct 
        {
        	BOOL	enabled;
        	int		max;
        } tell;

    } msg;

    //struct {
    	//BOOL stripUnused;
    //} func;

    struct 
    {
    	BOOL	vars;
        BOOL    functions;
        BOOL    banklist;
        BOOL    sourcesize;
    } list;

    struct
    {
    	BOOL	rawPrgChr;
        BOOL	padUp;
        BOOL	enableHeader;
    } output;
} config_t;
typedef config_t CONFIG;

// extern global configuration switches
extern CONFIG cfg;

// extern global path configuration parameters
extern char szfilename[4096];
extern char szoutdir[4096];
extern char szprogdir[4096];


BOOL InitConfig(void);
void ParseCommandLine(int argc, char* argv[]);

#endif

