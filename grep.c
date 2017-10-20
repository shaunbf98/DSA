/**************************************************************************
 *   grep.c - by Shaun Fernandez,111608058 shaunfernandez98@gmail.com     *
 *                                                                        *
 *   Copyright (C) 2017  Shaun Benjamin Fernandez              		  *
 *                                                                        *
 *   GREP is free software: you can redistribute it and/or modify         *
 *   it under the terms of the GNU General Public License as published    *
 *   by the Free Software Foundation, either version 3 of the License,    *
 *   or (at your option) any later version.                               *
 *                                                                        *
 *   GREP is distributed in the hope that it will be useful,              *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <ctype.h>

//Colors
#define RED   "\x1B[31;1m"
#define GREEN   "\x1b[32m"
#define GRAY   "\x1B[37;3m"
#define RESET "\x1B[0m"

//////OPTIONS///////
 	int grep_f;
	int grep_v;
	int grep_H;
	int grep_h;
	int grep_r;
	int grep_i;
	int grep_q;
	int grep_w;
	int grep_c;
	int grep_m, m_number;
	int grep_b;
//////OPTIONS///////




//Function space
void grep(char *pattern, char *filename);
void grepv(char *pattern, char *filename);




void printgrep(int type, char *filename, int byteoffset)
{
	if(type==0)
	{
		printf(GRAY "%s:", filename);
		printf(RESET "");
	}
	else if(type==1)
	{
		printf("grep.c:%d:", byteoffset);
	}
}

int checkbinary(char *filename)
{
	FILE *fp;
    int c;

    fp = fopen(filename, "r");
    while((c = fgetc(fp)) != EOF) 
    {
        if (c >= 0x00 && c<=0x7F) 
        {
        }
        else
        {
        	fclose(fp);
        	printf(GRAY "%s:",filename);
        	printf(RESET" File is Binary\n");
            return 1;		//Binary
        }
    }

    fclose(fp);
    return 0;				//text file
}


void grep(char *pattern, char *filename)
{
	if(checkbinary(filename)==1)
	{
		return ;
	}

	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		return ;
	}

	char line[512];


	if(grep_H == 0 && grep_h == 0)
	{
		grep_h=1;
	}



	char *lineptr,*ptr, i, pos;

	int count;


	// h and -i
	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
		}

	}




	// h alone
	if(grep_h==1 && (grep_i==0  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
		}

	}



	// H alone
	if(grep_H==1 && (grep_i==0  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			printgrep(0, filename, 0);
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
		}

	}


	// H and -i
	if(grep_H==1 && (grep_i==1  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			printgrep(0, filename, 0);
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
		}

	}


	//H i h i done

	// h c

	int matchcount=0;
	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			matchcount++;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			//printf("%s", lineptr);
		}
		printf("%d\n", matchcount);
	}

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			//printf("%s", lineptr);
		}
		printf("%d\n", matchcount);
	}

	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			//printf("%s", lineptr);
		}
		printgrep(0, filename, 0);
		printf("%d\n", matchcount);
	}

	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			//printf("%s", lineptr);
		}
		printgrep(0, filename, 0);
		printf("%d\n", matchcount);
	}





	// h and m and c

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			//printf("%s", lineptr);
			if(m_number<=matchcount)
				break;
		}
		printf("%d\n", m_number);
	}

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			//printf("%s", lineptr);
			if(m_number<=matchcount)
				break;
		}
		printf("%d\n", m_number);
	}


	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			//printf("%s", lineptr);
			if(m_number<=matchcount)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);
	}


	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					//putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					//printf(RED "%c", ptr[i]);
					count++;
					//printf(RESET "");
				}

				lineptr= lineptr + count;
				matchcount++;
				ptr=strcasestr(lineptr,pattern);
			}
			//printf("%s", lineptr);
			if(m_number<=matchcount)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);
	}





	// -b combinations
	int byteposition=0;
	int num=0;

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			ptr=strcasestr(lineptr, pattern);
			//if((num%2==1 || num==2) && num>1)
			//	byteposition++;
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			//num++;
		}

	}




	// h alone
	if(grep_h==1 && grep_i==0  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1)
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}



	// H alone and i
	if(grep_H==1 && (grep_i==0  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);			
		}

	}


	// H and -i and b
	if(grep_H==1 && (grep_i==1  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}



	//All cases done for normal grep functions



	//m cases forgotten

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			matchcount++;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}


	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			matchcount++;
			printgrep(0, filename, 0);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}

	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			matchcount++;
			printgrep(0, filename, 0);
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}



	//m and b and h 

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			matchcount++;
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}


	// H and m and b

	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			matchcount++;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}

	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}










	/*	while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			//printgrep(0,1);
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				for(i=0;i<pos;i++)
				{
					putchar(lineptr[i]);
					count++;
				}

				for(i=0;i<strlen(pattern);i++)
				{
					printf(RED "%c", ptr[i]);
					count++;
					printf(RESET "");
				}

				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
			}
			printf("%s", lineptr);
		}



		*/
}



