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
	uint16_t bfType;      //2Bytes������Ϊ"BM"����0x424D ����Windowsλͼ�ļ�
	uint32_t bfSize;	  //4Bytes������BMP�ļ��Ĵ�С
	uint16_t bfReserved1; //2Bytes��������Ϊ0
	uint16_t bfReserved2; //2Bytes��������Ϊ0
	uint32_t bfOffBits;	  //4Bytes���ļ���ʼλ�õ�ͼ���������ݵ��ֽ�ƫ����

	//UINT16 bfType;        //2Bytes������Ϊ"BM"����0x424D ����Windowsλͼ�ļ�
	//DWORD bfSize;         //4Bytes������BMP�ļ��Ĵ�С
	//UINT16 bfReserved1;  //2Bytes��������Ϊ0
	//UINT16 bfReserved2;  //2Bytes��������Ϊ0
	//DWORD bfOffBits;     //4Bytes���ļ���ʼλ�õ�ͼ���������ݵ��ֽ�ƫ����
} BITMAPFILEHEADER;

typedef struct _tagBMP_INFOHEADER
{
	uint32_t biSize;		//4Bytes��INFOHEADER�ṹ���С�����������汾I NFOHEADER����������
	uint32_t biWidth;		 //4Bytes��ͼ���ȣ�������Ϊ��λ��
	uint32_t biHeight;	  //4Bytes��ͼ��߶ȣ�+��ͼ��洢˳��ΪBottom2Top��-��Top2Bottom
	uint16_t biPlanes;	  //2Bytes��ͼ������ƽ�棬BMP�洢RGB���ݣ������Ϊ1
	uint16_t biBitCount;		 //2Bytes��ͼ������λ��
	uint32_t biCompression;	//4Bytes��0����ѹ����1��RLE8��2��RLE4
	uint32_t biSizeImage;		//4Bytes��4�ֽڶ����ͼ�����ݴ�С
	uint32_t biXPelsPerMeter;	//4 Bytes��������/�ױ�ʾ��ˮƽ�ֱ���
	uint32_t biYPelsPerMeter;	//4 Bytes��������/�ױ�ʾ�Ĵ�ֱ�ֱ���
	uint32_t biClrUsed;		 //4 Bytes��ʵ��ʹ�õĵ�ɫ����������0��ʹ�����еĵ�ɫ������
	uint32_t biClrImportant;	//4 Bytes����Ҫ�ĵ�ɫ����������0�����еĵ�ɫ����������Ҫ

	//DWORD  biSize;    //4Bytes��INFOHEADER�ṹ���С�����������汾I NFOHEADER����������
	//LONG   biWidth;    //4Bytes��ͼ���ȣ�������Ϊ��λ��
	//LONG   biHeight;    //4Bytes��ͼ��߶ȣ�+��ͼ��洢˳��ΪBottom2Top��-��Top2Bottom
	//WORD   biPlanes;    //2Bytes��ͼ������ƽ�棬BMP�洢RGB���ݣ������Ϊ1
	//WORD   biBitCount;         //2Bytes��ͼ������λ��
	//DWORD  biCompression;     //4Bytes��0����ѹ����1��RLE8��2��RLE4
	//DWORD  biSizeImage;       //4Bytes��4�ֽڶ����ͼ�����ݴ�С
	//LONG   biXPelsPerMeter;   //4 Bytes��������/�ױ�ʾ��ˮƽ�ֱ���
	//LONG   biYPelsPerMeter;   //4 Bytes��������/�ױ�ʾ�Ĵ�ֱ�ֱ���
	//DWORD  biClrUsed;          //4 Bytes��ʵ��ʹ�õĵ�ɫ����������0��ʹ�����еĵ�ɫ������
	//DWORD biClrImportant;     //4 Bytes����Ҫ�ĵ�ɫ����������0�����еĵ�ɫ����������Ҫ
}BMP_INFOHEADER;

typedef struct _tagRGBQUAD
{
	uint8_t rgbBlue;       //ָ����ɫǿ��
	uint8_t rgbGreen;      //ָ����ɫǿ��
	uint8_t rgbRed;        //ָ����ɫǿ��
	uint8_t rgbReserved;  //����������Ϊ0

	//BYTE  rgbBlue;       //ָ����ɫǿ��
	//BYTE  rgbGreen;      //ָ����ɫǿ��
	//BYTE  rgbRed;        //ָ����ɫǿ��
	//BYTE  rgbReserved;  //����������Ϊ0
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

