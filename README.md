SmartHistos
===========

SmartHistos is a tool that let you use ROOT histograms (TH1 and TH2) in a simpler way 
when using them in some analysis code.
Usually you need to declare the histograms and then you use them. When doing an analysis this
can get a little heavy since usually much more than 100 histograms need to be declared.
This implies a declaration of each one of them and a way to point to each one for the later 
use.

SmartHistos is a tool that has embeded a standard map of histograms. 
This makes the task easier in the sense that when you want to fill a give histogram you can refer
to it with a key that in this case is a string. This key is very descriptive since it is the name
of the histogram.
The power of SmartHistos comes when then operation to add a new value to a given histogram and its
initialization are done in the same line.

Example:
Imagin you have an histogram with the mass of particle a. You first declare the histogram and then
you start to fill it:

TH1 *a = new TH1("a_M","Mass of particle a",20,0,1000);
...
a->Fill(a.M(),weight);

This is equivalent to use Smarthistos doing:

histos->Fill(a.M(),weight,20,0,1000,"a_M","Mass of particle a");

Where histos is a SmartHistos object. While you need a declaration and a Fill call for each histograms
with SmartHistos you just to create one single object and perforns as any Fills as you want. As far
as you change the name of the histogram, in this case "a_M" it will be treated as a different one. 
The first time it is called it will be generated and the next times it will be filled only since it 
already exists.

This opens plenty of possibilities when creating pretty similar histograms. You can change the name 
into a loop and everytim the line with the fill is called a new histogram will be generated and filled.

Give it a try!
