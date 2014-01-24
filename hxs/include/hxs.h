/*
* LXS
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


#ifndef _LXS_H_
#define _LXS_H_

#define MAX_MEM 1000

#define BIN_MAGIC "SYM\x7a"

#define SYM_READ	0  // Read a number from stdin
#define SYM_WRITE	1  // Write the number in stdout
#define SYM_POP	2  // Save the current accumulator in memory
#define SYM_PUSH	3  // Push the element from memory to accumulator
#define SYM_ADD	4  // Add the element to accumulator
#define SYM_SUB	5  // Subtract the element to accumulator
#define SYM_MUL	6  // Multiple the element fot accumulator
#define SYM_DIV	7  // Divide the accumulator by element
#define SYM_MOD	8  // Module operand
#define SYM_AND	9  // And operand
#define SYM_OR		10 // Or operand
#define SYM_XOR	11 // Xor operand
#define SYM_NOT	12 // Not operand
#define SYM_SHL	13 // Left bit shift operand
#define SYM_SHR	14 // Right bit shift operand
#define SYM_DEL	15 // Restore the accumulator to 0
#define SYM_NOP	16 // No OPeration
#define SYM_JMP	17 // Jump to address in memory
#define SYM_CMP	18 // Compare the accumulator and the element
#define SYM_JN		19 // Jump !=
#define SYM_JZ		20 // Jump == 
#define SYM_JM		21 // Jump <= 
#define SYM_JG		22 // Jump >=
#define SYM_EXIT	23 // Exit forced
#define SYM_CHMOD	24 // Change display mode
#define SYM_INC	25 // Increment the accumulator
#define SYM_DEC	26 // Decrement the accumulator
#define SYM_CALL	27 // Calls an address
#define SYM_RET	28 // Return to the previous IP
#define SYM_STPUSH	29 // Push a variable to the stack
#define SYM_STPOP	30 // Pop a variable to the stack
#define SYM_ADDSP	31 // Increase the stack pointer
#define SYM_SUBSP	32 // Decrease the stack pointer
#define SYM_ONESC	33 // One's Complement

#define MAX_CALL	33

extern "C" {

	struct lxsHdr {
		char magic[4];
		int prog_size;
	};

	struct lxsSym_entry {
		int value;
		char* name;
	};

	typedef struct {
		int* mem;
		int  mm_len;
		int current;
	} _stack_t;

	typedef struct {
		int mem[MAX_MEM]; // Memory

		int mode;    // Display mode

		int count;   // Operation count
		int eax;     // Accumulator
		int flag;    // Jump flag
	
		int ip;      // Istruction Pointer
		int old_ip;  // IP for call function
		int code;    // Instruction code
		int op_code; // Operation code

		_stack_t stack; // LIFO Stack
	} sym_code_t;

	void toBin(int num);
	void sym_read (sym_code_t*);
	void sym_write(sym_code_t*);
	void sym_pop (sym_code_t*);
	void sym_push(sym_code_t*);
	void sym_add (sym_code_t*);
	void sym_sub (sym_code_t*);
	void sym_mul (sym_code_t*);
	void sym_div (sym_code_t*);
	void sym_mod (sym_code_t*);
	void sym_and (sym_code_t*);
	void sym_or  (sym_code_t*);
	void sym_xor (sym_code_t*);
	void sym_not (sym_code_t*);
	void sym_shl (sym_code_t*);
	void sym_shr (sym_code_t*);
	void sym_del (sym_code_t*);
	void sym_nop (sym_code_t*);
	void sym_jmp (sym_code_t*);
	void sym_cmp (sym_code_t*);
	void sym_jn  (sym_code_t*);
	void sym_jz  (sym_code_t*);
	void sym_jm  (sym_code_t*);
	void sym_jg  (sym_code_t*);
	void sym_exit(sym_code_t*);
	void sym_chmod(sym_code_t*);
	void sym_inc (sym_code_t*);
	void sym_dec (sym_code_t*);
	void sym_call(sym_code_t*);
	void sym_ret (sym_code_t*);
	void sym_stpush(sym_code_t*);
	void sym_stpop(sym_code_t*);
	void sym_addsp(sym_code_t*);
	void sym_subsp(sym_code_t*);
	void sym_onesc(sym_code_t*);

	static void (*sym_code_table[])(sym_code_t *) = { 
		sym_read,
		sym_write,
		sym_pop,
		sym_push,
		sym_add,
		sym_sub,
		sym_mul,
		sym_div,
		sym_mod,
		sym_and,
		sym_or,
		sym_xor,
		sym_not,
		sym_shl,
		sym_shr,
		sym_del,
		sym_nop,
		sym_jmp,
		sym_cmp,
		sym_jn,
		sym_jz,
		sym_jm,
		sym_jg,
		sym_exit,
		sym_chmod,
		sym_inc,
		sym_dec,
		sym_call,
		sym_ret,
		sym_stpush,
		sym_stpop,
		sym_addsp,
		sym_subsp,
		sym_onesc
	};
		
}

class SymClass {
	public:
		SymClass();
		
		sym_code_t simpletron;
		
		int readfile(char * name);
		void stdin_read();
		int pseudo_compile(char * name,char * out);
		int read_bin(char * name);
		int execute();
		void dump();
	private:
		int execute_op(int op);
		int atoi(char * str);
};

#ifdef DEBUG
static int debug = 1; /* 1 for debug */
#else
static int debug = 0;
#endif

#define VTEXT "hxs-"VERSION" Copyright (C) 2010 nex \n" \
		  "This program comes with ABSOLUTELY NO WARRANTY.\n" \
		  "This is free software, and you are welcome to redistribute it\n" \
	       "under certain conditions."

#endif