int atleastonewordi(char *line, char *pattern)
{
	char *ptr;

	int flag = 0, i , pos;
	char *lineptr=line;
	int lengthpattern=0;
	for(i=0;pattern[i]!='\0';i++)		//Getting length of pattern
	{
		lengthpattern++;
	}

	ptr=strcasestr(lineptr, pattern);
	while(ptr!=NULL)					//Used to find atleast one WORD not string within a sentence
	{
		pos = ptr - lineptr;
		if(ptr==lineptr)
		{
			if(isalnum(ptr[lengthpattern])==0 && ptr[lengthpattern]!='_')			//Words are defined as having no character or number before or after them
			{
				return 1;
			}
		}
		else if(ptr!=NULL)
		{
			if(isalnum(ptr[-1])==0 && ptr[-1]!='_' && isalnum(ptr[lengthpattern])==0 && ptr[lengthpattern]!='_')
			{
				return 1;
			}
		}
		lineptr = lineptr + pos + strlen(pattern);
		ptr=strcasestr(lineptr, pattern);
	}


	return 0;								//Meaning no word has been found

}


int atleastoneword(char *line, char *pattern)			//case sensitive
{
	char *ptr;

	int flag = 0, i , pos;
	char *lineptr=line;
	int lengthpattern=0;
	for(i=0;pattern[i]!='\0';i++)		//Getting length of pattern
	{
		lengthpattern++;
	}

	ptr=strstr(lineptr, pattern);
	while(ptr!=NULL)					//Used to find atleast one WORD not string within a sentence
	{
		pos = ptr - lineptr;
		if(ptr==lineptr)
		{
			if(isalnum(ptr[lengthpattern])==0 && ptr[lengthpattern]!='_')			//Words are defined as having no character or number before or after them
			{
				return 1;
			}
		}
		else if(ptr!=NULL)
		{
			if(isalnum(ptr[-1])==0 && ptr[-1]!='_' && isalnum(ptr[lengthpattern])==0 && ptr[lengthpattern]!='_')
			{
				return 1;
			}
		}
		lineptr = lineptr + pos + strlen(pattern);
		ptr=strstr(lineptr, pattern);
	}


	return 0;								//Meaning no word has been found

}



















