#include "Image.h"
#include "Color.h"
#include <fstream>
#include <iostream>

#pragma pack(2)

Image::Image(unsigned int width, unsigned int height):
	m_xResolution(width),m_yResolution(height),
	m_data(new uint8_t[width * height * 3])
{
}

Image::~Image()
{
	delete m_data;
}

void Image::SetColor(unsigned int x, unsigned int y, const Color &color)
{
	uint8_t *location = m_data + y * m_xResolution * 3 + x * 3;
	*location = static_cast<unsigned int>(color.r * 255);
	++location;
	*location = static_cast<unsigned int>(color.g * 255);
	++location;
	*location = static_cast<unsigned int>(color.b * 255);
}

typedef struct tagBITMAPFILEHEADER
{
	uint16_t bfType;      //2Bytes，必须为"BM"，即0x424D 才是Windows位图文件
	uint32_t bfSize;	  //4Bytes，整个BMP文件的大小
	uint16_t bfReserved1; //2Bytes，保留，为0
	uint16_t bfReserved2; //2Bytes，保留，为0
	uint32_t bfOffBits;	  //4Bytes，文件起始位置到图像像素数据的字节偏移量

	//UINT16 bfType;        //2Bytes，必须为"BM"，即0x424D 才是Windows位图文件
	//DWORD bfSize;         //4Bytes，整个BMP文件的大小
	//UINT16 bfReserved1;  //2Bytes，保留，为0
	//UINT16 bfReserved2;  //2Bytes，保留，为0
	//DWORD bfOffBits;     //4Bytes，文件起始位置到图像像素数据的字节偏移量
} BITMAPFILEHEADER;

typedef struct _tagBMP_INFOHEADER
{
	uint32_t biSize;		//4Bytes，INFOHEADER结构体大小，存在其他版本I NFOHEADER，用作区分
	uint32_t biWidth;		 //4Bytes，图像宽度（以像素为单位）
	uint32_t biHeight;	  //4Bytes，图像高度，+：图像存储顺序为Bottom2Top，-：Top2Bottom
	uint16_t biPlanes;	  //2Bytes，图像数据平面，BMP存储RGB数据，因此总为1
	uint16_t biBitCount;		 //2Bytes，图像像素位数
	uint32_t biCompression;	//4Bytes，0：不压缩，1：RLE8，2：RLE4
	uint32_t biSizeImage;		//4Bytes，4字节对齐的图像数据大小
	uint32_t biXPelsPerMeter;	//4 Bytes，用象素/米表示的水平分辨率
	uint32_t biYPelsPerMeter;	//4 Bytes，用象素/米表示的垂直分辨率
	uint32_t biClrUsed;		 //4 Bytes，实际使用的调色板索引数，0：使用所有的调色板索引
	uint32_t biClrImportant;	//4 Bytes，重要的调色板索引数，0：所有的调色板索引都重要

	//DWORD  biSize;    //4Bytes，INFOHEADER结构体大小，存在其他版本I NFOHEADER，用作区分
	//LONG   biWidth;    //4Bytes，图像宽度（以像素为单位）
	//LONG   biHeight;    //4Bytes，图像高度，+：图像存储顺序为Bottom2Top，-：Top2Bottom
	//WORD   biPlanes;    //2Bytes，图像数据平面，BMP存储RGB数据，因此总为1
	//WORD   biBitCount;         //2Bytes，图像像素位数
	//DWORD  biCompression;     //4Bytes，0：不压缩，1：RLE8，2：RLE4
	//DWORD  biSizeImage;       //4Bytes，4字节对齐的图像数据大小
	//LONG   biXPelsPerMeter;   //4 Bytes，用象素/米表示的水平分辨率
	//LONG   biYPelsPerMeter;   //4 Bytes，用象素/米表示的垂直分辨率
	//DWORD  biClrUsed;          //4 Bytes，实际使用的调色板索引数，0：使用所有的调色板索引
	//DWORD biClrImportant;     //4 Bytes，重要的调色板索引数，0：所有的调色板索引都重要
}BMP_INFOHEADER;

typedef struct _tagRGBQUAD
{
	uint8_t rgbBlue;       //指定蓝色强度
	uint8_t rgbGreen;      //指定绿色强度
	uint8_t rgbRed;        //指定红色强度
	uint8_t rgbReserved;  //保留，设置为0

	//BYTE  rgbBlue;       //指定蓝色强度
	//BYTE  rgbGreen;      //指定绿色强度
	//BYTE  rgbRed;        //指定红色强度
	//BYTE  rgbReserved;  //保留，设置为0
} RGBQUAD;

typedef struct tagIMAGEDATA
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}IMAGEDATA;

void Image::WriteToFile(const std::string filename)
{
	BITMAPFILEHEADER header;
	//memset(&header, 0, sizeof(header));
	header.bfType = 0x4D42;
	header.bfSize = 54+m_xResolution*m_yResolution*3; //size of this bmp (Byte)
	header.bfReserved1 = 0;
	header.bfReserved2 = 0;
	header.bfOffBits = 54; // offbit from 0000h to imagedata

	BMP_INFOHEADER info;
	memset(&info, 0, sizeof(info));
	info.biSize = 40;
	info.biWidth = 800;
	info.biHeight = 600;
	info.biPlanes = 1;
	info.biBitCount = 24;
	info.biCompression = 0;
	info.biSizeImage = 0;
	info.biXPelsPerMeter = 0;
	info.biYPelsPerMeter = 0;
	info.biClrUsed = 0;
	info.biClrImportant = 0;

	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	file.write((char *)&header, sizeof(header));
	file.write((char *)&info, sizeof(info));
	file.write((char *)m_data, m_xResolution*m_yResolution * 3);
	
	file.close();
}

