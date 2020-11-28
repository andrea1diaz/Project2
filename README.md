# Project 2 - Data Bases II

In this project we implemented a secondary memory index for book reviews and a UI for searching the words and retrival of the documents.

## Document processing 
We first process the documents by basing our secondary memory managment in Block Sort with an Onverted index for the words and block ids, every block is saved in a json file that is going to be used by the backend of the searching UI. The final index, that is saved in local memory until the blocks are processed, is then saved too in json file with the ids of the blocks they are in.

## TFIDF Scoring
The tfIDF  of word per doc is calculated by block and when is saved to secondary memory, this way when we do the search we first locate the block where the word is in, then the word and we get the id of the doc who has the highest score. As the output files of the indexing are type JSON our backend and frontend get the word in O(1) as it is a dictionary.

## UI
We implemented the frontend in Vue and the backend in Node.js. As the main implementation is done in C++ we first process the indexing and save in secondary memory in the program and the we have another C++ read program that just has the indexing file (word and block ids where it appears) to facilitate the search. In the Node.js backend everytime it receives a search from the front it executes a child process who runs the a.out of the read program, that return the blocks whe the words at. The backend just recovers the JSON files of the blocks in the list and returns the names of the files where they are in order of score.
