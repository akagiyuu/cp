use std::io;

macro_rules! readline {
    ($lines:ident) => {{
        let line = $lines.next().unwrap().unwrap();
        line
    }};
}

fn solve(a: Vec<i64>, b: Vec<i64>) -> i64 {
    let mut diff: Vec<_> = a.iter().zip(b.iter()).map(|(a_i, b_i)| a_i - b_i).collect();

    diff.sort_by(|a_i, b_i| b_i.cmp(a_i));

    diff.iter()
        .enumerate()
        .map(|(i, &diff_i)| i as i64 * diff_i)
        .sum::<i64>()
        + (a.len() as i64 - 1) * b.iter().sum::<i64>()
}

fn main() {
    let mut lines = io::stdin().lines();
    let entry_count: usize = readline!(lines).parse().unwrap();
    let (a, b): (Vec<_>, Vec<_>) = (0..entry_count)
        .map(|_| {
            let line = readline!(lines);
            let (a_i, b_i) = line.split_once(' ').unwrap();
            let a_i: i64 = a_i.parse().unwrap();
            let b_i: i64 = b_i.parse().unwrap();
            (a_i, b_i)
        })
        .unzip();

    println!("{}", solve(a, b));
}
