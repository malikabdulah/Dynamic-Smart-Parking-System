# Smart Parking System 🚗

A dynamic, console-based Smart Parking System built entirely in C++. This project was designed to heavily utilize raw pointers and dynamic memory allocation without relying on static arrays or C++ STL containers (like `std::vector`). 

The system maps out a parking lot using a 3-level deep dynamic structure (Blocks → Rows → Slots) and includes a geometric optimization algorithm to find the absolute closest parking spot for a user.

## ✨ Key Features
* **Fully Dynamic Layout:** The number of blocks, rows per block, and slots per row are defined at runtime.
* **Smart Parking Allocation:** Reads block $(x, y)$ coordinates from a text file and uses the Euclidean distance formula to assign users the physically closest available slot to their desired destination.
* **Dynamic Resizing:** Increase or decrease the number of slots in a specific row on the fly while the program is running, with safe memory reallocation.
* **Vehicle Management:** Park cars, remove cars, and view the entire layout in a clean console UI.
* **Search Functionality:** Search for a parked car by its registration number to get its exact Block, Row, and Slot.
* **Leak-Free Memory:** Implements rigorous multi-dimensional array teardown to ensure zero memory leaks upon exit.

## 🛠️ Concepts & Tech Stack
* **Language:** C++
* **Core Concepts:** 3D Pointers (`string***`), Dynamic Memory Allocation (`new` and `delete`), File I/O (`<fstream>`), Geometric Math (`<cmath>`).

## 🚀 How to Run
1. Clone the repository to your local machine.
2. Ensure you have a C++ compiler installed (like GCC or MSVC).
3. Create a file named `file.txt` in the same directory as the executable. The file should contain the number of blocks on the first line, followed by the $X$ and $Y$ coordinates for each block on subsequent lines. Example:
   ```text
   3
   0 0
   100 0
   50 200
