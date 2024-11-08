use std::{collections::HashMap, io};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(freqs: Vec<u64>, k: u64) -> u64 {
    let n: u64 = freqs.iter().sum();
    let m: u64 = freqs.iter().max().copied().unwrap();
    let mut desk_size = (n + k).min(m * freqs.len() as u64) / m;
    loop {
        if n % desk_size == 0 {
            break;
        }
        let need = (n / desk_size + 1) * desk_size - n;
        if need <= k {
            break;
        }
        desk_size -= 1;
    }
    desk_size
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<usize>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (_, k) = line.split_once(' ').unwrap();
        let k = k.parse().unwrap();
        let freqs = readline!(lines)
            .split_ascii_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();
        println!("{}", solve(freqs, k));
    }
}
