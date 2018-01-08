#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "ProcessManagement.h"


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

	int GetPID() { return PID; }
	int GetProcessState() { return processState; }
	int GetPid() { return PID; }

	Process(int ID, Process* father, std::string processName, std::string txt); //konstruktor procesu;
	
};


struct ProcessManagement
{
public:
	Process* init; //proces, kt�ry wytwarza si� przy startowaniu systemu

	std::vector<Process*> readyProcesses;
	//
	//
	//
	//
	// tu doda� marcina rzeczy
	//
	//
	//
	//
	

	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	ProcessManagement() {
		init = new Process(freeID, nullptr, "init", NULL);
		freeID++;
	};

	Process* FindProcess(int ID, Process* init); //funkcja przeszukuj�ca drzewo proces�w 


	int FindFreeID(); //wybieranie wolnego ID

	void AddProcess(std::string processName, std::string commands, int parentID = 0);

	void KillProcess(int ID);

	void ChangeState(int ID, int newstate);

	void PrintProcess(int ID);

	void PrintAllProcesses();
};