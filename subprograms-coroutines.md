## What's News

A large private-equity investor has agreed to purchase the Subprogram fast-food chain from its founders, Developer Associates,for almost $10 billion. The new owner wants to add 23,000 restaurant's to the chain's 37,000 existing locations.

## Coroutines

Just when you thought that you were getting the hang of subprograms, a new kid steps on the block: coroutines. Sebesta defines _coroutines_ as a subprogram that cooperates with a caller. The first time that a programmer uses a coroutine, they _call_ it at which point program execution is transferred to the statements of the coroutine. The coroutine executes until it _yields_ control. The coroutine may yield control back to its caller or to another coroutine. When the coroutine yields control, it does not cease to exist -- it simply goes dormant. When the coroutine is again invoked -- _resumed_ -- the coroutine begins executing where it previously yielded. In other words, coroutines have

1.  multiple entry points
2.  full control over execution until they yield
3.  the property that only one is active at a time (although many may be dormant)

Coroutines could be used to write a card game. 

We could architecture such a game using coroutines by giving each player a coroutine. That coroutine knows about the player to their left (that is, another coroutine). The `PlayerA` coroutine performs their actions (perhaps drawing a card from the deck, etc) and checks to see if they won. If they did not win, then the `PlayerA` coroutine yields to the `PlayerB` coroutine who performs the same set of actions. This process continues until a player no longer has someone to their left. At that point, everything unwinds back to the point where `PlayerA` was last resumed -- the signal that a round is complete. The process continues by resuming `PlayerA` to start another round of the game. Because each player is a coroutine, it never ceases to exist and, therefore, retains information about previous draws from the deck. When a player finally wins, the process completes. To see this in code, check out [https://github.com/hawkinsw/cs3003/blob/main/subprograms/cardgame.py](https://github.com/hawkinsw/cs3003/blob/main/subprograms/cardgame.py).

Can you see anything similar between objects in an object-oriented programming language and coroutines? Both can store information (state) private to themselves and separate from others (as local variables in the coroutine and member variables in the object) as long as they are in existence. Both can be assigned to variables and moved -- maybe they really aren't all that different at all!