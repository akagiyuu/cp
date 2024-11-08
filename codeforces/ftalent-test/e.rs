use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

const MOD: u64 = 1_000_000_007;

fn solve(a: Vec<u64>) -> u64 {
    let mut sum_odd = 0;
    let mut count_odd = 0;
    let mut sum_even = 0;
    let n = a.len() as u64;
    for x in a {
        if x % 2 == 1 {
            sum_odd += x;
            sum_odd %= MOD;
            count_odd += 1;
        } else {
            sum_even += x;
            sum_even %= MOD;
        }
    }

    ((sum_even * count_odd) % MOD + (sum_odd * (n - count_odd)) % MOD) % MOD
}

fn main() {
    let mut lines = io::stdin().lines();
    lines.next();
    let a = readline!(lines)
        .split_ascii_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
    println!("{}", solve(a));
}
