#include "common.h"

extern int clients[20];
extern int n;
extern server_db *head, *head1;
extern int flag;

int authentication(int sock)
{
	server_db user;
	char msg[20];
	char pass[6];
	char option[1];
	int len, i;
	while (1)
	{
		send(sock, "1.Register 2.Login 3.Logout\n",28,0);
		recv(sock, msg, 20, 0);
		printf("Server received : %s\n", msg);
		switch (msg[0])
		{
			case '1': 
				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				send(sock, "In register...\n",17,0);
				send(sock, "enter username: \n",20,0);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				printf("Server received : %s\n", msg);
				//Need to search user first and then proceed
				int ret = search_list(&head, msg, NULL, 1);
				if(ret == 1)
				{
					send(sock, "Enter Password: \n",20,0);
					len = recv(sock, pass, 5, 0);
					pass[len] = '\0';
					printf("Server received : %s\n", pass);

					if ((insert_at_last(&head, msg, pass, sock, 0)) == 0)
					{
						send(sock, "User already present\n",25,0);
					}
					else
					{
						send(sock, "Registered\n",20,0);
					}
				}
				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				break;

			case '2': 
				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				send(sock, "In login...\n",17,0);
				//send(sock, "enter username: ",17,0);
				write(sock, "enter username: \n",20);
				len = recv(sock, msg, 20, 0);
				msg[len] = '\0';
				printf("Server received : %s\n", msg);
				//Need to search user first and then proceed
				send(sock, "Enter Password: \n",17,0);
				len = recv(sock, pass, 5, 0);
				printf("length %d Server received : %s\n", len, pass);
				pass[len] = '\0';
				if (search_list(&head, msg, pass, 2))
				{
					send(sock, "Login successi\n",20,0);


					//Insert the logged in user in 2nd list
					//insert_at_last(&head1,msg, pass, sock);

					send(sock, "Authentication success\n", 23, 0);
				
					//memset(msg, '\0', 20);
					send(sock, "1.Groupchat 2.Singlechat 3.Logout\n", 34, 0);
					recv(sock, option, 20, 0);

					switch (option[0])
					{
						case '1' :
							insert_at_last(&head1,msg, pass, sock, 1);
							displayactiveusers(sock);
							return 1;

						case '2':
							insert_at_last(&head1,msg, pass, sock, 2);
							displayactiveusers(sock);
							return 2;

						default:
							return 3;
							

							
					}

/*					if(flag == 1)
					{
						clients[i] = sock;
						flag = 0;
					}*/
					
				}
				
				send(sock, "Login Failed\n",20,0);
			//	fd = sock;
			/*	i = n-1;
				clients[i] = 0;
				flag = 1;*/

				memset(msg, '\0', 20);
				memset(pass, '\0', 5);
				break;
			default:
				send(sock, "Wrong option\n",14,0);
		}
	}

}

