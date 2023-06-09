#include "../headers/Game.hpp"
#include "../headers/GameState.hpp"
#include <iostream>

bool Game::init() {
    //Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		Game::gWindow = SDL_CreateWindow( "Scooby Doo and The Haunted House", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( Game::gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			Game::gRenderer = SDL_CreateRenderer( Game::gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( Game::gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
                //Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
				else
				{
					// initializations of all the actors
					Game::assetManager = new AssetManager(Game::gRenderer);
					Game::scooby = new Scooby(0, 150 - 70);

					Game::floors = new BaseFloor*[3];
					Game::floors[0] = new Floor(0, 150);
					Game::floors[1] = new Floor(365, 300);
					Game::floors[2] = new Floor(0, 417);
					Game::floors[3] = new GroundFloor(0, 575);

					Game::snack1 = new Snack(800, 575 - 25); //25 is width of each floor
					Game::snack2 = new Snack(130, 150 - 25);

					Game::boobyTrap1 = new BoobyTrap(800, 300-25);
					Game::boobyTrap2 = new BoobyTrap(245, 417-25);

					// array of all treasure boxes of each floor
					Game::treasureBoxes = new TreasureBox*[12];
					int k = 0;
					for(int i = 0; i < 4; i++) { // loop over floors
						for(int j = 0; j < 3; j++) { // loop over treasure boxes
							Game::treasureBoxes[k++] = Game::floors[i]->getTreasureBoxes()[j]; // insert jth treasure box of ith floor in treasureBoxes array
						}
					}
					
					//Initialize renderer color
					SDL_SetRenderDrawColor( Game::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				}
			}
		}
	}

    return success;
}

// loads images and audioss from assets/
bool Game::loadAssets() {
    bool success = true;
	// 2nd param assigns they key to an image based on the provided source rect(3-6 params)
    success &= Game::assetManager->loadImage("assets/house.png", "bg", 0, 0, 1000, 600);
	success &= Game::assetManager->loadImage("assets/menu.png", "menu", 0, 0, 1000, 600);
	success &= Game::assetManager->loadImage("assets/gameover.png", "gameover", 0, 0, 1000, 600);
	success &= Game::assetManager->loadImage("assets/gamewin.png", "gamewin", 0, 0, 1000, 600);
	success &= Game::assetManager->loadImage("assets/instructions.png", "instructions", 0, 0, 1000, 600);
    success &= Game::assetManager->loadImage("assets/assets.png", "scooby_right0", 2108, 4075, 351, 179);
    success &= Game::assetManager->loadImage("assets/assets.png", "scooby_right1", 753, 116, 414, 192);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_right2", 741, 468, 416, 191);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_left0", 2108, 3717, 351, 179);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_left1", 741, 826, 416, 191);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_left2", 753, 1190, 414, 192);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_right0", 2000, 2870, 585, 358);
    success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_right1", 707, 1432, 585, 358);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_right2", 707, 1790, 585, 358);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_left0", 2000, 3228, 585, 358);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_left1", 707, 2148, 585, 358);
	success &= Game::assetManager->loadImage("assets/assets.png", "scooby_flashlight_left2", 707, 2506, 585, 358);
	success &= Game::assetManager->loadImage("assets/assets.png", "treasure_box_closed", 211, 2967, 1594, 754);
	success &= Game::assetManager->loadImage("assets/assets.png", "treasure_box_opened", 347, 3944, 1311, 1113);
	success &= Game::assetManager->loadImage("assets/assets.png", "snack", 277, 5566, 1492, 1271);
	success &= Game::assetManager->loadImage("assets/bolt.png", "energy", 264, 79, 672, 1042);
	success &= Game::assetManager->loadImage("assets/heart.png", "fear", 1, 1, 903, 847);
	success &= Game::assetManager->loadImage("assets/booby_trap.png", "booby_trap", 161, 162, 342, 212);

	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_W", 421, 244, 161, 175);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_A", 449, 846, 103, 172);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_R", 447, 1445, 107, 174);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_E", 453, 2043, 99, 178);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_H", 453, 2646, 101, 185);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_O", 451, 3248, 103, 174);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_U", 450, 3843, 107, 187);
	success &= Game::assetManager->loadImage("assets/warehouse.png", "clue_S", 451, 4444, 103, 176);

	bgmusic = Mix_LoadMUS("assets/bgmusic.mp3"); // ongoing bg music

	//sound effects
	treasure_open = Mix_LoadWAV("assets/chest.wav");
	clue_found = Mix_LoadWAV("assets/clue_found.wav");
	clue_notfound = Mix_LoadWAV("assets/scared.wav");
	scooby_scream = Mix_LoadWAV("assets/scream.wav");
	scooby_snack= Mix_LoadWAV("assets/snack.wav");
	gamewin = Mix_LoadWAV("assets/gamewin.wav");
	gamelose = Mix_LoadWAV("assets/gamelose.wav");
	if (bgmusic == NULL || treasure_open == NULL || clue_found == NULL || clue_notfound == NULL || scooby_scream == NULL || scooby_snack == NULL || gamewin == NULL || gamelose == NULL)
    {
        printf("Unable to load music: %s \n", Mix_GetError());
        success = false;
    }
    return success;
}

