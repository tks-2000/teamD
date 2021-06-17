#include "stdafx.h"
#include "Title.h"

Title::Title()
{
	
}

Title::~Title()
{

}

bool Title::Start()
{
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<Game>(0, "Game");
	}
}