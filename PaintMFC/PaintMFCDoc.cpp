
// PaintMFCDoc.cpp : implementation of the CPaintMFCDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PaintMFC.h"
#endif

#include "PaintMFCDoc.h"

#include <propkey.h>
#include <string>
#include <memory>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef CString(*LPGETPLUGINFIGURENAME)();
typedef CFigure*(*LPGETPLUGINFIGURE)();
typedef char(*LPGETPLUGINCONTROLBUTTON)();

std::wstring getDllsPath() {
	WCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return (std::wstring(buffer).substr(0, pos).append(L"\\*.dll"));
}

std::vector<std::pair<int, HMODULE>> EnumeratePlugins() {
	std::vector<std::pair<int, HMODULE>> result;

	int index = 1;
	WIN32_FIND_DATA wfd;
	HANDLE hSearchHandle;

	std::wstring searchTemplate = getDllsPath();
	hSearchHandle = FindFirstFile(searchTemplate.c_str(), &wfd);

	if (hSearchHandle == INVALID_HANDLE_VALUE)
		return result;

	do
	{
		HMODULE dll = LoadLibrary(wfd.cFileName);
		if (dll == NULL)
			continue;

		if (GetProcAddress(dll, "GetPluginFigureName") != NULL)
		{
			result.push_back(std::make_pair(index, dll));
			index++;
		}
		else
		{
			FreeLibrary(dll);
		}
	} while (FindNextFile(hSearchHandle, &wfd) != 0);

	FindClose(hSearchHandle);

	return result;
}

// CPaintMFCDoc

IMPLEMENT_DYNCREATE(CPaintMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CPaintMFCDoc, CDocument)
END_MESSAGE_MAP()


// CPaintMFCDoc construction/destruction

CPaintMFCDoc::CPaintMFCDoc() noexcept
{
	// TODO: add one-time construction code here

	this->dlls = EnumeratePlugins();
}

CPaintMFCDoc::~CPaintMFCDoc()
{
}

BOOL CPaintMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPaintMFCDoc serialization

void CPaintMFCDoc::Serialize(CArchive& ar)
{
	INT_PTR num = 0;
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		num = m_figures.GetCount();
		ar << num;
		for (int i = 0; i < num; i++) {
			ar << m_figures[i]->figureName;
			ar << m_figures[i]->x;
			ar << m_figures[i]->y;
			ar << m_figures[i]->width;
			ar << m_figures[i]->height;
		}
	}
	else
	{
		// TODO: add loading code here
		ar >> num;
		for (int i = 0; i < num; i++) {
			CFigure* r;
			int figType;
			CString figureName;
			ar >> figureName;

			bool figureReaded = false;
			for (auto pluginInfo : dlls) {
				LPGETPLUGINFIGURENAME GetPluginFigureName = (LPGETPLUGINFIGURENAME)GetProcAddress(pluginInfo.second, "GetPluginFigureName");
				if (GetPluginFigureName == NULL)
					continue;

				CString pluginFigureName = GetPluginFigureName();
				if (figureName == pluginFigureName) {
					HMODULE activeModule = pluginInfo.second;
					LPGETPLUGINFIGURE GetPluginFigure = (LPGETPLUGINFIGURE)GetProcAddress(activeModule, "GetPluginFigure");
					if (GetPluginFigure == NULL)
					{
						//std::cout << "bad plug, again!";
						AfxMessageBox(L"Ошибка добавления плагина");
					}
					r = GetPluginFigure();
					ar >> r->x;
					ar >> r->y;
					ar >> r->width;
					ar >> r->height;
					
					figureReaded = true;

					this->m_figures.Add(r);
				}
			}
			
			if (!figureReaded) {
				int x;
				int y;
				int width;
				int height;

				AfxMessageBox(L"У вас отсутствует один из нужных для работы с файлом плагинов! Подключите все плагины, используемые при создании файла для его корректного чтения");
				ar >> x;
				ar >> y;
				ar >> width;
				ar >> height;
			}
			
		}

	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPaintMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPaintMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPaintMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPaintMFCDoc diagnostics

#ifdef _DEBUG
void CPaintMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPaintMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPaintMFCDoc commands


void CPaintMFCDoc::DeleteContents()
{
	// TODO: Add your specialized code here and/or call the base class
	this->m_figures.RemoveAll();
	//this->dlls.clear();
	//for (auto dll : this->dlls)
	//{
	//	FreeLibrary(dll.second);
	//}

	CDocument::DeleteContents();
}
