
# FizzBuzz  in Assembly Language

Fizzbuzz is a well known programing challenge. The challenge involves the following:
1) Create a program that print numbers from 1 to 100
2) If the number is divisible by 3 we print "FIZZ"
3) If the number is divisible by 5 we print "BUZZ"
3) If the number is divisible by 3 and 5 we print "FIZZBUZZ"

#### *Simple right? ...*

This project was a MAJOR challenge to make! From the ... TODO, to the many problems I encountered in my jorney. Here is my finished prototype running on [marie.js.org](marie.js.org). Take a look!

![finished_result](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/c4a66575-c57d-4ee4-97ef-7ae30ff6568b)


Buckle your seat belts folks, lets dive into the details

# Architecture

As the title suggest, I wont be using *python*, *java*, or any other *high level language* for this project. I have willingly accepted the challenge to program this in Assembly Language.

### MARIE

MARIE stands for ('*Machine Architecture that is Really Intuitive and Easy*'), and is the machine architecture that I will be working with.

[Click here to view the MARIE website and online assembler](https://marie.js.org/)

Here is a bird-eye view of the Computer Arcitecture I am working with

![ComputerImage](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/20a9bf71-ac14-48c0-9ed4-5c275a8ba1ca)

Allow me explain what we are seeing here!

### Registers
Registers are quick & easy temporary store imbedded into the CPU (*Centeral Processing Unit*).

MARIE assembly is designed to be as simple as possible. It has a total of 7 registers! 

 - Accumilator             ( **AC** )
    - 
    Used for just about anything. I will be working directly with this one
 
 
 ### Fetch - Decode - Execute specifc Registers
 - Program Counter         ( **PC** )
    -
    Keep track of our current instruction ( or Line # )
 
 - Memory Access Register  ( **MAR** )
    -
    Where to fetch data and instruction in memory
 
 - Memory Buffer Register  ( **MBR** )
    -
    Store the fetched data
 - Instruction   Register  ( **IR** )
    -
    Holds our current instruction constiting of [ OPTCODE ] and [ OPERAND ]
        
 ### I/O specific Registers

 - Input   Register  ( **InREG** )
    -
    Handles program's inputs
 
 - Output   Register  ( **OutREG** )
    -
    Handles program's outputs

I will be working directly with the Accumilator to handle arethmatic operations, controll flow, and writting to memory.

In addition to this, I will be utilizing the Output register to write to the Terminal/Output using UTF 16BE Unicode.

![ascii](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/dd126b02-6ebc-47a6-9094-d62c8b1022db)


In otherwords, Certain values correspond **->** to a Symbol. This is great as I want the output to be readable and not hex or binary!
    
*Last thing I want to mention here:* 
Registers specific to the ***Fetch - Decode - Execute Cycle*** are cruitial for the CPU. Without these, the CPU woudnt even know where to begin excetuting, let alone - understand the instructions we give it!


### Architecture Specifics

the MARIE architecture is mostly based off of ***Accumilator Architecture***. All of the operations are given and utilized by the Accumilator. 

``` Assembly 
/ Accumilator = Acumilator + 1
Add ONE 

/ Accumilator = Acumilator - 2
Subt TWO
```

All instructions assume to include the Accumilator.
This provides short and simple instructions, with the cost of increased overall BUS memory traffic.

The Marie Instruction Set has no general purpose registers, infact it can be classified as a ***One Adress Instruction Set Architecture***.

This means that each instruction uses at most - **1 operand**. As we saw above, the accumilator is implicitly used by each instruction.

**Note**: not all instructions need an operand

``` Assembly 
/ ONE is the operand
/ Add is the optcode
Add ONE 

/ No operand, only optcode.
HALT
```

### More ISA Specifics

the MARIE Instruction Set Architecture ( **ISA** ) uses a fixed word length of 16 bits or 2 bytes.


<INSERT OPTCODE OPERAND PHOTO 16 BITS TOTAL>

<INSERT OPTCODE WITH NO OPERAND, WASTING SPACE>

As a consequence, the overall excecution and decoding process more efficient with the cost of wasting memory space.

Data representation is done using Signed 2's Compliment. With this we are able to represent both positive and negative numbers.

![u_int_range](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/487267b9-264b-4d46-9b50-a0c2e97d8363)

This is by far the most common representation used by computers today, including the MARIE computer.


To finalize, the MARIE computer supports a range of 4KB of word-adressable memory. The [marie.js.org](https://marie.js.org/) website provides a nice and nifty - ***Real Time*** - view of the computers memory being acessed. Take a look. 

![hex dump](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/271f8e2b-bf66-4633-a649-899f3d0c40d6)

here are the data / adress busses transmiting data in real time. pretty cool if you ask me


![fast](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/78ae4294-d500-479c-ac83-37f88fab3fa1)

Here it is slowed down x500

![slow](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/ffd25806-5cd9-4cba-9679-461a4185833d)


### Things left out
For simplistic reasons, MARIE doesent support catche memory, Interrupts, Flags,  ... ect. 




# FIZZBUZZ behind the scenes!

Lets look back at the Rules for the FIZZBUZZ challenge:

1) Create a program that print numbers from 1 to 100
2) If the number is divisible by 3 we print "FIZZ"
3) If the number is divisible by 5 we print "BUZZ"
3) If the number is divisible by 3 and 5 we print "FIZZBUZZ"


