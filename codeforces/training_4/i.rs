use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<(usize, u64)>) -> usize {
    let max_element = a.iter().max_by(|a, b| a.1.cmp(&b.1)).unwrap();
    let remaining = a
        .iter()
        .filter(|&&(i, _)| i != max_element.0)
        .collect::<Vec<_>>();
    let sum = remaining.iter().map(|&(_, x)| x).sum::<u64>();

    todo!()
}

fn main() {
    let mut lines = io::stdin().lines();
    lines.next();
    let a = readline!(lines)
        .split_ascii_whitespace()
        .enumerate()
        .map(|(i, x)| (i, x.parse::<u64>().unwrap()))
        .collect();
    println!("{}", solve(a));
}
