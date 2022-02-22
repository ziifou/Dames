#ifndef LOGEDCLIENT
  #define LOGEDCLIENT
    // les informations des clients dans le réseau
    struct ClientNetInfo{
      char username [10];
      int clientSock;
      int occupe;
    };
    #define MAXCLIENTS 10
    void loged(char *username, int clientSocket);
    void sendUsers(int clientSocket);
    void lancerPartie(int sock1, int sock2);

#endif