#### From the prompt, I was able to devise this plan:

Im going to need to 
 - Store values as variables
 - Iterate from 1 to 100
 - Test numbers for divisibility
 - Branch and use Controll Flow
 - Print numbers on the screen

 #### *Simple right? ...*

## Problems and complications galore

Inorder to test for divisibility, we commonly use modular division and test for a remainder of 0. Like this:

Using python
```python
if (n % 3 == 0):
    print("divisible")
```
Using C
```c
if (n % 3 == 0)
    printf("%s", "divisible");
```

The problem is that MARIE Instruction Set doesent include any modular division operator ( % ) let alone instructions. And its not just modular division, no multiplication nor division instructions are provided.

To add to this, their is no for() loop, nor is their if() else() statements.


```c
// Example in C
for (int n = 0; n <= 100; n++)
    printf("%u", n);
```

nor is their any if - else statements

```c
if (n == 1)
   // do something
else
{
   // do something else
}
```

I can assure you that this Project ***for sure*** put my Problem Solving skills on overdrive... oh my, well atleast printing to the OUTPUT *should* be simple....

*Note*:
From here on, I will be using the *C language* for my examples, as it closeley resembles the CPU instructions behind it ( *to a fair extent* ).

## Familiarity
### Starting with - Variables
In MARIE assembly, variables can be represented as values stored at a given adress.
I can store variables in decimal ( **DEC** ), hexadecimal ( **HEX** ), and a few others

``` Assembly
my_var,  DEC 10   

VARIABLE,  HEX FF        / I like to capitalize variables  
```

Seting values to variables is as follows:
``` Assembly
/ VARIABLE = Accumilator
Store VARIABLE
```

### Branching and Controll Flow


This is not bad, but looking into branching instructions had me perplexed. The Instruction set had no If - Else statements, instead, I was met with a "*Skip If*" instruction. It allowed the program to incriment the Program counter ( ***PC*** ) twice if the accumilator satisfied a condition.

 Now I was used to having 'x' instructions executed if the statement was true.

And having only 1 line to skip, it seemed like I needed to fit my code in 1 line ( *just my thought process* )

I learned that the skip instructions translated into this

```c
n = 5;
if (!(n < 0))           // skip if (n < 0)
   printf("n is >= 0");

printf("always executed");
```
I was detinitley not used to this logic, i felt that I was back to my Programing 1 class. Keep a note on this part,

### Iteration

Looking into possible Iteration instructions, I found that MARIE assembly - and practically any other Assembly Language - has JUMP instructions.


``` Assembly
/ X is the adress to jump to 
Jump X 

/ jump to adress 12 (line 12)
Jump 12 
```

I realized that the JUMP instruction closeley resembles the ***goto*** keyword in C and C++.

```c
n = 1;
++n;
goto 2;  // jump back to ++n (line 2)

```
or with labels
```c
loop:
   ++n;
   goto loop;  // jump back to label (loop)

```

Thus, I was quickly able to impliment the concept of Iteration in assembly. You can check out my test trials under
`Iterating/Iterations.mas` and `Iterating/Iterations.c`. 
 I simply made a program to add numbers 100 to 1 together. Here's a quick glance

note: MARIE allows for labels, you can see it as: ***LOOP,*** and ***LOOP_FINISH,***  
``` Assembly
LOOP,	LOAD I 
         Skipcond 800	/ If I > 0, continue,
         JUMP LOOP_FINISH
         ADD SUM        / Add to the sum
         STORE SUM		/ and store it
         LOAD I
         Subt ONE       / Decrement I by 1
         Store I
         JUMP LOOP      
		
LOOP_FINISH,   LOAD SUM	/ Print the sum
               OUTPUT
               HALT		/ End the program

```
in C

```c
   unsigned int SUM = 0;
   unsigned int i   = 100;

   for (; i > 0; i--)
   {
      SUM += i;
   }

   printf("%u", SUM);
```
### Tying it together

From here, I realized something quite interesting. Skipping is more efficient than If's and Else's

You can see this here when I managed to translate branching in C into MARIE assembly.

