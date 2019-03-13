#pragma once

#ifndef _GETPEFILEINFO__H__H__H
#define _GETPEFILEINFO__H__H__H

#include <Windows.h>
#include <wintrust.h>

//ͨ����ѧ�������ָ��ƫ�ƣ�������ͨ��ָ�����㣩
#define MakePtr(cast, ptr, addValue) ((cast)((DWORD_PTR)(ptr) + (DWORD_PTR)(addValue)))


//���ڼ�¼��Դ��ID��ʶ
#ifndef _WIN64
typedef DWORD IDTYPE;
typedef LPDWORD PIDTYPE;
#else
typedef ULONGLONG IDTYPE;
typedef PULONGLONG PIDTYPE;
#endif

class CPeFile
{
public:
	CPeFile();
	~CPeFile();
public:
	//��pe�ļ����ӵ����󣬳ɹ�����IMAGE_DOS_SIGNATURE��IMAGE_OS2_SIGNATURE��IMAGE_OS2_SIGNATURE_LE��IMAGE_NT_SIGNATURE֮һ��
	//ʧ�ܷ���0UL��δ֪���ͣ���1UL���ļ�����ʧ�ܣ���2���������󣩣�������û��PE�ļ����ӵ������ʱ���á�
	DWORD Attach(LPCSTR lpszFilePath);
	//����pe�ļ����ӵ��������ͷŹ���
	void Detach();
	//��ȡAttach��Ϣ���ɹ�����IMAGE_DOS_SIGNATURE��IMAGE_OS2_SIGNATURE��IMAGE_OS2_SIGNATURE_LE��IMAGE_NT_SIGNATURE֮һ��δ�ɹ�����0UL
	DWORD GetAttachInfo() const;

	//���º���������˵��Attach�ɹ��������
public:
	//��ȡ�ļ����
	HANDLE GetFileHandle() const;
	//��ȡ�ڴ�ӳ���ļ�ͷ����ַ
	DWORD_PTR GetMappedFileStart() const;
	//��ȡ�ڴ�ӳ���ļ�ͷ��ָ��ƫ�Ƶ�ַ
	DWORD_PTR GetMappedFileOffset(DWORD dwFoa) const;
	//��ȡdosͷ
	const IMAGE_DOS_HEADER* GetDosHeader() const;
	//��ȡdos����ڵ�ַ
	DWORD GetDosEntryPoint() const;
	// ���º���������˵��������IMAGE_NT_SIGNATURE
public:
	//��ȡpe�ļ�ͷ
	const IMAGE_NT_HEADERS32* GetNtHeader() const;
	//�����ļ��Ƿ�Ϊ64λ
	BOOL Is64Bit() const;
	//��ȡpe�ļ�ͷ�ļ��ػ�ַImageBase(64λ����ULONGLONG���ͣ�32λ����DWORD���ͣ���Ҫ����ת��)
	ULONGLONG GetImageBase() const;
	//��ȡpe�ļ�ͷ�е�DataDirectory
	const IMAGE_DATA_DIRECTORY* GetDataDirectory() const;
	//��ȡDataDirectory��ڵ�RVA
	DWORD GetDataDirectoryEntryRva(DWORD dwIndex) const;
	//��ȡ�ڱ�
	const IMAGE_SECTION_HEADER* GetSectionHeader(LPWORD lpSectionNum = NULL) const;
	//��RVAת��ΪFOA
	BOOL RvaToFoa(DWORD dwRva, LPDWORD lpFoa = NULL, LPWORD lpSection = NULL) const;
	//��FOAת��ΪRVA
	BOOL FoaToRva(DWORD dwFoa, LPDWORD lpRva = NULL, LPWORD lpSection = NULL) const;
	//VAתΪRVA
	DWORD VaToRva(DWORD dwVa) const; //32λ
	DWORD VaToRva(ULONGLONG ullVa) const; //64λ
	//RVAתVA
	ULONGLONG RvaToVa(DWORD dwRva) const;

