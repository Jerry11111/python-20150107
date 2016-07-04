#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int opt;
    char *optstring = "l";
    int i = 0;
    for(i = 0; i < argc; i++)
    {   
      printf("[%d] [%s]\n", i, argv[i]);

    }   
    int argind;
    int number = 0;
    while((opt = getopt(argc, argv, optstring)) != -1) 
    {   
        switch(opt)
        {   
            case 'n':
                number = 1;
                break;
            default:
                ;   
                    
        }   
        //printf("[%c] [%d] [%s]\n", opt, optind, argv[optind]);
    }   
    argind = optind;
    printf("[%d] [%s]\n", optind, argv[argind]);
    char curdir[2] = ".";
    char *infile = curdir;
	if(argv[argind] != NULL)
	{
		infile = argv[argind];
	}
    printf("[%s]\n", infile);
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(infile); ///open the dir
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {  
      unsigned char d_type = ptr->d_type;
      char *type = "";
      if(d_type == DT_REG)
	  {
		type = "-";
      } 
      else if(d_type == DT_DIR)
      {
		type = "d";
	  }
      else
      {
		type = "u";
	  }
      //printf("[%d] [%s]  [%s]\n", ptr->d_type, type, ptr->d_name);
      printf("%s  ", ptr->d_name);
    }  
    printf("\n");
    closedir(dir); 
	return 0;
}
