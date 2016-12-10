// BinToMon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma warning(disable : 4996)

void newline()
{
	printf("\n");
}

int main(int argc, char** argv)
{
	FILE *obj;
	int start_addr, length;
	unsigned char b;

	if (argc < 2)
	{
		fprintf(stderr, "Include file to convert on command line.\n");
	}
	else if (obj = fopen(argv[1], "rb"))
	{
		start_addr = length = 0;
		fread(&b, 1, 1, obj);
		start_addr = b;
		fread(&b, 1, 1, obj);
		start_addr |= b << 8;
		fread(&length, 1, 2, obj);
		printf("%04X:", start_addr);
		while (fread(&b, 1, 1, obj) == 1)
		{
			printf(" %02X", b);
			if (!(++start_addr & 0x07))
			{
				newline();
				printf(":");
			}
		}
		newline();
		fclose(obj);
	}
	else
	{
		fprintf(stderr, "Error opening %s: %s.\n", argv[1], strerror(errno));
	}

	return (0);
}