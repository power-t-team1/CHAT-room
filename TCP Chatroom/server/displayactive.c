#include "common.h"

extern pthread_mutex_t mutex;
extern int clients[20];
extern int n;
extern server_db *head, *head1;
extern int flag;

void displayactiveusers(int sock)
{
	server_db *temp1 = head1;
	char user[25];
	char user1[25];
	int len;


	pthread_mutex_lock(&mutex);
	//send(sock, "Active users\n", 13, 0);
	
	if (head1->link == NULL)
	{
		send(sock, "No users online\n", 16, 0);
	}
	
	
	while (temp1)
		{
			strcpy(user, temp1 -> username);
			len = strlen(user);
			user[len - 1] = '\0';
			strcat(user, " is online\n");
			printf("User : %s\n", user);
			if (temp1->cl_num != sock)
			{
				send(sock, user, strlen(user), 0);
			}
			else
			{
				strcpy(user1, temp1 -> username);
				len = strlen(user1);
				user1[len - 1] = '\0';
				strcat(user1, " has logged in\n");
				printf("User1 : %s\n", user1);
			}

			temp1 = temp1-> link;

		}

		temp1 = head1;

		while (temp1)
		{
			if ((temp1->cl_num != sock) && (temp1->mode == 1))
			{
				send(temp1->cl_num, user1, strlen(user1), 0);
			}
			temp1 = temp1 -> link;
			
		}



	pthread_mutex_unlock(&mutex);

}
