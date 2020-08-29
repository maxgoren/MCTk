namespace mctk {
class GameEngine {
private:
    //GameBoard
     mctk::board blanklayout;        
     mctk::zone base;                     
     mctk::bfDungeon* dg;
     mctk::compMaze* cmz;
     mctk::djMapper* dj;
     //Characters
     mctk::ent* g;
     mctk::ent* notg;
     //Game State
     bool playerTurn;
     bool aiTurn;
     bool showingDmap;
public:
     void mainLoop();
     void updateGame();
     void handleInput();
     void handleAI();
     void rendering();
     GameEngine();
};
}