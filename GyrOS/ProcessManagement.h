#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ProcessManagement.h"

struct Ram
{
	void WriteToMemory(int PID, int lenght, std::string txt); //wywo�ywanie pami�ci
};

Ram* ram;

struct Process
{
public:
	int PID;
	int processState; //0=virgin, 1=ready, 2=running, 3=waiting, 4=terminated;
	std::string name;

	Process* parent; //procesy przedstawiaj� drzewo, gdzie rodzic jest procesem macierzystym
	std::vector<Process*> children; //a dzieci jego procesami potomnymi

	int regA;    // 4 warto�ci rejestr�w procesora
	int regB;
	int regC;
	int regD;

	int programCounter = 0; //wskazuje nast�pn� instrukcj� do wykonania
	int programPosition;
	bool processBlocked;

	int GetPID() { return PID; }
	int GetProcessState() { return processState; }
	int GetPid() { return PID; }

	Process(int ID, Process* father, std::string processName, std::string txt) //konstruktor procesu;
	{
		processState = 0;
		processBlocked = false;
		PID = ID;
		parent = father;
		ram->WriteToMemory(ID, txt.length(), txt);
		name = processName;
	}
};


struct ProcessManagement
{
public:
	Process* init; //proces, kt�ry wytwarza si� przy startowaniu systemu

	std::vector<Process*> readyProcesses;
	//
	//
	// tu doda� marcina rzeczy
	//
	//
	//
	//
	

	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	ProcessManagement()
	{
		init = new Process(freeID, nullptr, "init", NULL);
		freeID++;
	}

	Process* FindProcess(int ID, Process* init) //funkcja przeszukuj�ca drzewo proces�w 
	{
		if (init->PID == ID) //je�eli ID procesu si� zgadza z szukanym
		{
			return init; //koniec rekurencji, zwraca znaleziony proces w postaci wska�nika
		}
		else
		{
			int i = 0;
			while (init->children[i]) //je�eli dzieci istniej�
			{
				i++;
				return FindProcess(ID, init->children[i]); //wykonaj rekurencje
			}
			return nullptr;
		}
	}

	int FindID() //znajdywanie wolnego ID
	{
		int ID = 0;
		while (FindProcess(ID, init)) //sprawdzanie czy ID jest juz u�ywane 
		{
			ID++;
		}
		return ID;
	}

	void AddProcess(std::string processName, std::string txt, int parentID = 0)
	{
		Process* virgin = new Process(freeID, FindProcess(parentID, init), processName, txt); //tworzenie procesu
		freeID++;
		FindProcess(parentID, init)->children.push_back(virgin); //dodawanie do listy potomk�w dla rodzimego procesu
	}

	void KillProcess(int ID)
	{
		Process* temp = FindProcess(ID, init);
		int i = 0;
		if (temp->children[i])
		{
			while (temp->children[i])
			{
				temp->children[i]->parent = init; //ustawianie wszystkich init jako rodzica wszystkich proces�w potomnych
			}
		}
		delete temp;
	}

	void ChangeState(int ID, int newstate)
	{
		Process* temp = FindProcess(ID, init);
		temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
		if (newstate == 1) //je�eli stan procesu ustawiany jest na ready to:
		{
			readyProcesses.push_back(temp); //dodawanie procesu do kolejki gotowych proces�w
		}
	}

	void PrintProcess(int ID)
	{
		std::cout << "Process " << FindProcess(ID, init)->PID << ": with parent ID " << FindProcess(ID, init)->parent << std::endl;
	}

	void PrintCurrent(Process* p)
	{

	}

	void PrintAllProcesses()
	{

	}
};

