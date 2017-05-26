/* 
 * 
 * funtion: 二分类SVM分类器
 * 
 *    Author: Bill Wang
 */

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <malloc.h>
#include<string>
#include<fstream>

using namespace cv;
using namespace std;

void usage()
{
	cout<<"It is 4-dimension SVM\n"
		<<"The first parameter is the FIRST part .txt file\n"
		<<"the second parameter is the other part file\n";
}

//动态分配二维数组空间，N*M
void wh_array2_malloc(int N,int M,float ** &array)
{
	array = (float **)malloc(sizeof(float *)*N);
	for (int i=0; i<N; i++)
		array[i] = (float *)malloc(sizeof(float)*M);
}

//释放二维数组空间
void wh_array2_malloc_free(int N,int M,float ** &array)
{
	for (int i=0; i<N; i++)
		free((void *)array[i]);
	free((void *)array);
}

void merge_arrays(float ** ptr1,float ** ptr2,int count1, int count2, float ** &data)
{
	wh_array2_malloc(count1+count2,4,data);
	int pointer=0;
	for ( ;pointer<count1;++pointer)
	{
		data[pointer][0]=ptr1[pointer][0];
		data[pointer][1]=ptr1[pointer][1];
		data[pointer][2]=ptr1[pointer][2];
		data[pointer][3]=ptr1[pointer][3];
	}

	for ( ;pointer<count1+count2;++pointer)
	{
		data[pointer][0]=ptr2[pointer-count1][0];
		data[pointer][1]=ptr2[pointer-count1][1];
		data[pointer][2]=ptr2[pointer-count1][2];
		data[pointer][3]=ptr2[pointer-count1][3];
	}
}

//返回有数据的行数
int read_from_txt(string path,float ** &content)
{
	//获取文件行数
	int count=0;
	ifstream fileline(path);
	string linetemp;
	while( getline(fileline,linetemp) )
		count++;
	fileline.close();

	//动态分配大小
	wh_array2_malloc(count,4,content);

	//正式的数组赋值
	ifstream file(path);
	for (int i=0;i<count;++i)
		for (int j = 0; j < 4; j++)
			file >> content[i][j];
	file.close();

	return count;
}

int main(int argc , char * argv[])
{
	usage();

	float** data;
	float** ptr1,** ptr2;
	//读入正常部分txt内容，计算总数
	int count1 = read_from_txt(argv[1],ptr1);
	ptr2 = &data[count1];
	int count2 = read_from_txt(argv[2],ptr2);

	//合并两个数组
	merge_arrays(ptr1,ptr2,count1,count2,data);
	wh_array2_malloc_free(count1,4,ptr1);
	wh_array2_malloc_free(count2,4,ptr2);

	wh_array2_malloc_free(count1+count2,4,data);
	return 0;
}