**Skipping example:**
```c
   if (!(n == 0))
      printf("not zero")
```
``` Assembly
   Skipcond 400    / if (AC != 0)
   Output
```
this example is good if are only executing 1 line like invoking a method or halting the program.

**IF - ELSE example:**
```c
   if (n == 0)
      printf("zero")
```
``` Assembly
   Skipcond 400    / if (AC != 0)
   Jump END_CURLY_BRACE
   
   Output

END_CURLY_BRACE, 
```



This was great, not only was I sucessfully able to translate assembly into logic Into logic I am familiar with, but I unlocked a new way of branching - ***Skipping***.

Note: I wont go into functions and methods as I want to cover my learning expirience and problem solving. However, a quick tutorial on it already exists, you can find it [here](https://github.com/MARIE-js/MARIE.js/wiki/Subroutines). 

## Convenient Solutions

At this point, I was starting to get familiar with the instruction set, and to be fair it is made to be as simple as possible :). 

Looking back at the FIZZBUZZ challenge,

These are the concepts I have to impliment

 - S̶t̶o̶r̶e̶ v̶a̶l̶u̶e̶s̶ a̶s̶ v̶a̶r̶i̶a̶b̶l̶e̶s̶
 - I̶t̶e̶r̶a̶t̶e̶ f̶r̶o̶m̶ 1̶ t̶o̶ 1̶0̶0̶
 - Test numbers for divisibility
 - B̶r̶a̶n̶c̶h̶ a̶n̶d̶ u̶s̶e̶ C̶o̶n̶t̶r̶o̶l̶l̶ F̶l̶o̶w̶
 - Print numbers on the screen

 I have 3 out of 5 concepts! Lets move on!

### Division


If you think about it - Division is just repeated subtraction.

More specifically I can describe Division as: start with a number (Dividend) and subtract it by the Divisor over and over again untill the number turns negative.

<INSERT SVG OF SUBTRACTION>

Our Quotient ( or answer ) is simply the amount of times  this subtraction takes place. We can incriment Quotient at every iteration.

Take a look at my implimentation!

```Assembly
/ Division is implimented as repeated subtraction
/ untill ACCUMILATOR is negative

DIVISION,	DEC 0 				/ return adress stored here
			
            
LOOP,		Store TEMP			/ store value of ACCUMILATOR
            Load QUOTIENT		
            Add ONE				/ incriment QUOTIENT
            Store QUOTIENT
           
/ subtraction
            Load TEMP
            Subt DIVISOR
            
            Skipcond 000		/ return if TEMP < 0
            Jump LOOP			/ repeat

            JumpI DIVISION		/ return
```
In C
```c
void Division()
{   // invisible return address here

    TEMP = AC;

    loop:
        ++Quotient;

        TEMP -= Divisor;       // subtract
        AC    = TEMP   ;
        if ( AC < 0 ) return;
        goto loop;             // repeat
}
```

### Modular Division

Modular division is acually simpler and requires less steps that Division!

<INSERT SVG OF MOD_DIVISION>


 The difference here is that we dont need a Quotient.  Instead we simply store the value of the Accumilator - into REMAINDER - before every subtraction. Once Accumilator is negative, we return.

```Assembly
/ Modular Division is implimented as repeated subtraction
/ untill ACCUMILATOR is negative
/ #returns value of AC before it dips below 0

MODULAR_DIV,DEC 0 				/ return adress stored here
			
LOOP,		Store REMAINDER		/ store value of ACCUMILATOR

/ subtraction
            Subt DIVISOR
            
            Skipcond 000		/ return if ACCUMILATOR < 0
            Jump LOOP			/ repeat

			JumpI MODULAR_DIV	/ return

```
In C
```c
void Modular_Division()
{   // invisible return adress here

    loop:
        Remainder = AC;

        AC   -= Divisor;       // subtract
        if ( AC < 0 ) return;
        goto loop;             // repeat
}
```

You can check out my test trials for division under
`Division_Examples/u_int_division.mas` and `Division_Examples/u_int_division.c`. 


and for modular division under
`Division_Examples/u_int_modular_division.mas` and `Division_Examples/u_int_modular_division.c`. 

