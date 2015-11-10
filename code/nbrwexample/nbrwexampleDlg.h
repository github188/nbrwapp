// nbrwexampleDlg.h : ͷ�ļ�
//

#pragma once


//ini �ļ�����
#define NBINIFILENAME                   "nbdatatr.ini"     //ini�ļ���

#define SEC_TRANSCONTRL                 "TransContrl"
#define SEC_REDWOOD                     "RedWood"
#define SEC_UDPLISTENER                 "UdpListener"

#define KEY_TRANSCONTRL_TRANSINTERVAL   "TransInterval"
#define KEY_TRANSCONTRL_TRANSFEROPTION  "IsTransChangeData"

#define KEY_REDWOOD_SRCDATAIP           "srcDataIp"
#define KEY_REDWOOD_SRCDATAPORT         "srcDataPort"
#define KEY_REDWOOD_USER                "user"
#define KEY_REDWOOD_PASSWORD            "password"

#define KEY_UDPLISTENER_DESCIP          "DescIp"
#define KEY_UDPLISTENER_DESCPORT        "DescPort"


// CnbrwexampleDlg �Ի���
class CnbrwexampleDlg : public CDialog
{
// ����
public:
	CnbrwexampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NBRWEXAMPLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
    void SetParameter();


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonStart();
    afx_msg void OnBnClickedButtonStop();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedCancel();
};
