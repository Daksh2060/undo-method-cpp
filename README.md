# String List Undo Method
This C++ project implements a dynamic array class called Stringlist, which allows you to create and manipulate an array of strings. The focus of the project is a special method of the Stringlist class called `undo` which allows the user to undo operations conducted on the Stringlist array. This allows users to dynamically manipulate a list of strings, such as adding, removing, copying, and shifting strings, and undoing these operations as they see fit.

## Features

- **Insertion and Deletion:** Stringlist allows the insertion of a string at any position within the array, via `insert_front`, `insert_back`, `insert_before`, and `insert_after`. Likewise, can also delete a specific string with `remove_first`, remove at a specific index with `remove_at`, or empty the string list with `remove_all`.

- **Assignment:** Can use the custom assignment class operator `=` to set a string list equal to another, as well as copying the undo sequence. (For more detail see code comments)

- **Searching:** Can also find the index of a specific word within the array using `index_of`, or verify the existence of a specific string in the list using `contains`.

- **Undo:** The `undo` method allows a user to undo their last manipulation to the string list. The method keeps track of all actions done on a string list in a sibling stack, allowing the user to undo every action even after several manipulations. It's essentially a `CTRL + Z` that you can use dynamically in running programs.

## How does it work?

The `undo` method works by using a set of counter operations in response to every action. Every time something is done to the string list, a private stack takes note of what action was done using a series of keywords. When `undo` is called, the stack is popped, and the corresponding keyword is associated with an inverse operation that cancels out that action. For example, if an item is added to the back of the list, the stack notes the key phrase `UNDO_INSERT_BACK`, and when undo is called, this keyphrase is read and the string list removes the last item. This applies to all non-idempotent operations available. 

## Installation and Use

Follow these steps to set up and run Stringlist in C++:

1. Clone the repository to your local machine:

   ```bash
   git clone 
   ```

2. 

   ```bash
   make
   ```

## Contact

Feel free to reach out if you have any questions, suggestions, or feedback:

- **Email:** dpa45@sfu.ca
- **LinkedIn:** [@Daksh Patel](https://www.linkedin.com/in/daksh-patel-956622290/)