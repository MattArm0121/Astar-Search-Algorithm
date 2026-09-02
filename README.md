Today we decided to expand upon our search algorithms from last week. Instead of learning one on our own, we went over four AI search algorithms. This final example is of an A* search algorithm.

For our own personal work, we were to add five hotspots that would have a higher cost than the normal tiles. You can see which tiles are a hotspot as they are red. So, the program goes and searches through what is the lowest cost path to the end goal. Even if it means going through a hotspot.

In the below example, you can see one example of this. The only path forward to the goal is through a hotspot, and it tries to go around it but with no path forward it decides to go through the hotspot to reach the end goal.
<img width="1984" height="990" alt="Screenshot 2026-09-02 075243" src="https://github.com/user-attachments/assets/f6ee1408-cbd5-44c8-b008-c7ad39257e35" />

However, in the example below. There are multiple paths to go to the end. So, it actually avoids the hotspots yet finds the best path forward to reach the goal with the lowest cost as possible.
<img width="1982" height="980" alt="Screenshot 2026-09-02 075312" src="https://github.com/user-attachments/assets/cb696aa1-2fca-4bfd-a3df-a8d1f8f8ea9c" />

It was a bit tricky learning this method as I'd have to assign a cost to every tile. But in my mind it is much better than the other search methods we went over as I thought it finding the best path with the lowest cost to be smart for whenever I code video game NPC pathing. It was fun learning the concept and I'm glad I was able to add hotspots to it on my own.
