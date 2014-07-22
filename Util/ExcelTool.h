#pragma once


class ExcelTool
{
private:
	ExcelTool(void);
	CString GetExcelDriver();
	CDatabase* database;
	void WriteTemplate();
	void WriteTemplate(CString path);
public:
	
	~ExcelTool(void);
	static ExcelTool* instance;
	static ExcelTool* getInstance();

	void WriteAndOpenTemplate(CString excel_path);
	void Open(CString excel_path);
	void Close();
	void Add(CString text);
	void GetString(CString origin,CString &result,BOOL fuzzy=TRUE);
	void GetString(void (*pf_select)(CString origin,CString synonymous));
};
