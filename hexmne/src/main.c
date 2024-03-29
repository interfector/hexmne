/*
* hexmne, last lol mnemonic
* Copyright (C) 2010 nex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include <hexmne.h>
#include <util.h>
#include <sys/stat.h>

char* i_file;
int suppress_error = 0,nline = 0;

struct hexmne_file hexmne;

int
stroff(char* str,char c)
{
	int i;

	for(i = 0;i < strlen(str);i++)
		if(str[i] == c)
			return i;

	return -1;
}

int
main(int argc,char **argv)
{
	int i;
	char* file = NULL;
	char* line = NULL;
	int   execute = 0;

	init_signal();

	o_stream = stdout;
	
	while((i = getopt_long(argc, argv, "svhxo:", long_options, NULL)) > 0)
	{
		switch(i)
		{
			case 's':
				suppress_error = 1;
				break;
			case 'v':
				die(VPRINT);
			case 'o':
				file = strdup(optarg);
				break;
			case 'x':
				execute = 1;
				break;
			case '?':
			case 'h':
			default:
				die(USAGE,argv[0]);
				break;
		}
	}

	banner();

	if(optind >= argc)
		die(USAGE,argv[0]);

	if(!(i_stream = fopen(argv[optind],"r")))
		xdie("fopen");

	i_file = argv[optind];

	if(file && !(o_stream = fopen(file,"w")))
		xdie("fopen");

	if(o_stream != stdout)
	{
		printf("Output redirected to %s...\n",file);

		close(1);
		if(dup(fileno(o_stream)) < 0)
			xdie("dup");
	}

	hexmne.symbols = malloc(sizeof(struct hexmne_sym));
	hexmne.syms_len = 1;

	hexmne.symbols[0].name = strdup("$$");
	hexmne.symbols[0].offset = 0;

	line = xmalloc(256);
	hexmne.instr = xmalloc(sizeof(struct hexmne_instr));
	hexmne.instr_len = i = 0;

	while(fgets(line,256,i_stream))
	{
		line[strlen(line)-1] = '\0';

#ifdef _DEBUG
		printf("[DEBUG]  %d:%s\n",nline,line);
#endif

		if(line[0] == '#' || line[0] == '\0')
			continue;

		if(stroff(line,'#') != -1)
			line[stroff(line,'#')] = '\0';

		if(line[0] == '@')
		{
			hexmne_preprocess( line );
			continue;
		}

		hexmne_parse_all( line );
	}

#ifdef _DEBUG
	dump_symbols();
#endif

	relocateAllSymbols();

	putchar('\n');

	printInstr();

	if(execute)
		lxs_execute();
	
	free(hexmne.symbols);
	free(hexmne.instr);
	free(line);

	if(file)
		free(file);

	if(o_stream != stdout)
		fclose(o_stream);

	return 0;
}
