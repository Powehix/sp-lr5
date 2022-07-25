#include<iostream>
#include<Windows.h>

using namespace std;

int main(int argc, char **argv)
{
	/* Вариант 1. Написать консольное приложение, выводящее на экран подключи заданного ключа реестра. 
	Имена корневого и заданного ключей вводится в программу с клавиатуры. */

	setlocale(LC_ALL, "Russian");

	//переменные для заполнения функции RegQueryInfoKey
	HKEY hKey = 0;
	char lpClass[256]; //адрес буфера для имени класса
	DWORD lpcchClass; //адрес размера буфера для имени класса
	DWORD lpReserved; //зарезервировано
	DWORD lpcSubKeys; //адрес буфера для количества подключей
	DWORD lpcbMaxSubKeyLen; //адрес буфера для наибольшего размера имени подключа
	DWORD lpcbMaxClassLen; //адрес буфера для наибольшего размера имени класса
	DWORD lpcValues; //адрес буфера для количества вхождений значений
	DWORD lpcbMaxValueNameLen; //адрес буфера для наибольшего размера имени значения
	DWORD lpcbMaxValueLen; //адрес буфера для наибольшего размера данных значения
	DWORD lpcbSecurityDescriptor; //адрес буфера для длины дескриптора безопасности
	FILETIME lpftLastWriteTime; //адрес буфера для получения времени последней записи

	//переменные для заполнения функции RegEnumKeyEx
	char lpName[256]; //адрес буфера для имени подключа
	DWORD lpcbName; //адрес размера буфера подключа

	//переменные для ввода заданных ключей
	char root[256], key[256];
	DWORD dWord;

	cout << "Enter root key: ";
	cin >> root;
	cin.ignore();
	cout << "Enter key: ";
	cin >> key;
	cin.ignore();

	//если введенный пользователем корневой ключ существует, то он открывается
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

	//получение информации о ключе
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

	//перечисление подключей и вывод их названий
	cout << "\nSubkeys: " << endl << endl;
	for (int i = 0; i < lpcSubKeys; i++)
	{
		lpcbName = MAX_PATH;
		dWord = RegEnumKeyEx(hKey, i, lpName, &lpcbName, NULL, NULL, NULL, NULL);
		if (dWord == ERROR_SUCCESS)
		{
			cout << i + 1 << ". " << lpName << endl;
		}
		else i = lpcSubKeys - 1;  //выход из цикла
	}

	RegCloseKey(hKey);

	cout << endl;
	system("PAUSE");
	return 0;
}
