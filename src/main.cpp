#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

//#include <boost/signals2.hpp>
//#include <sigc++/sigc++.h>
//#include <ev.h>
#include <Signal.h>

#include "console.hpp"
#include "library.hpp"
#include "player.hpp"
#include "rfid.hpp"

using namespace std;
using namespace console;
using namespace library;
using namespace player;
using namespace rfid;
//using namespace boost::signals2;
//using namespace sigc;
using namespace Gallant;

void start(string);
void printHelp(bool = false);
void resetLibrary(string);
void scanLibrary(void);

enum class Params
{
	HELP, RESET, SCAN
};
struct ParamsMap : map<Params, string>
{
	ParamsMap()
	{
		this->operator[](Params::HELP) = "-h";
		this->operator[](Params::RESET) = "-reset";
		this->operator[](Params::SCAN) = "-scan";
	};
	~ParamsMap(){};
};
static ParamsMap paramsMap;

ostringstream _outStream;
ostringstream _logStream;

int main(int argc, char **argv)
{
	string applicationPath = argv[0];
	
	if(argc==1)
	{
		start(applicationPath);
	}
	else if(argc==2)
	{
		string param = argv[1];
		
		if(param == paramsMap[Params::HELP])
			printHelp();
		else if(param == paramsMap[Params::RESET])
			resetLibrary(applicationPath);
		else if(param == paramsMap[Params::SCAN])
			scanLibrary();
	}
	else
	{
		printHelp(true);
		return -1;
	}
	
	return 0;
}

void start(string applicationPath)
{
	Console* _pConsole = new Console(VERTICAL_LAYOUT);
	Library* _pLibrary = new Library(applicationPath, &_pConsole);
	
	Player* _pPlayer = new Player(&_pConsole);
	Rfid* _pRfid = new Rfid(&_pConsole);
	
	_pLibrary->logOutRfidMap();
	
	/*
	 * Boost
	signal<void (string)> rfidSignal;
	rfidSignal.connect(bind(&Library::setEpisode, _pLibrary, _1));
	
	signal<void (Library::Navigation)> navigationSignal;
	navigationSignal.connect(bind(&Library::navigate, _pLibrary, _1));
	*/
	
	/*
	 * libsigc++
	 * 
	rfidSignal.connect(sigc::ptr_fun(_pLibrary, &Library::setEpisode));
	rfidSignal.connect(sigc::mem_fun(_pLibrary, &Library::setEpisode));
	*/
	
	/*
	 * libsigc++
	 * 
	signal<void, string> rfidSignal;
	rfidSignal.connect(_pLibrary->setEpisodeSlot);
	
	signal<void, Library::Navigation> navigationSignal;
	navigationSignal.connect(_pLibrary->navigateSlot);
	*/

	/*
	 * pbhogan_signals
	 * 
	Signal1<string> rfidSignal;
	rfidSignal.Connect(_pLibrary, &Library::setEpisode);
	
	Signal1<Library::Navigation> navigationSignal;
	navigationSignal.Connect(_pLibrary, &Library::navigate);
	*/
	
	bool isLoop = true;
	while(isLoop)
	{
		int charCode = _pConsole->waitForChar();
		_logStream << "charCode: " << charCode << " - char: " << (char)charCode;
		_pConsole->printLog(&_logStream);
		
		switch((char)charCode)
		{
			case 'c': //99
				isLoop = false;
				break;
			case 'n': //110
				//navigationSignal(Library::Navigation::NEXT);
				break;
			case 'p': //112
				//navigationSignal(Library::Navigation::PREVIOUS);
				break;
			case 'r': //
				//navigationSignal(Library::Navigation::RESET);
				break;
			case '1': //49
				//rfidSignal("x11111111");
				break;
			case '2': //50
				//rfidSignal("x12121212");
				break;
			case '3': //51
				//rfidSignal("x13131313");
				break;
			case '4': //52
				//rfidSignal("xxxxxxxxx");
				break;
			case '5': //53
				//rfidSignal("x21212121");
				break;
			case '6': //54
				//rfidSignal("x22222222");
				break;
		}
	}
	
	//delete _pRfid;
	//delete _pPlayer;
	delete _pLibrary;
	delete _pConsole;
}

void printHelp(bool isArgumentWrong)
{
	if(isArgumentWrong)
	{
		cout << "Wrong number of arguments. Use \"pi_player_kids -h\" for details" << endl;
	}
	cout << "pi_player_kids [-h|-scan|-reset]" << endl;
	cout << "   -h       This help." << endl;
	cout << "   -reset   Delete current library. WARNING: all RFID codes will be deleted!" << endl;
	cout << "   -scan    Scan for new files. Reorder files for episodes. Assign RFID codes to episodes." << endl;
}

void resetLibrary(string applicationPath)
{
}

void scanLibrary(void)
{
}
