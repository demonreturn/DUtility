// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DUTILITY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DUTILITY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DUTILITY_EXPORTS
#define DUTILITY_API __declspec(dllexport)
#else
#define DUTILITY_API __declspec(dllimport)
#endif

// �����Ǵ� DUtility.dll ������
class DUTILITY_API CDUtility {
public:
	CDUtility(void);
	// TODO: �ڴ�������ķ�����
};

extern DUTILITY_API int nDUtility;

DUTILITY_API int fnDUtility(void);
