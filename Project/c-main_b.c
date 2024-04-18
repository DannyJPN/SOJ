//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, , VSB-TUO
//
// Empty project
//
//***************************************************************************
#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

// Variables
//

char  corpas[64] = {0xE6,0x1B,0x6A,0x99,0x5F,0x8E,0x45,0xAA,
				0xF6,0x30,0x6E,0xE6,0xF6,0x7E,0x52,0x52,
				0x67,0x38,0x91,0x8A,0x33,0xEF,0x81,0x95,
				0xC2,0xCC,0x93,0x2F,0xA6,0xD4,0x63,0x82,
				0xDB,0x31,0x8B,0xD0,0x9A,0x3D,0xEA,0x57,
				0x85,0xD5,0xB8,0x9E,0xC8,0x3E,0xB8,0xC4,
				0x2A,0x8E,0x10,0x74,0xD1,0x3C,0x5B,0xFE,
				0x74,0xC1,0x30,0x26,0x7E,0x09,0xC3,0x4E};

int ComparePass(char* pass1,char * pass2);


char* GetFiles(char* dirname,int indent)
{

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(dirname)))
        return NULL;

    while ((entry = readdir(dir)) != NULL) 
	{
        if (entry->d_type == DT_DIR) 
		{
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            //printf("%s/",path);
			GetFiles(path, indent + 2);
        }
		else 
		{
			char fullname[PATH_MAX*4];
			realpath(entry->d_name,fullname);
			if(!access(fullname,X_OK))
            {
				printf("%*s- %s\n", indent, "", fullname);
				//printf("%s\n",entry->d_name);
			}
        }
    }
    closedir(dir);
	return NULL;
}	



//char*GetFiles(char* v)
//{
//	
//	  execl("/usr/bin/find", "find",   v  ,"-type","f","-executable",">","./.execfile",(char *) NULL    );
//	  FILE *fd;
//	  
//	  fd = NULL;
//    return 0;
//	
//}











void EncryptMode()
{
	char * files = GetFiles("../",0);
	
	
}

void DecryptMode(char* password)
{
	
}



int main(int argc, char **argv )
{

	if(argc <=1)
	{
		EncryptMode();
		
	}
	else
	{
		char *password = argv[1];
		printf("%s\n",password);
		DecryptMode(password);
		
	}
					 
					 
					 
}



