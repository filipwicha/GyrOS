#include "Shell.h"
#define test true ////////do testów
#define separator '~'
using namespace std;

void Shell::wydziel_rozkaz(string &kom) {
	int pos = -1;
	bool pom = true;
	string rozkaz, parametry;
	for (int i = 0; i < kom.size(); i++) {
		if (kom[i] != ' ')
		{
			pos++;
		}
		else
		{
			rozkaz = namale(kom.substr(0, pos + 1));

			if (rozkaz == "echo")
				parametry = kom.substr(pos + 2, kom.size() - pos);
			else
				parametry = end(standard(begin(kom.substr(pos + 2, kom.size() - pos))));

			rozpoznaj_rozkaz(rozkaz, parametry);
			pom = false;
			break;
		}
	}
	if (pom)
	{
		rozkaz = end(standard(namale(kom)));
		parametry = "";
		rozpoznaj_rozkaz(rozkaz, parametry);
	}
	/*cout << "\nKomenda: \"" << rozkaz << "\"";
	cout << "\nParametry: \"" << parametry << "\"";*/
}
void Shell::rozpoznaj_rozkaz(string s1, string s2) {
	switch (rozkaz[s1])
	{
	case 1: {help(); }; break;
	case 2: {cls();  }; break;
	case 3: {del(s2); }; break;
	case 4: {echo(s2); }; break;
	case 5: {ext(); }; break;
	case 6: {type(s2); }; break;
	case 7: {rename(s2); }; break;
	case 8: {start(s2); }; break;
	case 9: {taskkill(s2); }; break;
	case 10: {tasklist(); }; break;
	case 11: {go(); }; break;
	case 12: {check(); }; break;
	case 13: {mklink(s2); }; break;
	case 14: {dir(); }; break;
	default: {
		if (s1.size()>4 && s1[s1.size() - 4] == '.' && s1[s1.size() - 3] == 'b' && s1[s1.size() - 2] == 'a' && s1[s1.size() - 1] == 't')
		{
			czytaj_skrypt(s1);
		}
		else
		{
			cout << "\tNiepoprawna komenda.\n";
		}
	}; break;
	}
}
void Shell::help()
{
	cout << "\nHELP					Wyswietla na ekranie wszystkie dostepne komendy.";
	cout << "\nCLS					Czysci bufor ekranu.";
	cout << "\nDEL nazwa_pliku				Usuwa plik o wskazanej nazwie.";
	cout << "\nDIR					Wyswietla liste plikow.";
	cout << "\nECHO tekst				Przekzuje na ekran wpisany tekst.";
	cout << "\nECHO tekst>nazwa_pliku			Umozliwia przekazanie(nadpisanie) tekstu do wskazanego pliku.";
	cout << "\nECHO tekst>>nazwa_pliku			Umozliwia dopisanie tekstu na koniec wskazanego pliku.";
	cout << "\nEXIT					Zamyka system.";
	cout << "\nTYPE nazwa_pliku			Wyswietla zawartosc wskazanego pliku.";
	cout << "\nRENAME stara_nazwa nowa_nazwa		Zmienia nazwe wskazanego pliku.";
	cout << "\nSTART nazwa_procesu plik_procesu	Uruchamia proces o wskazanych parametrach.";
	cout << "\nTASKKILL nazwa_procesu			Wstrzymuje wskazany proces.";
	cout << "\nTASKLIST				Wyswietla liste procesow.";
	cout << "\nMKLINK nazwa_pliku alias_pliku		Tworzy Alias do wskazanego pliku.";
	cout << "\nGO					Wywoluje kolejny 'krok' systemu (jeden rozkaz asemblerowy).";
	cout << "\nCHECK					Wyswietla biezacy stan systemu.\n";
}
void Shell::echo(string &s) {
	if (echo_przekaz(s))
		cout << endl << s << endl;
}
bool Shell::echo_przekaz(string &s) //trzeba co nieco usprawnić
{
	bool tn = true;
	string txt = "", plik = "";
	int pos;
	for (int i = 0; i < s.size(); i++)
	{
		/*if (s[i] == '\'' || s[i] == '\"')
		{
		continue;
		}
		if (s[i] != '>')
		txt += s[i];*/
		if (s[0] == '\"')
		{
			txt = cudzy(s);
		}
		else
		{
			if (s[i] != '>')
			{
				txt += s[i];
			}
		}
		if (s[i] == '>')
		{
			pos = i;
			tn = false;
			if (s[i + 1] == '>')
			{
				if (s[i + 2] == '\"')
					tn = true;
			}
			else
			{
				if (s[i + 1] == '\"')
					tn = true;
			}
			break;
		}
	}
	if (!tn)
	{
		if (s[pos + 1] == '>')
		{
			plik = s.substr(pos + 2, s.size() - pos - 2);
			if (plik[0] == ' ')
				plik = plik.substr(1, plik.size() - 1);
			dopisz(txt, plik);
		}
		else
		{
			plik = s.substr(pos + 1, s.size() - pos - 1);
			if (plik[0] == ' ')
				plik = plik.substr(1, plik.size() - 1);
			nadpisz(txt, plik);
		}
	}
	/*cout << endl << "Tekst:" << txt << endl;
	cout << endl << "Docel:" << plik << endl;*/
	return tn;
}
void Shell::nadpisz(string &s, string &p)
{
	if (!test /*dysk.plikexist(p)*/)
	{
		dysk.writeFile(p, s);
	}
	else
	{
		dysk.createFile(p);
		dysk.writeFile(p, s);
	}

}
void Shell::dopisz(string &s, string &p)
{
	if (dysk.appendFile(p, s))
	{
		//cout << "\nDopisano: " << s << " do pliku: " << p << endl;
	}
	else
	{
		cout << "\nBlad otwarcia pliku" << endl;
	}
}
void Shell::cls() {
	system("cls");
}
void Shell::del(string &s)
{
	if (dysk.deleteFile(s))
	{
		cout << "\nPlik: " << s << " usunieto" << endl;
	}
	else
	{
		cout << "\nNie udalo sie usunac pliku: " << s << endl;
	}
}
void Shell::ext() {
	kropki("Zamykanie systemu");
	work = false;
}
void Shell::type(string &s)
{
	if (s.size() != 0)
	{
		string plik = "", tresc;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != separator)
				plik += s[i];
		}
		if (dysk.readFile(s, tresc))
			cout << "\nZawartosc pliku " << plik << ": " << tresc << endl;
		else
			cout << "\nBlad otwarcia pliku" << endl;
	}
	else
		cout << "\tNiepoprawna komenda.\n";
}
void Shell::rename(string &s)
{
	if (s.size() != 0)
	{
		string stara = "", nowa = "";
		bool n = false;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == separator)
			{
				n = true;
				continue;
			}
			if (!n)
			{
				stara += s[i];
			}
			if (n)
			{
				nowa += s[i];
			}
		}
		if (dysk.changeFilename(stara, nowa))
			cout << "\nZmiana nazwy pliku: " << stara << " na: " << nowa << endl;
		else
			cout << "\nNie udalo sie zmienic nazwy pliku: " << stara << endl;
	}
	else
		cout << "\n\tNiepoprawna komenda.\n";
}
void Shell::start(string &s)//usprawnij tą funkcję o błędy w wyniku złego zapisania
{
	if (s.size() != 0)
	{
		string nazwa = "", kod = ""; // roz = "";
		bool ok = true;
		int /*rozmiar,*/ e = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == separator)
			{
				e++;
				continue;
			}
			if (e == 0)
			{
				nazwa += s[i];
			}
			/*if (e == 1)
			{
			if(nazwa!="")
			roz += s[i];
			else
			{
			ok = false;
			break;
			}
			}*/
			if (e == 1)//bylo 2
			{
				if (nazwa != "")//byl roz
					kod += s[i];
				else
				{
					ok = false;
					break;
				}
			}
		}
		if (kod == "")
			ok = false;
		/*for (int j = 0; j < roz.size(); j++)
		{
		if (int(roz[j])< 48 || int(roz[j])>57)
		{
		ok = false;
		break;
		}
		}*/
		if (ok)
		{
			//rozmiar = stoi(roz);
			/*W tym miejcu wstaw funkcję od procesów*/
			if (test)
			{
				procesy.AddProcess(nazwa, kod, 0);
				cout << "Stworzono proces: " << nazwa << " o kodzie zrodlowym z pliku: " << kod;
			}
			else
				cout << "Blad przy tworzeniu procesu!";
		}
		else
		{
			cout << "\tNiepoprawna komenda.\n";
		}
	}
	else
		cout << "\tNiepoprawna komenda.\n";
}
void Shell::taskkill(string &s)
{
	if (s.size() != 0)
	{
		string nazwa = "";
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != separator)
				nazwa += s[i];
		}
		procesy.KillProcess(nazwa);
		cout << "Zabicie procesu o nazwie: " << nazwa;
	}
	else
		cout << "\tNiepoprawna komenda.\n";
}
void Shell::tasklist()
{
	procesy.PrintAllProcesses();
	//PrintAllProcess();
}
void Shell::go()
{
	//procesor.Step(1);
}
void Shell::mklink(string &s)
{
	if (s.size() != 0)
	{
		string nazwa = "", alias = "";
		bool n = false;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == separator)
			{
				n = true;
				continue;
			}
			if (n)
			{
				nazwa += s[i];
			}
			if (!n)
			{
				alias += s[i];
			}
		}
		if (compare(nazwa, alias))
		{
			if (dysk.addFilename(nazwa, alias))
				cout << "\nDopisanie aliasa: " << alias << " do pliku: " << nazwa << endl;
			else
				cout << "\nNie udalo sie dopisac aliasa do pliku: " << nazwa << endl;
		}
		else
			cout << "\nBlad tworzenia Aliasa. Niezgodnosc formatow.\n";
	}
	else
		cout << "\n\tNiepoprawna komenda.\n";

}
void Shell::check()
{
	cout << "\nStan systemu: ";
}
void Shell::dir()
{
	dysk.print_directory();
}
void Shell::czytaj_skrypt(string s)
{
	string  tekst;
	ifstream plik;
	plik.open(s);
	if (plik.is_open())
	{
		while (plik.good())
		{
			getline(plik, tekst);
			if (tekst != "");
			wydziel_rozkaz(tekst);
		}
	}
	else {
		cout << "\n\tNie znaleziono wskazanego pliku";
	}
}