void grepw(char *pattern, char *filename)
{
	if(checkbinary(filename)==1)
	{
		return ;
	}


	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		return ;
	}

	char line[512];


	if(grep_H == 0 && grep_h == 0)
	{
		grep_h=1;
	}



	char *lineptr,*ptr, i, pos;

	int count, flag;


	// h and -i
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;

			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
		}

	}


	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;

			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
		}

	}




	// H and w

	if(grep_H==1 && (grep_i==0  && grep_w==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;
			if(atleastoneword(line, pattern)==0)
				continue;

			printgrep(0, filename, 0);
			if(ptr==line)
				flag=10;
			ptr=strstr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
		}

	}

	//H and i and w
	if(grep_H==1 && (grep_i==1  && grep_w==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;
			if(atleastonewordi(line, pattern)==0)
				continue;

			printgrep(0, filename, 0);
			if(ptr==line)
				flag=10;
			ptr=strcasestr(lineptr, pattern);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
		}

	}


	int matchcount=0;
	// h and c and w and i
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
		}
		printf("%d\n", matchcount);
	}


	//h and w and c
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
		}
		printf("%d\n", matchcount);
	}



	// H and c and w and i
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
		}
		printgrep(0, filename, 0);
		printf("%d\n", matchcount);
	}


	//H and w and c
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
		}
		printgrep(0, filename, 0);
		printf("%d\n", matchcount);
	}







	//h i w c m
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		printf("%d\n", m_number);
	}


	//h and w and c and m
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			if(matchcount>=m_number)
				break;
			//printf("%s", lineptr);
		}
		printf("%d\n", m_number);
	}


	//H i w c m
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			//printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);
	}


	//H and w and c and m
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf(RED "%c", ptr[i]);
						count++;
						//printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						//putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						//printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			if(matchcount>=m_number)
				break;
			//printf("%s", lineptr);
		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);
	}



	// b combinations

	int byteposition=0;

	// h and -i and b
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;

			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}


	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;

			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}

	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;

			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}


	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==0 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;

			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
		}

	}


	// m combinations like h w m

	// h and m and w and i
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}


	//h and w and m
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;

		}
		//printf("%d\n", matchcount);
	}



	// H and m and w and i
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			printgrep(0, filename, 0);
			if(ptr==line)
				flag=10;
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}


	//H and w and m
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
				continue;
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			if(matchcount>=m_number)
				break;

		}
		//printf("%d\n", matchcount);
	}


	// h and m and w and i and b
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}


	//h and w and m and b
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;

		}
		//printf("%d\n", matchcount);
	}



	// H and m and w and i and b
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strcasestr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastonewordi(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strcasestr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strcasestr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;
		}
		//printf("%d\n", matchcount);
	}



	//h and w and m and b
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			count=0;
			if(strstr(line, pattern)==NULL)
			{
				byteposition=ftell(file);
				continue;
			}
			lineptr = line;

			if(atleastoneword(line, pattern)==0)
				continue;
			matchcount++;
			ptr=strstr(lineptr, pattern);
			if(ptr==line)
				flag=10;
			printgrep(0, filename, 0);
			printf(GREEN "%d:",byteposition);
			printf(RESET "");
			while(ptr!=NULL)
			{
				count = 0;
				pos = ptr - lineptr;
				if((flag==10 && isalnum(ptr[strlen(pattern)])==0) || (isalnum(ptr[-1])==0 && isalnum(ptr[strlen(pattern)])==0)) 
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf(RED "%c", ptr[i]);
						count++;
						printf(RESET "");
					}
				}
				else
				{
					for(i=0;i<pos;i++)
					{
						putchar(lineptr[i]);
						count++;
					}

					for(i=0;i<strlen(pattern);i++)
					{
						printf("%c", ptr[i]);
						count++;
						//prf(RESET "");
					}
				}
				lineptr= lineptr + count;
				ptr=strstr(lineptr,pattern);
				flag=0;
			}
			printf("%s", lineptr);
			byteposition=ftell(file);
			if(matchcount>=m_number)
				break;

		}
		//printf("%d\n", matchcount);
	}


}




int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


void grepr(char *path, int flag, char *pattern)
{
    DIR * dp = opendir(path);
    if(!dp) {
        perror(path);
        return;
    }
    struct dirent * dir;
    char newdir[512];

    grep_H=1;


    char regfile[512];
    while((dir = readdir(dp)))
        if(strncmp(dir->d_name, ".", 1))
        {
            sprintf(regfile, "%s/%s",path, dir->d_name);
            if(is_regular_file(regfile))
            {

            	if(grep_v==1)
            	{
            		grepv(pattern, regfile);
            	}
            	else if(grep_w==1)
            	{
            		grepw(pattern, regfile);
            	}
            	else
            	{
            		grep(pattern, regfile);
            	}
            }
         }




    closedir(dp);
    dp = opendir(path);
    while((dir = readdir(dp))) 
      if(strncmp(dir->d_name, ".", 1)) 
      {
        if(flag && dir->d_type == 4) {
            sprintf(newdir, "%s/%s", path, dir->d_name);
            grepr(newdir, 1, pattern);
        }
    }
    closedir(dp);
}

	



















