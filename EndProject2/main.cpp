#include "baseDonkey.h"
#include "DonkeyGame.h"
#include "loadDonkeyGame.h"

int main(int argc, char** argv) 
{
	BaseDonkey* donkey;
	bool isLoad = argc > 1 && std::string(argv[1]) == "-load";
	bool isSave= argc > 1 && std::string(argv[1]) == "-save";
	bool isSilent = isLoad && argc > 2 && std::string(argv[2]) == "-silent";
	
	
	if (isLoad)
	{
		donkey = new LoadDonkeyGame(isSilent);
	}
	else {
		donkey = new DonkeyGame(isSave);
	}

	donkey->startGame();

	delete donkey;
	
	
}
	
