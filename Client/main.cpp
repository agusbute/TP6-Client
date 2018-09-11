#include "stdafx.h"
#include "Client.h"
#include  <string>

#define PORT "80"
#define MAX_STRING_SIZE	30
#define SERVER_IP "127.0.0.1"

using namespace std;
bool ip_path_validation(string * str, char ** ip, char ** path);
int main(int argc, char* argv[])
{
	char * ip = (char *)calloc(MAX_STRING_SIZE, 1);
	char * path = (char *)calloc(MAX_STRING_SIZE, 1);	
	char * answer;
	FILE * pFile;
	client cl;
	string received;
	bool a;
	cout << "Trying to connect to " << SERVER_IP << " on port " << PORT << std::endl;

	cout << "Ingrese IP Y PATH asi: ip/path\nLuego presione ENTER" << endl;
	cin >> received;
	a = ip_path_validation(&received, &ip, &path);

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
	free(path);
	free(ip);
	return 0;
}

bool ip_path_validation(string * str, char ** ip, char ** path)
{
	int counter = 0;
	size_t stringSize = (*str).size();
	for (int i = 0; i <stringSize; i++)
	{
		if ((*str)[i] == '/')
			counter++;
	}
	if (counter != 1)
		return false;
	size_t limitPos = str->find("/");
	std::string ipS = str->substr(0, limitPos);
	std::string pathS = str->substr(limitPos + 1, stringSize);
	(*ip) = (char *)ipS.c_str();
	(*path) = (char *)pathS.c_str();
	return true;

}