Led cube for arduino Due with Mux Shield II from Mayhew labs

============================================================
This is my first Github repo.

I'm still learning how to program, that is why you'll see some inefficient coding from now and then.
I'm trying to make a sketch which will iterate over the ground layers fast enough to create a POV
effect. The led cube is made by following chr's instructable on how to build one.
(http://www.instructables.com/id/Led-Cube-8x8x8/)

Because the controller board failed, as many people experienced, I wanted to make it work my way.
I chose an Arduino Due with a MuxShield II to get the IO requirements. 

required libraries are:
DueTimer
MuxShield

To get the code running fast enough
I needed to make use of interrupts, these are handled different on a Due.
Luckily there exist an easy to use Timer library for the Due
https://github.com/ivanseidel/DueTimer 

I'm still struggeling to get some functions working to show some actual animations.

