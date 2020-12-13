# Feedback

SCRUM Master: Mark Montes

Group:

* Ben Lostheart
* Steven Van
* Jerry Smedley

***

# Video Notes

Very nice video demo and nice teamwork over all. All requirements met.

Glad that you guys were able to accomplish as much as you did as fast as you did with only 4 of you.

A good thing to keep in mind for future projects is constant integration. This means constantly testing **THEN** merging your new code into a working branch *(main/master)* so you avoid working with stale code and creating git conflicts. It also helps avoid creating incompatible code, *(which sometime introduces new bugs)* and allows for more rapid integration testing.

One thing that I had wished I introduced much earlier was priority tags (high, med, low priority) and sorting your kanban board accordingly. This is what can allow everyone to work on the important bits of the product first, while not necessarily making anyone wait around on other things. It also ensures that you have a minimum viable product faster, since more critical things must be done first, ergo some form of a product, even if primitive and a bit buggy, is demo-able sooner than later. Please do feel free to take that insight with you next time you find your self in an agile team.

***

# Gameplay Notes

Near all core features are present. One small oversight: no `q` hotkey to exit the game gracefully.

A few minor bugs:

* Game segfaults after selecting an "incorrect tool" then moving onto the obstacle
* Game asks to choose a tool, if inventory is empty, any selection causes the game to segfault
* A 'Y' character always appears before the clue info line, seems to be a curses draw bug

All requirements met.
