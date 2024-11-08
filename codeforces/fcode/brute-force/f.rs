use std::{i32, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<i32>, k: usize) -> i32 {
    if k == 1 {
        return *a.iter().min().unwrap();
    }
    if k >= 3 {
        return *a.iter().max().unwrap();
    }

    let n = a.len();
    let mut min_rights = vec![0; n];
    min_rights[n - 1] = a[n - 1];
    for i in (0..n - 1).rev() {
        min_rights[i] = min_rights[i + 1].min(a[i]);
    }

    let mut min_left = a[0];
    let mut max_value = i32::MIN;
    for pivot in 0..n {
        let value = match pivot {
            0 => min_rights[pivot],
            i => {
                let value = min_left.max(min_rights[pivot]);
                if i < n - 1 {
                    min_left = min_left.min(a[pivot]);
                }
                value
            }
        };

        max_value = max_value.max(value);
    }

    max_value
}

fn main() {
    let mut lines = io::stdin().lines();
    let line = readline!(lines);
    let (_, k) = line.split_once(' ').unwrap();
    let k: usize = k.parse().unwrap();
    let a = readline!(lines)
        .split(' ')
        .map(|x| x.parse::<i32>().unwrap())
        .collect();
    println!("{}", solve(a, k));
}
