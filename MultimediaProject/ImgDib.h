
#ifndef _INSIDE_VISUAL_CPP_ImgDib
#define _INSIDE_VISUAL_CPP_ImgDib

//ImgDib��
class ImgDib
{
public:
	// ͼ������ָ��
	unsigned char * m_pImgData;

	// ͼ����ɫ��ָ��
	LPRGBQUAD m_lpColorTable;

	//λ��
	int m_nBitCount;


private:
	//ָ��DIB��ָ��: ����BITMAPFILEHEADER��BITMAPINFOHEADER����ɫ��
	LPBYTE m_lpDib;

	//�߼���ɫ����
	HPALETTE m_hPalette;

	//��ɫ���ȣ����ٸ����
	int m_nColorTableLength;

protected:
	//ͼ��Ŀ�����Ϊ��λ
	int m_imgWidth;

	//ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeight;

	//ͼ����Ϣͷָ��
	LPBITMAPINFOHEADER m_lpBmpInfoHead;

public:
	//���������Ĺ��캯��
	ImgDib();

	//�������Ĺ��캯��
	ImgDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);

	//��������
	~ImgDib();

	//��ȡDIB�ĳߴ磨��ߣ�
	CSize GetDimensions();

	//DIB������
	BOOL Read(LPCTSTR lpszPathName);

	//DIBд����
	BOOL Write(LPCTSTR lpszPathName);

	//��ʾDIB
	BOOL Draw(CDC* pDC, CPoint origin, CSize size);

	// ���о�������
	BOOL UniformQuanlization(int cR);

	//���иĽ���ľ�������IGS
	BOOL IGSUniformQuanlization();

	// ����DCT�任
	BOOL DCTTransfrom(int N, int M);

	// ����DCT�任֮����DCT���任,abandon����Ҫ������������
	BOOL InverseDCTTransfrom(int N, int M, int abandon);

	//���µ������滻DIB
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);

	//������ɫ��ĳ���
	int ComputeColorTabalLength(int nBitCount);

private:
	//�����߼���ɫ��
	void MakePalette();

	//����ռ�
	void Empty();
};
#endif // _INSIDE_VISUAL_CPP_ImgDib
