#include "stdafx.h"
#include "Client.h"

#define PORT "80"
#define SERVER_IP "127.0.0.1"

using namespace std;

int main(int argc, char* argv[])
{
	char * ip;				//PONER ACA IP
	char * path;			//PONER ACA PATH
	char * answer;
	FILE * pFile;
	client cl;
	cout << "Trying to connect to " << SERVER_IP << " on port " << PORT << std::endl;

	if (cl.startConnection(SERVER_IP))
	{
		if (cl.send_message(ip,path))
		{
			answer = cl.receive_message();
			pFile = fopen("output.txt", "w+");
			if (pFile != NULL)
			{
				fputs(answer, pFile);
			}
			else
			{
				cout << "Error creating output text file." << endl;
			}
			fclose(pFile);
		}
	}
	else
	{
		cout << "There was an error while trying to connect to the server." << endl;
	}	
	cout << "Press Enter to close client." << std::endl;
	getchar();
	return 0;
}