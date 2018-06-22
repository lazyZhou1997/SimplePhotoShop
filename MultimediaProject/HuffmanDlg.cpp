// HuffmanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultimediaProject.h"
#include "HuffmanDlg.h"
#include "afxdialogex.h"


// CHuffmanDlg �Ի���

IMPLEMENT_DYNAMIC(CHuffmanDlg, CDialogEx)

CHuffmanDlg::CHuffmanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHuffmanDlg::IDD, pParent)
{

	EnableAutomation();

	m_dEntropy = 0.0;
	m_dCodLength = 0.0;
	m_dRatio = 0.0;

}

CHuffmanDlg::~CHuffmanDlg()
{
}

void CHuffmanDlg::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease��  ���ཫ�Զ�
	// ɾ���ö���  �ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CHuffmanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstTable);
	DDX_Text(pDX, IDC_EDIT3, m_dEntropy);
	DDX_Text(pDX, IDC_EDIT1, m_dCodLength);
	DDX_Text(pDX, IDC_EDIT2, m_dRatio);
}


BEGIN_MESSAGE_MAP(CHuffmanDlg, CDialogEx)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CHuffmanDlg, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IHuffmanDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {714FDF62-89E8-40E0-8145-A87E04C79124}
static const IID IID_IHuffmanDlg =
{ 0x714FDF62, 0x89E8, 0x40E0, { 0x81, 0x45, 0xA8, 0x7E, 0x4, 0xC7, 0x91, 0x24 } };

BEGIN_INTERFACE_MAP(CHuffmanDlg, CDialogEx)
	INTERFACE_PART(CHuffmanDlg, IID_IHuffmanDlg, Dispatch)
END_INTERFACE_MAP()


