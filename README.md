# 04_BattleTanks
An open-world head-to-head tank fight with simple AI, terrain, and an advanced control system for unreal 4.

Using tutorials from https://www.udemy.com/unrealcourse/learn/v4/content section 4.


Technical report on the review of violent video game literature by the American Phycological Association (2015):
https://www.apa.org/pi/families/review-video-games.pdf


Over the past few days I've been working on an algorithm that changes the color of a surface in a rainbow-like pattern for a power-up item in my group's jame jam game. I got the original idea fro a turorial here (https://www.youtube.com/watch?v=3bYbFQ6Cius)and tried to improve upon it. The idea behind it was that on a color wheel, if you go around the outside edge like I was trying to emulate, one of the RGB values stays at 1, another stays at 0, and the third is a float between 0-1. The end result was:
![alt text](https://raw.githubusercontent.com/setg2002/04_BattleTanks/master/GameDevMath.PNG)
It doesn't work perfectly as the color changes in more of a triangle hitting red, green, and blue instead of every color on the outside of the wheel. It works by taking the time as an input then passing it through a sine function with a period of 1 and then assigning that value to ethier the red blue or green channel. However, 1/3 and 2/3 is added to the green and blue channel repectively in order to "delay" when they reach 1 and 0. If this delay was not present, the red, blue, green channels would not change in sequence, but would rather fade in and out from white to black. Finally it then takes the RGB value and multiplies it by a Glow Strength (in this case 100) and uses the resulting value as the emissive color to make it glow. For example, at 0 seconds the red value would be 0, the green value would be 0.3333, and the blue value would be .6666 making it a light-ish blue. At 1 second the red would be .84, green would be .17, and the blue would be .51 making a light pink.
