#include "stdafx.h"
#include "Client.h"
#include  <string>

#define PORT "80"
#define MAX_STRING_SIZE	30

using namespace std;
bool ip_path_validation(string * str, char * ip, char * path);
int main(int argc, char* argv[])
{
	char ip[24];
	char path[20];	
	char * answer;
	FILE * pFile;
	client cl;
	string received;
	bool a;
	

	cout << "Ingrese IP Y PATH asi: ip/path\nLuego presione ENTER" << endl;
	cin >> received;
	a = ip_path_validation(&received, ip,path);

	cout << "Trying to connect to " << ip << " on port " << PORT << std::endl;

	if (cl.startConnection(ip))
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

bool ip_path_validation(string * str, char * ip, char * path)
{
	unsigned int counter = 0;
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
	strcpy(ip, ipS.c_str());
	strcpy(path, pathS.c_str());
	return true;

}