	//���º���������˵��������IMAGE_NT_SIGNATURE
public:
	//��ȡpe�еĵ�����
	BOOL ReadExport();
	//��ȡpe�еĵ����
	BOOL ReadImport();
	//��ȡpe�е���Դ��
	BOOL ReadResource();
	//��ȡpe�е��쳣��
	BOOL ReadException();
	//��ȡpe�е�����֤���
	BOOL ReadSecurity();
	//��ȡpe�еĻ�ַ�ض�λ��
	BOOL ReadBaseRelocation();
	//��ȡpe�еĵ�������
	BOOL ReadDebug();
	//��ȡpe���ֲ߳̾��洢��
	BOOL ReadTLS();
	//��ȡpe�м������ñ�
	BOOL ReadLoadConfig();
	//��ȡpe�а󶨵����
	BOOL ReadBoundImport();
	//��ȡpe���ӳټ��ص����
	BOOL ReadDelayImport();
	//����pe�е����
	void ClearExport();
	void ClearImport();
	void ClearResource();
	void ClearException();
	void ClearSecurity();
	void ClearBaseRelocation();
	void ClearDebug();
	void ClearTLS();
	void ClearLoadConfig();
	void ClearBoundImport();
	void ClearDelayImport();
	//��������
	void ClearAll();

	//�����Ƿ��ȡ��pe�еĵĵ�����
	BOOL IsReadExport() const;
	BOOL IsReadImport() const;
	BOOL IsReadResource() const;
	BOOL IsReadException() const;
	BOOL IsReadSecurity() const;
	BOOL IsReadBaseRelocation() const;
	BOOL IsReadDebug() const;
	BOOL IsReadTLS() const;
	BOOL IsReadLoadConfig() const;
	BOOL IsReadBoundImport() const;
	BOOL IsReadDelayImport() const;

