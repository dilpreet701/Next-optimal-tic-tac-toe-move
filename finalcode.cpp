using namespace std;

struct Move{
    int row, col;
};

class TicTacToe{
private:
    const char maximizer = 'x', minimizer = 'o';
    vector<vector<char>> board;
public:
    TicTacToe(vector<vector<char>> &b){
        board.assign(b.begin(), b.end());
    }

    int EvaluateScore(){
        // for every row
        for(int row = 0;row < 3;row++){
            if(board[row][0] == board[row][1] && board[row][1] == board[row][2]){
                if(board[row][0] == maximizer)
                    return 10;
                else if(board[row][0] == minimizer)
                    return -10;
            }
        }
        // for every column
        for(int col = 0;col < 3;col++){
            if(board[0][col] == board[1][col] && board[1][col] == board[2][col]){
                if(board[0][col] == maximizer)
                    return 10;
                else if(board[0][col] == minimizer)
                    return -10;
            }
        }
        // each diagonal
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2]){
            if(board[0][0] == maximizer)
                return 10;
            else if(board[0][0] == minimizer)
                return -10;
        }
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0]){
            if(board[0][2] == maximizer)
                return 10;
            else if(board[0][2] == minimizer)
                return -10;
        }

        return 0;
    }

    bool TerminalStateReached(){
        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(board[i][j] == '_')
                    return false;
            }
        }
        return true;
    }

    int Minimax(bool isMaximizer, int depth){
        int score = EvaluateScore();

        if(score == 10 || score == -10){
            if(isMaximizer)
                return score - depth;
            else
                return score + depth;
        }

        if(TerminalStateReached()){
            return score;
        }

        if(isMaximizer){
            int bestscore = INT32_MIN;

            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    if(board[i][j] == '_'){
                        // make the move
                        board[i][j] = maximizer;

                        bestscore = max(bestscore, Minimax(false, depth + 1));
                        // remove the move
                        board[i][j] = '_';
                    }
                }
            }

            return bestscore;
        }else{
            int bestscore = INT32_MAX;

            for(int i = 0;i < 3;i++){
                for(int j = 0;j < 3;j++){
                    if(board[i][j] == '_'){
                        // make the move
                        board[i][j] = minimizer;

                        bestscore = min(bestscore, Minimax(true, depth + 1));
                        // remove the move
                        board[i][j] = '_';
                    }
                }
            }

            return bestscore;
        }
    }

    Move FindOptimalMove(){
        Move optimal;
        int bestscore = INT32_MIN;

        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                if(board[i][j] == '_'){
                    board[i][j] = maximizer;

                    int score = Minimax(false, 0);

                    if(score > bestscore){
                        bestscore = score;
                        optimal.row = i, optimal.col = j;
                    }

                    board[i][j] = '_';
                }
            }
        }

        return optimal;
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        vector<vector<char>> board(3, vector<char>(3));

        for(int i = 0;i < 3;i++){
            for(int j = 0;j < 3;j++){
                cin >> board[i][j];
            }
        }

        TicTacToe tictactoe(board);
        Move optimal = tictactoe.FindOptimalMove();

        cout << optimal.row << " " << optimal.col << endl;
    }

    return 0;
}
