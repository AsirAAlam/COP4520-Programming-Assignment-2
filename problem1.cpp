#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <atomic>
#include <time.h>
using namespace std;

// Problem 1: Minotaur’s Birthday Party

int main(void)
{
  const int n = 100;
  vector<bool> in_laby(n), vis(n);
  mutex m;
  atomic<int> cake(1);
  int cnt = 0;
  srand(time(0));

  auto guest = [&](int gi)
  {
    // Counter guest
    if (gi == 0)
    {
      // If there is no cake, a regular guest was here.
      // Increment counter and bring another cake.
      if (cake == 0)
      {
        cake = 1;
        cnt++;
      }
      // If it's the counter guest's first time, increment counter.
      if (!vis[0])
      {
        cnt++;
        vis[0] = 1;
      }
    }
    // Regular guest
    else
    {
      // If it's this guest's first time here and there is a cake,
      // eat the cake to let the counter guest know.
      if (!vis[gi] && cake == 1)
      {
        vis[gi] = 1;
        cake = 0;
      }
    }

    // Mark guest as not in the labyrinth
    m.lock();
    in_laby[gi] = 0;
    m.unlock();
  };

  while (cnt < n)
  {
    // Choose a random guest to send into the maze.
    int gi = rand() % n;

    // If a regular guest has already visited the labyrinth, spawning the thread again
    // won't make a difference.
    if (gi != 0 && vis[gi]) continue;

    // If the guest is already in the labyrinth, do not spawn.
    if (in_laby[gi])
      continue;
    
    // Mark guest as in labyrinth
    m.lock();
    in_laby[gi] = 1;
    m.unlock();

    // Spawn thread
    thread t(guest, gi);
    t.detach();
  }
  cout << n << " guests have entered the labyrinth at least once.\n";

  return 0;
}
