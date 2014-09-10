/*
 ** client.c -- a stream socket client demo
 */
#include "client.h"
// get sockaddr, IPv4 or IPv6:
/*
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
 */
int connect_tcp (char* adresse)
{//Se connecte ne TCP au serveur de renvoie le numero de socket
	int sockfd, numbytes;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo(adresse, PORT, &hints, &servinfo)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	// loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) 
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) 
		{
			perror("client: socket");
			return 0;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
		{
			close(sockfd);
			perror("client: connect");
			return 0;
		}
		break;
	}
	if (p == NULL) 
	{
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),s, sizeof s);
	printf("client: connecting in tcp to %s on port %d\n", s,htons(((struct sockaddr_in *)p->ai_addr)->sin_port));

	freeaddrinfo(servinfo); // all done with this structure
	printf("Connecté en TCP sur la socket %d\n",sockfd);
	return sockfd;
}

void envoi_message (int sock,int touche)
{//Envoi un ordre au serveur (deplacement du perso ou attaque)
	printf("On va envoyer %i a la socket %i\n",touche,sock);
	int read_ret=0;
	char* buf=(char*)calloc(MAXDATASIZE,sizeof(char));
	crypt(buf,touche);//On crypte le message
	printf("Message crypté : %s\n",buf);
	read_ret=strlen(buf);
	printf("read_ret=%i\n",read_ret);
	buf[read_ret]='\0';
	if ((read_ret=send(sock,buf,read_ret,0))<0)
	{
		perror("Erreur d'ecriture sur la socket");
		exit(EXIT_FAILURE);
	}
	printf("Message envoyé\n");
	free(buf);
}

void envoi_ok (int sock)
{
	int read_ret=0;
	char *buf=(char *)calloc(8,sizeof(char));
	strcpy(buf,"OK\0");
	read_ret=strlen(buf);
	if ((read_ret=send(sock,buf,read_ret,0))<0)
	{
		perror("Envoi de OK");
		exit(EXIT_FAILURE);
	}
	printf("OK envoyé\n");
	free(buf);
}

