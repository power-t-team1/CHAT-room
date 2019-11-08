#include "common.h"
extern pthread_mutex_t mutex;
extern int clients[20];
extern int n;
extern server_db *head, *head1;
extern int flag;

void displayactiveusers(int sock)
{
	server_db *temp1 = head1;
	char *user= NULL;
	char *user1= NULL;


	pthread_mutex_lock(&mutex);
	send(sock, "Active users\n", 13, 0);
	
	if (head1 == NULL)
	{
		send(sock, "NILL\n", 5, 0);
	}
	
	
	while (temp1)
		{
			user = temp1 -> username;
			if (temp1->cl_num != sock)
			{
				send(sock, user, strlen(user), 0);
			}
			else
			{
				user1 = temp1 -> username;
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
