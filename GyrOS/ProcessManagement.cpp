#include "ProcessManagement.h"

Process::Process(int ID, Process* father, std::string processName, std::string commands) //konstruktor procesu;
{
	processState = 0;
	PID = ID;
	parent = father;
	//ram->WriteToMemory(ID, commands);
	name = processName;
}

int Process::GetPID() 
{ 
	return PID; 
}

int Process::GetProcessState() 
{ 
	return processState;
}

Process* ProcessManagement::FindProcess(int ID, Process* init)
{
	if (init->PID == ID) //je�eli ID procesu si� zgadza z szukanym
	{
		return init; //koniec rekurencji, zwraca znaleziony proces w postaci wska�nika
	}
	else
	{
		for each (Process* process in init->children)
		{
			Process* notnullptr = FindProcess(ID, process); //wykonaj rekurencje
			if (notnullptr)
			{
				return notnullptr;
			}
		}
		return nullptr;
	}
} //funkcja przeszukuj�ca drzewo proces�w 

Process* ProcessManagement::FindProcess(std::string name, Process* init)
{
	if (init->name == name) //je�eli ID procesu si� zgadza z szukanym
	{
		return init; //koniec rekurencji, zwraca znaleziony proces w postaci wska�nika
	}
	else
	{
		for each (Process* process in init->children)
		{
			Process* notnullptr = FindProcess(name, process); //wykonaj rekurencje
			if (notnullptr)
			{
				return notnullptr;
			}
		}
		return nullptr;
	}
} //funkcja przeszukuj�ca drzewo proces�w 

#include "ProcessManagement.h"

Process::Process(int ID, Process* father, std::string processName, std::string commands) //konstruktor procesu;
{
	processState = 0;
	PID = ID;
	parent = father;
	//ram->WriteToMemory(ID, commands);
	name = processName;
}

int Process::GetPID()
{
	return PID;
}

int Process::GetProcessState()
{
	return processState;
}

Process* ProcessManagement::FindProcess(int ID, Process* init)
{
	if (init->PID == ID) //je�eli ID procesu si� zgadza z szukanym
	{
		return init; //koniec rekurencji, zwraca znaleziony proces w postaci wska�nika
	}
	else
	{
		for each (Process* process in init->children)
		{
			Process* notnullptr = FindProcess(ID, process); //wykonaj rekurencje
			if (notnullptr)
			{
				return notnullptr;
			}
		}
		return nullptr;
	}
} //funkcja przeszukuj�ca drzewo proces�w 

int ProcessManagement::FindFreeID()
{
	int a = freeID;
	freeID++;
	return a;
}

void ProcessManagement::AddProcess(std::string processName, std::string commands, int parentID)
{
	Process* temp = FindProcess(parentID, init);
	if (temp == nullptr)
	{
		std::cout << "Wrong parent ID" << std::endl;
	}
	else
	{
		//PROCES RODZIC SIE WSTRZMUJE (U MARCINA)
		int id = FindFreeID();
		std::cout << "Stworzenie procesu o id: " << id << " o nazwie " << processName << ".\n";
		temp->children.emplace_back(new Process(id, temp, processName, commands)); //dodawanie do listy potomk�w dla rodzimego procesu
	}
}

void ProcessManagement::KillProcess(std::string name)
{
	Process* temp = FindProcess(name, init); // if nullptr
	if (!temp)
		std::cout << "Deleting process uncomplited.\n";
	int i = 0;

	for each (Process* process in temp->children)
	{
		process->parent = init;
		init->children.push_back(process);
	}
	auto it = temp->parent->children.begin();
	for (auto it = temp->parent->children.begin(); it != temp->parent->children.end(); it++)
	{
		if ((*it)->name == name)
		{
			temp->parent->children.erase(it);
			return;
		}
	}
	std::cout << "Theres no that process!\n";
}

void ProcessManagement::ChangeState(int ID, int newstate)
{
	Process* temp = FindProcess(ID, init);
	temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
	if (newstate == 1) //je�eli stan procesu ustawiany jest na ready to:
	{
		readyProcesses.push_back(temp); //dodawanie procesu do kolejki gotowych proces�w
	}
}

void ProcessManagement::PrintProcess(int ID)
{
	Process* temp = FindProcess(ID, init);
	std::cout << "Process " << temp->PID << "\twith parent ID " << temp->parent->PID << std::endl;
}

void ProcessManagement::PrintAllProcesses()
{
	for (int i = 0; i < freeID; i++)
	{
		Process* temp = FindProcess(i, init);

		if (temp)
		{
			if (temp->parent == nullptr)
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << std::endl;
			}
			else
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << " with parent ID " << temp->parent->PID << std::endl;
			}
		}
	}
}

int ProcessManagement::FindFreeID()
{
	int a = freeID;
	freeID++;
	return a;
}

void ProcessManagement::AddProcess(std::string processName, std::string commands, int parentID)
{
	Process* temp = FindProcess(parentID, init);
	if (temp == nullptr)
	{
		std::cout << "Wrong parent ID" << std::endl;
	}
	else
	{
		//PROCES RODZIC SIE WSTRZMUJE (U MARCINA)
		int id = FindFreeID();
		std::cout << "Stworzenie procesu o id: " << id << " o nazwie " << processName << ".\n";
		temp->children.emplace_back(new Process(id, temp, processName, commands)); //dodawanie do listy potomk�w dla rodzimego procesu
	}
}

void ProcessManagement::KillProcess(int ID)
{
	Process* temp = FindProcess(ID, init); // if nullptr
	if (!temp)
		std::cout << "Deleting process uncomplited.\n";
	int i = 0;

	for each (Process* process in temp->children)
	{
		process->parent = init;
		init->children.push_back(process);
	}
	// na iteratorach i temp->parent-children.erase(iterator), jesli iterator == .end() to blad w kodzie
	auto it = temp->parent->children.begin();
	for (auto it = temp->parent->children.begin(); it != temp->parent->children.end(); it++)
	{
		if ((*it)->PID == ID)
		{
			temp->parent->children.erase(it);
			return;
		}
	}
	std::cout << "Theres no that process!\n";
}

void ProcessManagement::ChangeState(int ID, int newstate)
{
	Process* temp = FindProcess(ID, init);
	temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
	if (newstate == 1) //je�eli stan procesu ustawiany jest na ready to:
	{
		readyProcesses.push_back(temp); //dodawanie procesu do kolejki gotowych proces�w
	}
}

void ProcessManagement::PrintProcess(int ID) 
{
	Process* temp = FindProcess(ID, init);
	std::cout << "Process " << temp->PID << "\twith parent ID " << temp->parent->PID << std::endl;
}

void ProcessManagement::PrintAllProcesses() 
{
	for (int i = 0; i < freeID; i++)
	{
		Process* temp = FindProcess(i, init);

		if (temp)
		{
			if (temp->parent == nullptr)
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << std::endl;
			}
			else
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << " with parent ID " << temp->parent->PID << std::endl;
			}
		}
	}
}