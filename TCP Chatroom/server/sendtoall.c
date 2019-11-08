#include "common.h"

extern pthread_mutex_t mutex;
extern int clients[20];
extern int n;
extern server_db *head, *head1;
extern int flag;

void sendtoall(char *msg,int curr)
{
	int i;
	server_db *temp = head1;
	server_db *temp1 = head1;
	char *user= NULL;

	pthread_mutex_lock(&mutex);

//	if (flag)
//	{
/*		while (temp1)
		{
			user = temp1 -> username;
			if (temp1->cl_num != curr)
			{
				send(curr, user, strlen(user), 0);
			}

			temp1 = temp1-> link;

		}
		flag = 0;
//	}*/

	while(temp)
	{
		printf("cl_num: %d\n curr : %d\n", temp -> cl_num, curr);
		if (temp->cl_num != curr)
		{
			send(temp->cl_num, msg, strlen(msg), 0);
		}
		temp = temp->link;
	}

	/*	for(i = 0; i < n; i++)
		{
		if(clients[i] != curr)
		{
		if(send(clients[i],msg,strlen(msg),0) < 0)
		{
		printf("sending failure \n");
		continue;
		}
		}
		}*/
	pthread_mutex_unlock(&mutex);
}

