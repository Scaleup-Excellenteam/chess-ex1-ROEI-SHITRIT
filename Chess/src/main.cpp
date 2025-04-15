// Chess 
#include "Chess.h"
#include "ChessBoard.h"

int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	//string _board = "##########K###############################Q#############r#r###k#";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
    ChessBoard gameBoard(board);
	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not Piece at the source
		12 - the Piece in the source is Piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that Piece
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		{ // put your code here instead that code
            try {
                codeResponse = gameBoard.runProgram(res);
            }
            catch (std::invalid_argument&) {
                cout << "Invalid input !!" << endl;
                res = a.getInput();
                continue;
            }
//			cout << "code response >> ";
//			cin >> codeResponse;
		}
		/**/

		a.setCodeResponse(codeResponse);
		res = a.getInput();
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}