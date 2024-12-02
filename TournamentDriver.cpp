#include "GameEngine.h"

void testTournament() {
    Observer* o = new LogObserver();
    GameEngine gm = GameEngine(o);
    gm.tournamentPhase();
    delete o;
}