void grepv(char *pattern, char *filename)
{

	if(checkbinary(filename)==1)
	{
		return ;
	}
	
	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		return ;
	}

	char line[512];


	if(grep_H == 0 && grep_h == 0)
	{
		grep_h=1;
	}


	int count;


	//h and i and v
	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
	}
	//h and v
	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
	}

	//H and v

	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
	}

	//H and v and i
	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
	}

	//h and c and v

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
		printf("%d\n", count);
	}

	//h i c and v
	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
		printf("%d\n", count);
	}


	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
		printgrep(0, filename, 0);
		printf("%d\n", count);
	}

	//H i c and v
	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==0 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
		}
		printgrep(0, filename, 0);
		printf("%d\n", count);
	}


	//h c and m and v

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		printf("%d\n", count);
	}

	//h i c m v
	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		printf("%d\n", count);
	}

	// h c v m
	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==1 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", count);
	}

	//H i c and v
	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==1 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", count);
	}

	//h b v

	int byteposition=0;

	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}


	// H b v

	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}

	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==0 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}



	//all b combinations -w excluded


	// h m v


	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);
	}

	//h i m v
	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				//printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);
	}

	//H m v
	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);
	}

	//H i m v
	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==0 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				printgrep(0, filename, 0);
				printf("%s", line);
			}	
			else
			{
				continue;
			}
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);
	}



	//h m v b

	// h m v b


	if(grep_h==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
				if(count>=m_number)
					break;
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}

	//h m v i b

	if(grep_h==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
				if(count>=m_number)
					break;
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}


	//H m v b
	if(grep_H==1 && grep_i==0  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strstr(line, pattern)==NULL)
			{
				count++;
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
				if(count>=m_number)
					break;
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}

	//H m v b i
	if(grep_H==1 && grep_i==1  && (grep_w==0 && grep_c==0 && grep_m==1 && grep_b==1 && grep_v==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(strcasestr(line, pattern)==NULL)
			{
				count++;
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
				byteposition = ftell(file);
				if(count>=m_number)
					break;
			}	
			else
			{
				byteposition = ftell(file);
				continue;
			}
		}
	}


	/// v and w need to be combined

	// h v w
	// h v w i

	//H v w
	//H v w i

	// h v w b

	//H v w b i

	//H v w m c i all of them lol goodluck



	//h i w v
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				printf("%s", line);
			}

		}

	}
	//h w v
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				printf("%s", line);
			}

		}

	}

	//H i w v
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				printgrep(0, filename, 0);
				printf("%s", line);
			}

		}

	}
	//H w v
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				printgrep(0, filename, 0);
				printf("%s", line);
			}

		}

	}



	//h i w v c
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				//printf("%s", line);
			}

		}
		printf("%d\n", count);

	}
	//h w v c
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				//printf("%s", line);
			}

		}
		printf("%d\n", count);
	}


	//H i w v c
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}

		}
		printgrep(0, filename, 0);
		printf("%d\n", count);
	}
	//H w v c
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==0 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}

		}
		printgrep(0, filename, 0);
		printf("%d\n", count);

	}



	//h i w v c m
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				//printf("%s", line);
			}
			if(count>=m_number)
				break;
		}
		printf("%d\n", m_number);

	}
	//h w v c m
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				//printf("%s", line);
			}
			if(count>=m_number)
				break;
		}
		printf("%d\n", m_number);
	}



	//H i w v c m
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}
			if(count>=m_number)
				break;

		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);
	}
	//H w v c m
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==1 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				//printgrep(0, filename, 0);
				//printf("%s", line);
			}
			if(count>=m_number)
				break;
		}
		printgrep(0, filename, 0);
		printf("%d\n", m_number);

	}



	//h i w v m
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				printf("%s", line);
			}
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);

	}
	//h w v m
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				printf("%s", line);
			}
			if(count>=m_number)
				break;

		}
		//printf("%d\n", count);
	}



	//H i w v m
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				printgrep(0, filename, 0);
				printf("%s", line);
			}
			if(count>=m_number)
				break;
		}
		//printgrep(0, filename, 0);
		//printf("%d\n", count);
	}
	//H w v m
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==0))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				printgrep(0, filename, 0);
				printf("%s", line);
			}
			if(count>=m_number)
				break;

		}
		//printgrep(0, filename, 0);
		//printf("%d\n", count);

	}





	//h i w v m b
	if(grep_h==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
			}
			byteposition=ftell(file);
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);

	}
	//h w v m b
	if(grep_h==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
			}
			byteposition=ftell(file);
			if(count>=m_number)
				break;

		}
		//printf("%d\n", count);
	}


	//H i w v m b
	if(grep_H==1 && grep_i==1  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{
			if(atleastonewordi(line, pattern)==0)
			{
				count++;
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
			}
			byteposition=ftell(file);
			if(count>=m_number)
				break;
		}
		//printf("%d\n", count);

	}
	//H w v m b
	if(grep_H==1 && grep_i==0  && (grep_w==1 && grep_v==1 && grep_c==0 && grep_m==1 && grep_b==1))
	{
		while(fgets(line, sizeof(line), file))
		{

			if(atleastoneword(line, pattern)==0)
			{
				count++;
				printgrep(0, filename, 0);
				printf(GREEN "%d:",byteposition);
				printf(RESET "");
				printf("%s", line);
			}
			byteposition=ftell(file);
			if(count>=m_number)
				break;

		}
		//printf("%d\n", count);
	}

}





