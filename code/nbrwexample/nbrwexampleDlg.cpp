// nbrwexampleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "nbrwexample.h"
#include "nbrwexampleDlg.h"

#include "nbRwTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CnbrwexampleDlg �Ի���

const char szTransferNotStart[]   = "ת����״̬�� ת������δ����";
const char szTransferStart[]      = "ת����״̬�� ת��������������";
const char szTransferErrorRead[]  = "ת����״̬�� ��ȡ redwood �豸���ݲ��ɹ�";
const char szTransferErrorParse[] = "ת����״̬�� ���� redwood �豸���ݲ��ɹ�";
const char szTransferErrorSend[]  = "ת����״̬�� ���� redwood �豸���ݲ��ɹ�";

CnbrwexampleDlg::CnbrwexampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CnbrwexampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnbrwexampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CnbrwexampleDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_START, &CnbrwexampleDlg::OnBnClickedButtonStart)
    ON_BN_CLICKED(IDC_BUTTON_STOP, &CnbrwexampleDlg::OnBnClickedButtonStop)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDCANCEL, &CnbrwexampleDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CnbrwexampleDlg ��Ϣ�������

BOOL CnbrwexampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    SetDlgItemText(IDC_STATIC_NOTE, "ʹ��˵����\r\n\r\n"
           "  1.������Ϊת�� redwood ���� dll��ʹ�����ӣ�\r\n\r\n"
           "  2.ʹ��ǰ����ȷ���ò�����\r\n\r\n"
           "  3.���ò����������ļ� nbdatatr.ini �н��У�\r\n\r\n"
           "  4.��� start ��ť�󣬽�ÿ��һ��ʱ�������õ� upd ������\r\n"
           "    ����ÿ�ζ����ı仯�����ݣ�\r\n");

    SetDlgItemText(IDC_STATIC_STATE, szTransferNotStart);    

    SetTimer(1, 1000, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnbrwexampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CnbrwexampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CnbrwexampleDlg::OnBnClickedButtonStart()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    SetParameter();
    StartTransferFlow();
}

void CnbrwexampleDlg::OnBnClickedButtonStop()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    StopTransferFlow();
}

void CnbrwexampleDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    int iTransferStates = GetTransferStates();

    switch (iTransferStates) {
        case TRANSFER_NOT_START:
            SetDlgItemText(IDC_STATIC_STATE, szTransferNotStart);  
            break;

        case TRANSFER_START:
            SetDlgItemText(IDC_STATIC_STATE, szTransferStart); 
            break;
            
        case TRANSFER_ERROR_READRWDATA:
            SetDlgItemText(IDC_STATIC_STATE, szTransferErrorRead);
            break;
            
        case TRANSFER_ERROR_PARSEDATA:
            SetDlgItemText(IDC_STATIC_STATE, szTransferErrorParse);
            break;
            
        case TRANSFER_ERROR_SENDDATA:
            SetDlgItemText(IDC_STATIC_STATE, szTransferErrorSend);
            break;

        default:
            break;
    }

    CDialog::OnTimer(nIDEvent);
}

void CnbrwexampleDlg::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    StopTransferFlow();
    OnCancel();

    /*
    char szIp[64] = {0};
    int iPort = 0;    
    char szUser[64] = {0};
    char szPw[64] = {0};
    int iTransInterval = 0;

    //����Դ����
    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_SRCDATAIP, 
        "192.168.0.245", szIp, sizeof(szIp), NBINIFILENAME);
    iPort = GetPrivateProfileIntA(SEC_REDWOOD, KEY_REDWOOD_SRCDATAPORT, 
        80, NBINIFILENAME);

    rwhandler.setNetAddr(szIp, iPort);  

    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_USER, 
        "admin", szUser, sizeof(szUser), NBINIFILENAME);
    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_PASSWORD, 
        "redwood", szPw, sizeof(szPw), NBINIFILENAME);

    rwhandler.setUserAndPw(szUser, szPw);

    //udp ��������
    GetPrivateProfileStringA(SEC_UDPLISTENER, KEY_UDPLISTENER_DESCIP, 
        "127.0.0.1", szIp, sizeof(szIp), NBINIFILENAME);
    iPort = GetPrivateProfileIntA(SEC_UDPLISTENER, KEY_UDPLISTENER_DESCPORT, 
        2222, NBINIFILENAME);

    nbDataSender.setPeerAddr(szIp, iPort); 

    //����ת������
    iTransInterval = GetPrivateProfileIntA(SEC_TRANSCONTRL, KEY_TRANSCONTRL_TRANSINTERVAL, 
        2, NBINIFILENAME);

    if (iTransInterval <= 0)
        iTransInterval = 2;

    iTimeDelay = iTransInterval * 1000;

    */
}

void CnbrwexampleDlg::SetParameter()
{
    char szPath[256] = {0};
    char szIniFilePath[256] = {0};
    
    GetCurrentDirectory(256, szPath);
    sprintf(szIniFilePath, "%s/%s", szPath, NBINIFILENAME);

    char szSrcIp[64] = {0};
    int iSrcPort = 0;    
    char szUser[64] = {0};
    char szPw[64] = {0};
    char szUdpIp[64]= {0};
    int iUdpPort = 0;
    int iTransInterval = 0;
    int iTransOption = 0;

    //����Դ����    
    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_SRCDATAIP, 
        "192.168.1.245", szSrcIp, sizeof(szSrcIp), szIniFilePath);
    iSrcPort = GetPrivateProfileIntA(SEC_REDWOOD, KEY_REDWOOD_SRCDATAPORT, 
        80, szIniFilePath);
    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_USER, 
        "admin", szUser, sizeof(szUser), szIniFilePath);
    GetPrivateProfileStringA(SEC_REDWOOD, KEY_REDWOOD_PASSWORD, 
        "redwood", szPw, sizeof(szPw), szIniFilePath);

    //udp ��������
    GetPrivateProfileStringA(SEC_UDPLISTENER, KEY_UDPLISTENER_DESCIP, 
        "127.0.0.1", szUdpIp, sizeof(szUdpIp), szIniFilePath);
    iUdpPort = GetPrivateProfileIntA(SEC_UDPLISTENER, KEY_UDPLISTENER_DESCPORT, 
        2222, szIniFilePath);

    //����ת������
    iTransInterval = GetPrivateProfileIntA(SEC_TRANSCONTRL, KEY_TRANSCONTRL_TRANSINTERVAL, 
        2, szIniFilePath);
    if (iTransInterval <= 0)
        iTransInterval = 2;

    iTransOption = GetPrivateProfileIntA(SEC_TRANSCONTRL, KEY_TRANSCONTRL_TRANSFEROPTION, 
        0, szIniFilePath);

    SetTransferParameter(szSrcIp, iSrcPort,
        szUser, szPw, szUdpIp, iUdpPort, 
        iTransInterval, iTransOption);
}