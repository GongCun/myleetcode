class Solution {

  private:
    vector<vector<bool>> unfill;
    
    bool inArea(vector<vector<char>>& board, int x, int y) {
        return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
    }

    void findUnfill(vector<vector<char>>& board, int x, int y) {
        if (!inArea(board, x, y) || board[x][y] == 'X') return;
        if (unfill[x][y]) return;
        unfill[x][y] = true;
        findUnfill(board, x, y + 1);
        findUnfill(board, x, y - 1);
        findUnfill(board, x - 1, y);
        findUnfill(board, x + 1, y);
    }

  public:
    void solve(vector<vector<char>>& board) {
        for (auto i = 0; i < board.size(); ++i)
            unfill.push_back(vector<bool>(board[0].size(), false));
        
        cout << "1" << endl;
        for (auto i = 0; i < board.size(); ++i) {
            if (board[i][0] == 'O' && unfill[i][0] == false)
                findUnfill(board, i, 0);
        }
        cout << "2" << endl;
        for (auto i = 0; i < board[0].size(); ++i) {
            if (board[0][i] == 'O' && unfill[0][i] == false)
                findUnfill(board, 0, i);
        }
        cout << "3" << endl;
        for (auto i = 0; i < board.size(); ++i) {
            if (board[i][board[0].size() - 1] == 'O' &&
                unfill[i][board[0].size() - 1] == false)
                findUnfill(board, i, board[0].size() - 1);
        }
        cout << "4" << endl;
        for (auto i = 0; i < board[0].size(); ++i) {
            if (board[board.size() - 1][i] == 'O' &&
                unfill[board.size() - 1][i] == false)
                findUnfill(board, board[0].size() - 1, i);
        }
        cout << "5" << endl;
        for (auto i = 0; i < board.size(); i++) {
            for (auto j = 0; j < board[0].size(); j++) {
                if (!unfill[i][j])
                    board[i][j] = 'X';
            }
        }

    }
};
