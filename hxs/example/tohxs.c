#include <stdio.h>
	
int
main(int argc,char** argv)
{
	FILE* fp;
	char buf[BUFSIZ];

	int instr,opcode;

	if(!argv[1])
		return 1;

	if(!(fp = fopen(argv[1],"r")))
		return 1;

	while(fgets(buf,BUFSIZ,fp))
	{
		if( buf[0] == '#' || buf[0] == '\n' || buf[0] == '\0')
			continue;

		instr = atoi( buf ) / 100;
		opcode = atoi( buf ) % 100;

		printf("%.2x%.2x\n", instr, opcode);
	}

	fclose(fp);

	return 0;
}
