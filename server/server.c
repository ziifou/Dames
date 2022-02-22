
#include "logsystem.h"
#include "logedClients.h"

void *connect_cli(void *p_client);
int main(int argc, char *argv[])
{
	int sockfd, connfd, len;
	struct sockaddr_in servadr,client;
	//socket creatiing
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("socket creation failed...\n");
		exit(0);
	}else
		printf("socket created...\n");

	bzero(&servadr, sizeof(servadr));
	
	servadr.sin_family = AF_INET;
	servadr.sin_addr.s_addr=htonl(INADDR_ANY);
	servadr.sin_port = htons(50000);
	
	
	if((bind(sockfd, (struct sockaddr*)&servadr, sizeof(servadr) )) < 0){
			printf("socket not binded \n");
			exit(0);
	}

	if((listen(sockfd, 5) < 0)){
		printf("Listen failed ...\n");
	}else
		printf("server listening.. \n");

	int sizeC = sizeof(client);

	while(1){
	    int connectfd = accept(sockfd, (struct sockaddr *) &client, &sizeC);
		char msg[10];
		pthread_t clientThrd;
		int *pclient = malloc(sizeof(int));
		*pclient = connectfd;
		pthread_create(&clientThrd, NULL, connect_cli, pclient);
		
	} 
}
//"thread spécialement pour le client"
void *connect_cli(void *p_client){
	int clientSocket = *((int *)p_client);
	free(p_client);
	printf("client connected \n");
	char msg[3] = "ok";
	send(clientSocket,msg, sizeof(msg), 0 );
	// recieving choice of the clinet
	int choi = 0;
	recv(clientSocket, &choi, sizeof(int),0 );
	switch(choi){
		// create account case
		case 1:;
       		struct User {
           	char username [10];
           	char password [10];
            };
        
         	struct User userInfo;
        
        	recv(clientSocket,userInfo.username, sizeof(userInfo.username),0 );
        
        	char msg [25] = "entrer le mot de passe";
        	send(clientSocket, msg, sizeof(msg), 0);
        
        	recv(clientSocket,userInfo.password, sizeof(userInfo.password),0 );
        
        	//write into the file
        	createAcc(userInfo.username,userInfo.password);
        	// close(clientSocket);
			// free(p_client);
        	// pthread_exit(NULL);
			break; 
		// login case
		case 2:;
			char username [15];
			char password [15];
			//rcv username
			recv(clientSocket, username, sizeof(username),0);
			//rcv pass
			recv(clientSocket, password, sizeof(password),0);

			int exist = 0;	
			exist = checkLogInfo(username, password);
			send(clientSocket, &exist, sizeof(exist), 0);
			if(exist)
				loged(username, clientSocket);
			// free(p_client);
		// spectateur case
		case 3:
			break;
	}

	close(clientSocket);
	// free(p_client);
	pthread_exit(NULL);

}
  
