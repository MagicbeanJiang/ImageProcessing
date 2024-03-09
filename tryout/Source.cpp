#include<iostream>
#include<fstream>
#include<string>
using namespace std;
	double PitchX, PitchY, PitchZ,Thickness;
	 unsigned short int pixel[761][512][512];
	 unsigned short int newpixel[761][512][512] = {0};

	 //int f(int x[4][], int y);


int main()
{
	string OrgFile;
	int SizeX, SizeY, SizeZ;
	short x = '1';
	char *p = (char *)&x;
	cout << *p << endl;
	cout << *(p + 1) << endl;

	OrgFile = "colon104.512.gz";
	SizeX = 512;
    SizeY=512;
    SizeZ= 761;
	PitchX = 0.625000;
	PitchY = 0.625000;
	PitchZ = 0.500000;
	Thickness = 1.000000;
	ifstream fin;
	ofstream fout;
	fin.open("colon104.512",ios::binary);
	fout.open("new.dat",ios::binary);

	/*
	for (int i = 0; i <514; i++)
	{
		for (int j = 0; j <514; j++)
		{
			for (int k = 0; k <763; k++)
			{
				pixel[i][j][k]=10000;
			}

		}
	}

	{
		for (int i = 1; i <= SizeX; i++)
		{
			for (int j = 1; j <= SizeY; j++)
			{
				for (int k = 1; k <= SizeZ; k++)
				{
				}

			}
		}
	}
	
	*/
	
	fin.read(reinterpret_cast<char*>(&pixel[0][0][0]), sizeof(pixel));

	//fout.write(reinterpret_cast<char*>(&(pixel[0][0][0])), sizeof(pixel));
	
	for (int i = 1; i < SizeZ-1; i++)
	{
		for (int j = 1; j < SizeY-1; j++)
		{
			for (int k = 1; k < SizeX-1; k++)
			{
				//int cnt = 0;
				double er=0;
				for (int m = i-1; m <= i + 1; m++)
				{
					for (int n = j-1; n <= j + 1; n++)
					{
						for (int p = k-1; p <= k + 1; p++)
						{
							//if (pixel[m][n][p] != 10000)
							{
								unsigned short x = (pixel[m][n][p] & 0x00ff)<<8 | (pixel[m][n][p] & 0xff00) >> 8;
								er += x;
								//cnt++;
							}
						}
					}
				}
				unsigned short x = int(0.5 + (er / 27.0));
				newpixel[i][j][k] = (x & 0x00ff) << 8 | (x & 0xff00) >> 8;
				
				
			}
		}
	}
	int len = sizeof(newpixel);
	cout << endl << len << endl;
	fout.write(reinterpret_cast<char*>(&(newpixel[0][0][0])), len);
	
	fin.close();
	fout.close();

	return 0;
}