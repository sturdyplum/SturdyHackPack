/*
For nims game: get the size of the stacks and then find the ^ of all of the numbers (N1 ^ N2 ^ N3 ...) if 0 then one person wins else another wins.

int n;cin >> n;while(n--){int t, g = 0; cin >> t;while(t--){int a; cin >> a; g ^= a;}cout << (g?"First\n":"Second\n");}

In misere nim (you want to be the last one) you just have to add a special case for when all stacks are size 1

For grundy numbers the requirements are:
The games are sequential. The players take turns one after the other, and there is no passing
The games are impartial. Given a state of the game, the set of available moves does not depend on whether you are player 1 or player 2.
Both players have perfect information about the game. There is no secrecy involved
The games are guaranteed to end in a finite number of moves.
In the end, the player unable to make a move loses. There are no draws. (This is known as a normal game. If on the other hand the last player to move loses, it is called a misère game)


When there are no moves aka the game is lost then the grundy number is zero. Otherwise the grundy number for i is the lowest grundy number which it cannot reach in its next move.

So if g1 can move to 0 and 1 then its number is 2
If g2 can move to g1  and 5 its number is 3 
If g3 can move to  g2 its number is 4
*/
