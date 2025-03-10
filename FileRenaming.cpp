#define _CRT_SECURE_NO_WARNINGS
#include <string>
//#include<io.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

using namespace std;

class Findupdate {
public:

	int checkFile(const string fileName);
};

int Findupdate::checkFile(const string fileName)
{
	//1、读取绝对路径		2、遍历指定后缀的文件，更改为 Result+序号		3、输出文件名序列
	//读取文件夹下所有文件（指定后缀）
	vector<string> Files;

	DIR *dirptr = NULL;
	struct dirent *dirp;

	printf("000000\n");

	if ((dirptr = opendir(fileName.c_str())) == NULL)//打开一个目录
	{
		return 0;
	}
	printf("11111\n");
	while ((dirp = readdir(dirptr)) != NULL)
	{
		if ((dirp->d_type == DT_REG) && 0 == (strcmp(strchr(dirp->d_name, '.'), ".stp")))//判断是否为文件以及文件后缀名
		{
			Files.push_back(dirp->d_name);
		}

	}
	closedir(dirptr);

	printf("11111\n");

	for (int i = 0; i < Files.size(); i++)
	{
		string Result;

		if (i < 10)
		{
			Result = "//Result-0";
		}
		else
		{
			Result = "//Result-";
		}

		char F_PATH[100];
		strcpy(F_PATH, fileName.c_str());
		strcat(F_PATH, Result.c_str());
		char F_ID[64];
		char *F_PATH_ = (char *)".stp";

		sprintf(F_ID, "%d", i);
		strcat(F_PATH, F_ID);
		strcat(F_PATH, F_PATH_);

		rename(Files[i].c_str(), F_PATH);

	}

	return 1;
}


int main()
{
	Findupdate Test;
	Test.checkFile("/home/zuoyan/Test");
	//printf("&d", Test.checkFile("\\home\\zuoyan\\Test"));
	return 1;
}