	//���º���������˵��������IMAGE_NT_SIGNATURE��ReadExport�ɹ�
public:
	//��ȡ�����
	const IMAGE_EXPORT_DIRECTORY* GetExportDirectory() const;
	//��ȡ�����������������ַ����
	const DWORD* GetExportFunction(LPDWORD lpFuncNum = NULL) const;
	//��ȡ�������б����������Ƶĸ������������Ƶ�ַ����
	const DWORD* GetExportName(LPDWORD lpNameNum = NULL) const;
	//��ȡ�������б����������Ƶĸ�������������������������lpNameNum������
	const WORD* GetExportNameOrdinal(LPDWORD lpNameNum = NULL) const;
	//��������������ַ������dwIndex�����ֵС��NumberOfNamesΪ�����Ƶ�������ֵΪ��ţ�������ֵ����NumberOfNames��Ϊ����ŵ���
	DWORD ParseExportFunction(DWORD dwIndex) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadImport�ɹ�
public:
	//��ȡ��������������������lpImportDescriptorNum������
	const IMAGE_IMPORT_DESCRIPTOR* GetImportDescriptor(LPDWORD lpImportDescriptorNum = NULL) const;
	//��ȡ��iImpoert��������е�IMAGE_THUNK_DATA32�ṹ��64λ����ʵ����IMAGE_THUNK_DATA64������������lpCount������
	const IMAGE_THUNK_DATA32* GetImportThunkData(DWORD iImport, LPDWORD lpCount = NULL) const;
	//����ĳ��IMAGE_THUNK_DATA32�ṹ��64λ����ʵ����IMAGE_THUNK_DATA64�������ؽ����1��ʾ����ŵ��루lpParam�ɴ�����ţ���2��ʾ�����Ƶ��루lpParam�ɴ�����ӦIMAGE_IMPORT_BY_NAME��FOA����0ʧ�ܡ�ֻ��ҪIMAGE_NT_SIGNATURE�����á�
	int ParseThunkData(const IMAGE_THUNK_DATA32* lpThunk, LPDWORD lpParam = NULL) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadResource�ɹ�
public:
	//��ȡ��һ����Դ��ID������1��ʾ��һ����Ŀ¼������2��ʾ��һ�������ݣ�����0��ʾ����Դ
	int GetFirstResourceId(PIDTYPE lpFirstID) const;
	//��ȡ��һ����Դ��ID������1��ʾ��һ����Ŀ¼������2��ʾ��һ�������ݣ�����0��ʾ����һ��
	int GetNextResourceId(IDTYPE Id, DWORD iRes, PIDTYPE NextID) const;
	//����Id��Ӧ��Ŀ¼�㣬lpEntryNum�ɴ�������������lpLevel�ɴ����ڼ���Ŀ¼��lpResourceEntry���������Ӧ��IMAGE_RESOURCE_DIRECTORY_ENTRY����
	const IMAGE_RESOURCE_DIRECTORY* ParseResourceDirectory(IDTYPE Id, LPDWORD lpEntryNum = NULL, LPDWORD lpLevel = NULL, IMAGE_RESOURCE_DIRECTORY_ENTRY** lpResourceEntry = NULL) const;
	//����dwId��Ӧ�����ݲ�
	const IMAGE_RESOURCE_DATA_ENTRY* ParseResourceData(IDTYPE Id) const;
	//����ĳ��IMAGE_RESOURCE_DIRECTORY_ENTRY�ṹ��Name��Ա�����ؽ����1��dwParamΪID����2��dwParamΪ��ӦIMAGE_RESOURCE_DIR_STRING_U��FOA����ֻ��ҪIMAGE_NT_SIGNATURE�����á�
	int ParseResourceDirectoryEntry(const IMAGE_RESOURCE_DIRECTORY_ENTRY* lpEntry, LPDWORD dwParam) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadException�ɹ�
public:
	//��ȡ�쳣����������lpRuntimeFunctionNum������
	const IMAGE_RUNTIME_FUNCTION_ENTRY* GetRuntimeFunction(LPDWORD lpRuntimeFunctionNum = NULL) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadSecurity�ɹ�
public:
	//��ȡ����֤�����������lpCertificateNum������
	const WIN_CERTIFICATE* const* GetCertificate(LPDWORD lpCertificateNum = NULL) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadBaseRelocation�ɹ�
public:
	//��ȡ����ַ�ض�λ����������lpBaseRelocationNum������
	const IMAGE_BASE_RELOCATION* const* GetBaseRelocation(LPDWORD lpBaseRelocationNum = NULL) const;
	//���ĳ����ַ�ض�λ���е��ض�λ�飨��������lpCount���������������õģ�
	const WORD* GetBaseRelocationBlock(const IMAGE_BASE_RELOCATION* lpBaseRelocation, LPDWORD lpCount = NULL) const;
	//����ĳ����ַ�ض�λ����ĳһ����ص��Ǹ�4λ��ֵ����12λ��ֵ����lpParam�������κ�ʱ�������á�
	static WORD ParseBaseRelocationBlock(WORD wBaseRelocationBlock, LPWORD lpParam = NULL);

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadDebug�ɹ�
public:
	//��ȡ�������ݣ���������lpDebugDirectoryNum������
	const IMAGE_DEBUG_DIRECTORY* GetDebugDirectory(LPDWORD lpDebugDirectoryNum = NULL) const;
	//��ȡ��dwIndex�������Ϣ��ʼ��ַ��δ��ȡ������NULL
	LPCVOID GetDebugInfoStart(DWORD dwIndex);

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadTLS�ɹ�
public:
	//��ȡ�ֲ߳̾��洢�������64λ���򣬷��ص�ʵ����const IMAGE_TLS_DIRECTORY64*��
	const IMAGE_TLS_DIRECTORY32* GetTLSDirectory() const;
	//��ȡ�ֲ߳̾��洢��ص����������ָ�루�����64λ���򣬷��ص�ʵ����const ULONGLONG*������������lpCallbackNum������
	const DWORD* GetTLSCallback(LPDWORD lpCallbackNum = NULL) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadLoadConfig�ɹ�

public:
	//��ȡ�������ñ������64λ���򣬷��ص�ʵ����const IMAGE_LOAD_CONFIG_DIRECTORY64*��
	const IMAGE_LOAD_CONFIG_DIRECTORY32* GetLoadConfigDirectory() const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadBoundImport�ɹ�

public:
	//��ȡ�󶨵������������lpBoundImportNum������
	const IMAGE_BOUND_IMPORT_DESCRIPTOR* const* GetBoundImportDescriptor(LPDWORD lpBoundImportNum = NULL) const;
	//��ȡ��iBoundImpoert���󶨵������������lpRefNum������
	const IMAGE_BOUND_FORWARDER_REF* GetBoundImportForwarderRef(DWORD iBoundImport, LPDWORD lpRefNum = NULL) const;

