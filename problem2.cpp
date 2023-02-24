#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <set>
#include <atomic>
#include <mutex>
#include <random>
#include <algorithm>
using namespace std;

// Problem 2: Minotaur’s Crystal Vase
// Approach 3: Queue in a line

int main(void)
{
  // Change n to change number of guests
  const int n = 100;

  // Probability of requeueing per roll.
  const int q_prob = 10;

  // Number of unique guest who have seen the vase so far.
  atomic<int> seen_cnt(0);

  // ID of the guest at the front and back of the queue.
  atomic<int> qfront(0), qback(0);

  // Mark guests if they have seen the at least once.
  vector<bool> seen(n);

  auto guest = [&](int gid)
  {
    // -1 = not queued
    int qid = -1;

    // Keep this thread alive until all guests have seen the vase.
    // Each iteration of this loop represents an event regarding this guest.
    while (seen_cnt <  n)
    {
      // Small delay so this loop does not trigger many times in a row.
      this_thread::sleep_for(chrono::milliseconds(20));

      // Not in queue or room
      if (qid == -1)
      {
        // Decide if we want to queue
        int roll = rand() % 100 + 1;

        if (roll <= q_prob)
          qid = qback++;

      }
      // In room
      else if (qid == qfront)
      {
        // First time seeing the vase. Update the count and mark guest as seen.
        if (!seen[gid])
        {
          seen[gid] = true;
          seen_cnt++;
        }

        // Stay in the room for some time
        this_thread::sleep_for(chrono::milliseconds(20));

        // Pop this guest from the front of the queue.
        qid = -1;

        // Increment front of the queue so the next guest can take the room.
        qfront++;
      }
    }
  };

  srand(time(0));

  vector<thread> gt(n);

  // Generate random order of spawning the guest threads
  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  shuffle(order.begin(), order.end(), default_random_engine(time(0)));

  for (int i = 0; i < n; i++)
    gt[i] = thread(guest, order[i]);

  for (int i = 0; i < n; i++)
    gt[i].join();

  cout << seen_cnt << " guests have seen the vase at least once.\n";

  return 0;
}