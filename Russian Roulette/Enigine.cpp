
void Engine::Initialize()
{
	running = true;
	gun.LoadGun(1, 4);
	giveItems();

	players[0] = make_shared<Player_Human>();
	players[1] = make_shared<Player_AI>();
}

// Give each player a random ammount of items.
void Engine::giveItems()
{
	// Create a random device for seeding.
	random_device rd;

	// Specify to make our device a Mersenne Twister random number engine.
	mt19937 gen(rd());

	// Setup a uniform distribution between minimum and maximum items then randomly generate a number.
	std::uniform_int_distribution<> distribution(minimumItemsPerRound, maximumItemsPerRound);
	int itemsToDistribute = distribution(gen);

	cout << "Lets spice things up... " << "Each player gets " << itemsToDistribute << " Items..." << endl;

	for (int i = 0; i < itemsToDistribute; i++)
	{
		if (items[0].size() < maxItemsAllowed)
		{
			items[0].push_back(GetRandomItem());
		}

		if (items[1].size() < maxItemsAllowed)
		{
			items[1].push_back(GetRandomItem());
		}
	}
}

void Engine::ProcessGameLogic()
{
	cout << endl;

	if (!turn)
	{
		cout << "Player 1 HP: " << players[0]->Health() << " Player 2 HP: " << players[1]->Health() << endl
			<< "What is your action?" << endl
			<< "1: Fire gun at opponent" << endl
			<< "2: Fire gun at self" << endl;

		// Print all users items.
		for (int i = 0; i < items[0].size(); i++)
		{
			cout << 3 + i << ": " << items[0].at(i)->ItemName() << " - " << items[0].at(i)->ItemExplaination() << endl;
		}

		cout << "0: Quit game" << endl;
	}

	TurnResult turnResult = players[turn]->TakeTurn(&gun);

	// Process the result of the players turn.
	switch (turnResult)
	{
	case TurnResult::noDamageSelf:
		cout << "Nothing... the player gets another turn" << endl;
		// The turn palyer gets an extra turn if the shoot themselves with a blank round.
		break;

	case TurnResult::noDamageOpponent:
		cout << "Nothing... the gun is handed to the other player..." << endl;
		turn = !turn;
		break;

	case TurnResult::damageOpponent:
		if (!turn)
		{
			cout << "BANG!... You hit the dealer!" << endl;
		}
		else
		{
			cout << "BANG!... the dealer hits you!" << endl;
		}

		players[!turn]->TakeDamage(1);

		turn = !turn;
		break;

	case TurnResult::damageSelf:
		if (!turn)
		{
			cout << "BANG!... You have hit yourself" << endl;
		}
		else
		{
			cout << "BANG!... the dealer hits himself" << endl;
		}

		players[turn]->TakeDamage(1);
		turn = !turn;
		break;

	case TurnResult::turnSkipped:
		cout << "The player spends their turn uncuffing themselves..." << endl;
		turn = !turn;
		break;

	case TurnResult::closeGame:
		running = false;
		break;
	}

	// TODO: check hp of both players and determine if there is a winner.

	// Check if gun needs to be reloaded.
	if (gun.isEmpty())
	{
		gun.LoadGun();
		giveItems();
	}
}

// Primary game loop, does initialization and shutdown as well.
void Engine::GameLoop()
{
	Initialize();

	while (running)
	{
		ProcessGameLogic();
	}
}

#endif