### Take a break :)
   Sweet! At this point, I am finally able to iterate, loop around, branch off, divide and find the remainder of two numbers!

 - S̶t̶o̶r̶e̶ v̶a̶l̶u̶e̶s̶ a̶s̶ v̶a̶r̶i̶a̶b̶l̶e̶s̶
 - I̶t̶e̶r̶a̶t̶e̶ f̶r̶o̶m̶ 1̶ t̶o̶ 1̶0̶0̶
 - T̶e̶s̶t̶ n̶u̶m̶b̶e̶r̶s̶ f̶o̶r̶ d̶i̶v̶i̶s̶i̶b̶i̶l̶i̶t̶y̶
 - B̶r̶a̶n̶c̶h̶ a̶n̶d̶ u̶s̶e̶ C̶o̶n̶t̶r̶o̶l̶l̶ F̶l̶o̶w̶
 - Print numbers on the screen

 One more concept to go!

 ### Printing Numbers 

 This is how you print numbers in python
 ```python
 print(5)
 ```
 
 this is probobaly the first thing programmers learn to do when they get into software developement. Ironically, For me learning assembly language, this was the absolute last thing i learned to do...

 MARIE Assembly uses the OUTPUT instruction
 ```Assembly
 Output
 ```
Very cool,
 Look what I get when I print out the number 1 ( stored in the accumilator )

 `  `

 here I print out the number 58

`;`

 here I print out the number 76

`L`

 here I print out the number 190

`¥`

 here I print out the number 209

`Ð`

but when I print out the number 48 i get

`0`  zero!

number 49 is
`1`

number 50 is
`2`

number 51 is
`3`
and so on....


This is because for my program's OUTPUT, I am using UNICODE UTF 16BE. Behind the scenes, MARIE is mapping the integer value to a symbol/letter on the ASCII table. ( In theory this is great because who wants the output to be in binary or hexadecimal??? )

When I realized this, I realized I hit a wall. Cement Wall.
Lets take a look at the ASCII table again

![ascii](https://github.com/seoProductions/FizzBuzz-In-Assembly-Language/assets/111206081/165d6dac-bc39-4299-9e76-e81e9ebbb8df)


 The Ascii table only has numbers 0 - 9  Meaning If want to print out an integer like we can in *python* and *C*, I would manualy have to go through each digit and print it. I needed an algorithm for this!

 ### My solution and Algorithm

 My aproach was to utilize my division and modular division instructions to isolate the digits of an integer. I made a cool animation to visualize it.

 <SVG OF ALGORITHM>


 This was by far the hardest thing I had attempted in low - level programing. I spent an ***entire day*** debugging it, but it is finished and working!

 You can find the algorithm under `print_n/print_Count.mas` and for the translation:  `print_n/print_Count.c` for a more readable expirience
## Reflection

Looking back at my project, I felt that I had grown 🌱 considerably. This expirience as a whole has made me a better programmer. I now take better desisions 🧠 when writing code, weather it be efficiency wise, and or architecture wise. I do not regret going through this jorney of a project! I do not regret the suffering 😊. I am glad I pushed through and I can now look back and reflect...
## Q&A

#### Why MARIE Assembly

I have been working closeley with the MARIE computer and its architecture in my programming classes this semester. I wanted to put my skills to the test, and apply what I was learning. This is simply my best way to learn, and 100% learned way more than I needed on my exams.

#### What about x86, ARM64, or other assembly languages?

We all start somewhere. I began programing on scratch ( yes the one with the cat ) close to a decade ago. From there, I leveled up to python, then java, ect... I know x86 and those similar languages are HUGE. I chose to focus more on the complexity of the computer than the complexity of the language. Now having made this program, I have got very comfortorable with MARIE assembly, and I even felt the limitations of its simplicity. For the scope of this project, I think MARIE assembly is a good choice.

Its all about that Growth Mindset!

#### How long did this take?

a week... or two..

#### What is in the /Other/ Folder?

Glad you noticed. I was messing around with the 16x16 display and I managed to get a pixel drawing on screen! Thank god for higher level languages!!!



#### Hows the weather like in houston?

It okay, and it could be worse, our summers last from April **->** November, but I still love my city and I am happy citizen here.

#### YO! is the Read.me so loong

I simply had a great list of things to get off my chest and explain! Funny enough this project acually helped me be more organized and detailed in my explanations. Apologies if its too much text, code, or white space. Feel free to skim through and read some topics of your interest! 

I figured a Table Of Contents with link's could help, any one know how to impliment that? Please let me know


#### I have another question!!

Feel free to reach out to me through my email or LinkedIn: 
- [duque.eliseo.7@gmail.com](duque.eliseo.7@gmail.com)
- [LinkedIn](https://www.linkedin.com/in/eliseo-duque)
I dont bite :)
## Related

A cool simulation/demo using c++. Got to work on some more lower level concepts along the way!

[Sand-Demo in C++](https://github.com/seoProductions/Sand-Demo)


## Authors

[@seoProductions](https://github.com/seoProductions)


## License
[MIT](https://choosealicense.com/licenses/mit/)
##   Sources

[MARIE-js Github Page](https://github.com/MARIE-js/MARIE.js/wiki/Introduction-to-MARIE)

[Ascii Table](https://www.johndcook.com/blog/2022/05/28/how-to-memorize-the-ascii-table/)
