# Mailbox Chess Engine

<b>Requirements:</b> SFML and Build Essential
<br>
<br>
<b>Quick install:</b>
<br>
- ```sudo apt-get install libsfml-dev```
- ```sudo apt-get install build-essential```

# Features

- Functional chess engine adhering to the standard rules of chess
- Display legal moves\
  
- AI opponent
  - Minimax algorithm with alpha-beta pruning
- Alert when king is in check\
  

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
