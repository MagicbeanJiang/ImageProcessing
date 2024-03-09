#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<memory.h>
using namespace std;
double PitchX, PitchY, PitchZ, Thickness;
unsigned short int pixel[761][512][512];
unsigned short int newpixel[761][512][512] = { 0 };
int allvoxel[761][512][512] = { 0 };


int main( )
{
	string OrgFile;
	int SizeX, SizeY, SizeZ;
	/*short x = '1';
	char *p = (char *)&x;
	cout << *p << endl;
	cout << *(p + 1) << endl;*/

	OrgFile = "colon104.512.gz";
	SizeX = 512;
	SizeY = 512;
	SizeZ = 761;
	PitchX = 1;//0.625000;
	PitchY = 1;// 0.625000;
	PitchZ = 1;// 0.500000;
	Thickness = 1.000000;
	ifstream fin;
	ofstream fout;
	fin.open("colon104.512", ios::binary);
	fin.read(reinterpret_cast<char*>(&pixel[0][0][0]), sizeof(pixel));
	_swab((char*)pixel, (char *)pixel, sizeof(pixel));

	//得到z方向的梯度
	fout.open("z.dat", ios::binary);
	cout << "calculating z..." << endl;
	for (int i = 1; i < SizeZ; i++)
	{
		for (int j = 0; j < SizeY; j++)
		{
			for (int k = 0; k < SizeX; k++)
			{
				newpixel[i][j][k] = abs((pixel[i][j][k] - pixel[i - 1][j][k]) / PitchZ);
				if (i != 0 && j != 0 && k != 0) allvoxel[i][j][k] += newpixel[i][j][k] * newpixel[i][j][k];
			}
		}
	}
	int len = sizeof(newpixel);
	_swab((char*)newpixel, (char *)newpixel, sizeof(newpixel));
	fout.write(reinterpret_cast<char*>(&(newpixel[0][0][0])), len);
	fout.close();
	cout << "z calculation done" << endl;


	//得到y方向的梯度
	memset(newpixel, 0, sizeof(newpixel));
	fout.open("y.dat", ios::binary);
	cout << "calculating y..." << endl;
	for (int j = 1; j < SizeY; j++)
	{
		for (int i = 0; i < SizeZ; i++)
		{
			for (int k = 0; k < SizeX; k++)
			{
				newpixel[i][j][k] = abs((pixel[i][j][k] - pixel[i][j-1][k]) / PitchZ);
				if (i != 0 && j != 0 && k != 0) allvoxel[i][j][k] += newpixel[i][j][k] * newpixel[i][j][k];
			}
		}
	}
	 len = sizeof(newpixel);
	 _swab((char*)newpixel, (char *)newpixel, sizeof(newpixel));
	fout.write(reinterpret_cast<char*>(&(newpixel[0][0][0])), len);
	fout.close();
	cout << "y calculation done" << endl;


	//得到x方向的梯度
	memset(newpixel, 0, sizeof(newpixel));
	fout.open("x.dat", ios::binary);
	cout << "calculating x..." << endl;
	for (int k = 1; k < SizeX; k++)
	{
		for (int j = 0; j < SizeY; j++)
		{
			for (int i = 0; i < SizeZ; i++)
			{
				newpixel[i][j][k] = abs((pixel[i][j][k] - pixel[i][j][k-1]) / PitchZ);
				if (i != 0 && j != 0 && k != 0) allvoxel[i][j][k] += newpixel[i][j][k] * newpixel[i][j][k];
			}
		}
	}
	 len = sizeof(newpixel);
	 _swab((char*)newpixel, (char *)newpixel, sizeof(newpixel));
	fout.write(reinterpret_cast<char*>(&(newpixel[0][0][0])), len);
	fout.close();
	cout << "x calculation done" << endl;


	//得到三个方向合成的梯度
	fout.open("all.dat", ios::binary);
	for (int i = 0; i < SizeZ; i++)
	{
		for (int j = 0; j < SizeY; j++)
		{
			for (int k = 0; k < SizeX; k++)
			{
				newpixel[i][j][k] = sqrt(allvoxel[i][j][k]);
			}
		}
	}
   len = sizeof(newpixel);
   _swab((char*)newpixel, (char *)newpixel, sizeof(newpixel));
	fout.write(reinterpret_cast<char*>(&(newpixel[0][0][0])), len);
	fout.close();



	fin.close();
	return 0;
}