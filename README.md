# COP3530 - Group 16 Project 3
This project is an interactive table built with the [Qt framework](https://www.qt.io/product/framework) using data parsed from a [Kaggle](https://www.kaggle.com/datasets/kasumil5x/howlongtobeat-games-completion-times) dataset focusing on the average completion rate of numerous video games as well as their platforms, publishers, and release dates. 

## Running the Program
Unzip the latest release and run the exe in the folder. 

## How to Use Program
This table contains a few functionalities:
### Search Bar
- Enter your search query into the bar and press enter to see results. If there are no results, the table will display *empty*.
### Toggle Search Type
- This button will change the search algorithm between a *Prefix Tree* and a *Skip List*. By default, it is set to search using a *Prefix Tree*.
### Reset Table
- This will clear the table view to its default state (alphabetical by title).
### Filter by Column
- You can click on any of the columns in the table to filter by Ascending or Descending order using a standard alphanumerical ordering.

## Sources and References
- https://www.cs.emory.edu/~cheung/Courses/253/Syllabus/Text/trie01.html
- https://www.qt.io/product/framework
- https://doc.qt.io/
- https://opendsa-server.cs.vt.edu/OpenDSA/Books/CS3/html/SkipList.html
- https://www.kaggle.com/datasets/kasumil5x/howlongtobeat-games-completion-times