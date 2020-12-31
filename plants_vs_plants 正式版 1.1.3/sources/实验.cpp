
#ifndef _GAMES_CPP_ 
    #define _GAMES_CPP_
    #include "game.cpp"
#endif

int main()
{
	srand(/*(int)time(NULL)*/26271587);
	const char *size_cmd="mode con cols=150 lines=40";
	User user;system(size_cmd);
	user.get_users_information((char *)"cc");
	int i=0,j;
	int K=4; 
	int start_cards=2;
	gamemode(&user);
	//game(&user,/*HARMONY*/HARD,K,start_cards,true);
    return 0;	
}
