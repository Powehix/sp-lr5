#include<iostream>
#include<Windows.h>

using namespace std;

int main(int argc, char **argv)
{
	/* ������� 1. �������� ���������� ����������, ��������� �� ����� �������� ��������� ����� �������. 
	����� ��������� � ��������� ������ �������� � ��������� � ����������. */

	setlocale(LC_ALL, "Russian");

	//���������� ��� ���������� ������� RegQueryInfoKey
	HKEY hKey = 0;
	char lpClass[256]; //����� ������ ��� ����� ������
	DWORD lpcchClass; //����� ������� ������ ��� ����� ������
	DWORD lpReserved; //���������������
	DWORD lpcSubKeys; //����� ������ ��� ���������� ���������
	DWORD lpcbMaxSubKeyLen; //����� ������ ��� ����������� ������� ����� ��������
	DWORD lpcbMaxClassLen; //����� ������ ��� ����������� ������� ����� ������
	DWORD lpcValues; //����� ������ ��� ���������� ��������� ��������
	DWORD lpcbMaxValueNameLen; //����� ������ ��� ����������� ������� ����� ��������
	DWORD lpcbMaxValueLen; //����� ������ ��� ����������� ������� ������ ��������
	DWORD lpcbSecurityDescriptor; //����� ������ ��� ����� ����������� ������������
	FILETIME lpftLastWriteTime; //����� ������ ��� ��������� ������� ��������� ������

	//���������� ��� ���������� ������� RegEnumKeyEx
	char lpName[256]; //����� ������ ��� ����� ��������
	DWORD lpcbName; //����� ������� ������ ��������

	//���������� ��� ����� �������� ������
	char root[256], key[256];
	DWORD dWord;

	cout << "Enter root key: ";
	cin >> root;
	cin.ignore();
	cout << "Enter key: ";
	cin >> key;
	cin.ignore();

	//���� ��������� ������������� �������� ���� ����������, �� �� �����������
	if (strcmp(root, "HKEY_CLASSES_ROOT") == 0)
	{
		RegOpenKeyEx(HKEY_CLASSES_ROOT, key, 0, KEY_READ, &hKey);
	}
	else if (strcmp(root, "HKEY_CURRENT_USER") == 0) 
	{
		RegOpenKeyEx(HKEY_CURRENT_USER, key, 0, KEY_READ, &hKey);
	}
	else if (strcmp(root, "HKEY_LOCAL_MACHINE") == 0)
	{
		RegOpenKeyEx(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hKey);
	}
	else if (strcmp(root, "HKEY_USERS") == 0) 
	{
		RegOpenKeyEx(HKEY_USERS, key, 0, KEY_READ, &hKey);
	}
	else if (strcmp(root, "HKEY_CURRENT_CONFIG") == 0) 
	{
		RegOpenKeyEx(HKEY_CURRENT_CONFIG, key, 0, KEY_READ, &hKey);
	}
	else
	{ 
		cout << "\nIncorrect root!" << endl << endl;
		system("PAUSE");
		return 0;
	}

	//��������� ���������� � �����
	RegQueryInfoKey(hKey,
		lpClass,
		&lpcchClass,
		&lpReserved,
		&lpcSubKeys,
		&lpcbMaxSubKeyLen,
		&lpcbMaxClassLen,
		&lpcValues,
		&lpcbMaxValueNameLen,
		&lpcbMaxValueLen,
		&lpcbSecurityDescriptor,
		&lpftLastWriteTime);

	//������������ ��������� � ����� �� ��������
	cout << "\nSubkeys: " << endl << endl;
	for (int i = 0; i < lpcSubKeys; i++)
	{
		lpcbName = MAX_PATH;
		dWord = RegEnumKeyEx(hKey, i, lpName, &lpcbName, NULL, NULL, NULL, NULL);
		if (dWord == ERROR_SUCCESS)
		{
			cout << i + 1 << ". " << lpName << endl;
		}
		else i = lpcSubKeys - 1;  //����� �� �����
	}

	RegCloseKey(hKey);

	cout << endl;
	system("PAUSE");
	return 0;
}
