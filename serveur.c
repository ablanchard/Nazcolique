/*
 ** selectserver.c -- a cheezy multiperson chat server
 */
#include "serveur.h"
#include "game.h"
#include "crypt.h"
// get sockaddr, IPv4 or IPv6:


void raz(char* m, int i)//fonction qui remet a zero un tableau de caracteres
{
	int j;
	for (j=0;j<i;j++)
		m[j]='\0';
}
void traiter_requete (int desc, char* message,int *table_ID, sdl_c *map)
{
	printf("On va bouger le perso n°%i sur %i\n",table_ID[desc],map->nb_pj);
	analyse_ordre (table_ID[desc],map,message);//analyse le message recu
	creation_message(table_ID[desc],map,message);//creer le message de mise a jour pour les clients
}

void actualisation_jserveur (sdl_c *map)
{ //actualise les infos du joueur joué par le serveur
	if (sockbcast)
	{
		char* m=(char *)calloc(MAXDATASIZE,sizeof(char));
		int nbytes;
		creation_message(0,map,m);
		if ((nbytes=sendto(sockbcast,m,strlen(m),0,(struct sockaddr *)&their_addr,sizeof(their_addr)))==-1)
			perror("sendto");
		printf("sent %s  %d bytes to %s\n", m,nbytes,inet_ntoa(their_addr.sin_addr));
		free(m);
	}
}

void actualisation_pnj (sdl_c *map)
{//actualise les infos des pnj 
	char *m=(char *)calloc(MAXDATASIZE,sizeof(char));
	int nbytes;
	int b=1;
	int d=0;
	int pas=5;//Determine le nombre de pnj actualisés par message permet d'eviter de depasser le MAXDATASIZE
	int f=d+pas-1;
	if (f>=map->nb_pnj)
		f=map->nb_pnj-1;
	if (sockbcast)
	{
		while (b)
		{
			creation_message_pnj(map,m,d,f);
			if ((nbytes=sendto(sockbcast,m,strlen(m),0,(struct sockaddr *)&their_addr,sizeof(their_addr)))==-1)
				perror("sendto");
			printf("sent %s  %d bytes to %s\n", m,nbytes,inet_ntoa(their_addr.sin_addr));
			d=f+1;
			f=f+pas;
			if (f>map->nb_pnj)
				f=map->nb_pnj-1;
			if (d>=map->nb_pnj)
				b=0;
			raz(m,nbytes);
		}
		free(m);
	}
}

void message_unload_pnj(int i)
{
	char m[32];
	int nbytes;
	sprintf(m,"UNLOAD_PNJ%i",i);
	if (sockbcast)
        {
                        if ((nbytes=sendto(sockbcast,m,strlen(m),0,(struct sockaddr *)&their_addr,sizeof(their_addr)))==-1)
                                perror("sendto");
                        printf("sent %s  %d bytes to %s\n", m,nbytes,inet_ntoa(their_addr.sin_addr));
                        raz(m,nbytes);
        }
}

void message_load_pnj(sdl_c *map)
{
        char m[32];
        int nbytes;
        sprintf(m,"LOAD_PNJ%i",map->nb_pnj);
        if (sockbcast)
        {
                        if ((nbytes=sendto(sockbcast,m,strlen(m),0,(struct sockaddr *)&their_addr,sizeof(their_addr)))==-1)
                                perror("sendto");
                        printf("sent %s  %d bytes to %s\n", m,nbytes,inet_ntoa(their_addr.sin_addr));
                        raz(m,nbytes);
        }
}


