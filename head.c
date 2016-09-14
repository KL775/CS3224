#include "types.h"
#include "user.h"

char buf[512];

void head(int fd, int maxLine, char *name){
	int i, n;
	int line = 0;
	while((n = read(fd, buf, sizeof(buf))) > 0){ 
		for(i = 0; i < n; ++i){
			if (line == maxLine){
				break;
			}
			if (buf[i] == '\n'){
				++line;
			}
			write(1, &buf[i], 1);
		}
		if (n < 0){
			printf(2, "Read Error. Exiting...");
			exit();
		}
	}
}

int main(int argc, char *argv[]){
	int fd, i;
	char* maxLine;
	if (argc <= 1){
		head(0, 10, "");
		exit();
	}
	if (argc == 3){
		maxLine = (char*) &argv[1][1];
	}
	else{
		maxLine = "10";
	}
	for(i = 1; i < argc; i++){
		if (argc == 3){
    		i++;
    	}
    	if((fd = open(argv[i], 0)) < 0){ //if cannot open, exit.
    	  printf(2, "Cannot open %s\n", argv[i]);
      	  exit();
    	}
    	head(fd, atoi(maxLine), argv[i]);
    	close(fd);
  	}
  exit();
}