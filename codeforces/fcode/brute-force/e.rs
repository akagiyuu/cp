use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn print_grid(grid: Vec<Vec<char>>) {
    for row in grid {
        println!("{}", row.iter().collect::<String>());
    }
    println!()
}

fn solve(grid: Vec<Vec<char>>) -> Vec<Vec<char>> {
    let mut grid = grid;
    let n = grid.len();
    let m = grid[0].len();

    loop {
        let mut has_fall = false;
        for i in (0..n - 1).rev() {
            for j in 0..m {
                if grid[i][j] != '*' {
                    continue;
                }
                while grid[i + 1][j] == '.' {
                    has_fall = true;
                    grid[i][j] = '.';
                    grid[i + 1][j] = '*';
                }
            }
        }
        if !has_fall {
            break;
        }
    }

    grid
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<u32>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (n, _) = line.split_once(' ').unwrap();
        let n: usize = n.parse().unwrap();
        let grid = (0..n).map(|_| readline!(lines).chars().collect()).collect();
        let grid = solve(grid);
        print_grid(grid);
    }
}
