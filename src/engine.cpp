
using namespace std;
GameEngine::GameEngine()
{
     //Setup Laout and Zone info
     mctk::board blanklayout = board(80, 40);         
     base = blanklayout.getZone();
     //Setup dungeon generator                        
     cmz = new compMaze(base);
     cmz->start();
     base = cmz->getZone();
     dg = new bfDungeon(base);
    // dg->plantSeeds(25, 5); //60 seeds for 5x5 rooms.
     //base = dg->getZone();
     //Dijkstra Mapping
     dj = new djMapper(base);
    //Characters (player & NPC)
    g = new ent(15,10,666,'@');
    notg = new ent(25,25, 717,'B');

    //Game state
    playerTurn = true;
    aiTurn = false;
    showingDmap = false;  
}


void GameEngine::mainLoop()
{
  cout<<"Game loop.\n";
  while (true)
  {
    terminal_clear();
  /************************************/  
    if (terminal_has_input())
    {
       handleInput();
    }
    updateGame();    
    handleAI();
    rendering();
  /*************************************/   
    terminal_refresh();                     
  }
}

void GameEngine::handleInput()
{
  int k;
  if (playerTurn == true)
    {
    k = terminal_read();
    switch (k)
    {
      case TK_UP: g->move(base.layout,0,-1); break;
      case TK_DOWN: g->move(base.layout,0,1); break;
      case TK_LEFT: g->move(base.layout,-1,0); break;
      case TK_RIGHT: g->move(base.layout,1, 0); break;
      case TK_1: showingDmap = !showingDmap; break;
      case TK_Q: terminal_close(); exit(0); break;
      default: break;
    }
      playerTurn = false;
      aiTurn = true;
    }
}

void GameEngine::updateGame()
{
  base.layout = dj->setMapValue(base.layout, g->pos, base.mapW*base.mapH);
}

void GameEngine::handleAI()
{
   if (aiTurn == true)
   {
       notg->automove(base.layout);
       aiTurn = false;
       playerTurn = true;
   }
}

void GameEngine::rendering()
{
    mctk::render(base, showingDmap);  
    notg->render();
    g->render(); 
}