// collission detector for scooby being on top of any type of actor
bool Game::isScoobyOnTopOf(Actor* actor) {
	return (
		actor->getX() < Game::scooby->getX() + Game::scooby->getW() && 
		actor->getX() + actor->getW() > Game::scooby->getX() && 
		actor->getY() == Game::scooby->getY() + Game::scooby->getH()
	);
}

// checks for on-top-of collission with all the floors and treasure boxes
bool Game::isScoobyOnTopOfFloorOrTreasureBox() {
	for(int i = 0; i < 4; i++) {
		if(Game::isScoobyOnTopOf(Game::floors[i])) return true;
	}

	for(int i = 0; i < 12; i++) {
		if(Game::isScoobyOnTopOf(Game::treasureBoxes[i])) return true;
	}

	return false;
}

bool Game::isScoobyCollidingWithAnyFloor() {
	for(int i = 0; i < 4; i++) {
		if(Game::floors[i]->isCollidingWith(*Game::scooby)) return true;
	}
}

//collision with treasure boxes
bool Game::isScoobyOnTheLeftOfAnyTreasureBox() {
	for(int i = 0; i < 12; i++) {
		if(Game::scooby->isCollidingWith(*Game::treasureBoxes[i]) && Game::scooby->getX() + Game::scooby->getW() < Game::treasureBoxes[i]->getX()) return true;
	}
	return false;
}

bool Game::isScoobyOnTheRightOfAnyTreasureBox() {
	for(int i = 0; i < 12; i++) {
		if(Game::scooby->getX() < Game::treasureBoxes[i]->getX() + Game::treasureBoxes[i]->getW() && Game::scooby->isCollidingWith(*Game::treasureBoxes[i])) return true;
	}
	return false;
}

