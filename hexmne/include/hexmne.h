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

#ifndef _HEXMNE_
#define _HEXMNE_

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <util.h>

struct hexmne_sym {
	int   offset;
	char* name;
};

struct hexmne_instr {
	char*  instr;
	TokenCtx ctx;

	int instr_code;
	int code;
	int opcode;
};

struct hexmne_file {
	struct hexmne_instr * instr;
	int instr_len;

	struct hexmne_sym * symbols;
	int syms_len;
};

struct lxs_mne {
	int instr, opcode;

	char* mne;
};

static const struct option long_options[] =
{
	{"suppress", no_argument, 0, 's' },
	{"output", required_argument, 0, 'o'},
	{"version", no_argument, 0, 'v'},
	{"execute", no_argument, 0, 'x' },
	{"help", no_argument, 0, 'h'}
};

static struct lxs_mne instruction_set[] = {
	{ 10, 1, "READ" },
	{ 11, 1, "WRITE" },
	{ 12, 1, "POP" },
	{ 13, 1, "PUSH" },
	{ 14, 1, "ADD" },
	{ 15, 1, "SUB" },
	{ 16, 1, "MUL" },
	{ 17, 1, "DIV" },
	{ 18, 1, "MOD" },
	{ 19, 1, "AND" },
	{ 20, 1, "OR"  },
	{ 21, 1, "XOR" },
	{ 22, 1, "NOT" },
	{ 23, 1, "SHL" },
	{ 24, 1, "SHR" },
	{ 25, 1, "DEL" },
	{ 26, 0, "NOP" },
	{ 27, 1, "JMP" },
	{ 28, 1, "CMP" },
	{ 29, 1, "JN"  },
	{ 30, 1, "JZ"  },
	{ 31, 1, "JM"  },
	{ 32, 1, "JG"  },
	{ 33, 1, "EXIT" },
	{ 34, 0, "DISPLAY" },
	{ 35, 1, "INC" },
	{ 36, 1, "DEC" },
	{ 37, 1, "CALL" },
	{ 38, 0, "RET" },
	{ 39, 1, "STPUSH" },
	{ 40, 1, "STPOP" },
	{ 41, 1, "ADDSP" },
	{ 42, 1, "SUBSP" },
	{ 43, 1, "ONESC" }
};

FILE* o_stream;
FILE* i_stream;

#define MAGIC "SYM\x7a"

#define USAGE "Usage: %s [-s] [-c] [-o <file>] [-v] [-h] input_file\n" \
		    "\t-s|--suppress\tDo not exit when find errors.(dangerous)\n" \
		    "\t-o|--output\tSet the output file.\n"  \
		    "\t-v|--version\tShow the program version.\n" \
		    "\t-x|--execute\tExecute the file via lxs.\n" \
		    "\t-h|--help\tShow this help.\n"

#define VPRINT "hexmne-"VERSION" Copyright (C) 2010 nex \n" \
		  "This program comes with ABSOLUTELY NO WARRANTY.\n" \
		  "This is free software, and you are welcome to redistribute it\n" \
	       "under certain conditions.\n"
/*
#define _DEBUG
*/
#endif
