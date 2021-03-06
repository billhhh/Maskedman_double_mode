#pragma once
#include <stdio.h>
#include <vector>
#include <qfile.h>
#include <QTextCodec>
#include <QStringList>
#include <QTextStream>
#include <qthread.h>
#include "EventNode.h"


class FileOperation
{
public:
	FileOperation(void);
	~FileOperation(void);
public:
	static void writeToFile(char* filePath, int jiange, int fps, int key_jiange, vector<EventNode> eventList);   //将摘要信息写入文件
	static void readFromFile(QString filePath, int& jiange, int& fps, int& key_jiange, vector<EventNode>& eventList);  //从文件读取摘要信息
};