string Shell::namale(string &s)
{
	string male = "";
	int pom = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (int(s[i]) >= 65 && int(s[i]) <= 90)
		{
			male += char(int(s[i]) + 32);
		}
		else
		{
			male += s[i];
		}
	}
	return male;
}
string Shell::standard(string &s)
{
	int pom = 0;
	string s2 = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			pom = 0;
			s2 += s[i];
		}
		else
		{
			pom++;
		}
		if (pom == 1)
		{
			s2 += separator;
		}
	}
	//cout << endl << "Standard: \"" << s2 << "\"";
	return s2;
}
string Shell::begin(string &s)
{
	string kom = "";
	bool pom = true;
	if (s[0] == ' ')
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != ' ')
			{
				pom = false;
			}
			if (!pom)
			{
				kom += s[i];
			}
		}
	}
	else
		kom = s;

	//cout << endl << "BEGIN: \"" << kom << "\"";
	return kom;
}
string Shell::end(string &s)
{
	string kom = "";
	bool pom = true;
	size_t z = s.size();
	if ((z - 1) > 0)
	{
		if (s[s.size() - 1] == separator)
		{
			for (size_t i = s.size() - 1; i >= 0; i--)
			{
				if (s[i] != separator)
				{
					pom = false;
				}
				if (!pom)
				{
					kom = s[i] + kom;
				}
			}
		}
		else
			kom = s;
		/*cout << endl << "END: \"" << kom << "\"";*/
	}

	return kom;
}
void Shell::kropki(string s)
{
	int pom = 0, i = 12;
	while (i)
	{
		pom++;
		if (pom>3)
			pom = pom - 3;

		if (pom == 1)
		{
			cout << s << ".";
			Sleep(300); system("cls");
		}
		if (pom == 2)
		{
			cout << s << "..";
			Sleep(300); system("cls");
		}
		if (pom == 3)
		{
			cout << s << "...";
			Sleep(300); system("cls");
		}
		i--;
	}
}
string Shell::cudzy(string &s)
{
	string s1 = "";
	int licz = 0;
	bool pole = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\"')
		{
			licz++;
			pole = true;
			continue;
		}
		if (s[i] == '\"')
		{
			pole = false;
		}
		if (licz == 1 && pole)
		{
			s1 += s[i];
		}
	}
	return s1;
}
bool Shell::compare(string &s1, string &s2)
{
	string r1 = "", r2 = "";
	bool zwroc = false, pom = false;
	for (int i = 0; i < s1.size(); i++)
	{
		if (s1[i] == '.')
		{
			pom = true;
		}
		if (pom)
		{
			r1 += s1[i];
		}
	}
	pom = false;
	for (int i = 0; i < s2.size(); i++)
	{
		if (s2[i] == '.')
		{
			pom = true;
		}
		if (pom)
		{
			r2 += s2[i];
		}
	}
	/*cout << "\nr1: " << r1;
	cout << "\nr2: " << r2;*/
	if (r1.compare(r2) == 0)
		zwroc = true;
	return zwroc;
}