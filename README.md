# ChineseAnimalChess
After learning c++ and Qt , I wrote this project to strengthen my programing skill.

This chess game is a popular(maybe) children game in China, and the rule is as follows:

* The board of the Animal Chess

  The arena chess board has seven horizontal columns and nine vertical rows, and the chess pieces are placed in a grid. On both sides, there are three traps and one animal den  on each side. There are two areas of water in the middle of Chess and Cards, which are called small rivers.

* Pawns in Animal Chess

  There are 16 chess pieces in the arena chess, divided into red and blue. Both sides have eight pieces of the same chess (hereinafter referred to as: beast or animal). According to the strength of the fighting force, they are arranged as follows: elephant>lion>tiger>leopard>wolf> dog>cat>mouse.

* How to move the pawns

  At the beginning of the game, the red side moves first, and then takes turns. You can walk one beast at a time, and each beast walks one square at a time. Except for your own beast den and the small river, you can move around. However, the lion, tiger, and rat also have different ways of walking:

  Lion and Tiger Jumping into the River: When the liger is at the side of the river, it can jump across the river vertically and horizontally, and can eat the smaller beasts on the other side of the river, but if the other mouse is in the river, block the jumping route You can’t jump. If the other side is a beast that is stronger than yourself, you can’t jump over the river;

  Mouse swimming across the river: The mouse is the only beast that can walk into the river. The walking method is the same as that on land. You can walk one square at a time, up and down, left and right. Moreover, other beasts on the land cannot eat the rats in the river. Rats in the middle can't eat elephants on land, and rats eat each other without being affected by the river.

* How to eat the pawns

  Animal Chess eating methods are divided into ordinary eating methods and special eating methods. The ordinary eating method is based on the strength of the beast's fighting power, and the strong can eat the weak.

  The special eating method is as follows:

  1. The method of eating elephants by rats: In addition to the order of the eight beasts' fighting power, rats can eat elephants, but elephants cannot eat rats.

  2. How to eat each other: When the same kind meets, they can eat each other.

  3. Trap: A trap is set on the chessboard to limit the fighting power of the enemy beast (your own beast is not restricted). When the enemy beast enters the trap, it loses its fighting power. Any beast on the side can eat the beast in the trap. . No beast can enter its own trap.

  Integrating ordinary eating methods and special eating methods, this method of Animal Chess is summarized as follows:

  mice can eat mice and elephants;

  Cats can eat cats and mice;

  Dogs can eat dogs, cats, mice;

  Wolves can eat wolves, dogs, cats, and mice;

  Leopards can eat leopards, wolves, dogs, cats, and mice;

  Tigers can eat tigers, leopards, wolves, dogs, cats, and mice;

  Lions can eat lions, tigers, leopards, wolves, dogs, cats, and mice;

  Elephants can eat elephants, lions, tigers, leopards, wolves, dogs, cats;

* Judgment of Animal Chess

1. The beast of either side is considered to be a victory if it enters the enemy's den (your own beast cannot enter its own den);

2. Either side of the beast will lose even if it is eaten up, and the other side will win;

3. When all the living beasts on either side are trapped by the other side and cannot move, even if they lose, the other side wins;

4. In 100 consecutive rounds, neither side has an animal eaten, and both sides draw the game	 

P.S. these rules are translated by https://translate.google.cn, maybe hard to read.

  

