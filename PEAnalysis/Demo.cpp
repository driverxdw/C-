#include "pch.h"
#include "CPeFile.h"
#include <iostream>

using namespace std;
int main()
{
	const char* lpszPath = "D:\\C++_PROJ\\PEAnalysis\\crackme2019D7.exe";
	CPeFile PE;
	if (PE.Attach(lpszPath) != IMAGE_NT_SIGNATURE)
		//cout << hex<<PE.Attach(lpszPath) << endl;
		return -1;
	//HANDLE m_hFile = ::CreateFileA(lpszPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//��ȡdosͷָ��(�ṹ������)
	const IMAGE_DOS_HEADER*  lpDosHeader = PE.GetDosHeader();
	//lpDosHeader->e_xxx
	/*
	typedef struct _IMAGE_DOS_HEADER {      // DOS .EXE header
	WORD   e_magic;                     // Magic number
	WORD   e_cblp;                      // Bytes on last page of file
	WORD   e_cp;                        // Pages in file
	WORD   e_crlc;                      // Relocations
	WORD   e_cparhdr;                   // Size of header in paragraphs
	WORD   e_minalloc;                  // Minimum extra paragraphs needed
	WORD   e_maxalloc;                  // Maximum extra paragraphs needed
	WORD   e_ss;                        // Initial (relative) SS value
	WORD   e_sp;                        // Initial SP value
	WORD   e_csum;                      // Checksum
	WORD   e_ip;                        // Initial IP value
	WORD   e_cs;                        // Initial (relative) CS value
	WORD   e_lfarlc;                    // File address of relocation table
	WORD   e_ovno;                      // Overlay number
	WORD   e_res[4];                    // Reserved words
	WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
	WORD   e_oeminfo;                   // OEM information; e_oemid specific
	WORD   e_res2[10];                  // Reserved words
	LONG   e_lfanew;                    // File address of new exe header
	} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;
	*/
	cout << "*************************IMAGE_DOS_HEADER**************************" << endl;
	cout<<"ħ��:" <<hex<< lpDosHeader->e_magic << endl; //ħ������0x4d5a
	cout <<"�ļ����ҳ���ֽ���:"<< hex << lpDosHeader->e_cblp << endl; //�ļ����ҳ���ֽ���
	cout <<"�ļ�ҳ��:"<< hex << lpDosHeader->e_cp << endl; //�ļ�ҳ��
	cout <<"�ض�λԪ�ظ���:"<< hex << lpDosHeader->e_crlc << endl;//�ض�λԪ�ظ���
	cout <<"ͷ���ߴ�:"<< hex << lpDosHeader->e_cparhdr << endl;//ͷ���ߴ�
	cout << "�������С���Ӷ�:"<<hex << lpDosHeader->e_minalloc << endl;//�������С���Ӷ�
	cout << "�������󸽼Ӷ�:"<<hex << lpDosHeader->e_maxalloc << endl;//�������󸽼Ӷ�
	cout << "��ʼssֵ:"<<hex << lpDosHeader->e_ss << endl;//��ʼssֵ��ջ�� ƫ�ƣ�
	cout << "��ʼspֵ:"<<hex << lpDosHeader->e_sp << endl;//��ʼspֵ
	cout <<"У���:"<< hex << lpDosHeader->e_csum << endl;//У���
	cout << "��ʼipֵ:"<<hex << lpDosHeader->e_ip << endl;//��ʼipֵ
	cout << "��ʼcsֵ:"<<hex << lpDosHeader->e_cs << endl;//��ʼcsֵ������� ƫ�ƣ�
	cout << "�ض�λ����ļ���ƫ��:"<<hex << lpDosHeader->e_lfarlc << endl;//�ض�λ����ļ���ƫ��
	cout << "���Ǻ�:"<<hex << lpDosHeader->e_ovno << endl;//���Ǻ�
	//cout << hex << lpDosHeader->e_res << endl;//������
	cout << "OEM��ʶ��:"<<hex << lpDosHeader->e_oemid << endl;//OEM��ʶ��
	//cout << hex << lpDosHeader->e_res2[0]<< endl;//������
	cout << "��exeͷ����ַ:"<<hex << lpDosHeader->e_lfanew << endl;//��exeͷ����ַ

	cout << "**********************IAMGE_NT_HEADER*******************************" << endl;
	const IMAGE_NT_HEADERS32* lpNtHeader32 = PE.GetNtHeader();
	const IMAGE_NT_HEADERS64* lpNtHeader64 = (IMAGE_NT_HEADERS64*)lpNtHeader32;
	BOOL b64Bit =PE.Is64Bit();
	if (b64Bit == 0)
	{
		cout << "32λ����" << endl;
		cout << "IMAGE_NT_SIGNATUREħ��:"<<hex << lpNtHeader32->Signature << endl; //IMAGE_NT_SIGNATUREħ��

		//�������IMAGE_FILE_HEADER�ĸ���Ԫ��
		/*
		typedef struct _IMAGE_FILE_HEADER {
		WORD    Machine;
		WORD    NumberOfSections;
		DWORD   TimeDateStamp;
		DWORD   PointerToSymbolTable;
		DWORD   NumberOfSymbols;
		WORD    SizeOfOptionalHeader;
		WORD    Characteristics;
		} IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
		*/
		cout <<"����ƽ̨:"<< hex << lpNtHeader32->FileHeader.Machine << endl;//����ƽ̨
		/*
		#define IMAGE_FILE_MACHINE_UNKNOWN           0
		#define IMAGE_FILE_MACHINE_TARGET_HOST       0x0001  // Useful for indicating we want to interact with the host and not a WoW guest.
		#define IMAGE_FILE_MACHINE_I386              0x014c  // Intel 386.
		#define IMAGE_FILE_MACHINE_R3000             0x0162  // MIPS little-endian, 0x160 big-endian
		*/
		cout << "�ļ�������Ŀ:"<<hex << lpNtHeader32->FileHeader.NumberOfSections << endl;//�ļ�������Ŀ 
		cout << "�ļ��������ں�ʱ��:"<<hex << lpNtHeader32->FileHeader.TimeDateStamp << endl;//�ļ��������ں�ʱ��
		cout << "ָ����ű�:"<<hex << lpNtHeader32->FileHeader.PointerToSymbolTable << endl;//ָ����ű�(���ڵ��ԣ�
		cout << "���ű��з��Ÿ���:"<<hex << lpNtHeader32->FileHeader.NumberOfSymbols << endl;//���ű��з��Ÿ���(���ڵ���)
		cout << "IMAGE_OPTIONAL_HEADER32�ṹ��С:"<<hex << lpNtHeader32->FileHeader.SizeOfOptionalHeader << endl;//IMAGE_OPTIONAL_HEADER32�ṹ��С
		cout << "�ļ�����:"<<hex << lpNtHeader32->FileHeader.Characteristics << endl;//�ļ�����
		

		cout << "**********************IMAGE_OPTIONAL_HEADER**************************" << endl;
		//IMAGE_FILE_HEADER�����Զ���pe�ļ����ԣ���������ʹ����IMAGE_OPTIONAL_HEADER
		//���128���ֽ�Ϊ����Ŀ¼(IMAGE_DATA_DIRECTORY)
		/*
		WORD    Magic;
		BYTE    MajorLinkerVersion;
		BYTE    MinorLinkerVersion;
		DWORD   SizeOfCode;
		DWORD   SizeOfInitializedData;
		DWORD   SizeOfUninitializedData;
		DWORD   AddressOfEntryPoint;
		DWORD   BaseOfCode;
		DWORD   BaseOfData;
		//
		// NT additional fields. NT�ṹ���ӵ�����
		//
		DWORD   ImageBase;
		DWORD   SectionAlignment;
		DWORD   FileAlignment;
		WORD    MajorOperatingSystemVersion;
		WORD    MinorOperatingSystemVersion;
		WORD    MajorImageVersion;
		WORD    MinorImageVersion;
		WORD    MajorSubsystemVersion;
		WORD    MinorSubsystemVersion;
		DWORD   Win32VersionValue;
		DWORD   SizeOfImage;
		DWORD   SizeOfHeaders;
		DWORD   CheckSum;
		WORD    Subsystem;
		WORD    DllCharacteristics;
		DWORD   SizeOfStackReserve;
		DWORD   SizeOfStackCommit;
		DWORD   SizeOfHeapReserve;
		DWORD   SizeOfHeapCommit;
		DWORD   LoaderFlags;
		DWORD   NumberOfRvaAndSizes;
		*/

		//��־�֣�ROMӳ��(107h),��ͨ��ִ���ļ�(10bh)
		cout <<"�ļ�����:"<< hex << lpNtHeader32->OptionalHeader.Magic << endl;
		//���ӳ�������汾��
		cout << "���ӳ�������汾��:"<<hex << lpNtHeader32->OptionalHeader.MajorLinkerVersion << endl;
		//���ӳ���ΰ汾��
		cout << "���ӳ���ΰ汾��:"<<hex << lpNtHeader32->OptionalHeader.MinorImageVersion << endl;
		//����δ�С
		cout << "����δ�С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfCode << endl;
		//�ѳ�ʼ�����ݴ�С
		cout << "�ѳ�ʼ�����ݴ�С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfInitializedData << endl;
		//δ��ʼ�����ݴ�С(bss)
		cout <<"δ��ʼ�����ݴ�С:"<< hex << lpNtHeader32->OptionalHeader.SizeOfUninitializedData << endl;
		//��ڵ��ַ(RVA)
		cout << "��ڵ��ַ:"<<hex << lpNtHeader32->OptionalHeader.AddressOfEntryPoint << endl;
		//�������ʼ��ַ��RVA��
		cout << "�������ʼ��ַ:"<<hex << lpNtHeader32->OptionalHeader.BaseOfCode << endl;
		//���ݶ���ʼ��ַ��RVA��
		cout << "���ݶ���ʼ��ַ:"<<hex << lpNtHeader32->OptionalHeader.BaseOfData << endl;
		
		//�������ѡװ�ص�ַ
		cout << "�������ѡװ�ص�ַ:"<<hex << lpNtHeader32->OptionalHeader.ImageBase << endl;
		//�ڴ�����������С
		cout << "�ڴ�����������С:"<<hex << lpNtHeader32->OptionalHeader.SectionAlignment << endl;
		//�ļ�����������С
		cout << "�ļ�����������С:"<<hex << lpNtHeader32->OptionalHeader.FileAlignment << endl;
		//Ҫ�����ϵͳ��Ͱ汾�ŵ����汾��
		cout << "Ҫ�����ϵͳ��Ͱ汾�ŵ����汾��:"<<hex << lpNtHeader32->OptionalHeader.MajorOperatingSystemVersion << endl;
		//Ҫ�����ϵͳ��Ͱ汾�ŵĸ��汾��
		cout << "Ҫ�����ϵͳ��Ͱ汾�ŵĸ��汾��:"<<hex << lpNtHeader32->OptionalHeader.MinorOperatingSystemVersion << endl;
		/*
		.
		.
		.
		*/
		//ӳ��װ���ڴ����ܳߴ�
		cout << "ӳ��װ���ڴ����ܳߴ�:"<<hex << lpNtHeader32->OptionalHeader.SizeOfImage << endl;
		//����ͷ+�����ĳߴ��С
		cout << "����ͷ+�����ĳߴ��С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfHeaders << endl;
		//ӳ���У���
		cout << "ӳ���У���:"<<hex << lpNtHeader32->OptionalHeader.CheckSum << endl;
		//��ִ���ļ��ڴ�����ϵͳ
		cout << "��ִ���ļ��ڴ�����ϵͳ:"<<hex << lpNtHeader32->OptionalHeader.Subsystem << endl;
		//��ʼ��ʱջ��С
		cout << "��ʼ��ʱջ��С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfStackReserve << endl;
		//��ʼ��ʱʵ���ύ��ջ��С
		cout << "��ʼ��ʱʵ���ύ��ջ��С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfStackCommit << endl;
		//��ʼ��ʱ�����ĶѴ�С
		cout << "��ʼ��ʱ�����ĶѴ�С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfHeapReserve << endl;
		//��ʼ��ʱʵ���ύ�ĶѴ�С
		cout << "��ʼ��ʱʵ���ύ�ĶѴ�С:"<<hex << lpNtHeader32->OptionalHeader.SizeOfHeapCommit << endl;
		//������йأ�Ĭ��Ϊ0
		//cout << hex << lpNtHeader32->OptionalHeader.LoaderFlags << endl;
		//��һ���ṹ�壨����Ŀ¼��������(Ĭ��16)
		cout <<"��һ���ṹ�壨����Ŀ¼��������(Ĭ��16)"<<hex << lpNtHeader32->OptionalHeader.NumberOfRvaAndSizes << endl;
	}
	if (b64Bit == -1)
		cout << "64λ����" << endl;
	//cout << hex << lpNtHeader32->Signature << endl;
	//cout << b64Bit << hex << endl;

	cout << "*************************IMAGE_Section_Header***********************" << endl;
	/*
	typedef struct _IMAGE_SECTION_HEADER {
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
			DWORD   PhysicalAddress;
			DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   PointerToRelocations;
	DWORD   PointerToLinenumbers;
	WORD    NumberOfRelocations;
	WORD    NumberOfLinenumbers;
	DWORD   Characteristics;
	} IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

	*/
	WORD wSectionNum;
	const IMAGE_SECTION_HEADER* lpSectionHeader = PE.GetSectionHeader(&wSectionNum);
	for (WORD i = 0; i < wSectionNum; i++) {
		cout << "��" << i+1 << "������:" << endl;
		cout <<"������:"<< lpSectionHeader[i].Name<< endl; //����������
		cout <<"�����ַ:"<< hex<<lpSectionHeader[i].Misc.PhysicalAddress<<endl;//�����ַ
		cout << "��������ǰ�Ĵ�С:"<<hex<<lpSectionHeader[i].Misc.VirtualSize<<endl;//��������ǰ�Ĵ�С��ʵ�ʴ�С��
		cout << "�ÿ�װ�ص��ڴ��е�RVA:"<<hex << lpSectionHeader->VirtualAddress << endl;//�ÿ�װ�ص��ڴ��е�RVA
		cout << "�����ȣ��ļ��ж����Ĵ�С):"<<hex << lpSectionHeader->SizeOfRawData << endl;//�����ȣ��ļ��ж����Ĵ�С��
		cout << "�ڻ����ļ���ƫ����:"<<hex << lpSectionHeader->PointerToRawData << endl;//�ڻ����ļ���ƫ����
		cout << "�ض�λ��ƫ��:"<<hex << lpSectionHeader->PointerToRelocations << endl;//�ض�λ��ƫ��
		cout <<"�кű�ƫ��:"<< hex << lpSectionHeader->PointerToLinenumbers << endl;//�кű�ƫ��
		cout <<"�ض�λ�����Ŀ:"<< hex << lpSectionHeader->NumberOfRelocations << endl;//�ض�λ�����Ŀ
		cout <<"�кű����Ŀ:"<< hex << lpSectionHeader->NumberOfLinenumbers << endl;//�кű����Ŀ
		cout <<"������:"<< hex << lpSectionHeader->Characteristics << endl;//������
	}


	//�����
	/*
	union {
    DWORD   Characteristics;            // 0 for terminating null import descriptor
    DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
	//����ָ��IMAGE_DATA����������Ʊ�INT��RVA�Ľṹ������
    } DUMMYUNIONNAME;
    DWORD   TimeDateStamp;                  // 0 if not bound,
                                            // -1 if bound, and real date\time stamp
                                            //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                            // O.W. date/time stamp of DLL bound to (Old BIND)

    DWORD   ForwarderChain;                 // -1 if no forwarders
    DWORD   Name; //ָ�򱻵����DLL����
    DWORD   FirstThunk;   ָ�������ַ��IAT��RVA��IAT��һ��IMAGE_THUNK_DATA�ṹ������
	}IMAGE_IMPORT_DESCRIPTOR;
	*/
//	DWORD nImport;
	/*
	typedef struct _IMAGE_THUNK_DATA32 {
	union {
		DWORD ForwarderString;      // PBYTE ָ���ַ���RVA
		DWORD Function;             // PDWORD ָ�����뺯������ڵ�ַ
		DWORD Ordinal; �ú���������/����
		DWORD AddressOfData;        // PIMAGE_IMPORT_BY_NAME ָ�� ָ��IMAGE_IMPORT_BY_NAME
		} u1;
	} IMAGE_THUNK_DATA32;
	*/
	/*
	const IMAGE_IMPORT_DESCRIPTOR* lpImport = PE.GetImportDescriptor(&nImport);
	if (lpImport)
	{	
		for (DWORD i = 0UL; i < nImport; i++)
		{
			DWORD nThunk;
			const IMAGE_THUNK_DATA32* lpThunk = PE.GetImportThunkData(i,&nThunk);
			for (DWORD j = 0UL; j < nThunk; i++)
			{
				cout<<lpThunk->u1.ForwarderString<<endl;
			}
		}
	}
	*/
	//���뵼�����RVA
	cout << "���뵼�����RVA"<<hex << lpNtHeader32->OptionalHeader\
		.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress<<endl;
	//���������RVA
	cout << "���������RVA"<<hex << lpNtHeader32->OptionalHeader.\
		DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress<<endl;

	return 0;
}