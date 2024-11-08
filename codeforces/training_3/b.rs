use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn fill_non_overlap(n: u32, s: u32) -> Vec<u32> {
    if s == n {
        return vec![2];
    }
    if s == n - 1 {
        if n == 2 {
            return vec![1];
        }
        return vec![1, 2];
    }

    if s == 0 {
        return vec![0];
    }

    if s == 1 {
        if n == 2 {
            return vec![1];
        }
        return vec![0, 1];
    }

    vec![0, 1, 2]
}

fn solve(n: u32, u: u32, r: u32, d: u32, l: u32) -> bool {
    let u = fill_non_overlap(n, u);
    let r = fill_non_overlap(n, r);
    let d = fill_non_overlap(n, d);
    let l = fill_non_overlap(n, l);
    let required = [u, r, d, l];

    const ACCEPTED_PATTERN: [[u32; 4]; 15] = [
        [2, 2, 2, 2],
        [2, 1, 1, 2],
        [2, 2, 1, 1],
        [2, 1, 0, 1],
        [1, 1, 2, 2],
        [1, 0, 1, 2],
        [1, 1, 1, 1],
        [1, 0, 0, 1],
        [1, 2, 2, 1],
        [1, 2, 1, 0],
        [1, 1, 0, 0],
        [0, 1, 2, 1],
        [0, 0, 1, 1],
        [0, 1, 1, 0],
        [0, 0, 0, 0],
    ];
    for pattern in ACCEPTED_PATTERN {
        let mut is_match = true;
        for i in 0..4 {
            if !required[i].contains(&pattern[i]) {
                is_match = false;
            }
        }
        if is_match {
            return true;
        }
    }
    false
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse::<u32>().unwrap())
            .collect::<Vec<_>>();
        println!(
            "{}",
            if solve(line[0], line[1], line[2], line[3], line[4]) {
                "YES"
            } else {
                "NO"
            }
        )
    }
}
