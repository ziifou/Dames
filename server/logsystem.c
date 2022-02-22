#include "logsystem.h"
#include <unistd.h>
pthread_mutex_t lock;

void user_info(char *logInfo, char *user, char *password){
	strcpy(logInfo,user);
	char *space = "  ";
	strcat(logInfo, space);
	strcat(logInfo, password);
	strcat(logInfo, "\n");
}

int checkLogInfo(char *username, char *password){
	char logInfo[30];
	user_info(logInfo, username, password);
	char filelogInfo[30];
	FILE *fp;
	fp = fopen("users.txt","r");

	int read = 0;
	char *line;
	size_t len = 0;

	while((read = getline(&line, &len , fp)) != -1){
		//username and pass exist 
	  if((strcmp(line, logInfo)) == 0)
		 return 1;
	}
	fclose(fp);
	return 0;
}


char createAcc(char *user, char *password){
    FILE *fp;
	fp = fopen("users.txt","a");

	
	char logInfo[30];
    user_info(logInfo, user, password);

	pthread_mutex_lock(&lock);
	  fputs(logInfo, fp);
	pthread_mutex_unlock(&lock);

	pthread_mutex_destroy(&lock);
	fclose(fp);

}