void Game::run() {
	bool check = false; // game loop boolean for menu screen
    SDL_Event e;

	// initially menu screen is shown and instructions is hidden
	bool menuScreen = true; 
	bool instructionsScreen = false;

	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	while (!check)
    {
        SDL_RenderCopyEx(gRenderer, gTexture, NULL, NULL, 0, 0, SDL_FLIP_NONE);
        SDL_RenderPresent(gRenderer);

		if(menuScreen) {
			assetManager->render("menu", 0, 0); //render menu bg
			int xMouse, yMouse;

			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					SDL_GetMouseState(&xMouse, &yMouse);
					if (xMouse > 690 && xMouse < 820 && yMouse > 350 && yMouse < 450) // handle click on play button
					{
						check = true;
						Mix_PlayMusic(bgmusic,-1);
					}

					if (xMouse > 870 && xMouse < 940 && yMouse > 470 && yMouse < 540) // handle click on instructions button
					{
						menuScreen = false;
						instructionsScreen = true;
					}
				}
			}
		} else if(instructionsScreen) {
			assetManager->render("instructions", 0, 0); // render instruction bg
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_KEYDOWN) // handle keypress on instruction screen
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_ESCAPE:
							menuScreen = true;
							instructionsScreen = false;
							break;
					}
				}
			}
		}
    }

    bool quit = false; // main game loop boolean
	int FEAR_TIMEOUT = 4; // num seconds for each heart to drop
	Uint32 fearTimeout = SDL_GetTicks() + FEAR_TIMEOUT*1000;
    while( !quit )
    {
		SDL_RenderClear( gRenderer );
		assetManager->render("bg", 0, 0); // render house background

        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT ) { // if user closes window
                quit = true;
            }
        }

		if(!GameState::getInstance()->isGameOver()) {

			// move left if left key pressed only if scooby is not touching the left side of the screen and not blocked by any treasure box
			if(keystate[SDL_SCANCODE_LEFT] && Game::scooby->getX() > 0 && !Game::isScoobyOnTheRightOfAnyTreasureBox()) {
				Game::scooby->moveLeft();
			}
			
			// move right if right key pressed only if scooby is not touching the right side of the screen and not blocked by any treasure box
			if(keystate[SDL_SCANCODE_RIGHT] && Game::scooby->getX() + Game::scooby->getW() < Game::SCREEN_WIDTH && !Game::isScoobyOnTheLeftOfAnyTreasureBox()) {
				Game::scooby->moveRight();
			}
			
			// start scooby jump on arrow key up only if its not failling down due to gravity
			if(!Game::isScoobyFalling && keystate[SDL_SCANCODE_UP]) Game::isScoobyJumping = true;
			
			// open flashlight on F key only if battery > 0
			if(keystate[SDL_SCANCODE_F] && Game::scooby->getBattery() > 0) {
				Game::scooby->turnFlashlightOn();
				FEAR_TIMEOUT = 8; // increase fear timeout to 8 seconds
			}
			else {
				Game::scooby->turnFlashlightOff();
				FEAR_TIMEOUT = 4; // decrease fear timeout back to 4 seconds when flashlight off
			}

			// if not moving left, right or up, toggle stand animation of scooby
			if(!keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_RIGHT] && !keystate[SDL_SCANCODE_UP]) Game::scooby->stand();

			// scooby jump if not in a falling state
			if(Game::isScoobyJumping && !Game::isScoobyFalling) {
				// incase scooby goes out of the top wall or hits a treasure box or a floor, jump is interrupted
				if((!Game::isScoobyOnTopOfFloorOrTreasureBox() && Game::isScoobyCollidingWithAnyFloor()) || Game::scooby->getY() < 0) {
					Game::scooby->interruptJump();
				}
				Game::scooby->jump();
				Game::isScoobyJumping = Game::scooby->isJumping(); // update jumping state to keep track of scooby jump
			}
			
			// if scooby is not jumping and not on top of floor or box, keep going down
			if(!(Game::isScoobyJumping || Game::isScoobyOnTopOfFloorOrTreasureBox())) {
				Game::scooby->moveDown();
				Game::isScoobyFalling = true;
			} else {
				Game::isScoobyFalling = false;
			}


			// if scooby is in air in a state of jump and lands on a floor or a box, halt the jump
			if(Game::isScoobyOnTopOfFloorOrTreasureBox() && Game::scooby->isInAir()) {
				Game::isScoobyJumping = false;
				Game::scooby->resetJump();
			}

			// render current energy bolts according to game state
			for(int i = 0; i < GameState::getInstance()->getEnergy(); i++) {
				assetManager->render("energy", 10 + i*30, 10, 15, 24);
			}

			// render current fear hearts according to game state
			for(int i = 0; i < GameState::getInstance()->getFear(); i++) {
				assetManager->render("fear", Game::SCREEN_WIDTH - 10 - (i+1)*35, 10, 25, 24);
			}

			// loop over 9 clues
			for(int i = 0; i < 9; i++) {
				if(GameState::getInstance()->hasFoundClue(i)) { // if clue number i has been found
					string clueLetter(1, GameState::getInstance()->getClue()[i]);
					// i*24 assigns unique position to each clue letter to display the clue letters in order
					assetManager->render("clue_" + clueLetter, 400 + i*24, 10, 24, 24); // render the clue letter
				}
			}

			// render non eaten snack 1
			if(!Game::snack1->isEaten()) {
				assetManager->render(Game::snack1->getAssetKey(), Game::snack1->getX(), Game::snack1->getY(), Game::snack1->getW(), Game::snack1->getH());
			}

			// render non eaten snack 2
			if(!Game::snack2->isEaten()) {
				assetManager->render(Game::snack2->getAssetKey(), Game::snack2->getX(), Game::snack2->getY(), Game::snack2->getW(), Game::snack2->getH());
			}

			// render booby traps
			assetManager->render(Game::boobyTrap1->getAssetKey(), Game::boobyTrap1->getX(), Game::boobyTrap1->getY(), Game::boobyTrap1->getW(), Game::boobyTrap1->getH());
			assetManager->render(Game::boobyTrap2->getAssetKey(), Game::boobyTrap2->getX(), Game::boobyTrap2->getY(), Game::boobyTrap2->getW(), Game::boobyTrap2->getH());

			// render scooby
			assetManager->render(Game::scooby->getAssetKey(), Game::scooby->getX(), Game::scooby->getY(), Game::scooby->getW(), Game::scooby->getH());
			
			// render treasure boxes
			for(int i = 0; i < 12; i++) {
				// if user presses space while colliding with a treasure box
				if(Game::scooby->isCollidingWith(*Game::treasureBoxes[i]) && keystate[SDL_SCANCODE_SPACE]) {
					if(!Game::treasureBoxes[i]->isOpened()) {
						Game::treasureBoxes[i]->open(); //open the treasure box if not already opened
						Mix_PlayChannel(-1, treasure_open,0); // play treasure box sound effect
						if(Game::treasureBoxes[i]->containsClue()) { // if box had a clue
							GameState::getInstance()->incrementCluesFound(); //increment clues found
							Mix_PlayChannel(-1, clue_found,0); // play clue found sound effect
						} else {
							Mix_PlayChannel(-1, clue_notfound,0); //play clue not found sound effect
						}
						GameState::getInstance()->decrementEnergy(); // decrement energy for opening a box
					}
				}
				//render the box
				assetManager->render(Game::treasureBoxes[i]->getAssetKey(), Game::treasureBoxes[i]->getX(), Game::treasureBoxes[i]->getY(), Game::treasureBoxes[i]->getW(), Game::treasureBoxes[i]->getH());
			}

			//if scooby collides with a snack, increment the energy and play snack sound effect
			if(Game::snack1->isCollidingWith(*Game::scooby)) {
				if(!Game::snack1->isEaten()) {
					GameState::getInstance()->incrementEnergy();
					Mix_PlayChannel(-1, scooby_snack,0);
				}
				Game::snack1->eat();
			}
			else if(Game::snack2->isCollidingWith(*Game::scooby)) {
				if(!Game::snack2->isEaten()) {
					GameState::getInstance()->incrementEnergy();
					Mix_PlayChannel(-1, scooby_snack,0);
				}
				Game::snack2->eat();
			}
			// if scooby collids with any booby trap, end the game
			else if(Game::boobyTrap1->isCollidingWith(*Game::scooby)) {
				GameState::getInstance()->forceGameOver();
			}
			else if(Game::boobyTrap2->isCollidingWith(*Game::scooby)) {
				GameState::getInstance()->forceGameOver();
			}
			
			// check if current ticks are ahead of current fear timeout
			if (SDL_TICKS_PASSED(SDL_GetTicks(), fearTimeout)) {
				GameState::getInstance()->incrementFear(); // time to drop a heart
				fearTimeout = SDL_GetTicks() + FEAR_TIMEOUT*1000; // reset the fear timeout to 4s ahead in the future again
			}
		} else {
			Mix_HaltMusic(); // stop music when game over
			if(GameState::getInstance()->gameFailed()) { // if not a win
				assetManager->render("gameover", 0, 0); // render gameover screen
				Mix_PlayChannel(-1, gamelose,0); //play lose sound effect
			} else {
				assetManager->render("gamewin", 0, 0); // render gamewin screen
				Mix_PlayChannel(-1, gamewin,0); //play win sound effect
			}
			if(keystate[SDL_SCANCODE_RETURN]) quit = true;
		}

        SDL_RenderPresent( gRenderer );
		SDL_Delay(5);
    }
}

Game::~Game() {
	SDL_DestroyRenderer( Game::gRenderer );
	SDL_DestroyWindow( Game::gWindow );
	Game::gWindow = NULL;
	Game::gRenderer = NULL;
	
	Mix_FreeMusic(bgmusic);
	Mix_FreeChunk(treasure_open);
	Mix_FreeChunk(scooby_snack);
	Mix_FreeChunk(clue_found);
	Mix_FreeChunk(clue_notfound);
	Mix_FreeChunk(scooby_scream);

	for (int i = 0; i < 12; i++){
		delete treasureBoxes[i];
		treasureBoxes[i] = nullptr;
	}
	delete [] treasureBoxes;
	treasureBoxes = nullptr;
    
	bgmusic = NULL;
    treasure_open = NULL;
    scooby_snack= NULL;
    clue_found = NULL;
    clue_notfound = NULL;
    scooby_scream = NULL;
    
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}