//Function space




char *readfile(char *filename)
{
    FILE *file = fopen(filename, "r");
    char *text;
    int i = 0;
    char ch;

    if (file == NULL)
     {
		perror("Error");
		exit(0);	
     }		

    text = malloc(512);

    while ((ch = fgetc(file)) != EOF)
    {
        text[i++] = ch;
    }
    text[i] = '\0';        
    return text;
}

int main(int argc, char *argv[])
{
	int option;
	int count=0;
	m_number=0;
	char *patternfile;
	char *filename;
	while((option = getopt(argc, argv, "vHhriqwf:cm:b"))!=-1)
		switch(option)
		{
			case 'v':
					grep_v=1;
					count++;
					break;
			case 'H':
					grep_H=1;
					count++;
					break;
			case 'h':
					grep_h=1;
					count++;
					break;
			case 'r':
					grep_r=1;
					count++;
					break;
			case 'i':
					grep_i=1;
					count++;
					break;
			case 'q':
					grep_q=1;
					count++;
					break;
			case 'f':
					grep_f=1;
					count+=2;
					patternfile = optarg;
					break;

			case 'w':
					grep_w=1;
					count++;
					break;
			case 'c':
					grep_c=1;
					count++;
					break;
			case 'm':
					grep_m=1;
					count+=2;
					m_number=atoi(optarg);
					break;
			case 'b':
					grep_b=1;
					count++;
					break;
			default:
					fprintf(stderr, "Usage: grep [OPTIONS]... PATTERN [FILENAME]...\n");
					exit(0);
			}

	if(argc<3)
	{
		fprintf(stderr, "Usage: grep [OPTIONS]... PATTERN [FILENAME]...\n");
		exit(0);
	}

	if(grep_h == 1 && grep_H == 1)
	{
		fprintf(stderr, "Usage: grep [OPTIONS]... PATTERN [FILENAME]...  -h and -H have opposite effects\n");
		exit(0);
	}

	char *pattern;


	if(grep_f==0)
	{
		pattern=argv[count+1];
		if(argv[count+2] == 0 && grep_r==0)
		{
			fprintf(stderr, "Usage: grep [OPTIONS]... PATTERN [FILENAME]...\n");
			exit(0);
		}
		if(grep_r==0)
		{
			filename=argv[count+2];
			int fp;
			fp=open(filename, O_RDONLY);
			if(fp==-1)
			{
				perror("Error");
				exit(0);
			}	
			close(fp);
		}

		if(grep_q==1)
		{
			exit(0);
		}
		
		if(m_number<0)
		{
			m_number=0;
			grep_m=0;
		}
	}

	else if(grep_f==1)
	{
		pattern = readfile(patternfile);
		if(argv[count+1] == 0 && grep_r==0)
		{
			fprintf(stderr, "Usage: grep [OPTIONS]... PATTERN [FILENAME]...\n");
			exit(0);
		}
		if(grep_r==0)
		{
			filename=argv[count+1];
			int fp;
			fp=open(filename, O_RDONLY);
			if(fp==-1)
			{
				perror("Error");
				exit(0);
			}	
			close(fp);
		}

		if(grep_q==1)
		{
			exit(0);
		}
		
		if(m_number<0)
		{
			m_number=0;
			grep_m=0;
		}

	}



	if(grep_r==1)
	{
		grepr(".", 1, pattern);
	}
	else if(grep_v==1)
	{
		grepv(pattern, filename);
	}
	else if(grep_w==1)
	{
	   grepw(pattern, filename);   //works
	}
	else
	{
		grep(pattern, filename);
	}
}

















