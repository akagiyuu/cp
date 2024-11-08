use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

const MOD: u64 = 1_000_000_007;

fn solve(max_n: usize, max_k: usize) -> u64 {
    let mut f = vec![vec![1; max_n + 1]; max_k + 1];

    for k in 2..=max_k {
        let mut partial_sum = f[k - 1][max_n - 1];
        for n in 1..=max_n {
            f[k][n] = (1 + partial_sum) % MOD;
            if n < max_n {
                partial_sum += f[k - 1][max_n - 1 - n];
                partial_sum %= MOD;
            }
        }
    }

    f[max_k][max_n]
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count: usize = readline!(lines).parse().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (n, k) = line.split_once(' ').unwrap();
        let n: usize = n.parse().unwrap();
        let k: usize = k.parse().unwrap();
        println!("{}", solve(n, k));
    }
}
