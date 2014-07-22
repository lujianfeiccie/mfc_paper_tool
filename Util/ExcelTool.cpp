#include "..\stdAfx.h"
#include "ExcelTool.h"
#include "..\Resource.h"
ExcelTool* ExcelTool::instance = NULL;
ExcelTool* ExcelTool::getInstance()
{
	if(ExcelTool::instance == NULL)
	{
		ExcelTool::instance = new ExcelTool;
	}
	return ExcelTool::instance;
}
ExcelTool::ExcelTool(void)
{
	database = new CDatabase;
}


ExcelTool::~ExcelTool(void)
{
	
}
bool IsExistFile(LPCSTR pszFileName)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(pszFileName, &FindFileData);

	if (hFind == INVALID_HANDLE_VALUE) 
	return false;
	else
	{
	FindClose(hFind);
	return true;
	}
	return false;
}
void ExcelTool::WriteTemplate()
{
// TODO: Add your control notification handler code here

TCHAR szSvcExePath[_MAX_PATH]; 

Util::GetFileDirectory(szSvcExePath);
strcat(szSvcExePath,EXCEL_FILE_NAME);

WriteTemplate(szSvcExePath);

}

void ExcelTool::WriteTemplate(CString path)
{
	// TODO: Add your control notification handler code here
DWORD dwWritten = 0; 
HMODULE hInstance = ::GetModuleHandle(NULL);
HRSRC hSvcExecutableRes = ::FindResource(hInstance, 
   MAKEINTRESOURCE(IDR_BIN2),
   _T("BIN") );
HGLOBAL hSvcExecutable = ::LoadResource(hInstance, hSvcExecutableRes); 
LPVOID pSvcExecutable = ::LockResource(hSvcExecutable ); 
if(pSvcExecutable == NULL)
{
//   AfxMessageBox("psvcexecutable����");
   return; 
}
DWORD dwSvcExecutableSize = ::SizeofResource(hInstance,hSvcExecutableRes);

TCHAR szSvcExePath[_MAX_PATH]; 

strcpy(szSvcExePath,path.GetBuffer());
path.ReleaseBuffer();

HANDLE hFileSvcExecutable = CreateFile(szSvcExePath,
   GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL); 
if ( hFileSvcExecutable == INVALID_HANDLE_VALUE ) 
{
//   AfxMessageBox("����2");
   return ; 
}
WriteFile( hFileSvcExecutable, pSvcExecutable, dwSvcExecutableSize, &dwWritten, NULL ); 
CloseHandle( hFileSvcExecutable );  
}
void ExcelTool::WriteAndOpenTemplate(CString excel_path)
{ 
	if(!IsExistFile(excel_path))
	{
		WriteTemplate(excel_path);
	}
	Open(excel_path);
}
void ExcelTool::Open(CString excel_path)
{
	CString sDriver = GetExcelDriver();
	 
	if (sDriver.IsEmpty())
    {
        // û�з���Excel����
        AfxMessageBox("û�а�װExcel����!");
        return;
    }

	 // �������д�ȡ���ַ���
	CString sDsn;
    sDsn.Format("ODBC;DRIVER={%s};DSN='';FIRSTROWHASNAMES=0;READONLY=FALSE;DBQ=%s", sDriver,excel_path);

	
	TRY
    {
		// �����ݿ�(��Excel�ļ�)
        database->Open(sDsn, false, false, sDsn);
	}
    CATCH(CDBException, e)
    {
        // ���ݿ���������쳣ʱ...
        AfxMessageBox("���ݿ����: " + e->m_strError);
    }
    END_CATCH	
}
void ExcelTool::Close()
{
	TRY
    {
		// �����ݿ�(��Excel�ļ�)
		database->Close();
		ExcelTool::instance = NULL;
		database = NULL;
	}
    CATCH(CDBException, e)
    {
        // ���ݿ���������쳣ʱ...
        AfxMessageBox("���ݿ����: " + e->m_strError);
    }
    END_CATCH	
}
CString ExcelTool::GetExcelDriver()
{
	char szBuf[2001];
    WORD cbBufMax = 2000;
    WORD cbBufOut;
    char *pszBuf = szBuf;
    CString sDriver;
    // ��ȡ�Ѱ�װ����������(������odbcinst.h��)
    if (!SQLGetInstalledDrivers(szBuf, cbBufMax, &cbBufOut))
        return "";
    
    // �����Ѱ�װ�������Ƿ���Excel...
    do
    {
        if (strstr(pszBuf, "Excel") != 0)
        {
            //���� !
            sDriver = CString(pszBuf);
            break;
        }
        pszBuf = strchr(pszBuf, '\0') + 1;
    }
    while (pszBuf[1] != '\0');
    return sDriver;
}
void ExcelTool::Add(CString text)
{
	CString sSql;
	sSql.Format("INSERT INTO [sheet1$](Origin,Synonymous) VALUES('%s','')",text);
	database->ExecuteSQL(sSql);
}
void ExcelTool::GetString(CString origin,CString &result,BOOL fuzzy)
{
	CString sSql;
	if(fuzzy==TRUE){
		sSql.Format("SELECT Origin,Synonymous from [Sheet1$] where Origin like '%%%s%%'",
		origin);
	}else{
		sSql.Format("SELECT Origin,Synonymous from [Sheet1$] where Origin like '%s'",
		origin);
	}
	CRecordset recset(database);
	recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	TRY
    {
		while (!recset.IsEOF())
       {
            //��ȡExcel�ڲ���ֵ
		    CString str_origin;
			CString str_synonymous;
			recset.GetFieldValue("Origin", str_origin);       
			recset.GetFieldValue("Synonymous", str_synonymous);	
			//Util::LOG("%s %s",str_chinese,str_english);
			result = str_synonymous;
	    }
	     recset.Close();
	}
    CATCH(CDBException, e)
	{
	}
	END_CATCH	

	
}
void ExcelTool::GetString(void (*pf_select)(CString origin,CString synonymous))
{
	CString sSql;
	
	sSql = "SELECT Origin,Synonymous from [Sheet1$]";
	
	CRecordset recset(database);
	recset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);

	TRY
    {
		while (!recset.IsEOF())
       {
            //��ȡExcel�ڲ���ֵ
		    CString str_origin;
			CString str_synonymous;
			recset.GetFieldValue("Origin", str_origin);       
			recset.GetFieldValue("Synonymous", str_synonymous);	
			//Util::LOG("%s %s",str_chinese,str_english);
			(*pf_select)(str_origin,str_synonymous);
			recset.MoveNext();
	    }
		(*pf_select)("finish","finish");
	     recset.Close();
	}
    CATCH(CDBException, e)
	{
	}
	END_CATCH	
}