void remplir_struct (char* m, sdl_c *map)
{//Lorsque l'on recoit un message du serveur on l'analyse pour savoir quoi mettre a jour
	printf("Analyse du message ...");
	int i=0;
	char buf[32];
	int k=0;
	int j=0;
	int pnj=0;
	int pj=0;
	int player=0;
	if (strncmp(m,"LOAD_PJ",7)==0)//Commande LOAD
	{
		printf("c'est une commande load ... ");
		sscanf(m,"LOAD_PJ%dPNJ%dP%d",&i,&pnj,&player);
		printf("il y a %i pj et %i pnj\n",i,pnj);
		if (map->nb_pnj!=pnj)//Si le client est un nouveau client
		{
			map->nb_pj=i;
			map->nb_pnj=pnj;
			n_player=player;
			allocation_pers(map);//On alloue de la memoire pour tous les perso pj et pnj
		}
		else//Si le client a deja tout charge et qu'il s'agit de la connection d'un nouveau joueur
		{
			load_pj(map,NULL,map->nb_pj);//Il ne charge que le nouveau joueur
			map->nb_pj++;
		}
	}
	else
	{
		if (strncmp(m,"LOAD_PNJ",8)==0)
		{
			printf("c'est une commande load_pnj ... ");
                	sscanf(m,"LOAD_PNJ%d",&pnj);
                	printf("il y a %i pnj\n",pnj);
			map->nb_pnj=pnj;
			load_pnj(map,"102005050",0,map->nb_pnj);
			envoi_ok(socktcp);
		}
		else
		{

		if (strncmp(m,"UNLOAD_PJ",9)==0)//Commande UNLOAD
		{
			printf("C'est une commande unload...");
			sscanf(m,"UNLOAD_PJ%d",&i);
			unload_pj(map,i);//Pas de question a se poser on dealloue la memoire du perso i
		}
		else
		{
			if (strncmp(m,"UNLOAD_PNJ",10)==0)
			{
				printf("C'est une commande Unload_pnj...");
				sscanf(m,"UNLOAD_PNJ%d",&i);
				unload_pnj(map,i);
			}
			else
			{
				if (strncmp(m,"PNJ",3)==0)
				{
					printf("c'est une mise a jour des coord des pnj...\n");
					for (i=3;i<strlen(m);i++)//On decompose le message recu
					{
						while (m[i]!='x')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						j=atoi(buf);
						printf("il s'agit du pnj %i",j);
						i++;
						k=0;
						while (m[i]!='y')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tac[j]->pos.x=atoi(buf);
						printf(" nouvelle coord x=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='p')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tac[j]->pos.y=atoi(buf);
						printf(" y=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='s')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tac[j]->pv=atoi(buf);
						printf(" pv=%i\n",atoi(buf));
						i++;
						k=0;
						map->tac[j]->sens=m[i]-48;
						i++;
						map->tac[j]->pos_s=m[i]-48;
						i++;
						map->tac[j]->att=m[i]-48;
						move_c_net (map,j);
					}
				}
				else
				{
					printf("C'est une mise a jour des coordonnees...");
					for (i=0;i<strlen(m);i++)
					{
						while (m[i]!='x')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						j=atoi(buf);
						printf("il s'agit du joueur %i",j);
						i++;
						k=0;
						while (m[i]!='y')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tab[j]->pos.x=atoi(buf);
						printf(" nouvelle coord x=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='p')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tab[j]->pos.y=atoi(buf);
						printf(" y=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='m')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tab[j]->pv=atoi(buf);
						printf(" pv=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='d')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tab[j]->pv_m=atoi(buf);
						printf(" pv_m=%i",atoi(buf));
						i++;
						k=0;
						while (m[i]!='s')
						{
							buf[k]=m[i];
							i++;
							k++;
						}
						buf[k]='\0';
						map->tab[j]->deg=atoi(buf);
						printf(" deg=%i",atoi(buf));
						i++;
						k=0;
						map->tab[j]->sens=m[i]-48;
						i++;
						map->tab[j]->pos_s=m[i]-48;
						i++;
						map->tab[j]->att=m[i]-48;
						move_p_net (map,j);
						printf(" sens=%i\n",m[i]-48);
						printf("Le joueur %i se deplace en x=%i, y=%i, s=%i\n",j,map->tab[j]->pos.x,map->tab[j]->pos.y,map->tab[j]->sens);
					}
				}
			}
		}
		}
	}
}

void* client(sdl_c *map)
{
	printf("Client lancé \n");
	int read_ret=0;
	char* buf=(char *)calloc(MAXDATASIZE,sizeof(char));
	int sockbcast;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr_storage their_addr;
	socklen_t addr_len;
	char s[INET6_ADDRSTRLEN];
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP
	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}
	// loop through all the results and bind to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next)
	{
		if (( sockbcast = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1)
		{
			perror("listener: socket");
			continue;
		}
		if (bind( sockbcast, p->ai_addr, p->ai_addrlen) == -1)
		{
			close( sockbcast );
			perror("listener: bind");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "listener: failed to bind socket\n");
		exit(2);
	}
	freeaddrinfo(servinfo);
	addr_len = sizeof their_addr;
	printf("Service de reception bcast initialisé\n");
	int raz=0;
	while (1)
	{
		printf("listener: waiting to recvfrom...\n");
		if ((numbytes = recvfrom( sockbcast, buf, MAXDATASIZE-1 , 0,(struct sockaddr *)&their_addr, &addr_len)) == -1) 
		{
			perror("recvfrom");
			exit(1);
		}
		else
		{
			printf("message recu : %s de %d bytes\n",buf,numbytes);
			buf[numbytes]='\0';
			remplir_struct(buf,map);
		}
		for (raz=0;raz<numbytes;raz++)
			buf[raz]='\0';
	}
	close( sockbcast );
	return 0;
}
