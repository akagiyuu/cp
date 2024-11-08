use std::fmt::Write;
use std::{io, u32};

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn cal_distance(a: &str, b: &str) -> u32 {
    a.bytes()
        .zip(b.bytes())
        .map(|(c, d)| {
            let min = c.min(d);
            let max = c.max(d);
            (max - min) as u32
        })
        .sum()
}

fn solve(words: Vec<String>) -> u32 {
    let mut min_distance = u32::MAX;
    for i in 0..words.len() {
        for j in i + 1..words.len() {
            let distance = cal_distance(&words[i], &words[j]);
            min_distance = min_distance.min(distance);
        }
    }

    min_distance
}

fn main() {
    let mut lines = io::stdin().lines();
    let test_case_count = readline!(lines).parse::<u32>().unwrap();
    for _ in 0..test_case_count {
        let line = readline!(lines);
        let (n, _) = line.split_once(' ').unwrap();
        let n: usize = n.parse().unwrap();
        let words = (0..n).map(|_| readline!(lines)).collect();
        println!("{}", solve(words));
    }
}