// CHuffmanDlg ��Ϣ�������
BOOL CHuffmanDlg::OnInitDialog()
{

	// ����Ĭ�ϵ�OnInitDialog()����
	CDialog::OnInitDialog();

	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;

	// �м����
	double	dT;

	// �ַ�������
	CString	str2View;

	// �ؼ�ListCtrl��ITEM
	LV_ITEM lvItem;

	// ����ؼ�ListCtrl����ӵ�ITEM���
	int		item2View;

	// ��������м���������
	double *	dTemp;

	// ����������ŻҶ�ֵ����λ��֮���ӳ��
	int	*	pos;

	// ��ʼ������
	m_dEntropy = 0.0;
	m_dCodLength = 0.0;

	// �����ڴ�
	m_strCode = new CString[nColorNum];
	pos = new int[nColorNum];
	dTemp = new double[nColorNum];

	// ��dTemp��ֵ
	// ��ʼ�ĻҶ�ֵ���Ҷ�ֵ��С������ͬ
	for (i = 0; i < nColorNum; i++)
	{
		dTemp[i] = dProba[i];
		pos[i] = i;
	}

	// ��ð�ݷ��Խ��лҶ�ֵ���ֵĸ�������
	// ͬʱ�ı�Ҷ�ֵλ�õ�ӳ���ϵ
	for (j = 0; j < nColorNum - 1; j++)
	{
		for (i = 0; i < nColorNum - j - 1; i++)
		{
			if (dTemp[i] > dTemp[i + 1])
			{
				dT = dTemp[i];
				dTemp[i] = dTemp[i + 1];
				dTemp[i + 1] = dT;

				// ��i��i+1�Ҷȵ�λ��ֵ����
				for (k = 0; k < nColorNum; k++)
				{
					if (pos[k] == i)
						pos[k] = i + 1;
					else if (pos[k] == i + 1)
						pos[k] = i;
				}
			}
		}
	}

	/*******************************************************
	��������������
	*******************************************************/

	// �Ӹ��ʴ���0����ʼ����
	for (i = 0; i < nColorNum - 1; i++)
	{
		if (dTemp[i] > 0)
			break;
	}

	for (; i < nColorNum - 1; i++)
	{
		// ����m_strCode
		for (k = 0; k < nColorNum; k++)
		{
			// �Ҷ�ֵ�Ƿ�i
			if (pos[k] == i)
			{
				// �Ҷ�ֵ��С�����ּ�1
				m_strCode[k] = "1" + m_strCode[k];
			}
			else if (pos[k] == i + 1)
			{
				// �Ҷ�ֵ��С�����ּ�0
				m_strCode[k] = "0" + m_strCode[k];
			}
		}

		// ������С������������ӣ�������dTemp[i + 1]��
		dTemp[i + 1] += dTemp[i];

		// �ı�ӳ���ϵ
		for (k = 0; k < nColorNum; k++)
		{
			// ��λ��Ϊi�ĻҶ�ֵi��Ϊ�Ҷ�ֵi+1
			if (pos[k] == i)
				pos[k] = i + 1;
		}

		// ��������
		for (j = i + 1; j < nColorNum - 1; j++)
		{
			if (dTemp[j] > dTemp[j + 1])
			{
				// ����
				dT = dTemp[j];
				dTemp[j] = dTemp[j + 1];
				dTemp[j + 1] = dT;

				// // ��i��i+1�Ҷȵ�λ��ֵ����
				for (k = 0; k < nColorNum; k++)
				{
					if (pos[k] == j)
						pos[k] = j + 1;
					else if (pos[k] == j + 1)
						pos[k] = j;
				}
			}
			else
				// �˳�ѭ��
				break;
		}
	}

	// ����ͼ����
	for (i = 0; i < nColorNum; i++)
	{
		if (dProba[i] > 0)
		{
			// ����ͼ����
			m_dEntropy -= dProba[i] * log(dProba[i]) / log(2.0);
		}
	}

	// ����ƽ�����ֳ���
	for (i = 0; i < nColorNum; i++)
	{
		// �ۼ�
		m_dCodLength += dProba[i] * m_strCode[i].GetLength();
	}

	// �������Ч��
	m_dRatio = m_dEntropy / m_dCodLength;

	// ����䶯
	UpdateData(FALSE);

	/*************************************************
	���������
	*************************************************/

	// ����CListCtrl�ؼ���ʽ
	m_lstTable.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	// ��List�ؼ����Header
	m_lstTable.InsertColumn(0, "�Ҷ�ֵ", LVCFMT_LEFT, 60, 0);
	m_lstTable.InsertColumn(1, "����ֵ", LVCFMT_LEFT, 78, 0);
	m_lstTable.InsertColumn(2, "����������", LVCFMT_LEFT, 110, 1);
	m_lstTable.InsertColumn(3, "���ֳ���", LVCFMT_LEFT, 78, 2);

	// ������ʽΪ�ı�
	lvItem.mask = LVIF_TEXT;

	// �����ʾ
	for (i = 0; i < nColorNum; i++)
	{
		// ��һ����ʾ
		lvItem.iItem = m_lstTable.GetItemCount();
		str2View.Format("%u", i);
		lvItem.iSubItem = 0;
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		item2View = m_lstTable.InsertItem(&lvItem);

		// ��������ʾ
		lvItem.iItem = item2View;

		// ��ӻҶ�ֵ�ĸ���ֵ
		lvItem.iSubItem = 1;
		str2View.Format("%f", dProba[i]);
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		m_lstTable.SetItem(&lvItem);

		// ��ӹ���������
		lvItem.iSubItem = 2;
		lvItem.pszText = (LPTSTR)(LPCTSTR)m_strCode[i];
		m_lstTable.SetItem(&lvItem);

		// ������ֳ���
		lvItem.iSubItem = 3;
		str2View.Format("%u", m_strCode[i].GetLength());
		lvItem.pszText = (LPTSTR)(LPCTSTR)str2View;
		m_lstTable.SetItem(&lvItem);
	}

	//  �ڴ��ͷ�
	delete pos;
	delete dTemp;

	// ����TRUE
	return TRUE;
}