void actualisation_pj (sdl_c *map)
{//Actualiser les infos des pj
	char *m=(char *)calloc(MAXDATASIZE,sizeof(char));
	char *buf=(char*)calloc(32,sizeof(char));
	int nbytes;
	int b=1;
	int d=0;
	int pas=4;//Dtermine les nombre de pj actualisés par message permet d'eviter de depasser le MAXDATASIZE
	int i;
	int f=d+pas-1;
	if (f>=map->nb_pj)
		f=map->nb_pj-1;
	if (sockbcast)
	{
	while (b)
	{
		for (i=d;i<=f;i++)
		{
			creation_message(i,map,buf);
			strcat(m,buf);
		}
		if ((nbytes=sendto(sockbcast,m,strlen(m),0,(struct sockaddr *)&their_addr,sizeof(their_addr)))==-1)
			perror("sendto");
		printf("sent %s  %d bytes to %s\n", m,nbytes,inet_ntoa(their_addr.sin_addr));
		d=f+1;
		f=f+pas;
		if (f>=map->nb_pj)
			f=map->nb_pj-1;
		if (d>=map->nb_pj)
			b=0;
		raz(m,nbytes);
	}
	}
	free(m);
	free(buf);
}

void creation_message_pnj(sdl_c *map,char *m,int d,int f)
{//Cree un message contenant toutes les infos des pnj compris entre d et f
	int i;
	char buf[64];
	int nbytes;
	sprintf(m,"PNJ");
	for (i=d;i<=f;i++)
	{
		sprintf(buf,"%ix%iy%ip%is%i%i%i",i,map->tac[i]->pos.x,map->tac[i]->pos.y,map->tac[i]->pv,map->tac[i]->sens,map->tac[i]->pos_s,map->tac[i]->att);
		strcat(m,buf);
	}
}

void creation_message(int ID,sdl_c *map, char *m)//Cree un message contenant toute les infos d'un pj
{
	sprintf(m,"%dx%dy%dp%dm%dd%ds%d%d%d",ID,map->tab[ID]->pos.x,map->tab[ID]->pos.y,map->tab[ID]->pv,map->tab[ID]->pv_m,map->tab[ID]->deg,map->tab[ID]->sens,map->tab[ID]->pos_s,map->tab[ID]->att);
}


void analyse_ordre (int ID, sdl_c *map,char *m)
{
	int i=0;
	int k=0;
	if (strcmp(m,"OK")==0)
		map->tab[ID]->ok=1;
	else
	{	
	long long clair=decrypt(m);//On decrypte le message
	char buf[128];
	sprintf(buf,"%lli\0",clair);
	char* date=(char*)calloc(32,sizeof(char));
	epoch(date);
	//printf("cle=%s\ndate=%s\n",buf,date);
	if (strncmp(buf,date,10)==0)//On compare avec la date actuelle pour valider l'ordre
	{
		printf("Il s'agit de %i ",buf[strlen(buf)-1]-48);
		switch (buf[strlen(buf)-1]-48)
		{
			case DOWN: // Déplacer vers le bas
				printf("En bas ...");
				map->tab[ID]->sens=DOWN;
				move_p(map,ID);
				break;
			case LEFT: // Déplacer vers la gauche
				printf("A gauche ...");
				map->tab[ID]->sens=LEFT;
				move_p(map,ID);
				break;
			case RIGHT: // Déplacer vers la droite
				printf("A droite ...");
				map->tab[ID]->sens=RIGHT;
				move_p(map,ID);
				break;
			case UP: // Déplacer vers le haut
				printf("En haut ...");
				map->tab[ID]->sens=UP;
				move_p(map,ID);
				break;
			case SPACE:
				printf("Attaque ...");
				map->tab[ID]->att=1;
				break;
			default:
				printf("Deplacement non reconnu\n");
				break;
		}
		printf("Déplacement effectué\n");
	}
	else
		printf("La clé ne correspond pas\n");
}
}


void reception_initiale (int desc, int* table_ID,int* dispo_ID)
{
	int i=1;
	while (dispo_ID[i]!=(-1))//DEs qu'un ID est libre on le prend
		i++;
	table_ID[desc]=i;
	dispo_ID[i]=desc;
	printf("ID choisi pour la socket %d : %d\n",desc,table_ID[desc]);
}



