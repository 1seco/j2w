Jeb's worse whow(a cli calendar/todo app)

usage: ```command <repeat(o)> <start-time> <end-time(o)> title(quotes) @tag_here```
(o) meaning optional

example:
- sched ev "8:00" "9:00" "do something" @random
- todo "something" @banana
- event "4/5/6^8:15" "title here" @iWillProbablyForgetThis
- sched ev 4/5/6^8:15 6/7/8^9:30 title @tag
- sched month=6 %^4:46 % thistitle @newtag

ev su mo tu we th fr sa invalid
