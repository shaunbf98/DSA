

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

#define RED   "\x1B[31m"
#define GREEN   "\x1b[32m"
#define GRAY   "\x1b[37m"
#define RESET "\x1B[0m"

//////OPTIONS///////
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


void printgrep(int type, char *filename, int byteoffset)
{
	if(type==0)
	{
		printf(GREEN "%s:", filename);
		printf(RESET "");
	}
	else if(type==1)
	{
		printf("grep.c:%d:", byteoffset);
	}
}

void grep(char *pattern, char *filename)
{
	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		return ;
	}

	char line[256];


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
	if(grep_H==1 && (grep_i==0  && grep_w==0 && grep_c==0 && grep_m==0 && grep_b==0))
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
				continue;
			lineptr = line;
			ptr=strcasestr(lineptr, pattern);
			//if((num%2==1 || num==2) && num>1)
			//	byteposition++;
			printf("%d:",byteposition);
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
				continue;
			lineptr = line;
			ptr=strstr(lineptr, pattern);
			printf("%d:",byteposition);
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
				continue;
			lineptr = line;
			printgrep(0, filename, 0);
			printf("%d:",byteposition);
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
				continue;
			lineptr = line;
			printgrep(0, filename, 0);
			printf("%d:",byteposition);
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















void grepv(char *pattern, char *filename)
{
	FILE* file = fopen(filename, "r");

	if(file == NULL)
	{
		return ;
	}

	char line[256];


	if(grep_H == 0 && grep_h == 0)
	{
		grep_h=1;
	}



	char *lineptr,*ptr, i, pos;

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
				printf("%d:", byteposition);
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
				printf("%d:", byteposition);
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
				printf("%d:", byteposition);
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
				printf("%d:", byteposition);
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

}





//Function space
















int main(int argc, char *argv[])
{
	int i,j;

	int option;
	int count=0;

	while((option = getopt(argc, argv, "vHhriqwcm:b"))!=-1)
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

	char *pattern=argv[count+1];

	char *filename=argv[count+2];
	/*
	printf("values of functions \n");
	printf("%d grep_v\n", grep_v);
	printf("%d grep_h\n", grep_h);
	printf("%d grep_H\n", grep_H);
	printf("%d grep_b\n", grep_b);
	printf("%d grep_c\n", grep_c);
	printf("%d grep_m\n", grep_m);
	printf("%d m_value\n", m_number);
	printf("%d grep_r\n", grep_r);
	printf("%d grep_w\n", grep_w);
	printf("%d grep_i\n", grep_i);
	*/

	/*char *pattern2;
	pattern2=malloc(sizeof(pattern)+3);
	pattern2[0]=' ';
	for(i=0;i<strlen(pattern);i++)
	{
		pattern2[i+1]=pattern[i];
	}
	pattern2[i+1]=' ';
	pattern2[i+2]='\0';*/

	/*if(grep_w==1)
	{
		if(grep_v==1)
		{
			grepv(pattern2, filename);
		}
		else if(grep_r==1)
		{
			//
		}
		else
		{
			grep(pattern2, filename);
		}
	}*/


	if(grep_v==1)
	{
		grepv(pattern, filename);
	}
	else if(grep_r==1)
	{
		//grepr(pattern, filename);
	}
	else
	{
	   grep(pattern, filename);   //works
	}




}

















