use std::{collections::{BinaryHeap, VecDeque}, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

// #[derive(Ord, Eq)]
struct State {
    i: usize,
    j: usize,
    // rhombus_size: u32,
}
//
// impl PartialEq for State {
//     fn eq(&self, other: &Self) -> bool {
//         self.rhombus_size == other.rhombus_size
//     }
// }
//
// impl PartialOrd for State {
//     fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
//         self.rhombus_size.partial_cmp(&other.rhombus_size)
//     }
// }

fn solve(grid: Vec<Vec<char>>) -> u32 {
    let n = grid.len();
    let m = grid[0].len();
    let mut max_rhombuses = vec![vec![0; m]; n];

    let mut fixed_count = 0;
    let mut is_fixed = vec![vec![false; m]; n];
    for i in 0..n {
        for j in 0..m {
            if i == 0 || j == 0 || i == n - 1 || j == m - 1 {
                is_fixed[i][j] = true;
                fixed_count += 1;
                continue;
            }
            for (next_i, next_j) in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)] {
                if grid[i][j] != grid[next_i][next_j] {
                    is_fixed[i][j] = true;
                    fixed_count += 1;
                    break;
                }
            }
        }
    }

    let mut queue = VecDeque::new();
    for i in 0..n {
        for j in 0..m {
            if is_fixed[i][j] {
                continue;
            }
            queue.push_back(State {
                i,
                j,
                // rhombus_size: 0,
            });
        }
    }
    while let Some(State { i, j }) = queue.pop_front() {
        if is_fixed[i][j] {
            continue;
        }
        if fixed_count == n * m {
            break;
        }
        let mut min_size = u32::MAX;
        let mut is_all_fixed = true;
        for (next_i, next_j) in [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)] {
            is_all_fixed &= is_fixed[next_i][next_j];
            min_size = min_size.min(max_rhombuses[next_i][next_j]);
        }
        if min_size + 1 > max_rhombuses[i][j] {
            max_rhombuses[i][j] = min_size + 1;
            if !is_fixed[i - 1][j] {
                queue.push_back(State {
                    i: i - 1,
                    j,
                    // rhombus_size: min_size + 1,
                });
            }
            if !is_fixed[i + 1][j] {
                queue.push_back(State {
                    i: i + 1,
                    j,
                    // rhombus_size: min_size + 1,
                });
            }
            if !is_fixed[i][j - 1] {
                queue.push_back(State {
                    i,
                    j: j - 1,
                    // rhombus_size: min_size + 1,
                });
            }
            if !is_fixed[i][j + 1] {
                queue.push_back(State {
                    i,
                    j: j + 1,
                    // rhombus_size: min_size + 1,
                });
            }
        }
        if is_all_fixed {
            is_fixed[i][j] = true;
            fixed_count += 1;
            continue;
        }
    }
    max_rhombuses.iter().flatten().sum::<u32>() + (n * m) as u32
}

fn main() {
    let mut lines = io::stdin().lines();
    let line = readline!(lines);
    let (n, _) = line.split_once(' ').unwrap();
    let n: usize = n.parse().unwrap();
    let grid = (0..n).map(|_| readline!(lines).chars().collect()).collect();
    println!("{}", solve(grid));
}
