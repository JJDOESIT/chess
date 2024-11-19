# Mailbox Chess Engine
<b>Requirements:</b> Windows or Linux Environment
<br>
<br>
<b>Quick Install:</b>
<br>
1. Download the latest <b><a href="https://github.com/JJDOESIT/chess/releases/tag/v1.0.0">chess.zip</a></b> release for Windows or Linux
3. Extract the files
4. Run chess.exe
    * If permissions denied, run ```chmod 700 <path to chess.exe>``` and try running again




<b>Build Yourself:</b>
<br>
1. Clone the repo or download the source code in a Linux environment
2.  Install the requirements: ```sudo apt-get install libsfml-dev``` and ```sudo apt-get install build-essential```
3. Run the makefile in command shell or IDE terminal
    - Note: Neccesary changes to install location of SFML might be required in the makefile

# Features
- AI opponent
  - Different opening playbooks
  - Built on minimax algorithm, optimized with alpha-beta pruning
- Display legal moves\
  <img src="https://github.com/JJDOESIT/chess/assets/138625553/ddde85a0-a2b6-4342-b23a-4f2d49677ab3" width="250"></img>
- Alert when king is in check\
  <img src="https://github.com/JJDOESIT/chess/assets/138625553/e0e2e7b9-3590-4d76-97b5-88793f197d92" width="250"></img> 
  

# Special Moves

- <b>Castling</b>
  - Moving the king two squares toward a rook and then moving the rook to the square that the king passed over
  - Cannot castle into or through check or checkmate
  - Before and after example:\
    <img src="https://github.com/JJDOESIT/chess/assets/138625553/42cf9b40-1aae-4f63-8a6a-6140bbe6ba8b)" width="250"><img>
    <img src="https://github.com/JJDOESIT/chess/assets/138625553/5349d0ca-f9f3-4c09-93ac-4e9f976a97c5" width="250"><img>

- <b>En Passant</b>
  - The capture by a pawn of an enemy pawn on the same row and adjacent column that has just made a two-square advance
  - Before and after example:\
<img src="https://github.com/JJDOESIT/chess/assets/138625553/6baf0e37-73ae-464d-a40a-57b597d1f41c" width="250"></img>
<img src="https://github.com/JJDOESIT/chess/assets/138625553/a69e2549-9f44-42f6-a073-db9de7727e67" width="250"></img>

- <b>Pawn Promotion</b>
  - The replacement of a pawn with a new piece when the pawn is moved to its farthest possible square
  - Before and after example:\
<img src="https://github.com/JJDOESIT/chess/assets/138625553/04d9c1ab-b27e-44f2-9039-4b07d5ef0462" width="250"></img>
<img src="https://github.com/JJDOESIT/chess/assets/138625553/6f19861e-54ea-4a9b-95e2-acfb0b99646f" width="250"></img>

# <a href="https://www.youtube.com/watch?v=TpB3E4_cgZ0">Video</a>
<a href="https://www.youtube.com/watch?v=TpB3E4_cgZ0"><img src="https://img.youtube.com/vi/TpB3E4_cgZ0/maxresdefault.jpg" alt="Chess" width="600" ></a>
