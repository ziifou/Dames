/*
 * =====================================================================================
 *
 *       Filename:  network.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  26/12/2021 12:04:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Khelafi Sif-Eddine (), S-Eddine.KHELAFI@etu.uca.fr
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef NETWORE_H
#define NETWORE_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int connectToServ();
void createAccount();
void spectateur();
void startgame(int socketClient, char *myname);
#endif