	// ���º���������˵��������IMAGE_NT_SIGNATURE��ReadDelayImport�ɹ�

public:
	//��ȡ�ӳټ��ص������������lpDelayImportNum������
	const IMAGE_DELAYLOAD_DESCRIPTOR* GetDelayImportDescriptor(LPDWORD lpDelayImportNum = NULL) const;


	//��ֹ�������ƶ�����ֵ
private:
	CPeFile(const CPeFile&);
	CPeFile(const CPeFile&&);
	CPeFile& operator=(const CPeFile&);
	CPeFile& operator=(const CPeFile&&);

protected:
	class CPeExportManager
	{
	public:
		CPeExportManager();
		BOOL Initialize(IMAGE_EXPORT_DIRECTORY* lpExportStart, const CPeFile* lpPe);
	public:
		IMAGE_EXPORT_DIRECTORY* m_lpExportDirectory;
		DWORD* m_lpExportFunction;
		DWORD* m_lpExportName;
		WORD* m_lpExportNameOrdinal;
	};
	class CPeImportManager
	{
	public:
		CPeImportManager();
		~CPeImportManager();
		BOOL Initialize(IMAGE_IMPORT_DESCRIPTOR* lpImportStart, const CPeFile* lpPe);
	public:
		DWORD m_dwImportDescriptorNum;
		IMAGE_IMPORT_DESCRIPTOR* m_lpImportDescriptor;
		DWORD* m_lpThunkDataCount;
		IMAGE_THUNK_DATA32** m_lpThunkData;
	};
	class CPeResourceManager
	{
	public:
		CPeResourceManager(IMAGE_RESOURCE_DIRECTORY* lpResourceStart);
		~CPeResourceManager();
	protected:
		CPeResourceManager();
		void SearchResource(IMAGE_RESOURCE_DIRECTORY* lpResourceDirectory, DWORD dwLevel, IMAGE_RESOURCE_DIRECTORY* lpResourceStart);
	public:
		DWORD m_dwLevel;
		IMAGE_RESOURCE_DIRECTORY* m_lpResourceDirectory;
		DWORD m_dwResourceDirectoryEntryNum;
		CPeResourceManager* m_lpNext;
	};
	class CPeExceptionManager
	{
	public:
		CPeExceptionManager(IMAGE_RUNTIME_FUNCTION_ENTRY* lpRuntimeFunctionStart, const CPeFile* lpPe);
	public:
		DWORD m_dwRuntimeFunctionNum;
		IMAGE_RUNTIME_FUNCTION_ENTRY* m_lpRuntimeFunctionStart;
	};
	class CPeSecurityManager
	{
	public:
		CPeSecurityManager(WIN_CERTIFICATE* lpSecurityStart, DWORD dwSize);
		~CPeSecurityManager();
	public:
		DWORD m_dwSecuritNum;
		WIN_CERTIFICATE** m_lpSecurity;
	};
	class CPeBaseRelocationManager
	{
	public:
		CPeBaseRelocationManager(IMAGE_BASE_RELOCATION* lpBaseRelocationStart);
		~CPeBaseRelocationManager();
	public:
		DWORD m_dwBaseRelocationNum;
		IMAGE_BASE_RELOCATION** m_lpBaseRelocation;
	};
	class CPeDebugManager
	{
	public:
		CPeDebugManager(IMAGE_DEBUG_DIRECTORY* lpDebugStart, const CPeFile* lpPe);
	public:
		DWORD m_dwDebugDirectoryNum;
		IMAGE_DEBUG_DIRECTORY* m_lpDebugDirectory;
	};
	class CPeTLSManager
	{
	public:
		BOOL Initialize(IMAGE_TLS_DIRECTORY32* lpTLSStart, const CPeFile* lpPe);
	public:
		IMAGE_TLS_DIRECTORY32* m_lpTLSDirectory;
		DWORD* m_lpTLSCallback;
		DWORD m_dwTLSCallbackNum;
	};
	class CPeLoadConfigManager
	{
	public:
		CPeLoadConfigManager(IMAGE_LOAD_CONFIG_DIRECTORY32* lpLoadConfigStart);
	public:
		IMAGE_LOAD_CONFIG_DIRECTORY32* m_lpLoadConfigDirectory;
	};
	class CPeBoundImportManager
	{
	public:
		CPeBoundImportManager(IMAGE_BOUND_IMPORT_DESCRIPTOR* lpBoundImportStart);
		~CPeBoundImportManager();
	public:
		DWORD m_dwBoundImportDescriptorNum;
		IMAGE_BOUND_IMPORT_DESCRIPTOR** m_lpBoundImportDescriptor;
	};
	class CPeDelayImportManager
	{
	public:
		CPeDelayImportManager(IMAGE_DELAYLOAD_DESCRIPTOR* lpDelayImportStart);
	public:
		DWORD m_dwDelayImportDescriptorNum;
		IMAGE_DELAYLOAD_DESCRIPTOR* m_lpDelayImportDescriptor;
	};

protected:
	int OpenPeFile(LPCSTR lpszFilePath);
	void CloseFile();
	DWORD CheckHeaders();
	BOOL ReadExportAux();
	BOOL ReadImportAux();
	BOOL ReadResourceAux();
	BOOL ReadExceptionAux();
	BOOL ReadSecurityAux();
	BOOL ReadBaseRelocationAux();
	BOOL ReadDebugAux();
	BOOL ReadTLSAux();
	BOOL ReadLoadConfigAux();
	BOOL ReadBoundImportAux();
	BOOL ReadDelayImportAux();
	void ClearExportAux();
	void ClearImportAux();
	void ClearResourceAux();
	void ClearExceptionAux();
	void ClearSecurityAux();
	void ClearBaseRelocationAux();
	void ClearDebugAux();
	void ClearTLSAux();
	void ClearLoadConfigAux();
	void ClearBoundImportAux();
	void ClearDelayImportAux();

protected:
	HANDLE m_hFile;
	HANDLE m_hFileMap;
	LPVOID m_lpMemory;
	DWORD m_dwType;
	BOOL m_b64Bit;
	IMAGE_DOS_HEADER* m_lpDosHeader;
	IMAGE_NT_HEADERS32* m_lpNtHeader;
	IMAGE_SECTION_HEADER* m_lpSectionHeader;
	DWORD m_dwReadFlag;
	CPeExportManager* m_lpExportManager;
	CPeImportManager* m_lpImportManager;
	CPeResourceManager* m_lpResourceManager;
	CPeExceptionManager* m_lpExceptionManager;
	CPeSecurityManager* m_lpSecurityManager;
	CPeBaseRelocationManager* m_lpBaseRelocationManager;
	CPeDebugManager* m_lpDebugManager;
	CPeTLSManager* m_lpTLSManager;
	CPeLoadConfigManager* m_lpLoadConfigManager;
	CPeBoundImportManager* m_lpBoundImportManager;
	CPeDelayImportManager* m_lpDelayImportManager;

};
#endif