#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct student {
	string surname;
	string name;
	string otchestvo;
	string data;
	int mark;
	student *next;
} *head;



void AddStudent(student *&ph, student *&pt, string surname, string name, string otchestvo, string data, int mark) {
	student *t = new student;
	t->surname = surname; t->name = name; t->otchestvo = otchestvo; t->data = data; t->mark = mark;
	t->next = NULL;
	if (ph == NULL) ph = pt = t; else pt = pt->next = t;
}

void PrintStudent(student *ph) {
	if (ph == NULL) {
		cout << "Queque clear";
	}
	while (ph != NULL) {
		cout << ph->surname << " " << ph->name << " " << ph->otchestvo << " " << ph->data << " " << ph->mark;
		cout << endl; ph = ph->next;
	}
	cout << endl;
}
void SerialStudent(student *ph) {
	ofstream fout("dump.bin", ios::binary);
	while (ph != NULL) {
		fout << ph->surname << " " << ph->name << " " << ph->otchestvo << " " << ph->data << " " << ph->mark;
		fout << endl; ph = ph->next;
	}
	cout << endl;
}

void FindStudent(student *ph, string surname, string name) {
	int k = 1;
	while (ph != NULL) {
		if (ph->surname == surname && ph->name == name) {
			cout << "Фамилия:" << ph->surname << " " << "Имя:" << ph->name << endl;
			return;
		}
		ph = ph->next;	k++;
	}
	cout << "-1" << endl;
	return;
}

void DeleteStudent(student *&ph, int n) {

	student *t1 = ph;
	if (n == 1) {
		ph = t1->next;
		delete t1;
		return;
	}
	for (int i = 1; i < n - 1; ++i) {
		t1 = t1->next;
		if ((t1 == NULL) || (t1->next == NULL)) {
			cout << "Error";
			cout << endl;
			return;
		}
	}
	student *t2 = t1->next;
	t1->next = t2->next;
	delete t2;
	return;
}


void SortStudent(student *ph) {

	student *p = new student;
	student *pp = new student;
	for (student *p = ph; p != NULL; p = p->next)
		for (student *pp = ph; pp->next != NULL; pp = pp->next)
			if (pp->surname > pp->next->surname) {
				swap(pp->surname, (pp->next)->surname);
				swap(pp->name, (pp->next)->name);
				swap(pp->otchestvo, (pp->next)->otchestvo);
				swap(pp->data, (pp->next)->data);
				swap(pp->mark, (pp->next)->mark);
			}
			else if ((pp->surname == pp->next->surname) && (pp->name > pp->next->name)) {
				swap(pp->surname, (pp->next)->surname);
				swap(pp->name, (pp->next)->name);
				swap(pp->otchestvo, (pp->next)->otchestvo);
				swap(pp->data, (pp->next)->data);
				swap(pp->mark, (pp->next)->mark);
			}
}



int main() {
	system("CLS");
	setlocale(0, "RUS");

	string surname, name, otchestvo, data;
	int mark;
	student *t = new student;
	student *ph = NULL;
	student *pt = NULL;  
	int variant = 0;
	bool flag = true;
	while (1) {

		cout << "Что хотите сделать?\n" << endl;
		cout << "1. Добавить студента\n"
			<< "2. Посмотреть студента\n"
			<< "3. Поиск по фамилии и имени\n"
			<< "4. Удалить студента по номеру\n"
			<< "5. Сортировка по фамилии и имени\n"
			<< "6. Сериализация\n"
			<< "7. Выйти\n" << endl;
		cout << "Что хотите сделать?\n" << endl;
		cin >> variant;
		system("CLS");
		switch (variant) {
		case 1:
			flag = true;
			while (flag) {
				cout << "Добавить студента:" << endl;
				cout << "Фамилия, имя, отчество, дата рождения, оценка" << endl;
				cin >> surname; if (surname == "end") { break; }
				cin >> name >> otchestvo >> data >> mark;
				AddStudent(ph, pt, surname, name, otchestvo, data, mark);

				cout << "Студент добавлен" << endl;
				cout << endl;
				flag = false;
			}
			system("CLS");
			break;
		case 2:
			cout << endl;
			PrintStudent(ph);
			break;
		case 3:
			cout << "Поиск по фамилии и имени: " << endl;
			cin >> surname >> name;
			FindStudent(ph, surname, name);
			break;
		case 4:

			cout << "Номер студента: ";
			int n;
			cin >> n;
			cout << endl;
			DeleteStudent(ph, n);
			break;
		case 5:
			cout << "Сортировка по фамилии и имени" << endl;
			SortStudent(ph);
			break;
		case 6:
			SerialStudent(ph);
			cout << "Сериализация выполнена успешно" << endl;
			break;
		case 7:
			cout << "Пока Оичан!" << endl;
			exit(EXIT_SUCCESS);
		default:
			cout << "А по нормальному нельзя? -_-";
		}
	}
	system("PAUSE");
	return 0;
}
