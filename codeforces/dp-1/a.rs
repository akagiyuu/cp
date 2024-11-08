use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(board: [Vec<char>; 2]) -> u64 {
    let n = board[0].len();
    let mut result = 0;
    let mut pre = match (board[0][0], board[1][0]) {
        ('0', '0') => 2,
        ('0', 'X') => 1,
        ('X', '0') => 1,
        ('X', 'X') => 0,
        _ => unreachable!(),
    };
    for i in 1..n {
        let cur = match (board[0][i], board[1][i]) {
            ('0', '0') => 2,
            ('0', 'X') => 1,
            ('X', '0') => 1,
            ('X', 'X') => 0,
            _ => unreachable!(),
        };

        match (pre, cur) {
            (2, 2) => {
                pre = 1;
                result += 1;
            }
            (2, 1) | (1, 2) => {
                pre = 0;
                result += 1;
            }
            (1, 1) | (_, 0) | (0, _) => {
                pre = cur;
            }
            _ => unreachable!(),
        }
    }

    result
}

fn main() {
    let mut lines = io::stdin().lines();
    let board = [
        readline!(lines).chars().collect(),
        readline!(lines).chars().collect(),
    ];

    println!("{}", solve(board));
}
