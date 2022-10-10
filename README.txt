to compile code: gcc adventure.c items.c rooms.c avatar.c -g -o adventure

code for main function is in adventure.c, prompting user for commands and setting board up
for use by the player. The location of the rooms and connections between rooms are set up in rooms.c, and a pointer to the randomized array of room structs.

add_item and drop_item are in items.c, where user passes in an item they want to drop from or add to a specific linked list of items. items.c also
contains a function which generates an array of struct Item* using malloc, giving a name to each of these items. 

adventure.c contains all of the algorithms for if the user types in any command such as "take", "drop", "go", etc. To find each command,
use control f and type in the command surrounded by quotations to find the code for the specific command. Commands are ordered according
to the clue documentation as well