void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int get_in_port (struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return htons(((struct sockaddr_in*)sa)->sin_port);
	}
	return htons(((struct sockaddr_in6*)sa)->sin6_port);
}


void* serveur(sdl_c *map)
{
	fd_set master; // master file descriptor list
	fd_set read_fds; // temp file descriptor list for select()
	int fdmax; // maximum file descriptor number
	int listener; // listening socket descriptor
	int newfd; // newly accept()ed socket descriptor
	int talker;
	struct sockaddr_storage remoteaddr; // client address
	socklen_t addrlen;
	char* buf=(char*)calloc(MAXDATASIZE,sizeof(char));
	int nbytes;
	int k=0;
	char adresse[32];
	char bcast[32];//="192.168.1.255";
	   FILE* fic;
	  system("bash ./addr.bash > addr");
	   fic=fopen("addr","r");
	   fgets(adresse,32,fic);
	   fgets(bcast,32,fic);
	   fclose(fic);
	for (k=0;k<strlen(bcast);k++)
	{
		if (bcast[k]=='\n')
			bcast[k]='\0';
	}
	char remoteIP[INET6_ADDRSTRLEN];
	int yes=1; // for setsockopt() SO_REUSEADDR, below
	int i,j, rv;
	struct addrinfo hints, udp, *ai, *p;
	struct timeval tv;
	int port;
	int *table_ID=(int *)calloc(NB_PERS_MAP+5,sizeof(int));
	int* dispo_ID=(int *)calloc(NB_PERS_MAP,sizeof(int));
	for (k=0;k<NB_PERS_MAP;k++)
		dispo_ID[k]=-1;
	dispo_ID[0]=0;
	char* recu=(char*)calloc(MAXDATASIZE,sizeof(char));
	char s[INET6_ADDRSTRLEN];
	FD_ZERO(&master); // clear the master and temp sets
	FD_ZERO(&read_fds);
	// Creation de la socket TCP
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(adresse, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
		exit(1);
	}
	for(p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) {
			continue;
		}
		// lose the pesky "address already in use" error message
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}
		break;
	}
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);
	printf("Socket TCP %i %s on port %d\n",listener,s,get_in_port((struct sockaddr*)p->ai_addr));
	// if we got here, it means we didn't get bound
	if (p == NULL) {
		fprintf(stderr, "selectserver: failed to bind\n");
		exit(2);
	}
	freeaddrinfo(ai); // all done with this
	/* Creation de la socket UDP de broadcast*/
	struct hostent *he;
	int broadcast = 1;
	printf("Adresse de bcast : %s\n",bcast);
	if ((he=gethostbyname(bcast)) == NULL) { // get the host info
		perror("gethostbyname");
		exit(1);
	}
	if ((sockbcast = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
	// this call is what allows broadcast packets to be sent:
	if (setsockopt(sockbcast, SOL_SOCKET, SO_BROADCAST, &broadcast,
				sizeof broadcast) == -1) {
		perror("setsockopt (SO_BROADCAST)");
		exit(1);
	}
	their_addr.sin_family = AF_INET; // host byte order
	their_addr.sin_port = htons(UDPPORT); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);
	printf("socket de broadcast crée %i\n",sockbcast);
	//listen
	if (listen(listener, 10) == -1) {
		perror("listen");
		exit(3);
	}
	// add the listener to the master set
	FD_SET(listener, &master);
	// keep track of the biggest file descriptor
	fdmax = listener; // so far, it's this one
	// main loop	
	printf("Attente de connection....\n");
	for(;;) 
	{
		tv.tv_sec = 1;
		tv.tv_usec = 0;

		read_fds = master; // copy it
		if (select(fdmax+1, &read_fds, NULL, NULL, &tv) == -1) 
		{
			perror("select");
			exit(4);
		}
		// run through the existing connections looking for data to read
		for(i = 0; i <= fdmax; i++) 
		{
			if (FD_ISSET(i, &read_fds)) 
			{ 	// we got one!!
				if (i == listener) 
				{
					// handle new connections
					addrlen = sizeof remoteaddr;
					newfd = accept(listener,
							(struct sockaddr *)&remoteaddr,
							&addrlen);
					if (newfd == -1) 
					{
						perror("accept");
					} 
					else 
					{
						FD_SET(newfd, &master); // add to master set
						if (newfd > fdmax) 
						{ // keep track of the max
							fdmax = newfd;
						}
						//table_udp[newfd]=(struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));
						printf("selectserver: new connection from %s on port %d on ""socket %d\n",
								inet_ntop(remoteaddr.ss_family,
									get_in_addr((struct sockaddr*)&remoteaddr),
									remoteIP, INET6_ADDRSTRLEN),get_in_port((struct sockaddr*)&remoteaddr),
								newfd);
						reception_initiale(newfd,table_ID,dispo_ID);//associe un ID a la nouvelle socket
						load_pj(map,NULL,table_ID[newfd]);//alloue la memoire pour le nouveau joueur
						map->nb_pj++;//increment le nb de joueur
						sprintf(buf,"LOAD_PJ%iPNJ%iP%i\0",map->nb_pj,map->nb_pnj,table_ID[newfd]);//Message envoye aux clients
						if ((nbytes=sendto(sockbcast,buf,strlen(buf), 0,(struct sockaddr *)&their_addr, sizeof their_addr)) == -1) 
						{
							perror("envoi de la commande load_pj");
							exit(1);
						}
						printf("Commande Load_pj envoyée : %s\n",buf);
						raz(buf,nbytes);
						actualisation_pj(map);//On envoie une fois que les clients on allouer la memoire la position actuelle des joueurs
					}
				} 
				else 
				{
					// handle data from a client
					if ((nbytes = recv(i,recu,MAXDATASIZE-1, 0)) <= 0) 
					{
						// got error or connection closed by client
						if (nbytes == 0) 
						{
							// connection closed
							printf("selectserver: socket %d hung up\n", i);
						} 
						else 
						{
							perror("recv");
						}
						close(i); // bye!
						FD_CLR(i, &master); // remove from master set
						sprintf(buf,"UNLOAD_PJ%d",table_ID[i]);//Message de deconnection d'un joueur
						if ((nbytes=sendto(sockbcast,buf, strlen(buf), 0,(struct sockaddr *)&their_addr, sizeof their_addr)) == -1) 
						{
							perror("sendto");
							exit(1);
						}
						printf("Commande Unload_pj envoyée : %s\n",buf);
						raz(buf,nbytes);
						printf("La socket %i avec l'ID %i hung up\n",i,table_ID[i]);
						printf("Desormais la socket %i qui avait l'ID %i a l'ID %i\n",dispo_ID[map->nb_pj-1],table_ID[dispo_ID[map->nb_pj-1]],table_ID[i]);
						table_ID[dispo_ID[map->nb_pj-1]]=table_ID[i];//le dernier joueur dans le tbaleau prend la place de celui qui s'est deconnecté
						dispo_ID[map->nb_pj-1]=-1;//On met a jour dispo_ID
						unload_pj(map,table_ID[i]);//On desalloue le joueur dans la memoire
					} 
					else 
					{
						printf("Ordre recu %s %d bytes de la socket %d\n",recu,nbytes,i);
						recu[nbytes]='\0';
						traiter_requete(i,recu,table_ID,map);//On analyse le message puis on en cree un nouveau
						if ((nbytes=sendto(sockbcast, recu,strlen(recu), 0,(struct sockaddr *)&their_addr, sizeof their_addr)) == -1) 
						{
							perror("sendto");
							exit(1);
						}
						printf("sent %s  %d bytes to %s\n", recu,nbytes,inet_ntoa(their_addr.sin_addr));
					}
					raz(recu,nbytes);
				} // END handle data from client
			} // END got new incoming connection
		} // END looping through file descriptors
	} // END for(;;)--and you thought it would never end!
	return 0;
}
